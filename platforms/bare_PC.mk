# platform settings for PC's with GCC and NO standard libraries
TOOLCHAIN_PREFIX =
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra -pedantic -nostdlib -fomit-frame-pointer -fno-stack-protector -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-unroll-loops -fmerge-all-constants -fno-ident -mfpmath=sse -mfancy-math-387 -ffunction-sections -fdata-sections -Wl,--gc-sections
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
ALIBS +=
LINK_FLAGS += -Wl,-static -Wl,-nostdlib -Wl,-z,norelro -Wl,--hash-style=sysv -Wl,--build-id=none -Wl,--gc-sections -Wl,-flto
LINK_FLAGS_RELEASE += -Wl,-s