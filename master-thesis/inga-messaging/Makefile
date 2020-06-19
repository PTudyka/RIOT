# name of the application
APPLICATION = inga-messaging

# If no BOARD is found in the environment, use this default:
BOARD ?= stm32f4discovery
# BOARD ?= nucleo-l073rz

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# required features
# FEATURES_REQUIRED += periph_spi

USEMODULE += stdio_cdc_acm
# USEMODULE += usbus_cdc_acm

GNRC_NETIF_NUMOF := 2

USEMODULE += at86rf215
# USEMODULE += gnrc
USEMODULE += gnrc_netdev_default
USEMODULE += gnrc_pktdump
USEMODULE += gnrc_txtsnd
USEMODULE += auto_init_gnrc_netif
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands

# allow to use a smaller packet buffer in low-PDU drivers
# ifdef GNRC_PKTBUF_SIZE
#   CFLAGS += -DGNRC_PKTBUF_SIZE=$(GNRC_PKTBUF_SIZE)
# endif

# CFLAGS += -DDEBUG_ASSERT_VERBOSE

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
