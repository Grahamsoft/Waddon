/******************************************************************************
* Filename		:	Signals.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	This initialises, and sets the colours of the signals.
*					Signal Locations:
*					1. Platform 1
*					2. Platfrom 2
*********************************************************************************/
#include <p18f2550.h>
#include "H/Types.h"
#include "Signals.h"

void IntSignals( void )
{
	SetSignalRed( SignalNo1 );
	SetSignalRed( SignalNo2 );
}

void SetSignalRed( SIGNAL_ID Signal_ID )
{
	switch( Signal_ID )
	{
	case SignalNo1 :

		PORTBbits.RB2 = 1;	// RED Pin 23 Port B2	
		PORTBbits.RB1 = 0;	// GREEN Pin 22 Port B1
		break;

	case SignalNo2 :

		PORTAbits.RA6 = 1;	// RED Pin 10 Port A6	
		PORTCbits.RC0 = 0;	// GREEN Pin 11 Port C0
		break;
	} 
}

void SetSignalGreen( SIGNAL_ID Signal_ID )
{
	switch( Signal_ID )
	{
	case SignalNo1 :

		PORTBbits.RB2 = 0;	// RED Pin 23 Port B2	
		PORTBbits.RB1 = 1;	// GREEN Pin 22 Port B1
		break;

	case SignalNo2 :

		PORTAbits.RA6 = 0;	// RED Pin 10 Port A6	
		PORTCbits.RC0 = 1;	// GREEN Pin 11 Port C0
		break;
	} 
}
