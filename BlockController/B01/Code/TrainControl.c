/******************************************************************************
* Filename		:	TrainControl.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	This manages train movement and speed.
*********************************************************************************/
#include <p18f2550.h>
#include <pwm.h>
#include <usart.h>
#include <delays.h>
#include "H/Types.h"
#include "H/TrainControl.h"
#include "H/Timer.h"

PROCESS_STATE TrainMotorHome( int speed, int AcDeceleration )
{
	static int Current_Forward_Speed = 0;
	int Steps = 0;
	PROCESS_STATE ReturnStatus = In_Progress;

	switch ( AcDeceleration )
	{
	case 1:
		Steps = 100;
	break;
	case 2:
		Steps = 200;
	break;
	case 3:
		Steps = 300;
	break;
	case 4:
		Steps = 400;
	break;
	case 5:
		Steps = 500;
	break;
	}
	
	if ( Check_Timer( TRAIN_MOVEMENT ) == MATURED ) // Matured
	{
		if ( speed == Current_Forward_Speed )
		{
	//		putrsUSART( "Forward: Train at requested speed...\r\n" );
			ReturnStatus = Command_Complete;
		}
		else if ( speed > Current_Forward_Speed )
		{
			Current_Forward_Speed = Current_Forward_Speed + Steps;
	//		putrsUSART( "Forward: +400\r\n" );
			if ( Current_Forward_Speed > 1023)
			{
	//		putrsUSART( "Forward: More than 1023 setting to 'speed'...\r\n" );
				Current_Forward_Speed = speed;
			}
			SetDCPWM1( Current_Forward_Speed );
		}
		else if ( speed < Current_Forward_Speed )
		{
			Current_Forward_Speed = Current_Forward_Speed - Steps;
		//	putrsUSART( "Forward: +400\r\n" );
			if ( Current_Forward_Speed < speed )
			{
		//		putrsUSART( "Forward: less than 'speed' so setting to 'speed'...\r\n" );
				Current_Forward_Speed = speed;
			}
		
			SetDCPWM1( Current_Forward_Speed );
		}

		Set_Timer(TRAIN_MOVEMENT, 0, 1, 0 );
	}

return ReturnStatus;
}

PROCESS_STATE TrainMotorAway( int speed, int AcDeceleration )
{
	static int Current_Backward_Speed = 0;
	int Steps = 0;
	PROCESS_STATE ReturnStatus = In_Progress;

	switch ( AcDeceleration )
	{
	case 1:
		Steps = 100;
	break;
	case 2:
		Steps = 200;
	break;
	case 3:
		Steps = 300;
	break;
	case 4:
		Steps = 400;
	break;
	case 5:
		Steps = 500;
	break;
	}
	
	if ( Check_Timer( TRAIN_MOVEMENT ) == MATURED ) // Matured
	{
		if ( speed == Current_Backward_Speed )
		{
		//	putrsUSART( "Forward: Train at requested speed...\r\n" );
			ReturnStatus = Command_Complete;
		}
		else if ( speed > Current_Backward_Speed )
		{
			Current_Backward_Speed = Current_Backward_Speed + Steps;
		//	putrsUSART( "Forward: +400\r\n" );
			if ( Current_Backward_Speed > 1023)
			{
		//	putrsUSART( "Forward: More than 1023 setting to 'speed'...\r\n" );
				Current_Backward_Speed = speed;
			}
			SetDCPWM2( Current_Backward_Speed );
		}
		else if ( speed < Current_Backward_Speed )
		{
			Current_Backward_Speed = Current_Backward_Speed - Steps;
		//	putrsUSART( "Forward: +400\r\n" );
			if ( Current_Backward_Speed < speed )
			{
		//		putrsUSART( "Forward: less than 'speed' so setting to 'speed'...\r\n" );
				Current_Backward_Speed = speed;
			}
		
			SetDCPWM2( Current_Backward_Speed );
		}

		Set_Timer(TRAIN_MOVEMENT, 0, 1, 0 );
	}

return ReturnStatus;
}

void TrainStop()
{
		PORTCbits.RC1 = 0;
		PORTCbits.RC2 = 0;
}

void EnableMotorPower( void )
{
	PORTBbits.RB0 = 1;
}

void DisableMotorPower( void )
{
	PORTBbits.RB0 = 0;
}
