/*
 * usb.c
 *
 *  Created on: 31-03-2013
 *      Author: Tomek
 */

#include <stm32l/usb.h>
#include <util/minmax.h>

/* btable offset */
void USB_SetBtableOffset(uint16_t offset)
{
	/* set btable offset */
	USB->_BTABLE = offset;
}

/* set device address */
void USB_SetDeviceAddress(uint8_t address)
{
	/* set address and set enable flag */
	USB->_DADDR = USB_DADDR_EF | address;
}

/* set endpoint status (used for marking buffer as ready-to-receive) */
void USB_SetEndpointRxStatus(uint8_t ep_num, uint16_t status)
{
	/* get current stat rx state */
	uint32_t epr = USB->_EPR[ep_num] & (USB_EPR_EA | USB_EPR_EP_KIND |
			USB_EPR_EP_TYPE | USB_EPR_STAT_RX);

	/* toggle */
	USB->_EPR[ep_num] = USB_EPR_MASK | (epr ^ status);
}

/* set endpoint status (used for marking buffer as ready-to-send) */
void USB_SetEndpointTxStatus(uint8_t ep_num, uint16_t status)
{
	/* get current stat tx state */
	uint32_t epr = USB->_EPR[ep_num] & (USB_EPR_EA | USB_EPR_EP_KIND |
			USB_EPR_EP_TYPE | USB_EPR_STAT_TX);

	/* toggle */
	USB->_EPR[ep_num] = USB_EPR_MASK | (epr ^ status);
}

/* set endpoint address and type */
void USB_SetEndpointTypeAddress(uint8_t ep_num, uint16_t type,
		uint16_t address)
{
	/* kind field will not be changed */
	uint32_t epr = USB->_EPR[ep_num] & USB_EPR_EP_KIND;

	/* set type and address, but do not touch any other stuff */
	USB->_EPR[ep_num] = USB_EPR_MASK | type | address | epr;
}

/* clear endpoint ctr flag for reception */
void USB_ClearEnpointCTRRx(uint8_t ep_num)
{
	/* kind field will not be changed */
	uint32_t epr = USB->_EPR[ep_num] & (USB_EPR_EA | USB_EPR_EP_KIND |
			USB_EPR_EP_TYPE);

	/* keep tx flag as it is */
	USB->_EPR[ep_num] = epr | USB_EPR_CTR_TX;
}

/* clear endpoint ctr flag for transmission */
void USB_ClearEnpointCTRTx(uint8_t ep_num)
{
	/* kind field will not be changed */
	uint32_t epr = USB->_EPR[ep_num] & (USB_EPR_EA | USB_EPR_EP_KIND |
			USB_EPR_EP_TYPE);

	/* keep tx flag as it is */
	USB->_EPR[ep_num] = epr | USB_EPR_CTR_RX;
}

/* set endpoint receive address */
void USB_SetEndpointRxBuffer(uint8_t ep_num, uint16_t addr, uint16_t size)
{
	/* get btable entry */
	usb_btable_t *b = USB_BTABLE(ep_num);

	/* set rx buffer */
	b->ADDR_RX = addr;

	/* if size is greater than 32 bytes then it needs to be encoded */
	if (size >= 32) {
		/* size is expressed in 32 byte blocks */
		size = (size >> 5) - 1;
		/* set block size flag */
		b->COUNT_RX = USB_COUNT_RX_BLSIZE | size << 10;
	/* normally size is expressed in two byte blocks */
	} else {
		/* size is expressed in 2 byte blocks */
		size = size >> 1;
		/* do not set block size flag */
		b->COUNT_RX = size << 10;
	}
}

/* set endpoint transmit address */
void USB_SetEndpointTxBuffer(uint8_t ep_num, uint16_t addr, uint16_t size)
{
	/* get btable entry */
	usb_btable_t *b = USB_BTABLE(ep_num);

	/* set tx buffer */
	b->ADDR_TX = addr;
	/* there is some magic in size encoding */
	b->COUNT_TX = size;
}

/* set endpoint receive double buffering addresses */
void USB_SetEnpointRxDoubleBuffer(uint8_t ep_num, uint16_t addr_0,
		uint16_t size_0, uint16_t addr_1, uint16_t size_1)
{
	/* get btable entry */
	usb_btable_t *b = USB_BTABLE(ep_num);

	/* set rx buffer addresses */
	b->ADDR_TX = addr_0;
	b->ADDR_RX = addr_1;

	/* if size is greater than 32 bytes then it needs to be encoded */
	if (size_0 >= 32) {
		/* size is expressed in 32 byte blocks */
		size_0 = (size_0 >> 5) - 1;
		/* set block size flag */
		b->COUNT_TX = USB_COUNT_RX_BLSIZE | size_0 << 10;
	/* normally size is expressed in two byte blocks */
	} else {
		/* size is expressed in 2 byte blocks */
		size_0 = size_0 >> 1;
		/* do not set block size flag */
		b->COUNT_TX = size_0 << 10;
	}

	/* if size is greater than 32 bytes then it needs to be encoded */
	if (size_1 >= 32) {
		/* size is expressed in 32 byte blocks */
		size_1 = (size_1 >> 5) - 1;
		/* set block size flag */
		b->COUNT_RX = USB_COUNT_RX_BLSIZE | size_1 << 10;
	/* normally size is expressed in two byte blocks */
	} else {
		/* size is expressed in 2 byte blocks */
		size_1 = size_1 >> 1;
		/* do not set block size flag */
		b->COUNT_RX = size_1 << 10;
	}
}

