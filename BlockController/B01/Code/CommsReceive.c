/******************************************************************************
* Filename		:	CommsReceive.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	Handles the receiving of communications.
*********************************************************************************/
#include "Types.h"
#include <p18f2550.h>
#include <usart.h>
#include <string.h>
#include <stdlib.h>
#include "JobManager.h"
#include "PlatformManger.h"
#include "CommsReceive.h"
#include "Identification.h"

//GLOBAL STRINGS FOR COMMSSEND
	char ToString[] = "to";
	char FromString[] = "from";
	char ActionString[] = "action";
	char DestinationString[] = "destination";
	char PlatformString[] = "platform";
	char ReplyString[] = "reply";
	char WhishString[] = "whish";
	char TraintypeString[] = "traintype";
	char SpeedString[] = "speed";
	char OriginPlatform[] = "originplatform";
	char NullChar = 0b0000000;
	char CRChar = 0b0001101;
	char Wey[] = "wey";
	char Wat[] = "wat";	
	char One[] = "1";
	char Two[] = "2";
	char Emu2[] = "emu2";
	char Emu3[] = "emu3";
	char Emu4[] = "emu4";
	char Br47c1[] = "br47c1";
	char Br47[] = "br47";
	char Ten[] = 	"10";
	char Twenty[] = "20";
	char Thirty[] = "30";
	char Forty[] = 	"40";
	char Fifty[] = 	"50";
/*	char Sixty[] =	"60";
	char Seventy[] = "70";
	char Eighty[] =	"80";
	char Ninety[] = "90";
	char Hundred[] ="100";*/
	char Get[] = "get";
	char Set[] = "set";
	char Depart[] = "depart";

//END GLOBALS

	static NODE TO;					// To
	static NODE FROM;				// From
	static ACTION_TYPE ACTION;		// Action
	static PLATFORMS ORIGIN;		// Platform Origin
	static TARGET DESTINATION;		// Destination
	static PLATFORMS PLATFORM;		// Platform Number
	static int WHISHID;				// Whish ID
	static REPLY_TYPE REPLY;		// Reply
	static T_TYPE TRAINTYPE;		// Train Type
	static int SPEED;				// Speed

	static SIGNAL_ID SIGNALID;
	static SIGNAL_COLOUR SIGNALCR;
	static int POINTID;
	static POINT_STATE POINTSTATE;

	static char Zero[] = "000";
	static char xxOne[] = "001";
	static char xxTwo[] = "002";

