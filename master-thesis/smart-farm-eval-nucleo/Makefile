# name of the application
APPLICATION = smart-farm-eval

# If no BOARD is found in the environment, use this default:
# BOARD ?= stm32f4discovery
BOARD ?= nucleo-l073rz

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# FEATURES_REQUIRED += periph_adc
FEATURES_REQUIRED += periph_uart

# required modules
# USEMODULE += auto_init_gnrc_netif
USEMODULE += dyn_boot
# USEMODULE += gnrc
# USEMODULE += gnrc_netdev_default
# USEMODULE += gnrc_pktdump
# USEMODULE += gnrc_txtsnd
# USEMODULE += pm
# USEMODULE += pm_layered
# USEMODULE += ps
USEMODULE += saul_default
# USEMODULE += shell
# USEMODULE += shell_commands

USEMODULE += ds18
USEMODULE += phydat

CFLAGS += -I$(CURDIR)

# USEMODULE += gpio_measurement
# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 0

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
