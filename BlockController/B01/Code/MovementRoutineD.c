/******************************************************************************
* Filename		:	MovementRoutineD.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	This is a movement routine. It takes the train AWAY out of
*					platform 1 BUT via the siding. This is a 'rap around' 
*					routine.
*********************************************************************************/
#include "H/Types.h"
#include "MovementRoutineD.h"
#include "H/Signals.h"
#include "H/Sensors.h"
#include "H/TrainControl.h"
#include "H/Points.h"
#include "Timer.h"

PROCESS_STATE RoutineD( void )
{
	typedef enum
	{
		POWER_ON_A,
		WAIT_FOR_SENSOR3,
		POWER_OFF_A,
		OPEN_POINT1,
		OPEN_POINT2,
		OPEN_POINT3,
		POWER_ON_B,
		WAIT_FOR_SENSOR1,
		WAIT_FOR_TIMER,
		POWER_OFF_B,
		CLOSE_POINT1,
		CLOSE_POINT2,
		CLOSE_POINT3
	} MOVEMENT_STATE;

	PROCESS_STATE ReturnStatus = In_Progress;
	static MOVEMENT_STATE MovementState = POWER_ON_A;

	switch ( MovementState )
	{
		case POWER_ON_A :
			EnableMotorPower();
			if ( TrainMotorHome( 800, 5 ) == Command_Complete )
			{
				MovementState = WAIT_FOR_SENSOR3;
			}		
			break;

		case WAIT_FOR_SENSOR3 :
			if ( TrainPresent( 3 ) == true )
			{
				MovementState = POWER_OFF_A;
			}
			break;

		case POWER_OFF_A :
			if ( TrainMotorHome( 0, 5 ) == Command_Complete )
			{
				DisableMotorPower();
				MovementState = OPEN_POINT1;
			}
			break;

		case OPEN_POINT1 :
			if ( OpenPoint( 1 ) == Command_Complete )
			{
				MovementState = OPEN_POINT2;
			}
			break;

		case OPEN_POINT2 :
			if ( OpenPoint( 2 ) == Command_Complete )
			{
				MovementState = OPEN_POINT3;
			}
			break;

		case OPEN_POINT3 :
			if ( OpenPoint( 3 ) == Command_Complete )
			{
				MovementState = POWER_ON_B;
			}
			break;

		case POWER_ON_B :
			EnableMotorPower();
			if ( TrainMotorAway( 1023, 5 ) == Command_Complete )
			{
				MovementState = WAIT_FOR_SENSOR1;
			}		
			break;

		case WAIT_FOR_SENSOR1 :
			if ( TrainPresent( 1 ) == true )
			{
				MovementState = WAIT_FOR_TIMER;
				Set_Timer(GENERIC, 0, 6, 0 );
			}
			break;

		case WAIT_FOR_TIMER :
			if ( Check_Timer( GENERIC ) == MATURED )
			{
				MovementState = POWER_OFF_B;
			}
			break;

		case POWER_OFF_B :
			if ( TrainMotorAway( 0, 5 ) == Command_Complete )
			{
				DisableMotorPower();
				MovementState = CLOSE_POINT1;
			}
			break;

		case CLOSE_POINT1 :
			if ( ClosePoint( 1 ) == Command_Complete )
			{
				MovementState = CLOSE_POINT2;
			}
			break;

		case CLOSE_POINT2 :
			if ( ClosePoint( 2 ) == Command_Complete )
			{
				MovementState = CLOSE_POINT3;
			}
			break;

		case CLOSE_POINT3 :
			if ( ClosePoint( 3 ) == Command_Complete )
			{
				MovementState = POWER_ON_A;
				ReturnStatus = Command_Complete;
			}
			break;
	}
	return ReturnStatus;
}