PROCESS_STATE Receive_Comms()
{	
	typedef enum
	{
		INT_VARS,
		GET_MESSAGE,
		PARSE_MESSAGE,
		CHECK_MSG_TOFROM,
		IS_THIS_FOR_ME,
		ACTION_OR_WHISH,
		ADD_ACTION,
		GET_SET_DEPART,
		IS_MSG_REPLY,
		CREATE_NEW_MSG,
		GET_WISHID,
		SET_TRAIN_AT_PLATFORM,
		WHAT_TYPE_OF_SET,
		CLEAR_MESSAGE,
		SET_SIGNAL_COLOUR,
		SET_POINT_STATE,
		RELAY_MSG
	} COMMS_STATE;

	static COMMS_STATE  Comms_State = INT_VARS;
	PROCESS_STATE ReturnStatus = In_Progress;

	static char MsgString[ 200 ];	// Should be the same as MaxMsgLength
	static char MsgStringCopy[1];

	char ReceivedChar;
	unsigned int MaxMsgLength = 200;

	static unsigned int Marker = 0;
	int DefaultValue = -10;
	unsigned int error;

	char delims[] = "<>";
	char *result = NULL;

	switch ( Comms_State )
	{
		case INT_VARS:

			TO			= DefaultValue;
			FROM		= DefaultValue;
			ACTION		= DefaultValue;
			ORIGIN		= DefaultValue;
			DESTINATION = DefaultValue;
			PLATFORM	= DefaultValue;
			WHISHID		= DefaultValue;
			REPLY		= DefaultValue;
			TRAINTYPE	= DefaultValue;
			SPEED		= DefaultValue;	
			
			SIGNALID	= DefaultValue;
			SIGNALCR	= DefaultValue;
			POINTID		= DefaultValue;
			POINTSTATE	= DefaultValue;

			for ( Marker = 0; Marker < MaxMsgLength; Marker++ )
			{
				MsgString[Marker] = ' ';
			}

			Marker = 0;	

			Comms_State = GET_MESSAGE;

		break;

		case GET_MESSAGE:
			if ( ( DataRdyUSART() == 1 ) && ( BusyUSART() == 0 ) )
			{
				ReceivedChar = getcUSART();

				if ( ( ReceivedChar == NullChar ) || ( ReceivedChar == CRChar) )
				{ // Finish when NULL or carriage return found
				
					if ( Marker == ( MaxMsgLength - 1 ) )
					{
						// The Message is too long
						Comms_State = CLEAR_MESSAGE;
					}
					else
					{
						MsgString[Marker] = NullChar;
						// Now process message

			//			strcpy( MsgStringCopy, MsgString );
						Comms_State = PARSE_MESSAGE;
					}
				}
				else // Not a NULL or Carriage Return.
				{
					if ( Marker == ( MaxMsgLength - 1 ) )
					{
					// The Message is too long.. Do Nothing.
					}
					else
					{
						MsgString[Marker] = ReceivedChar;
						Marker++;
					}
				}
			}
			else
			{
				ReturnStatus = Command_Complete;
			}
		break;

		case PARSE_MESSAGE:
			result = strtok( MsgString, delims );

			while( result != NULL )		// TODO: -------  Must be changed to a IF  -------
			{  
				if ( strcmp( result,ToString ) == 0 )
				{
					DetermineTo( strtok( NULL, delims ) );
					#ifdef DEBUG
					putrsUSART( "E1\r\n" );
					#endif
				}
				else if ( strcmp( result,FromString ) == 0 )
				{
					DetermineFrom( strtok( NULL, delims ) );
					
					#ifdef DEBUG
					putrsUSART( "E2\r\n" );
					#endif
				}
				else if ( strcmp( result,ActionString ) == 0 )
				{
					DetermineAction( strtok( NULL, delims ) );
				}
				else if ( strcmp( result,DestinationString ) == 0 )
				{
					DetermineDestination( strtok( NULL, delims ) );
				}
				else if ( strcmp( result,PlatformString) == 0 )
				{
					DeterminePlatform( strtok( NULL, delims ) );
				}
				else if ( strcmp( result,ReplyString ) == 0 )
				{
					DetermineReply( strtok( NULL, delims ) );
				}
				else if ( strcmp( result,WhishString ) == 0 )
				{
					SetWhish( strtok( NULL, delims ) );
				}
				else if ( strcmp( result,TraintypeString ) == 0 )
				{
					DetermineTrainType( strtok( NULL, delims ) );
				}
				else if ( strcmp( result,SpeedString ) == 0 )
				{
					DetermineSpeed( strtok( NULL, delims ) );
				}
				else if (strcmp ( result,OriginPlatform ) == 0 )
				{
					DetermineOriginPlatform( strtok( NULL, delims ) );
				}
			 
				result = strtok( NULL, delims );
			}	
			Comms_State = CHECK_MSG_TOFROM;
		break;

		case CHECK_MSG_TOFROM:
			
			if ( ( TO == DefaultValue ) || ( FROM == DefaultValue ) )
			{
			//TODO: There are no To or From in the message.
				#ifdef DEBUG
				
				#endif
				if ( BusyUSART() == 0 )
				{
					putrsUSART( "<debug>nomsg</debug>" );
					Comms_State = CLEAR_MESSAGE;
					
				}

			}
			else
			{
				if ( FROM == GetNodeID() )
				{
					#ifdef DEBUG
					putrsUSART( "E27\r\n" );
					#endif
					Comms_State = CLEAR_MESSAGE;
				}
				else
				{
					Comms_State = ACTION_OR_WHISH;
				}
			}
		break;

		case ACTION_OR_WHISH:
			if ( ACTION != DefaultValue )
			{
				#ifdef DEBUG
				putrsUSART( "E4\r\n" );
				#endif	
				Comms_State = ADD_ACTION;
			}
			else
			{
				#ifdef DEBUG
				putrsUSART( "E5\r\n" );
				#endif
				Comms_State = IS_MSG_REPLY;
			}		
		break;

		case ADD_ACTION:

			AddJobAction( TO, FROM, ACTION, PLATFORM, DESTINATION, TRAINTYPE, ORIGIN );
			Comms_State = CLEAR_MESSAGE;

		break;

		case IS_MSG_REPLY:
			if ( REPLY != DefaultValue )
			{
				Comms_State = GET_WISHID;
			}
			else
			{
				Comms_State = CREATE_NEW_MSG;
			}
		break;

		case CREATE_NEW_MSG:

			error = 0;			

			if ( WHISHID == DefaultValue )
			{
				#ifdef DEBUG
				putrsUSART( "E7\r\n" );	
				#endif
				error = 1;
			}
			if ( DESTINATION == DefaultValue )
			{
				#ifdef DEBUG
				putrsUSART( "E8\r\n" );
				#endif
				error = 1;	
			}
			if ( PLATFORM == DefaultValue )
			{
				#ifdef DEBUG
				putrsUSART( "E9\r\n" );
				#endif
				error = 1;
			}
			if ( TRAINTYPE == DefaultValue )
			{
				#ifdef DEBUG
				putrsUSART( "E10\r\n" );
				#endif	
				error = 1;
			}
			if ( SPEED == DefaultValue ) // 16/3/08 No longer required
			{
				#ifdef DEBUG
				putrsUSART( "E11\r\n" );
				#endif
				// error = 1;
				SPEED = 50; // For this version we dont use speed.
			}

			if ( error != 1 )
			{
				AddJob( TO, FROM, DESTINATION, WHISHID, PLATFORM, TRAINTYPE, SPEED, ORIGIN );
				#ifdef DEBUG
				putrsUSART( "E12\r\n" );
				#endif
				Comms_State = CLEAR_MESSAGE;
			}
			else
			{
				Comms_State = CLEAR_MESSAGE;
			}	
		break;

		case GET_WISHID:
			if ( WHISHID == DefaultValue )
			{
				// There is no Whish ID found.
				#ifdef DEBUG
				putrsUSART( "E13\r\n" );
				#endif
			}
			else
			{
				if ( ( TO != GetNodeID() ) && ( FROM != GetNodeID() ) )
				{
					AddJobReply( TO, FROM, WHISHID, REPLY );	// Used only for forwared messages
				}
				else
				{

					// TODO: We must check if the reply is other than 'granted'
					if ( REPLY == GRANTED )
					{
						GrantJob( WHISHID );
						#ifdef DEBUG
						putrsUSART( "E14\r\n" );
						#endif	
					}
				}			
			}
			Comms_State = CLEAR_MESSAGE;
		break;

		case WHAT_TYPE_OF_SET:
			if ( ( PLATFORM 	!= DefaultValue ) &&
				 ( DESTINATION 	!= DefaultValue ) &&
				 ( ORIGIN		!= DefaultValue ) )
			{
				Comms_State = SET_TRAIN_AT_PLATFORM;
			}
			else if ( ( SIGNALID != DefaultValue ) &&
					  ( SIGNALCR != DefaultValue ) )
			{
				Comms_State = SET_SIGNAL_COLOUR;
			}
			else if( ( POINTID 	  != DefaultValue ) &&
					 ( POINTSTATE != DefaultValue ) )
			{
				Comms_State = SET_POINT_STATE;
			}
			else
			{
				Comms_State = CLEAR_MESSAGE;
			}
		break;

		case SET_TRAIN_AT_PLATFORM:
			SetPlatformDestination(ORIGIN, DESTINATION, PLATFORM);
			
			if ( TRAINTYPE	!= DefaultValue )
			{
				SetPlatformTrainType(ORIGIN, TRAINTYPE);
			}
			#ifdef DEBUG
			putrsUSART( "E15\r\n" );
			#endif
			Comms_State = CLEAR_MESSAGE;
		break;

		case SET_SIGNAL_COLOUR:
		break;

		case SET_POINT_STATE:
		break;

		case CLEAR_MESSAGE:
			
			Comms_State = INT_VARS;
			ReturnStatus = Command_Complete;
		break;
	}
return ReturnStatus;
}

