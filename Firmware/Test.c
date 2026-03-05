/*============================================================================*/
/*
 Copyright (c) 2025, Isaac Marino Bavaresco
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:
	 * Redistributions of source code must retain the above copyright
	   notice, this list of conditions and the following disclaimer.
	 * Neither the name of the author nor the
	   names of its contributors may be used to endorse or promote products
	   derived from this software without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE AUTHOR ''AS IS'' AND ANY
 EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
/*============================================================================*/
#include <stdio.h>
#include <reg52.h>
#include "System.h"
#include "LCD.h"
#include "Keyboard.h"
#include "AT28Cxxx.h"
/*============================================================================*/
int main( void )
	{
	static const char code	Msg[] = "Hello World!\n";
	unsigned char xdata		*p = 0x8000;
	unsigned char code		*q;
	unsigned				i;
	unsigned char			j;

	LCDInit();
	TickInit();

	printf( Msg );

	for( i = 0; i < 0x7f00; i++ )
		p[i]	= (unsigned char)i;

	for( i = 0; i < 0x7f00; i++ )
		if( p[i] != (unsigned char)i )
			break;

	if( i < 0x7f00 )
		printf( "Error RAM %04X\n", i + (unsigned short)p );
	else
		printf( "RAM OK\n" );

	
	for( i = 0, q = 0; i < 0x8000; i++ )
		if( AT28CxxxWriteByte( i, q[i] ) < 0 )
			break;

	for( i = 0, q = 0; i < 0x8000; i++ )
		if( AT28CxxxReadByte( i ) != q[i] )
			break;

	if( i < 0x8000 )
		printf( "Error EE  %04X", i );
	else
		printf( "EE  OK" );

	while( 1 )
		{
		unsigned char	c;

		if(( c = getch() ) != 0 )
			{
			printf( "%c", c );
			if( c == '\b' )
				printf( " \b" );
			}
		}
	}
/*============================================================================*/
