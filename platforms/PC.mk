# platform settings for PC's with GCC and libc
TOOLCHAIN_PREFIX =
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
LINK_FLAGS += -flto -Wl,--gc-sections -Wl,-print-memory-usage