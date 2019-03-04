# project settings
BIN_NAME = squantorMinUnitCexample
C_SOURCES = src/test.c src/00_start.c src/syscall.c src/_exit.c
CXX_SOURCES = 
S_SOURCES =
INCLUDES = -Iinc
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra -pedantic -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=sse -mfancy-math-387 -ffunction-sections -fdata-sections -Wl,--gc-sections
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
ALIBS +=
LINK_FLAGS += -static -nostdlib -z norelro --hash-style=sysv --build-id=none --gc-sections -flto
LINK_FLAGS_RELEASE += -s