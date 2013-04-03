/******************************************************************************
* Filename		:	MovementRoutineE.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	This is a movement routine. It takes the train HOME to
*					platform 2.
*********************************************************************************/
#include "H/Types.h"
#include "MovementRoutineD.h"
#include "H/Sensors.h"
#include "H/TrainControl.h"
#include "H/Points.h"

PROCESS_STATE RoutineE( void )
{
	PROCESS_STATE ReturnStatus = In_Progress;

	typedef enum
	{
		OPEN_POINT,
		POWER_ON,
		WAIT_FOR_SENSOR1,
		WAIT_FOR_SENSOR2,
		POWER_OFF,
		CLOSE_POINT
	} MOVEMENT_STATE;

	static MOVEMENT_STATE MovementState = OPEN_POINT;

	switch ( MovementState )
	{
		case OPEN_POINT :
			if ( OpenPoint( 1 ) == Command_Complete )
			{
				MovementState = POWER_ON;
			}
			break;
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
			if ( ( TrainPresent( 5 ) == true ) && ( TrainPresent( 1 ) == false ) )
			{			
				MovementState = POWER_OFF;
			}
			break;
		case POWER_OFF :
			if ( TrainMotorHome( 0, 5 ) == Command_Complete )
			{
				DisableMotorPower();
				MovementState = CLOSE_POINT;
			}
			break;
		case CLOSE_POINT :
			if ( ClosePoint( 1 ) == Command_Complete )
			{
				MovementState = OPEN_POINT;
				ReturnStatus = Command_Complete;
			}
			break;
	}
	return ReturnStatus;
}
