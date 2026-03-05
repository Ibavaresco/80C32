/*============================================================================*/
/*
 Copyright (c) 2013-2025, Isaac Marino Bavaresco
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
#include <reg52.h>
#include "Keyboard.h"
/*============================================================================*/
static signed char		PreviousScan	= -1;
static signed char		CurrentScan		= -1;
static unsigned char	Column			=  0;
static char				KBDBuffer		=  0;
/*============================================================================*/
static const signed char code	KBDDecode[3][8]	=
	{
		{ '\b', '7',  -1, '4',  -1,  -1,  -1, '1' },
		{  '0', '8',  -1, '5',  -1,  -1,  -1, '2' },
		{ '\n', '9',  -1, '6',  -1,  -1,  -1, '3' }
	};
/*============================================================================*/
void ScanKeyboard( void )
	{
	unsigned char	c;

	switch( Column )
		{
		default:
			Column		= 0;
		case 0:
			CurrentScan	= 0;
			c			= *(const unsigned char xdata*)0xfffe;
			break;
		case 1:
			c			= *(const unsigned char xdata*)0xfffd;
			break;
		case 2:
			c			= *(const unsigned char xdata*)0xfffb;
			break;
		}

	c	= ~c & 0x0f;

	if( c != 0 )
		{
		if( CurrentScan != 0 || c > 8 )
			CurrentScan	= -1;
		else
			CurrentScan	= KBDDecode[Column][c-1];
		}

	if( ++Column > 2 )
		{
		Column	= 0;
		if( PreviousScan == 0 && CurrentScan > 0 )
			KBDBuffer	= CurrentScan;
		PreviousScan	= CurrentScan;
		}
	}
/*============================================================================*/
char getch( void )
	{
	char	Temp;

	ET0			= 0;
	Temp		= KBDBuffer;
	KBDBuffer	= 0;
	ET0			= 1;

	return Temp;
	}
/*============================================================================*/
void flushbkd( void )
	{
	KBDBuffer	= 0;
	}
/*============================================================================*/
