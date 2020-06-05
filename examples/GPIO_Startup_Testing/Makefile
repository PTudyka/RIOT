# name of the application
APPLICATION = GPIO_Startup_Testing

# If no BOARD is found in the environment, use this default:
BOARD ?= nucleo-l073rz

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../..

# required modules
USEMODULE += shell
USEMODULE += shell_commands
USEMODULE += ps
USEMODULE += saul_default

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
DEVELHELP ?= 1

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

FEATURES_OPTIONAL += periph_rtc

ifneq (,$(filter msba2,$(BOARD)))
  USEMODULE += mci
  USEMODULE += random
endif

include $(RIOTBASE)/Makefile.include
