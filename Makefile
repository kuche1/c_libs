
MAKEFLAGS += -rR
# `-r` removes all built-in make riles
# `-R` removes all built-in make variables

CC := gcc

CFLAGS := -std=c99
CFLAGS += -Werror -Wextra -Wall -pedantic -Wfatal-errors -Wshadow
CFLAGS += -fwrapv # make signed integer operations defined

COMPILE_SHARED_LIB := $(CC) $(CFLAGS) -shared -o

# `$@` is the name of the target

buf.so: Makefile buf.c buf.h
	$(COMPILE_SHARED_LIB) $@ buf.c buf.h
