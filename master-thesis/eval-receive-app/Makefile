# name of the application
APPLICATION = eval-receive-app

# If no BOARD is found in the environment, use this default:
BOARD ?= inga_red

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# required modules
USEMODULE += auto_init
USEMODULE += auto_init_gnrc_netif
USEMODULE += dyn_boot
USEMODULE += gnrc
USEMODULE += gnrc_netdev_default
USEMODULE += ps
USEMODULE += phydat
USEMODULE += shell
USEMODULE += shell_commands

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 0

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

include $(RIOTBASE)/Makefile.include
