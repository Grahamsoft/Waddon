/******************************************************************************
* Filename		:	Sensors.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	Returns values from the sensors
*					Sensor locations:
*					1. Far Away
*					2. Platfrom 1
*					3. Far Home
*					4. Siding
*					5. Platform 2
*********************************************************************************/
#include <p18f2550.h>
#include "Types.h"
#include "Sensors.h"


BOOLEAN TrainPresent( int Location )
{

	BOOLEAN ReturnStatus = false;
	switch ( Location )
		{
		case 1	:
		if ( PORTBbits.RB7 == 0 )
		{ ReturnStatus = true; }
		break;
		case 2	:
		if ( PORTBbits.RB6 == 0 )
		{ ReturnStatus = true; }
		break;
		case 3	:
		if ( PORTBbits.RB5 == 0 )
		{ ReturnStatus = true; }
		break;
		case 4	:
		if ( PORTBbits.RB4 == 0 )
		{ ReturnStatus = true; }
		break;
		case 5	:
		if ( PORTBbits.RB3 == 0 )
		{ ReturnStatus = true; }
		break;
		}

return ReturnStatus;

}
