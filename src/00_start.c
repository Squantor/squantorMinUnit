/*
 * Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */

#include <rt0/rt0.h>

/* pointer to array of char* strings that define the current environment variables */
char **__environ;
int errno;

void _start( void ) __attribute__((noreturn));

void _start( void )
{
   __asm__ volatile(
        /* Setup the base */
        "pop	%rbp\n\t"                            \
        "mov	%rsp,	%rbp\n\t"                    \
        /* argc = RDI = [ RSP ] */
        /* argv = RSI = [ RSP+8 ] */
        /* envp = RDX = [ argv+8*argc+8 ] */
        "mov	(0)(%rbp),	%rdi\n\t"            \
        "lea	(8)(%rbp),	%rsi\n\t"            \
        "lea	(8)(%rsi,%rdi,8),	%rdx\n\t"    \
        /* align the stack */
        "and	$-16,	%rsp\n\t"
        "call	main\n" \
        "movq   %rax, %rdi\n" \
        "call   _exit");

   for(;;);
}
