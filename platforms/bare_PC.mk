# platform settings for PC's with GCC and NO standard libraries
TOOLCHAIN_PREFIX =
C_SOURCES += src/main_PC.c src/00_start.c src/syscall.c src/_exit.c
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra -pedantic -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=sse -mfancy-math-387 -ffunction-sections -fdata-sections -Wl,--gc-sections
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
ALIBS +=
LINK_FLAGS += -static -nostdlib -z norelro --hash-style=sysv --build-id=none --gc-sections
LINK_FLAGS_RELEASE += -s