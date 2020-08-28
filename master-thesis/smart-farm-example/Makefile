# name of the application
APPLICATION = smart-farm-example

# If no BOARD is found in the environment, use this default:
# BOARD ?= inga_red
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# USEMODULE += stdio_cdc_acm

# required modules
# USEMODULE += at86rf215
# USEMODULE += auto_init_gnrc_netif
# # USEMODULE += gnrc
# USEMODULE += gnrc_netdev_default
# USEMODULE += gnrc_pktdump
# USEMODULE += gnrc_txtsnd
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
# USEMODULE += saul_default
# USEMODULE += saul_init
# USEMODULE += ADXL345 # Accelerometer
# USEMODULE += L3G4200D # Gyroscope

# USEMODULE += auto_init_saul

## Sensors
USEMODULE += saul_default
# USEMODULE += adxl345
# USEMODULE += l3g4200d
# USEMODULE += bmp180

# FEATURES_REQUIRED += periph_i2c

## GNRC and Radio
USEMODULE += gnrc
# use the default network interface for the board
USEMODULE += gnrc_netdev_default
# automatically initialize the network interface
USEMODULE += auto_init_gnrc_netif
# shell command to send L2 packets with a simple string
USEMODULE += gnrc_txtsnd
# the application dumps received packets to stdout
USEMODULE += gnrc_pktdump

# Dynamic boot behaviour
USEMODULE += dyn_boot
# Include application directory to use params file 
# for dyn_boot configuration
CFLAGS += -I$(CURDIR)


# USEMODULE += mci
USEMODULE += random

# CPPFLAGS += -DMODULES_LIST=\"$(shell echo '$(ED)' | tr 'a-z-' 'A-Z_')\"
# CFLAGS += -DMODULES_LIST=\"$(_ALLMODULES)\"
# CFLAGS += -DMODULES_LIST=\{\"$(_ALLMODULES)\"\}
# CFLAGS += -DMODULES_LIST=${1}

# ED = $(addprefix MODULE_,$(_ALLMODULES))
# EXTDEFINES = $(addprefix -D,$(shell echo '$(ED)' | tr 'a-z-' 'A-Z_'))
# CFLAGS += $(EXTDEFINES)


# required features
#FEATURES_REQUIRED += periph_spi

# CFLAGS += -DLOG_LEVEL=LOG_DEBUG

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 0

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# CFLAGS += -DMODULES_LIST=$(_ALLMODULES)

include $(RIOTBASE)/Makefile.include

# $(info $(M_TMP))
# CFLAGS += -DMODULES_LIST=\"$(_ALLMODULES)\"
# $(info $(_ALLMODULES))
# $(foreach v, $(.VARIABLES), $(info $(v) = $($(v))))