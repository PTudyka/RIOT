# name of your application
APPLICATION = default

# If no BOARD is found in the environment, use this default:
# BOARD ?= native
BOARD ?= inga_red
# BOARD ?= nucleo-l073rz
# BOARD ?= stm32f4discovery

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# Uncomment these lines if you want to use platform support from external
# repositories:
#RIOTCPU ?= $(CURDIR)/../../RIOT/thirdparty_cpu
#EXTERNAL_BOARD_DIRS ?= $(CURDIR)/../../RIOT/thirdparty_boards

# Uncomment this to enable scheduler statistics for ps:
#USEMODULE += schedstatistics

# If you want to use native with valgrind, you should recompile native
# with the target all-valgrind instead of all:
# make -B clean all-valgrind

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 0

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Modules to include:
USEMODULE += shell
USEMODULE += shell_commands
#USEMODULE += ps
# include and auto-initialize all available sensors
USEMODULE += saul_default

ifneq (,$(filter $(BOARD),inga_red))
 USEMODULE += adxl345
 USEMODULE += l3g4200d
 USEMODULE += bmp180
#  USEMODULE += mag3110
endif

# Dynamic boot behaviour
USEMODULE += dyn_boot
# Include application directory to use params file 
# for dyn_boot configuration
CFLAGS += -I$(CURDIR)
FEATURES_REQUIRED = periph_adc

# Additional Flags for measurement
CFLAGS += -DINTERN_TIMING_MEASUREMENT=1
CFLAGS += -DEXTERN_GPIO_MEASUREMENT=1


BOARD_PROVIDES_NETIF := acd52832 adafruit-clue airfy-beacon atmega256rfr2-xpro \
        arduino-nano-33-ble avr-rss2 b-l072z-lrwan1 cc2538dk fox \
        derfmega128 derfmega256 hamilton iotlab-m3 iotlab-a8-m3 lobaro-lorabox lsn50 mulle microbit msba2 \
        microduino-corerf native nrf51dk nrf51dongle nrf52dk nrf52840dk nrf52840-mdk nrf6310 \
        nucleo-f207zg nucleo-f767zi openmote-b openmote-cc2538 pba-d-01-kw2x remote-pa \
        remote-reva ruuvitag samr21-xpro samr30-xpro spark-core telosb thingy52 yunjia-nrf51822 z1 \
        frdm-kw41z phynode-kw41z usb-kw41z openlabs-kw41z-mini openlabs-kw41z-mini-256kib \
        stm32f4discovery inga_red

ifneq (,$(filter $(BOARD),$(BOARD_PROVIDES_NETIF)))
  # Use modules for networking
  # gnrc is a meta module including all required, basic gnrc networking modules
  USEMODULE += gnrc
  # use the default network interface for the board
  USEMODULE += gnrc_netdev_default
  # automatically initialize the network interface
  USEMODULE += auto_init_gnrc_netif
  # shell command to send L2 packets with a simple string
  USEMODULE += gnrc_txtsnd
  # the application dumps received packets to stdout
  USEMODULE += gnrc_pktdump

# ifneq (,$(filter $(BOARD),stm32f4discovery))
#   GNRC_NETIF_NUMOF := 2
#   USEMODULE += at86rf215
#   USEMODULE += stdio_cdc_acm
#   # USEMODULE += usbus_cdc_acm
# endif

#CFLAGS=-DDEBUG_ASSERT_VERBOSE

  # We use only the lower layers of the GNRC network stack, hence, we can
  # reduce the size of the packet buffer a bit
  # Set GNRC_PKTBUF_SIZE via CFLAGS if not being set via Kconfig.
ifndef CONFIG_GNRC_PKTBUF_SIZE
  CFLAGS += -DCONFIG_GNRC_PKTBUF_SIZE=512
endif
endif

FEATURES_OPTIONAL += periph_rtc

ifneq (,$(filter msba2,$(BOARD)))
  USEMODULE += mci
  USEMODULE += random
endif

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk
