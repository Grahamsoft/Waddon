/******************************************************************************
* Filename		:	MovementRoutineB.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	This is a movement routine. It takes the train AWAY out of
*					platform 2.
*********************************************************************************/
#include "H/Types.h"
#include "MovementRoutineB.h"
#include "H/Signals.h"
#include "H/Sensors.h"
#include "H/Points.h"
#include "Timer.h"
#include "TrainControl.h"


PROCESS_STATE RoutineB( void )
{
	PROCESS_STATE ReturnStatus = In_Progress;

	typedef enum
	{
		OPEN_POINT,
		SIGNAL_TO_GREEN,
		WAIT_FOR_TIMER1,
		POWER_ON,
		WAIT_FOR_SENSOR2,
		SIGNAL_TO_RED,
		WAIT_FOR_TIMER2,
		POWER_OFF,
		CLOSE_POINT
	} MOVEMENT_STATE;

	static MOVEMENT_STATE MovementState = OPEN_POINT;

	switch ( MovementState )
	{
		case OPEN_POINT :
		
			if ( OpenPoint( 1 ) == Command_Complete )
			{
				MovementState = SIGNAL_TO_GREEN;
			}
			break;

		case SIGNAL_TO_GREEN :
			SetSignalGreen( SignalNo2 );
			Set_Timer( GENERIC, 0, 3, 0 );
			MovementState = WAIT_FOR_TIMER1;
			break;

		case WAIT_FOR_TIMER1 :
			//TODO A timer should be added here.
			if ( Check_Timer( GENERIC ) == MATURED )
			{
				MovementState = POWER_ON;
			}
			break;

		case POWER_ON :
			EnableMotorPower();
			if ( TrainMotorAway( 1023, 5 ) == Command_Complete )
			{
				MovementState = WAIT_FOR_SENSOR2;
			}		
			break;

		case WAIT_FOR_SENSOR2 :
			if ( ( TrainPresent( 1 ) == true ) && ( TrainPresent( 5 ) == false ) )
			{	
				MovementState = SIGNAL_TO_RED;		
			}
			break;

		case SIGNAL_TO_RED :
			SetSignalRed( SignalNo2 );
			Set_Timer(GENERIC, 0, 6, 0 );
			MovementState = WAIT_FOR_TIMER2;
			break;

		case WAIT_FOR_TIMER2 :
			//TODO A timer should be added here.
			if ( Check_Timer( GENERIC ) == MATURED )
			{
				MovementState = POWER_OFF;
			}
			break;

		case POWER_OFF :
			if ( TrainMotorAway( 0, 5 ) == Command_Complete )
			{
				DisableMotorPower();
				MovementState = CLOSE_POINT;
			}
			break;

		case CLOSE_POINT :
			if ( ClosePoint(1) == Command_Complete )
			{			
				MovementState = OPEN_POINT;
				ReturnStatus = Command_Complete;
			}
			break;
	}
	return ReturnStatus;
}
