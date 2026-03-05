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
#include "System.h"
#include "AT28Cxxx.h"
/*============================================================================*/
#define EEPROM_FIRST_ADDRESS	0x0000
#define	EEPROM_LAST_ADDRESS		0x7fff
/*============================================================================*/
signed char AT28CxxxWriteByte( unsigned short Address, unsigned char Data )
	{
	unsigned char xdata	*p;
	tickcount_t			t1;

#if			EEPROM_FIRST_ADDRESS > 0x0000
	if( Address < EEPROM_FIRST_ADDRESS || Address > EEPROM_LAST_ADDRESS )
#else	/*	EEPROM_FIRST_ADDRESS > 0x0000 */
	if( Address > EEPROM_LAST_ADDRESS )
#endif	/*	EEPROM_FIRST_ADDRESS > 0x0000 */
		return AT28CXXX_ADDRESS_ERROR;

	p	= (unsigned char xdata*)Address;

	if( *p == Data )
		return AT28CXXX_WRITE_UNNECESSARY;

	*p	= Data;

	t1	= GetTickCount();

	while(( *p & 0x80 ) != ( Data & 0x80 ) && GetTickCount() - t1 < 5 )
		{}

	if( *p != Data )
		return AT28CXXX_WRITE_ERROR;

	return AT28CXXX_WRITE_OK;
	}
/*============================================================================*/
unsigned char AT28CxxxReadByte( unsigned short Address )
	{
#if			EEPROM_FIRST_ADDRESS > 0x0000
	if( Address < EEPROM_FIRST_ADDRESS || Address > EEPROM_LAST_ADDRESS )
#else	/*	EEPROM_FIRST_ADDRESS > 0x0000 */
	if( Address > EEPROM_LAST_ADDRESS )
#endif	/*	EEPROM_FIRST_ADDRESS > 0x0000 */
		return 0xff;

	return *(unsigned char	xdata*)Address;
	}
/*============================================================================*/
