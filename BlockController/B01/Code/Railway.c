#include "Types.h"
#include "Setup.h"
#include "Railway.h"
#include <stdlib.h>
#include "Points.h"
#include "Signals.h"
#include "TrainControl.h"
#include "Sensors.h"
#include "Timer.h"
#include <timers.h>
#include <delays.h>
#include <usart.h>
#include <pwm.h>

static GLOBAL_STATE GlobalState = INITIALISE;
static int start = 0;

void Manage_Railway( void )
{
	int result;
	int dave = 0;
	int graham = 0;
	char mybuff = 'A';
	char data[5];
	switch ( GlobalState )
			{
			case INITIALISE		:

				if ( Initialise() == Command_Complete )
         		{
					GlobalState = CHECK_TRAIN_START_LOCATION;

				putrsUSART( "Initialised Done.\r\n" );
				}
				break;

			case CHECK_TRAIN_START_LOCATION :

				if ( start == 1 )
         		{
					start = 0;
					EnableMotorPower();

					GlobalState = TRAIN_AT_START_LOCATION;
				}
				break;
			
			case TRAIN_AT_START_LOCATION :
putrsUSART( "Debug: Forward 1020\r\n" );
SetDCPWM1( 575 );
//				if ( TrainForward( 1020,5 ) == Command_Complete )
//       		{
					GlobalState = TRAIN_MOVING_HOME_FAST;
//				}
				break;

			case TRAIN_MOVING_HOME_FAST :

				if ( TrainPresent( 2 ) == true )
         		{
					Set_Timer(GENERIC, 0, 0, 25 );
putrsUSART( "Debug: Forward 800\r\n" );
//SetDCPWM1( 500 );
					GlobalState = TRAIN_MOVING_HOME_SLOWING;
				}
				else if  ( TrainPresent( 3 ) == true )
				{
					putrsUSART( "Debug: Forward: Error Missed Sensor 2\r\n" );
					GlobalState = TRAIN_MOVING_HOME_STOPPING;
				}
				break;
			

			case TRAIN_MOVING_HOME_SLOWING :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 0 );
					Set_Timer(GENERIC, 0, 2, 0 );
					GlobalState = TRAIN_WAITING_FOR_TIMER;
				}
		//		if ( TrainForward( 900,5 ) == Command_Complete )
		//		{
				break;

			case TRAIN_WAITING_FOR_TIMER :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 1000 );
					Set_Timer(GENERIC, 0, 0, 3 );
					GlobalState = A;
				}					
		//		}
				break;

			case A :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 0 );
					Set_Timer(GENERIC, 0, 0, 3 );
					GlobalState = B;
				}				
			break;

			case B :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 1000 );
					Set_Timer(GENERIC, 0, 0, 3 );
					GlobalState = C;
				}
			break;

			case C :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 0 );
					Set_Timer(GENERIC, 0, 0, 3 );
					GlobalState = D;
				}

			case D :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 600 );
					GlobalState = TRAIN_MOVING_HOME_SLOW;
				}

			case TRAIN_MOVING_HOME_SLOW :

				if ( TrainPresent( 3 ) == true )
        		{
					GlobalState = TRAIN_MOVING_HOME_STOPPING;
					Set_Timer(GENERIC, 0,0, 10 );
				}
				break;
	
			case TRAIN_MOVING_HOME_STOPPING :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
				putrsUSART( "Debug: Forward 0\r\n" );
				SetDCPWM1( 0 );
				//	if ( TrainForward( 0,5 ) == Command_Complete )
				//	{
					GlobalState = TRAIN_STOPPED_AT_HOME;
				//	}
				}
				break;

			case TRAIN_STOPPED_AT_HOME :

				DisableMotorPower();
				GlobalState = IDLE;
				Set_Timer(GENERIC, 0, 2, 0 );
