# this is only used to generate the linkerscript.
# based on https://github.com/libopencm3/libopencm3-template/blob/522115dcc239bc3fa754f1c396a9632bcfa0f901/my-project/Makefile

DEVICE=${ENV_DEVICE}

PREFIX  ?= arm-none-eabi-
CC      = $(PREFIX)gcc
CXX     = $(PREFIX)g++
LD      = $(PREFIX)gcc
OBJCOPY = $(PREFIX)objcopy
OBJDUMP = $(PREFIX)objdump

INCLUDES += $(patsubst %,-I%, . $(SHARED_DIR))
OPENCM3_DIR=.

include $(OPENCM3_DIR)/mk/genlink-config.mk
include $(OPENCM3_DIR)/mk/genlink-rules.mk
