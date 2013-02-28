/******************************************************************************
* Filename		:	Comms.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	Polls both the major Comms functions, Send and Receive.
*********************************************************************************/
#include "Types.h"
#include "Comms.h"
#include "CommsSend.h"
#include "CommsReceive.h"

void Manage_Comms( void )
{	
	typedef enum
	{
		DO_SEND,
		DO_RECEIVE

	} COMMS_STATE;

	static COMMS_STATE  Comms_State = DO_SEND;

	switch ( Comms_State )
	{
		case DO_SEND:
			if ( Send_Comms() == Command_Complete )
			{
				Comms_State = DO_RECEIVE;
			}
		break;

		case DO_RECEIVE:
			if ( Receive_Comms() == Command_Complete )
			{
				Comms_State = DO_SEND;
			}
		break;
	}
}
