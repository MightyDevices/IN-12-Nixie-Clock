/* Program Entry, set to mark it as "used" and avoid gcc warnings */
ENTRY(ResetHandler)

/* Memory Spaces Definitions */
MEMORY
{
	RAM      (RWX) : ORIGIN = 0x20000000, LENGTH = 16K
	FLASH    (RX)  : ORIGIN = 0x08000000, LENGTH = 128K
	EEPROM   (RW)  : ORIGIN = 0x08080000, LENGTH = 4K
}
/* code/data sections */

SECTIONS
{
    /* code */
    .text : 
    {
        /* flash located vectors */
        .  = 0x0000;
        KEEP(*(.vectors_flash))
        
        /* internal storage start */
        .  = 0x0100;
        __is_fl_start = .;       
        . += 0x0100;
        __is_fl_end = .;
        
        /* Program code */
        *(.text)                    
        *(.text.*)                  
        *(.stub .gnu.linkonce.t.*)
        *(.rodata .rodata.*)
        
        . = ALIGN(4); 
    } > FLASH
    
    /* needed for 64 bit division */
	.ARM.exidx : 
	{
		*(.ARM.exidx*)
		
		. = ALIGN(4); 
	} > FLASH
    
    /* all initialized data will go here */ 
    __datai_start = .;
     
    .data : AT ( __datai_start )
    {
        . = ALIGN(4);
        /* ram vectors */
        __data_start = .;
        *(.vectors_ram)
        
        /* data memory */             
        *(.data)                    
        *(.data.*)
        . = ALIGN(4);
        __data_end = .; 
    } > RAM
    
    .eeprom (NOLOAD) :
    {
        /* internal storage start */
        __is_ee_start = .;
        . += 0x0200;
        __is_ee_end = .;
        
        *(.eeprom)
    } > EEPROM AT > FLASH


    .bss :
    {
        /* Zero-filled run time allocate data memory */
        . = ALIGN(4);
        __bss_start = .;
        *(.bss)       
        *(.bss.*)
        *(COMMON)
        . = ALIGN(4);
        __bss_end = .;
    } > RAM
     
    
    .heap :
    {
        __heap_start = .;
    } > RAM
    
     __heap_end = ORIGIN(RAM) + LENGTH(RAM);
     __stack = ORIGIN(RAM) + LENGTH(RAM) - 4;
} 
