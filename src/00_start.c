/*
MIT License

Copyright (c) 2019 Bart Bilos

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
/*
Adapted from https://github.com/lpsantil/rt0
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