/* set endpoint transmit double buffering addresses */
void USB_SetEnpointTxDoubleBuffer(uint8_t ep_num, uint16_t addr_0,
		uint16_t size_0, uint16_t addr_1, uint16_t size_1)
{
	/* get btable entry */
	usb_btable_t *b = USB_BTABLE(ep_num);

	/* set tx buffer addresses */
	b->ADDR_TX = addr_0;
	b->ADDR_RX = addr_1;

	/* set tx buffer data count */
	b->COUNT_TX = size_0;
	b->COUNT_RX = size_1;
}

/* read from endpoint rx buffer, ptr must be uint16_t aligned, max size must be
 * even */
int USB_ReadEndpointBuffer(uint8_t ep_num, void *ptr, uint16_t max_size)
{
	/* set source (pma) address, math is crazy here, I now that,
	 * don't blame me, blame ST. */
	uint16_t *dst = ptr;
	uint32_t *src = (uint32_t *)(USB_PMA_ADDR +
			USB_BTABLE(ep_num)->ADDR_RX * 2);

	/* limit data size */
	uint16_t size = min(USB_BTABLE(ep_num)->COUNT_RX & USB_COUNT_RX_COUNT_RX,
			max_size);
	/* number of transfers */
	uint32_t cnt = (size + 1) / 2;

	/* copy byte after byte */
	while (cnt--) {
		/* copy */
		*(dst) = *(src);
		/* increment */
		dst++; src++;
	}

	/* report size */
	return size;
}

/* read from endpoint rx buffer in double buffered mode, ptr must be
 * uint16_t aligned, max size must be even */
int USB_ReadEndpointDoubleBuffer(uint8_t ep_num, uint8_t buf, void *ptr,
		uint16_t max_size)
{
	/* btable entry */
	usb_btable_t *b = USB_BTABLE(ep_num);

	/* address register */
	uint16_t addr_rx = buf == 0 ? b->ADDR_TX : b->ADDR_RX;
	/* count register */
	uint16_t count_rx = buf == 0 ? b->COUNT_TX : b->COUNT_RX;


	/* set source (pma) address, math is crazy here, I now that,
	 * don't blame me, blame ST. */
	uint16_t *dst = ptr;
	uint32_t *src = (uint32_t *)(USB_PMA_ADDR + addr_rx * 2);

	/* limit data size */
	uint16_t size = min(count_rx & USB_COUNT_RX_COUNT_RX, max_size);
	/* number of transfers */
	uint32_t cnt = (size + 1) / 2;

	/* copy byte after byte */
	while (cnt--) {
		/* copy */
		*(dst) = *(src);
		/* increment */
		dst++; src++;
	}

	/* report size */
	return size;
}

/* write to endpoint tx buffer */
int USB_WriteEndpointBuffer(uint8_t ep_num, void *ptr, uint16_t size)
{
	/* set source (pma) address, math is crazy here, I now that,
	 * don't blame me, blame ST. */
	uint32_t *dst = (uint32_t *)(USB_PMA_ADDR +
			USB_BTABLE(ep_num)->ADDR_TX * 2);
	uint16_t *src = ptr;

	/* number of transfers */
	uint32_t cnt = (size + 1) / 2;

	/* copy byte after byte */
	while (cnt--) {
		/* copy */
		*(dst) = *(src);
		/* increment */
		dst++; src++;
	}

	/* set counter */
	USB_BTABLE(ep_num)->COUNT_TX = size;
	/* report size */
	return size;
}

/* write to endpoint tx double buffer */
int USB_WriteEndpointDoubleBuffer(uint8_t ep_num, uint8_t buf, void *ptr,
		uint16_t size)
{
	/* btable entry */
	usb_btable_t *b = USB_BTABLE(ep_num);

	/* address register */
	uint16_t addr_tx = buf == 0 ? b->ADDR_TX : b->ADDR_RX;

	/* set source (pma) address, math is crazy here, I now that,
	 * don't blame me, blame ST. */
	uint32_t *dst = (uint32_t *)(USB_PMA_ADDR + addr_tx * 2);
	uint16_t *src = ptr;

	/* number of transfers */
	uint32_t cnt = (size + 1) / 2;

	/* copy byte after byte */
	while (cnt--) {
		/* copy */
		*(dst) = *(src);
		/* increment */
		dst++; src++;
	}

	/* set counter */
	if (buf == 0) {
		b->COUNT_TX = size;
	} else {
		b->COUNT_RX = size;
	}

	/* report size */
	return size;
}
