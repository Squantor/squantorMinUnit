# project settings
BIN_NAME = squantorMinUnitCexample
C_SOURCES = src/main.c src/tests1.c
CXX_SOURCES =
S_SOURCES =
INCLUDES = -Iinc
COMPILE_C_FLAGS += -std=gnu11 -Wall -Wextra
COMPILE_CXX_FLAGS += -std=c++17 -Wall -Wextra
COMPILE_ASM_FLAGS += -c -x assembler-with-cpp
LINK_FLAGS += -flto -Xlinker --gc-sections -Xlinker -print-memory-usage
