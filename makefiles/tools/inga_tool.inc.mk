export FLASHER = $(RIOTBASE)/dist/tools/inga_tool/inga_tool
# Using the FFLAGS here to append the port for the inga_tool and avrdude
# export FFLAGS = -d $(PORT) -r && avrdude -c avr109 -p m1284p -P $(PORT) -b 230400 -u -U flash:w:$(HEXFILE) 38400
export FFLAGS = -d $(PORT) -r && avrdude -c inga -p m1284p -b 115200 -u -U flash:w:$(HEXFILE) -C +$(RIOTBASE)/avrdude_bitbang.conf && sudo rmmod ftdi_sio && sudo modprobe ftdi_sio
FLASHDEPS += $(RIOTBASE)/dist/tools/inga_tool/inga_tool
