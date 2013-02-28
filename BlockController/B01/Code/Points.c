/******************************************************************************
* Filename		:	Points.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	This initialises, opens and closes the points.
*********************************************************************************/
#include <p18f2550.h>
#include "Types.h"
#include "H/Timer.h"
#include "H/Points.h"
#include <delays.h>

static POINT_STATE Point_State[3];
static TIMER_STATUS TimerStatus = UNSET;

void IntPoints( void )
{
//------------------------------------------------------------------------------*/
// Function: Initialises the points. This is a blocking function to prevent
//			 any movements occuring while the points are in a unknown state.
//------------------------------------------------------------------------------*/
	Point_State[1] = UNKNOWN;
	Point_State[2] = UNKNOWN;
	Point_State[3] = UNKNOWN;

	while ( OpenPoint(1) != Command_Complete );
	while ( ClosePoint(1) != Command_Complete );

	while ( OpenPoint(2) != Command_Complete );
	while ( ClosePoint(2) != Command_Complete );

	while ( OpenPoint(3) != Command_Complete );
	while ( ClosePoint(3) != Command_Complete );
}

PROCESS_STATE OpenPoint( int Point_ID )
{
//------------------------------------------------------------------------------*/
// Function: Changes the point into the Open state.
//------------------------------------------------------------------------------*/
	
	PROCESS_STATE ReturnStatus = In_Progress;
	
	if ( Point_State[ Point_ID ] == OPEN )
	{
		return Command_Complete;
	}

	switch ( TimerStatus )
		{
		case UNSET :
	
		//Set_Timer( Timer ID, Mins, Secs, Half Secs )
		Set_Timer( POINT, 0, 1, 0);
	
		switch ( Point_ID )
			{
			case 1	:
			PORTAbits.RA0 = 1;
			break;
	
			case 2 	:
			PORTAbits.RA2 = 1;
			break;
	
			case 3 	:
			PORTAbits.RA4 = 1;	
			break;		
			}
		TimerStatus = SET;
		break;
	
		case SET :
		
			if ( Check_Timer( POINT ) == MATURED )
			{
				PORTAbits.RA0 = 0;
				PORTAbits.RA2 = 0;
				PORTAbits.RA4 = 0;
				Set_Timer( POINT, 0, 1, 0);
				TimerStatus = DO_CHARGE;
			}
		break;

		case DO_CHARGE :
			if ( Check_Timer( POINT ) == MATURED )
			{
				TimerStatus = UNSET;
				ReturnStatus = Command_Complete;
				Point_State[ Point_ID ] = OPEN;
			}
		break;
		}

return ReturnStatus;
}

PROCESS_STATE ClosePoint( int Point_ID )
{
//------------------------------------------------------------------------------*/
// Function: Changes the point into the Close state.
//------------------------------------------------------------------------------*/
	PROCESS_STATE ReturnStatus = In_Progress;
	
	if ( Point_State[ Point_ID ] == CLOSE )
	{
		return Command_Complete;
	}

	switch ( TimerStatus )
		{
		case UNSET :
	
		//Set_Timer( Timer ID, Mins, Secs, Half Secs )
		Set_Timer( POINT, 0, 1, 0);
	
		switch ( Point_ID )
			{
			case 1	:
			PORTAbits.RA1 = 1;
			break;
	
			case 2 	:
			PORTAbits.RA3 = 1;
			break;
	
			case 3 	:
			PORTAbits.RA5 = 1;	
			break;		
			}
		TimerStatus = SET;
		break;
	
		case SET :
		
			if ( Check_Timer( POINT ) == MATURED )
			{
				PORTAbits.RA1 = 0;
				PORTAbits.RA3 = 0;
				PORTAbits.RA5 = 0;
				Set_Timer( POINT, 0, 1, 0);
				TimerStatus = DO_CHARGE;
			}
		break;

		case DO_CHARGE :
			if ( Check_Timer( POINT ) == MATURED )
			{
				TimerStatus = UNSET;
				ReturnStatus = Command_Complete;
				Point_State[ Point_ID ] = CLOSE;
			}
		break;
		}

return ReturnStatus;
}
