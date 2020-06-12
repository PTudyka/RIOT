# name of the application
APPLICATION = AT86RF215_example

# If no BOARD is found in the environment, use this default:
BOARD ?= stm32f4discovery

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

FEATURES_REQUIRED = periph_spi

# Required for using uart over usb 
USEMODULE += stdio_cdc_acm

# USB device vendor and product ID
# DEFAULT_VID = 1209
# DEFAULT_PID = 7D00
# USB_VID ?= $(DEFAULT_VID)
# USB_PID ?= $(DEFAULT_PID)

# required modules
USEMODULE += at86rf215
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands

GNRC_NETIF_NUMOF := 2

USEMODULE += gnrc_netdev_default
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc_netif_dedup

# USEMODULE += gnrc_ipv6_default
# USEMODULE += gnrc_ipv6

# allow to use a smaller packet buffer in low-PDU drivers
ifdef GNRC_PKTBUF_SIZE
  CFLAGS += -DGNRC_PKTBUF_SIZE=$(GNRC_PKTBUF_SIZE)
endif

# gnrc is a meta module including all required, basic gnrc networking modules
# USEMODULE += gnrc

# # automatically initialize the network interface
# # USEMODULE += auto_init_gnrc_netif

# # shell command to send L2 packets with a simple string
# USEMODULE += gnrc_txtsnd

# # the application dumps received packets to stdout
# USEMODULE += gnrc_pktdump

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# CFLAGS += -DDEBUG_ASSERT_VERBOSE

include $(RIOTBASE)/Makefile.include

# Set a custom channel if needed
include $(RIOTMAKE)/default-radio-settings.inc.mk