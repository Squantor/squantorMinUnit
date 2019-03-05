/*
 * Copyright (c) 2015, Louis P. Santillan <lpsantil@gmail.com>
 * All rights reserved.
 * See LICENSE for licensing details.
 */
#include <rt0/rt0.h>

long syscall6( long n, long a0, long a1, long a2, long a3, long a4, long a5 )
{
   long ret;
   register long r10 __asm__( "r10" ) = a3,
                 r08 __asm__( "r8" ) = a4,
                 r09 __asm__( "r9" )  = a5;

   __asm__ volatile( "syscall"
                     : "=a" ( ret )
                     : "a" ( n ), "D" ( a0 ), "S" ( a1 ), "d" ( a2 ),
                       "r" ( r08 ), "r" ( r09 ), "r" ( r10 )
                     : "rcx", "r11", "memory");

   ret = ( 0 > ret ? errno = -ret, -1 : ret );
   return( ret );
}
