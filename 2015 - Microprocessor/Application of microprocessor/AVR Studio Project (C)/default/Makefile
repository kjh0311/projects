###############################################################################
# Makefile for the project Project_6_9
###############################################################################

## General Flags
PROJECT = Project_6_9
MCU = atmega128
TARGET = Project_6_9.elf
CC = avr-gcc

CPP = avr-g++

## Options common to compile, link and assembly rules
COMMON = -mmcu=$(MCU)

## Compile options common for all C compilation units.
CFLAGS = $(COMMON)
CFLAGS += -Wall -gdwarf-2 -Os -std=gnu99 -funsigned-char -funsigned-bitfields -fpack-struct -fshort-enums
CFLAGS += -MD -MP -MT $(*F).o -MF dep/$(@F).d 

## Assembly specific flags
ASMFLAGS = $(COMMON)
ASMFLAGS += $(CFLAGS)
ASMFLAGS += -x assembler-with-cpp -Wa,-gdwarf2

## Linker flags
LDFLAGS = $(COMMON)
LDFLAGS +=  -Wl,-Map=Project_6_9.map


## Intel Hex file production flags
HEX_FLASH_FLAGS = -R .eeprom -R .fuse -R .lock -R .signature

HEX_EEPROM_FLAGS = -j .eeprom
HEX_EEPROM_FLAGS += --set-section-flags=.eeprom="alloc,load"
HEX_EEPROM_FLAGS += --change-section-lma .eeprom=0 --no-change-warnings


## Objects that must be built in order to link
OBJECTS = WatchSetControl.o DoorControl.o KeyPadRead.o Main.o Moter.o F8X8A.o showtimealarmdiff.o startwatch.o updatewatch.o Watch.o EasyPK_AVR.o eaypkglcd.o graphiclcd.o shownumberandtext.o showsettingrect.o ShowTitle.o 

## Objects explicitly added by the user
LINKONLYOBJECTS = 

## Build
all: $(TARGET) Project_6_9.hex Project_6_9.eep Project_6_9.lss size

## Compile
WatchSetControl.o: ../WatchSetControl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

DoorControl.o: ../DoorControl.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

KeyPadRead.o: ../KeyPadRead.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Main.o: ../Main.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Moter.o: ../Moter.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

F8X8A.o: ../Watch/F8X8A.C
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

showtimealarmdiff.o: ../Watch/showtimealarmdiff.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

startwatch.o: ../Watch/startwatch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

updatewatch.o: ../Watch/updatewatch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

Watch.o: ../Watch/Watch.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

EasyPK_AVR.o: ../Watch/Show/EasyPK_AVR.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

eaypkglcd.o: ../Watch/Show/eaypkglcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

graphiclcd.o: ../Watch/Show/graphiclcd.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

shownumberandtext.o: ../Watch/Show/shownumberandtext.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

showsettingrect.o: ../Watch/Show/showsettingrect.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

ShowTitle.o: ../Watch/Show/ShowTitle.c
	$(CC) $(INCLUDES) $(CFLAGS) -c  $<

##Link
$(TARGET): $(OBJECTS)
	 $(CC) $(LDFLAGS) $(OBJECTS) $(LINKONLYOBJECTS) $(LIBDIRS) $(LIBS) -o $(TARGET)

%.hex: $(TARGET)
	avr-objcopy -O ihex $(HEX_FLASH_FLAGS)  $< $@

%.eep: $(TARGET)
	-avr-objcopy $(HEX_EEPROM_FLAGS) -O ihex $< $@ || exit 0

%.lss: $(TARGET)
	avr-objdump -h -S $< > $@

size: ${TARGET}
	@echo
	@avr-size -C --mcu=${MCU} ${TARGET}

## Clean target
.PHONY: clean
clean:
	-rm -rf $(OBJECTS) Project_6_9.elf dep/* Project_6_9.hex Project_6_9.eep Project_6_9.lss Project_6_9.map


## Other dependencies
-include $(shell mkdir dep 2>/dev/null) $(wildcard dep/*)