static void DetermineTo( char *ToValue )
{
	if ( strcmp( ToValue,Zero ) == 0 )
	{
		TO = SCHEDULER;
	}
	else if ( strcmp( ToValue,xxOne ) == 0 )
	{
		TO = WEYMOUTH_CONTROLLER;
	}
	else if ( strcmp( ToValue,xxTwo ) == 0 )
	{
		TO = LONDON_CONTROLLER;
	}
}

static void DetermineFrom( char *FromValue )
{
	if ( strcmp( FromValue,Zero ) == 0 )
	{
		FROM = SCHEDULER;
	}
	else if ( strcmp( FromValue,xxOne ) == 0 )
	{
		FROM = WEYMOUTH_CONTROLLER;
	}
	else if ( strcmp( FromValue,xxTwo ) == 0 )
	{
		FROM = LONDON_CONTROLLER;
	}
}

static void DetermineAction( char *ActionValue )	// TODO: Depart action
{
//	extern char Get[];
//	extern char Set[];
//	extern char Depart[];

/*	char Get[] = "get";
	char Set[] = "set";
	char Depart[] = "depart";*/

	if ( strcmp( ActionValue,Get ) == 0 )
	{
		ACTION = A_GET;
	}
	else if ( strcmp( ActionValue,Set ) == 0 )
	{
		ACTION = A_SET;
	}
	else if ( strcmp( ActionValue,Depart ) == 0 )
	{
		ACTION = A_DEPART;
	}
}