putrsUSART( "Debug: Waiting for Timer to Mature\r\n" );
				break;

			case IDLE :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					GlobalState = E;
					EnableMotorPower();
				}
				break;

			case E :
				if ( OpenPoint(2) == Command_Complete )
				{
					GlobalState = F;
				}
				break;
			
			case F :
				if ( OpenPoint(3) == Command_Complete )
				{
					GlobalState = G;
				}
				break;

			case G :
				if ( OpenPoint(1) == Command_Complete )
				{
					GlobalState = TRAIN_MOVING_AWAY;
				}
				break;
			case TRAIN_MOVING_AWAY :
putrsUSART( "Debug: Backward 1020\r\n" );
SetDCPWM2( 1020 );
		//		if ( TrainBackward( 1020,5 ) == Command_Complete )
		//		{
					GlobalState = TRAIN_MOVING_TO_FAR;
		//		}
				break;

			case TRAIN_MOVING_TO_FAR :
				if ( TrainPresent( 1 ) == true )
         		{
				Set_Timer(GENERIC, 0,1, 0 );

putrsUSART( "Debug: Backward 0\r\n" );
					GlobalState = TRAIN_AT_FAR;
				}
				break;

			case TRAIN_AT_FAR :
		//		if ( TrainBackward( 0,5 ) == Command_Complete )
		//		{
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM2( 0 );
					GlobalState = H;
				}
		//		}
				break;

			case H :
				if ( ClosePoint(1) == Command_Complete )
				{
					GlobalState = I;
				}
				break;
			
			case I :
				if ( ClosePoint(3) == Command_Complete )
				{
					GlobalState = J;
				}
				break;

			case J :
				if ( ClosePoint(2) == Command_Complete )
				{
					GlobalState = K;
				}
				break;

			case K :
				Set_Timer(GENERIC, 0, 2, 0 );
				putrsUSART( "Debug: Waiting for Timer to Mature\r\n" );
				GlobalState = L;
				break;

			case L :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM1( 600 );
					GlobalState = M;
				}
				break;

			case M :
				if ( TrainPresent( 2 ) == true )
        		{
					SetDCPWM1( 0 );
					Set_Timer(GENERIC, 0, 2, 0 );
					SetSignalGreen( SignalNo1 );
					GlobalState = N;
				}
				break;

			case N :

				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM2( 700 );		
					GlobalState = O;
				}
				break;
			case O :
				if ( TrainPresent( 1 ) == true )
        		{

					Set_Timer(GENERIC, 0, 3, 0 );
					SetSignalRed( SignalNo1 );
					GlobalState = P;
				}
				break;

			case P :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					SetDCPWM2( 0 );		
					GlobalState = TRAIN_AT_START;
				}
				break;
				
			case TRAIN_AT_START :
				Set_Timer(GENERIC, 0, 2, 0 );
				DisableMotorPower();
				GlobalState = WAIT;
				putrsUSART( "Debug: Waiting for Timer to Mature\r\n" );
				break;

			case WAIT :
				if ( Check_Timer( GENERIC ) == MATURED )
				{
					GlobalState = CHECK_TRAIN_START_LOCATION;
				}
				break;
				

				

/*			case FORWARD_STOP	:
				
				if ( TrainForward( 0 ) == Command_Complete )
				{
					GlobalState = BACKWARD;
				}
			break;

			case BACKWARD	:
				if ( TrainBackward( 1020 ) == Command_Complete )
         		{
					GlobalState = BACKWARD_STOP;
				}
				
				break;

			case BACKWARD_STOP	:
				if ( TrainBackward( 0 ) == Command_Complete )
         		{
					GlobalState = CHECK_LOCATION;
				}	
				break;
			case CHECK_LOCATION	:
				if ( TrainPresent( 1 ) == true )
         		{
					GlobalState = CLOSE_POINT;
				}	
				break;
			case CLOSE_POINT :
			ClosePoint(1);
			
			GlobalState = FORWARD;
			break;*/
			}
			
}

void Start( void )
{
start = 1;
}