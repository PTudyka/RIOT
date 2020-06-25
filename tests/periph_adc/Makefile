# BOARD ?= pba-d-01-kw2x
BOARD ?= stm32f4discovery
include ../Makefile.tests_common

USEMODULE += stdio_cdc_acm
FEATURES_REQUIRED = periph_adc
USEMODULE += xtimer

include $(RIOTBASE)/Makefile.include
