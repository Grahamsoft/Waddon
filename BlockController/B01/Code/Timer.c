/******************************************************************************
* Filename		:	Timer.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	Manages the timer. This includes the timer interrupt routine	
*********************************************************************************/
#include "Types.h"
#include "Timer.h"
#include "Points.h"
#include <p18f2550.h>
#include <timers.h>
#include <usart.h>
#include <stdlib.h>
#include <string.h>

static unsigned int Half_Second = 0;

static unsigned int temptimer = 0;
static unsigned int Point_Timer = 0;
static unsigned int Generic_Timer = 0;

#pragma interrupt Increment_Timer
void Increment_Timer( void )
{
//------------------------------------------------------------------------------*/
// Function: Saves the time.
//------------------------------------------------------------------------------*/
	if ( Half_Second == 72000 )	//Hour achived
	{
		Half_Second = 0;
	}
	else
	{
		Half_Second++;
	}
}
TIMER_STATUS Check_Timer( TIMER_IDS TimerID )
{
//------------------------------------------------------------------------------*/
// Function: Check to see in a timer has matured.
//------------------------------------------------------------------------------*/
	int kk = 0;	// Unknown why it is called kk but it is 
				// not being changed at this point. (todo)

	switch ( TimerID )
	{
		case TRAIN_MOVEMENT :
			kk = temptimer;
			break;
	
		case POINT :
			kk = Point_Timer;
			break;

		case GENERIC :
			kk = Generic_Timer;
			break;
	}

	if ( Get_Time() > kk )
	{
		return MATURED;
	}
	else
	{
		return SET;
	}
}
int Get_Time( void )
{
	return Half_Second;
}
void Set_Timer( TIMER_IDS TimerID, int Mins, int Seconds, int HalfSecond )
{
//------------------------------------------------------------------------------*/
// Function: Sets a timer.
//------------------------------------------------------------------------------*/
	int Total_Half_Seconds = 0;
	int Current_Time = 0;

	Total_Half_Seconds = HalfSecond;	//Max30
	Total_Half_Seconds = Total_Half_Seconds + ( Seconds * 30 );
	Total_Half_Seconds = Total_Half_Seconds + ( Mins * 1200 );

	Current_Time = Get_Time();

	switch ( TimerID )
	{
		case TRAIN_MOVEMENT :
			temptimer = Current_Time + Total_Half_Seconds;
			break;
	
		case POINT :
			Point_Timer = Current_Time + Total_Half_Seconds;
			break;
	
		case GENERIC :
			Generic_Timer = Current_Time + Total_Half_Seconds;
			break;
	}
}
#pragma code high_vector=0x18
void high_interrupt (void)
{
_asm GOTO timer_isr _endasm
}

#pragma code

#pragma interruptlow timer_isr
void timer_isr (void)
{
//------------------------------------------------------------------------------*/
// Function: Interrupt routine
//------------------------------------------------------------------------------*/
	INTCONbits.TMR0IF = 0;	// Resets the flag
	Increment_Timer();		// Saves the time
	WriteTimer0( 0 );		// Resets the Timer
}
