# output name
OUTPUT = main

# linker script
LD_SCRIPT = stm32l152.ld

# sources
SRC += main.c startup.c

# sys sources
SRC += ./sys/src/time.c

# util soutrces
SRC += ./util/src/stdio.c ./util/src/string.c
SRC += ./util/src/circbuf.c

# lib sources
SRC += ./stm32l/src/rcc.c ./stm32l/src/gpio.c
SRC += ./stm32l/src/usart.c ./stm32l/src/nvic.c
SRC += ./stm32l/src/systick.c ./stm32l/src/stm32l.c
SRC += ./stm32l/src/dma.c ./stm32l/src/flash.c
SRC += ./stm32l/src/timer.c ./stm32l/src/wwdg.c
SRC += ./stm32l/src/adc.c ./stm32l/src/i2c.c
SRC += ./stm32l/src/pwr.c ./stm32l/src/ri.c
SRC += ./stm32l/src/iwdg.c ./stm32l/src/rtc.c
SRC += ./stm32l/src/exti.c ./stm32l/src/syscfg.c
SRC += ./stm32l/src/uid.c ./stm32l/src/scb.c
SRC += ./stm32l/src/lcd.c ./stm32l/src/dac.c
SRC += ./stm32l/src/spi.c ./stm32l/src/usb.c
SRC += ./stm32l/src/comp.c

# dev sources
SRC += ./dev/src/systime.c ./dev/src/m2m.c
SRC += ./dev/src/usart1.c ./dev/src/debug.c
SRC += ./dev/src/stepup.c ./dev/src/ob.c
SRC += ./dev/src/display.c ./dev/src/dots.c
SRC += ./dev/src/hsi.c ./dev/src/power.c
SRC += ./dev/src/lse.c ./dev/src/realtime.c
SRC += ./dev/src/buttons.c ./dev/src/extimux.c
SRC += ./dev/src/failsafe.c ./dev/src/dev.c
SRC += ./dev/src/watchdog.c

# life cycle
SRC += ./lifecycle/src/lc.c

# nixie clock
SRC += ./nixie/src/nixie.c ./nixie/src/shutdown.c

# test routines
SRC += ./test/src/test.c

# flags
CC_FLAGS  = -mcpu=cortex-m3 -mthumb -Wall -g -Os -I. -fdata-sections 
CC_FLAGS += -Wsign-compare -ffunction-sections -Wl,--gc-sections
LD_FLAGS  = -T$(LD_SCRIPT)
LD_FLAGS += -nostartfiles -Wl,-Map=$(OUTPUT).map,--cref
LD_FLAGS += -lm
OBC_FLAGS = -O binary

# tools
CC = arm-none-eabi-gcc
AS = arm-none-eabi-gcc
LD = arm-none-eabi-ld
OBC = arm-none-eabi-objcopy
OBD = arm-none-eabi-objdump
NM = arm-none-eabi-nm
RM = cs-rm
SIZE = arm-none-eabi-size
ECHO = echo
# sources converted to objs

OBJ = $(SRC:%.c=%.o)

# generate elf and bin
all: $(OUTPUT).elf $(OUTPUT).bin $(OUTPUT).lst map size

# generate elf file from objs
$(OUTPUT).elf: $(OBJ)
	@ $(ECHO) ---------------------    Linking   ---------------------
	$(CC) $(CC_FLAGS) $(OBJ) --output $@ $(LD_FLAGS) 

# generate bin file
$(OUTPUT).bin: $(OUTPUT).elf
	@ $(ECHO) ---------------------    Copying   ---------------------
	$(OBC) $(OBC_FLAGS) $< $@

# geneate listing
$(OUTPUT).lst: $(OUTPUT).elf
	@ $(ECHO) ---------------------    Listing   ---------------------
	$(OBD) -S $< > $@

# compile all sources
%.o : %.c
	@ $(ECHO) --------------------- Compiling $< ---------------------
	$(CC) -c $(CC_FLAGS) $< -o $@

# show size information
size: $(OUTPUT).elf
	@ $(ECHO) --------------------- Section size ---------------------
	$(SIZE) $(OUTPUT).elf

# generate symbol map
map: $(OUTPUT).elf
	@ $(ECHO) --------------------- Symbol map ---------------------
	$(NM) -n -o $(OUTPUT).elf > $(OUTPUT).map

# cleanser xD
clean:
	$(RM) -f $(OBJ) $(OUTPUT).lst $(OUTPUT).bin $(OUTPUT).elf $(OUTPUT).map
