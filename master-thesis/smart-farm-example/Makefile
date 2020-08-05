# name of the application
APPLICATION = smart-farm-example

# If no BOARD is found in the environment, use this default:
BOARD ?= inga_red

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# USEMODULE += stdio_cdc_acm

# required modules
# USEMODULE += at86rf215
USEMODULE += auto_init_gnrc_netif
# USEMODULE += gnrc
USEMODULE += gnrc_netdev_default
USEMODULE += gnrc_pktdump
USEMODULE += gnrc_txtsnd
USEMODULE += ps
USEMODULE += shell
USEMODULE += shell_commands
# USEMODULE += saul_default
# USEMODULE += saul_init
# USEMODULE += ADXL345 # Accelerometer
# USEMODULE += L3G4200D # Gyroscope

# USEMODULE += auto_init_saul

# required features
#FEATURES_REQUIRED += periph_spi

# CFLAGS += -DLOG_LEVEL=LOG_DEBUG

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
