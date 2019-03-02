# project settings
BIN_NAME = squantorMinUnitCexample
C_SOURCES = src/main.c
CXX_SOURCES = 
S_SOURCES =
INCLUDES = -Iinc
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra -ffreestanding
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra -ffreestanding
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp -ffreestanding
ALIBS += -lgcc
LINK_FLAGS += -flto -Xlinker --gc-sections -Xlinker -print-memory-usage -Xlinker -nodefaultlibs