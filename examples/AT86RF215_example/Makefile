# name of the application
APPLICATION = AT86RF215_example

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

FEATURES_REQUIRED = periph_spi

# required modules
USEMODULE += at86rf215
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands

# allow to use a smaller packet buffer in low-PDU drivers
ifdef GNRC_PKTBUF_SIZE
  CFLAGS += -DGNRC_PKTBUF_SIZE=$(GNRC_PKTBUF_SIZE)
endif

# gnrc is a meta module including all required, basic gnrc networking modules
USEMODULE += gnrc

# automatically initialize the network interface
USEMODULE += auto_init_gnrc_netif

# shell command to send L2 packets with a simple string
USEMODULE += gnrc_txtsnd

# the application dumps received packets to stdout
USEMODULE += gnrc_pktdump

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk