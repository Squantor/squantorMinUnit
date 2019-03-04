# platform settings for PC's with GCC and libc
TOOLCHAIN_PREFIX =
C_SOURCES += src/main_PC.c
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
LINK_FLAGS += -Wl,--gc-sections -Wl,-print-memory-usage
LINKER = gcc