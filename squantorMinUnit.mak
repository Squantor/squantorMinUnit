# SPDX-License-Identifier: MIT
#
# Copyright (c) 2020-2020 Bart Bilos
# For conditions of distribution and use, see LICENSE file

# squantorMinUnit library files
#
# Version: 20220715

# library settings
NAME := squantorMinUnit

# current makefile base dir relative to Makefile
LIB_DIR := $(patsubst %/,%,$(dir $(lastword $(MAKEFILE_LIST))))

$(NAME)_LIB_FILES := $(LIB_DIR)/src/MinUnit.c

$(NAME)_LIB_INCLUDES := -I$(LIB_DIR)/inc

# --- nothing user definable below ---
LIBRARIES += $(NAME)
