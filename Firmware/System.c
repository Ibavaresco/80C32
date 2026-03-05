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
#include <REG52.h>
/*============================================================================*/
#include "System.h"
#include "Keyboard.h"
/*============================================================================*/
static tickcount_t	SystemTick	= 0;
/*============================================================================*/
void Timer0_ISR( void ) interrupt 1
	{
	TR0	= 0;

#pragma ASM
	mov 	A,TL0
	add 	A,#248	; 0xf8
	mov 	TL0,A
	mov 	A,TH0
	addc	A,#216	; 0xd8
	mov 	TH0,A
#pragma ENDASM

	TR0	= 1;

	SystemTick++;   /* Increment the overflow count */

	ScanKeyboard();
	}
/*============================================================================*/
void TickInit( void )
	{
	TR0		= 0;						/* Stop Timer 0 */

	TL0		= -10000 & 0xff;
	TH0		= -10000 >> 8;

	TMOD	= ( TMOD & 0xF0 ) | 0x01;	/* Set T/C0 Mode */
	ET0		= 1;						/* Enable Timer 0 Interrupts */
	TR0		= 1;						/* Start Timer 0 Running */
	EA		= 1;						/* Global Interrupt Enable */
	}
/*============================================================================*/
tickcount_t GetTickCount( void )
	{
	tickcount_t	Temp;

	ET0	= 0;
	Temp	= SystemTick;
	ET0	= 1;

	return Temp;
	}
/*============================================================================*/
void Delay_10ms( unsigned short t )
	{
	tickcount_t	t1;

	t1	= GetTickCount();
	while( GetTickCount() - t1 < t )
		{}
	}
/*============================================================================*/
