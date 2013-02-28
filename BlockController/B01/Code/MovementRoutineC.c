/******************************************************************************
* Filename		:	MovementRoutineC.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	This is a movement routine. It takes the train HOME into
*					platform 1.
*********************************************************************************/
#include "Types.h"
#include "MovementRoutineC.h"
#include "Sensors.h"
#include "TrainControl.h"

PROCESS_STATE RoutineC( void )
{
	PROCESS_STATE ReturnStatus = In_Progress;

	typedef enum
	{
		POWER_ON,
		WAIT_FOR_SENSOR1,
		WAIT_FOR_SENSOR2,
		POWER_OFF
	} MOVEMENT_STATE;

	static MOVEMENT_STATE MovementState = POWER_ON;

	switch ( MovementState )
	{
		case POWER_ON :
			EnableMotorPower();
			if ( TrainMotorHome( 1023, 5 ) == Command_Complete )
			{
				MovementState = WAIT_FOR_SENSOR1;
			}
			break;

		case WAIT_FOR_SENSOR1 :
			if ( TrainPresent( 1 ) == true )
			{
				MovementState = WAIT_FOR_SENSOR2;
			}
			break;
		case WAIT_FOR_SENSOR2 :
			if ( TrainPresent( 2 ) == true )
			{			
				MovementState = POWER_OFF;
			}
			break;
		case POWER_OFF :
			if ( TrainMotorHome( 0, 5 ) == Command_Complete )
			{
				DisableMotorPower();
				MovementState = POWER_ON;
				ReturnStatus = Command_Complete;
			}
			break;
	}

	return ReturnStatus;
}
