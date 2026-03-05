/*============================================================================*/
/*
 Copyright (c) 2025-2025, Isaac Marino Bavaresco
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
#if			!defined __LCD_H__
#define __LCD_H__
/*============================================================================*/
void			LCDInit				( void );
signed char		LCDHasFailed		( void );
void			LCDClearFailedFlag	( void );
signed char		LCDResizeScreen		( unsigned char width, unsigned char height );
void			LCDDefineChar		( unsigned char CharIndex, const unsigned char *Pattern );
/*----------------------------------------------------------------------------*/
void			gotoxy				( signed char x, signed char y );
void			clrscr				( void );
unsigned char	getmaxx				( void );
unsigned char	getmaxy				( void );
unsigned char	getcursorx			( void );
unsigned char	getcursory			( void );
/*----------------------------------------------------------------------------*/
#define CURSOR_MODE_OFF				0
#define CURSOR_MODE_BLINK			1
#define CURSOR_MODE_ON				2
/*----------------------------------------------------------------------------*/
void			LCDControlCursor	( unsigned char Mode );
/*----------------------------------------------------------------------------*/
#define	SCROLL_MODE_NORMAL	0
#define	SCROLL_MODE_DELAYED	1
/*----------------------------------------------------------------------------*/
void			setscrollmode		( unsigned char Mode );
/*============================================================================*/
#endif	/*	!defined __LCD_H__ */
/*============================================================================*/