static void DetermineDestination( char *DestinationValue )
{
	

	if ( strcmp( DestinationValue,Wey ) == 0 )
	{
		DESTINATION = WEYMOUTH;
	}
	else if ( strcmp( DestinationValue,Wat ) == 0 )
	{
		DESTINATION = LONDON;
	}
}

static void DeterminePlatform( char *PlatformValue )
{
	if ( strcmp( PlatformValue,One ) == 0 )
	{
		PLATFORM = PLAT1;
	}
	else if ( strcmp( PlatformValue,Two ) == 0 )
	{
		PLATFORM = PLAT2;
	}
}

static void DetermineOriginPlatform( char *PlatformValue )
{
	if ( strcmp( PlatformValue,One ) == 0 )
	{
		ORIGIN = PLAT1;
	}
	else if ( strcmp( PlatformValue,Two ) == 0 )
	{
		ORIGIN = PLAT2;
	}
}

static void DetermineReply( char *ReplyValue )
{
	char Granted[] = "granted";
	char Denied[] = "denied";
	char True[] = "true";
	char False[] = "false";

	if ( strcmp( ReplyValue,Granted ) == 0 )
	{
		REPLY = GRANTED;
	}
	else if ( strcmp( ReplyValue,Denied ) == 0 )
	{
		REPLY = DENIED;
	}
	else if ( strcmp( ReplyValue,True ) == 0 )
	{
		REPLY = TRUE;
	}
	else if ( strcmp( ReplyValue,False ) == 0 )
	{
		REPLY = FALSE;
	}
}

static void DetermineTrainType( char *TrainTypeString )
{

	
	if ( strcmp( TrainTypeString,Emu2 ) == 0 )
	{
		TRAINTYPE = EMU2;
	}
	else if ( strcmp( TrainTypeString,Emu3 ) == 0 )
	{
		TRAINTYPE = EMU3;
	}
	else if ( strcmp( TrainTypeString,Emu4 ) == 0 )
	{
		TRAINTYPE = EMU4;
	}
	else if ( strcmp( TrainTypeString,Br47c1 ) == 0 )
	{
		TRAINTYPE = BR47C1;
	}
	else if ( strcmp( TrainTypeString,Br47 ) == 0 )
	{
		TRAINTYPE = BR47;
	}
}

static void DetermineSpeed( char *SpeedString )
{
	char Ten[] = 	"10";
	char Twenty[] = "20";
	char Thirty[] = "30";
	char Forty[] = 	"40";
	char Fifty[] = 	"50";
	char Sixty[] =	"60";
	char Seventy[] = "70";
	char Eighty[] =	"80";
	char Ninety[] = "90";
	char Hundred[] ="100";
	
	if ( strcmp( SpeedString,Ten ) == 0 )
	{
		SPEED = 10;
	}
	else if ( strcmp( SpeedString,Twenty ) == 0 )
	{
		SPEED = 20;
	}
	else if ( strcmp( SpeedString,Thirty ) == 0 )
	{
		SPEED = 30;
	}
	else if ( strcmp( SpeedString,Forty ) == 0 )
	{
		SPEED = 40;
	}
	else if ( strcmp( SpeedString,Fifty ) == 0 )
	{
		SPEED = 50;
	}
	else if ( strcmp( SpeedString,Sixty ) == 0 )
	{
		SPEED = 60;
	}
	else if ( strcmp( SpeedString,Seventy ) == 0 )
	{
		SPEED = 70;
	}
	else if ( strcmp( SpeedString,Eighty ) == 0 )
	{
		SPEED = 80;
	}
	else if ( strcmp( SpeedString,Ninety ) == 0 )
	{
		SPEED = 90;
	}
	else if ( strcmp( SpeedString,Hundred ) == 0 )
	{
		SPEED = 100;
	}
}

static void SetWhish( char *WhishString )
{
	WHISHID = atoi( WhishString );	//Converts the string to a int
}
