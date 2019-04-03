# update per change V0006

# project name
BIN_NAME = template_microcontroller
PLATFORM ?= PC

# project settings
C_SOURCES += src/tests1.c
CXX_SOURCES +=
S_SOURCES +=
INCLUDES += -Iinc -I../inc
DEFINES +=
ALIBS +=
RLIBS +=
DLIBS +=
ALIBDIR +=
RLIBDIR +=
DLIBDIR +=
COMPILE_C_FLAGS = -std=gnu11 -Wall -Wextra -Wno-main -fno-common -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections
COMPILE_CXX_FLAGS = -std=c++17 -Wall -Wextra -Wno-main -fno-common -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-rtti -fno-exceptions
COMPILE_ASM_FLAGS = -c -x assembler-with-cpp
LINK_FLAGS +=

#custom build rules
pre-clean:

pre-release:

pre-debug:

#project hardware specific commands

.PHONY: pre-clean pre-release pre-debug
