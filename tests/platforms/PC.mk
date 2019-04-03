# platform settings for PC's with GCC and libc
TOOLCHAIN_PREFIX =
C_SOURCES += src/main_PC.c
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
#LINK_FLAGS += -Wl,--gc-sections -Wl,-print-memory-usage -Wl,--trace
LINK_FLAGS += --gc-sections -print-memory-usage
PLATFORM_OBJECTS =  /usr/lib/x86_64-linux-gnu/Scrt1.o /usr/lib/x86_64-linux-gnu/crti.o /usr/lib/gcc/x86_64-linux-gnu/7/crtbeginS.o /usr/lib/gcc/x86_64-linux-gnu/7/crtendS.o /usr/lib/x86_64-linux-gnu/crtn.o
LIBS += -L /usr/lib/x86_64-linux-gnu -L /usr/lib/gcc/x86_64-linux-gnu/7/ -lgcc -lgcc_eh -lc
LINKER = ld