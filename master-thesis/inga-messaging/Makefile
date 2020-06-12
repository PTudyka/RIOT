# name of the application
APPLICATION = inga-messaging

# If no BOARD is found in the environment, use this default:
BOARD ?= stm32f4discovery

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= /home/elitedose/Dokumente/Masterarbeit/Fork/RIOT

USEMODULE += stdio_cdc_acm

# required modules
USEMODULE += at86rf215
USEMODULE += auto_init_gnrc_netif
USEMODULE += gnrc
USEMODULE += gnrc_netdev_default
USEMODULE += gnrc_pktdump
USEMODULE += gnrc_txtsnd
# USEMODULE += ps
USEMODULE += shell
# USEMODULE += shell_commands

# required features
FEATURES_REQUIRED += periph_spi

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
