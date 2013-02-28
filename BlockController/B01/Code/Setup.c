/******************************************************************************
* Filename		:	Setup.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	Sets up the ports and hardware settings.
*********************************************************************************/
#include <p18f2550.h>
#include <usart.h>
#include <timers.h>
#include <pwm.h>
#include "H/Types.h"
#include "Setup.h"
#include "H/Signals.h"
#include "H/Points.h"
#include "H/Sensors.h"
#include "JobManager.h"
#include "PlatformManger.h"
#include "Timer.h"
//#define DEBUG Change this to apply debug.

PROCESS_STATE Configure( void )
{

	PROCESS_STATE ReturnStatus = In_Progress;

	static CONFIGURE_STATUS State = Set_Port_A;

	switch ( State )
	{
	case Set_Port_A :	
		ADCON1 = 0b00001111;
		TRISA  = 0b00000000;
		PORTA  = 0;
		State = Set_Port_B;
		break;

	case Set_Port_B :

		TRISB = 0b11111000;
		PORTB = 0;
		State = Set_Port_C;
		break;

	case Set_Port_C :
		
		TRISC = 0b10000000;
		PORTC = 0;
		State = Set_Oscillator;
		break;

	case Set_Oscillator :
	
		OSCCON = 0b01111110;
		State = Set_Timer0;
		break;

	case Set_Timer0 :

		OpenTimer0( TIMER_INT_ON &//Should be ON
					T0_8BIT &
					T0_SOURCE_INT &
					T0_PS_1_256 );

		State = Set_Timer2;
		break;

	case Set_Timer2 :

		OpenTimer2( TIMER_INT_OFF	&
					T2_PS_1_1		&
					T2_POST_1_8		);

		State = Set_PWM;
		break;

	case Set_PWM :

		OpenPWM1( 0xff );
		SetDCPWM1( 0 );
		OpenPWM2( 0xff );
		SetDCPWM2( 0 );

		State = Set_Interrupts;
		break;

	case Set_Interrupts :

		INTCONbits.GIE = 1;
		State = Set_USART;
		break;

	case Set_USART :
				
		OpenUSART( USART_TX_INT_OFF &
				   USART_RX_INT_OFF &
				   USART_ASYNCH_MODE &
				   USART_EIGHT_BIT &
				   USART_CONT_RX &
				   USART_BRGH_LOW,
				   12 );
		State = Finished;
		break;

	case Finished :
		ReturnStatus = Command_Complete;
		break;
	}

return ReturnStatus;
}

PROCESS_STATE Initialise( void )
{
	PROCESS_STATE ReturnStatus = In_Progress;
	IntSignals();
	
	Set_Timer(GENERIC, 0, 1, 0 );
	while ( Check_Timer( GENERIC ) != MATURED );
	IntPoints();
		
	ClearJobs();
	ClearPlatforms();

	if ( TrainPresent( 2 ) == true )
	{
		// Is there a train at platform 1?
		SetPlatformTrainPresent( PLAT1 );
		#ifdef DEBUG
		putrsUSART( "TP 1\r\n" );
		#endif
	}
	if ( TrainPresent( 5 ) == true )		
	{
		// Is there a train at platform 2?
		SetPlatformTrainPresent( PLAT2 );
		#ifdef DEBUG
		putrsUSART( "TP 2\r\n" );
		#endif
	}

	ReturnStatus = Command_Complete;

	return ReturnStatus;
}

