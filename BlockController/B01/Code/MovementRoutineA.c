/******************************************************************************
* Filename		:	MovementRoutineA.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	This is a movement routine. It takes the train AWAY out of
*					platform 1.
*********************************************************************************/
#include "H/Types.h"
#include "MovementRoutineA.h"
#include "H/Signals.h"
#include "H/Sensors.h"
#include "Timer.h"
#include "TrainControl.h"


PROCESS_STATE RoutineA( void )
{
	PROCESS_STATE ReturnStatus = In_Progress;

	typedef enum
	{
		SIGNAL_TO_GREEN,
		WAIT_FOR_TIMER1,
		POWER_ON,
		WAIT_FOR_SENSOR2,
		SIGNAL_TO_RED,
		WAIT_FOR_TIMER2,
		POWER_OFF
	} MOVEMENT_STATE;

	static MOVEMENT_STATE MovementState = SIGNAL_TO_GREEN;

	switch ( MovementState )
	{
		case SIGNAL_TO_GREEN :
			SetSignalGreen( SignalNo1 );
			Set_Timer(GENERIC, 0, 3, 0 );
			MovementState = WAIT_FOR_TIMER1;
			break;

		case WAIT_FOR_TIMER1 :
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
			if ( TrainPresent( 1 ) == true )
			{	
				MovementState = SIGNAL_TO_RED;		
			}
			break;

		case SIGNAL_TO_RED :
			SetSignalRed( SignalNo1 );
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
				MovementState = SIGNAL_TO_GREEN;
				ReturnStatus = Command_Complete;
			}
			break;
	}

	return ReturnStatus;

}