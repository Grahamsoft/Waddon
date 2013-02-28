/******************************************************************************
* Filename		:	Main.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	Block Controller Firmware for PIC18F2550 microcontroller.
*					Contains 'Main'. 
*					Polls both the major functions:
*					-> Manage_Comms()
*					-> Manage_Movements()
*********************************************************************************/
#include "Types.h"
#include "Setup.h"
#include "Comms.h"
#include "Movements.h"

void main( void )
{

	typedef enum
	{	CONFIGURE,
		INITIALISE1,
		RUN
	} MAINLOOP_STATE;

	static MAINLOOP_STATE MainLoopState = CONFIGURE;

	while( 1 ) // Main Super Loop
	{
		switch ( MainLoopState )
		{
		case CONFIGURE :
			
			if ( Configure() == Command_Complete )
         	{
				MainLoopState = INITIALISE1;
			}
		break;

		case INITIALISE1 :
			if ( Initialise() == Command_Complete )
			{
				MainLoopState = RUN;
			}
		break;

		case RUN :
		
			Manage_Comms();
			Manage_Movements();
		break;
		}
	}

}

