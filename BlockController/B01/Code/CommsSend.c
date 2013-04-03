/******************************************************************************
* Filename		:	CommsSend.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	Handles the sending of communications.
*********************************************************************************/
#include "CommsSend.h"
#include "Types.h"
#include "Comms.h"
#include <p18f2550.h>
#include <usart.h>
#include <string.h>
#include <stdio.h>
#include "JobManager.h"
#include "Identification.h"

PROCESS_STATE Send_Comms()
{
	typedef enum
	{
		INT_VARS,
		ANY_UNSENT_JOBS,
		GET_UNSENT_JOB,
		UPDATE_RECORD,
		TO_A,
		TO_B,
		TO_C,
		TO_D,
		TO_E,
		TO_F,
		TO_Fi,
		TO_G,
		TO_H,
		TO_I,
		TO_J,
		FROM_A,
		FROM_B,
		FROM_C,
		FROM_D,
		FROM_E,
		FROM_F,
		FROM_Fi,
		FROM_G,
		FROM_H,
		FROM_I,
		FROM_J,
		JOB_FOUND,
		JOB_A,
		JOB_B,
		JOB_C,
		JOB_D,
		JOB_E,
		JOB_F,
		JOB_G,
		JOB_H,
		ACT_FOUND,
		ACT_A,
		ACT_B,
		ACT_C,
		ACT_D,
		ACT_E,
		ACT_F,
		ACT_G,
		ACT_H,
		IS_MSG_REPLY,
		REPLY_A,
		REPLY_B,
		REPLY_C,
		REPLY_D,
		REPLY_E,
		REPLY_F,
		REPLY_G,
		REPLY_H,
		REPLY_I,
		DES_FOUND,
		DES_A,
		DES_B,
		DES_C,
		DES_D,
		DES_E,
		DES_F,
		DES_G,
		DES_H,
		PLATFORM_FOUND,
		PLAT_A,
		PLAT_B,
		PLAT_C,
		PLAT_D,
		PLAT_E,
		PLAT_F,
		PLAT_G,
		PLAT_H,
		TRAINTYPE_FOUND,
		TTYPE_A,
		TTYPE_B,
		TTYPE_C,
		TTYPE_D,
		TTYPE_E,
		TTYPE_F,
		TTYPE_G,
		TTYPE_H,
		SPEED_FOUND,
		SPEED_A,
		SPEED_B,
		SPEED_C,
		SPEED_D,
		SPEED_E,
		SPEED_F,
		SPEED_G,
		SPEED_H,
		ORGPLAT_FOUND,
		ORGPLAT_A,
		ORGPLAT_B,
		ORGPLAT_C,
		ORGPLAT_D,
		ORGPLAT_E,
		ORGPLAT_F,
		ORGPLAT_G,
		ORGPLAT_H	
	} COMMS_STATE;
	
	static COMMS_STATE  Comms_State = ANY_UNSENT_JOBS;
	PROCESS_STATE ReturnStatus = In_Progress;

	static AJob UnsentJob;
	char slash1		= '<';
	char slash2		= '/';
	char slash3		= '>';
	char Scheduler[] = "000";
	char Weymouth[]	= "001";	//TODO needs to be checked!!!
	char London[]	= "002";
	static char Whishid[4];
	char Reply1[]	= "granted";
	int DefaultValue = -10;

	extern char ToString[];
	extern char FromString[];
	extern char ActionString[];
	extern char DestinationString[];
	extern char PlatformString[];
	extern char ReplyString[];
	extern char WhishString[];
	extern char TraintypeString[];
	extern char SpeedString[];
	extern char OriginPlatform[];
	extern char NullChar;
	extern char CRChar;
	extern char Wey[];
	extern char Wat[];
	extern char One[];
	extern char Two[];

	extern char Emu2[];
	extern char Emu3[];
	extern char Emu4[];
	extern char Br47c1[];
	extern char Br47[];

	extern char Ten[];
	extern char Twenty[];
	extern char Thirty[];
	extern char Forty[];
	extern char Fifty[];
/*	extern char Sixty[];
	extern char Seventy[];
	extern char Eighty[];
	extern char Ninety[];
	extern char Hundred[];*/

	extern char Get[];
	extern char Set[];
	extern char Depart[];

	static unsigned int i;
	static int NumberLength;



if ( BusyUSART() == 0 )
{
	switch ( Comms_State )
	{
		case ANY_UNSENT_JOBS:

			if ( UnSentJobs() == true )
			{
				Comms_State = GET_UNSENT_JOB;
			}
			else
			{
				ReturnStatus = Command_Complete;
			}
		break;

		case GET_UNSENT_JOB:
			UnsentJob = GetUnSentJob();
			Comms_State = TO_A;
		break;
//---------------------------------------------- TO ---------------
		case TO_A:
				putcUSART( slash1 );
				Comms_State = TO_B;	
				i = 0;
			break;
		case TO_B:
			if ( i < 2 )
			{
				putcUSART( ToString[i] );
				i++;
			}
			else if ( i == 2 )
			{
				Comms_State = TO_C;
			}	
			break;
		case TO_C:
				putcUSART( slash3 );
				Comms_State = TO_D;	
				i = 0;
			break;
		case TO_D:
			if( ( UnsentJob.To != GetNodeID() ) && ( UnsentJob.From != GetNodeID() ) )
			{
				switch ( UnsentJob.To )
				{
					case WEYMOUTH_CONTROLLER:
						Comms_State = TO_E;
					break;
					case LONDON_CONTROLLER:
						Comms_State = TO_F;
					break;
					case SCHEDULER:
						Comms_State = TO_Fi;
					break;
				}
			}
			else
			{
				if ( UnsentJob.To == GetNodeID() )
				{
					switch ( UnsentJob.From )
					{
						case WEYMOUTH_CONTROLLER:
							Comms_State = TO_E;
						break;
						case LONDON_CONTROLLER:
							Comms_State = TO_F;
						break;
						case SCHEDULER:
							Comms_State = TO_Fi;
						break;
					}
				}
				else
				{
					switch ( UnsentJob.To )
					{
						case WEYMOUTH_CONTROLLER:
							Comms_State = TO_E;
						break;
						case LONDON_CONTROLLER:
							Comms_State = TO_F;
						break;
						case SCHEDULER:
							Comms_State = TO_Fi;
						break;
					}
				}
			}
			break;
		case TO_E:
			if ( i < 3 )
			{
				putcUSART( Weymouth[i] );
				i++;
			}
			else if ( i == 3 )
			{
				Comms_State = TO_G;
			}
			break;
		case TO_F:
			if ( i < 3 )
			{
				putcUSART( London[i] );
				i++;
			}
			else if  ( i == 3 )
			{
				Comms_State = TO_G;
			}
			break;
		case TO_Fi:
			if ( i < 3 )
			{
				putcUSART( Scheduler[i] );
				i++;
			}
			else if  ( i == 3 )
			{
				Comms_State = TO_G;
			}
			break;
		case TO_G:
				putcUSART( slash1 );
				Comms_State = TO_H;	
				i = 0;
			break;
		case TO_H:
				putcUSART( slash2 );
				Comms_State = TO_I;	
				i = 0;
			break;
		case TO_I:
			if ( i < 2 )
			{
				putcUSART( ToString[i] );
				i++;
			}
			else if ( i == 2 )
			{
				Comms_State = TO_J;
			}
			break;
		case TO_J:
				putcUSART( slash3 );
				Comms_State = FROM_A;	
				i = 0;
			break;
//---------------------------------------------- FROM -------------
		case FROM_A:
				putcUSART( slash1 );
				Comms_State = FROM_B;	
				i = 0;
			break;
		case FROM_B:
			if ( i < 4 )
			{
				putcUSART( FromString[i] );
				i++;
			}
			else if ( i == 4 )
			{
				Comms_State = FROM_C;
			}	
			break;
		case FROM_C:
				putcUSART( slash3 );
				Comms_State = FROM_D;	
				i = 0;
			break;
		case FROM_D:
			if( ( UnsentJob.To != GetNodeID() ) && ( UnsentJob.From != GetNodeID() ) )
			{
				switch ( UnsentJob.From )
				{
					case WEYMOUTH_CONTROLLER:
						Comms_State = FROM_E;
					break;
					case LONDON_CONTROLLER:
						Comms_State = FROM_F;
					break;
					case SCHEDULER:
						Comms_State = FROM_Fi;
					break;
				}
			}
			else
			{
				switch ( GetNodeID() )
				{
					case WEYMOUTH_CONTROLLER:
						Comms_State = FROM_E;
					break;
					case LONDON_CONTROLLER:
						Comms_State = FROM_F;
					break;
					case SCHEDULER:
						Comms_State = FROM_Fi;
					break;
				}
			}
			break;
		case FROM_E:
			if ( i < 3 )
			{
				putcUSART( Weymouth[i] );
				i++;
			}
			else if ( i == 3 )
			{
				Comms_State = FROM_G;
			}
			break;
		case FROM_F:
			if ( i < 3 )
			{
				putcUSART( London[i] );
				i++;
			}
			else if  ( i == 3 )
			{
				Comms_State = FROM_G;
			}
			break;
		case FROM_Fi:
			if ( i < 3 )
			{
				putcUSART( Scheduler[i] );
				i++;
			}
			else if  ( i == 3 )
			{
				Comms_State = FROM_G;
			}
			break;
		case FROM_G:
				putcUSART( slash1 );
				Comms_State = FROM_H;	
				i = 0;
			break;
		case FROM_H:
				putcUSART( slash2 );
				Comms_State = FROM_I;	
				i = 0;
			break;
		case FROM_I:
			if ( i < 4 )
			{
				putcUSART( FromString[i] );
				i++;
			}
			else if ( i == 4 )
			{
				Comms_State = FROM_J;
			}
			break;
		case FROM_J:
				putcUSART( slash3 );
				Comms_State = JOB_FOUND;	
				i = 0;
			break;
//---------------------------------------------- JOB --------------
		case JOB_FOUND :
			if ( UnsentJob.Whishid == DefaultValue ) //DeafultValue, no Des
			{
				//This is a new outgoing message
				Comms_State = ACT_FOUND;
			}
			else
			{
				//This is a reply	
				Comms_State = JOB_A;
			}
			break;
		case JOB_A:
				putcUSART( slash1 );
				Comms_State = JOB_B;	
				i = 0;
			break;
		case JOB_B:
			if (i < 5)
			{
				putcUSART( WhishString[i] );

				i++;
			}
			else if ( i == 5 )
			{
				Comms_State = JOB_C;
			}
			break;
		case JOB_C:
				putcUSART( slash3 );
				Comms_State = JOB_D;	
				i = 0;
				NumberLength = sprintf( Whishid, "%d", UnsentJob.Whishid ); //Convets int to string
			break;
		case JOB_D:
			if ( i < NumberLength )
			{
				putcUSART( Whishid[i] );
				i++;
			}
			else if ( i == NumberLength )
			{
				Comms_State = JOB_E;
			}
			break;
		case JOB_E:
				putcUSART( slash1 );
				Comms_State = JOB_F;	
				i = 0;
			break;
		case JOB_F:
				putcUSART( slash2 );
				Comms_State = JOB_G;	
				i = 0;
			break;
		case JOB_G:
			if ( i < 5 )
			{
				putcUSART( WhishString[i] );
				i++;
			}
			else if ( i == 5 )
			{
				Comms_State = JOB_H;
			}
			break;
		case JOB_H:
				putcUSART( slash3 );
				Comms_State = ACT_FOUND;	
				i = 0;
			break;






//--------------------------------------- Action ------------
		case ACT_FOUND :
			if ( UnsentJob.Action == DefaultValue ) //DeafultValue, no reply
			{
				//This is a new outgoing message
				Comms_State = IS_MSG_REPLY;
			}
			else
			{
				//This is a Action	
				Comms_State = ACT_A;
			}
			break;
		case ACT_A :
				putcUSART( slash1 );
				Comms_State = ACT_B;	
				i = 0;
			break;
		case ACT_B :
			if ( i < 6 )
			{
				putcUSART( ActionString[i] );
				i++;
			}
			else if ( i == 6 )
			{
				Comms_State = ACT_C;
			}	
			break;
		case ACT_C :
				putcUSART( slash3 );
				Comms_State = ACT_D;	
				i = 0;
			break;
		case ACT_D :
			switch ( UnsentJob.Action )
			{
			case A_GET:
				if ( i < 3 )
				{
					putcUSART( Get[i] );
					i++;
				}
				else if ( i == 3 )
				{
					Comms_State = ACT_E;
				}
				break;
			case A_SET:
				if ( i < 3 )
				{
					putcUSART( Set[i] );
					i++;
				}
				else if ( i == 3 )
				{
					Comms_State = ACT_E;
				}
				break;
			case A_DEPART:
				if ( i < 6 )
				{
					putcUSART( Depart[i] );
					i++;
				}
				else if ( i == 6 )
				{
					Comms_State = ACT_E;
				}
				break;
			default:
				Comms_State = ACT_E;
			}
			break;
		case ACT_E :
				putcUSART( slash1 );
				Comms_State = ACT_F;	
				i = 0;
			break;
		case ACT_F :
				putcUSART( slash2 );
				Comms_State = ACT_G;	
				i = 0;
			break;
		case ACT_G :
			if ( i < 6 )
			{
				putcUSART( ActionString[i] );
				i++;
			}
			else if ( i == 6 )
			{
				Comms_State = ACT_H;
			}	
			break;
		case ACT_H :
				putcUSART( slash3 );
				Comms_State = IS_MSG_REPLY;	
				i = 0;
			break;
//---------------------------------------------- Reply ------------
		case IS_MSG_REPLY:
			if ( ( UnsentJob.Reply == DefaultValue ) || ( UnsentJob.Reply == PENDING ) ) //DeafultValue, no reply
			{
				//This is a new outgoing message
				Comms_State = DES_FOUND;
			}
			else
			{
				//This is a reply	
				Comms_State = REPLY_A;
			}
			break;
		case REPLY_A:
				putcUSART( slash1 );
				Comms_State = REPLY_B;	
				i = 0;
			break;
		case REPLY_B:
			if ( i < 5 )
			{
				putcUSART( ReplyString[i] );
				i++;
			}
			else if ( i == 5 )
			{
				Comms_State = REPLY_C;
			}	
			break;
		case REPLY_C:
				putcUSART( slash3 );
				Comms_State = REPLY_D;	
				i = 0;
			break;
		case REPLY_D:
			switch ( UnsentJob.Reply )
			{
				case GRANTED:
					Comms_State = REPLY_E;
				break;
				default:
					Comms_State = REPLY_F;
			}
			break;
		case REPLY_E:
			if ( i < 7 )
			{
				putcUSART( Reply1[i] );
				i++;
			}
			else if ( i == 7 )
			{
				Comms_State = REPLY_F;
			}
			break;
		case REPLY_F:
				putcUSART( slash1 );
				Comms_State = REPLY_G;	
				i = 0;
			break;
		case REPLY_G:
				putcUSART( slash2 );
				Comms_State = REPLY_H;	
				i = 0;
			break;
		case REPLY_H:
			if ( i < 5 )
			{
				putcUSART( ReplyString[i] );
				i++;
			}
			else if ( i == 5 )
			{
				Comms_State = REPLY_I;
			}
			break;
		case REPLY_I:
				putcUSART( slash3 );
				Comms_State = UPDATE_RECORD;	
				i = 0;
			break;
//--------------------------------------- Destination ------------
		case DES_FOUND :
			if ( UnsentJob.Destination == DefaultValue ) //DeafultValue, no reply
			{
				//This is a new outgoing message
				Comms_State = PLATFORM_FOUND;
			}
			else
			{
				//This is a reply	
				Comms_State = DES_A;
			}
			break;
		case DES_A :
				putcUSART( slash1 );
				Comms_State = DES_B;	
				i = 0;
			break;
		case DES_B :
			if ( i < 11 )
			{
				putcUSART( DestinationString[i] );
				i++;
			}
			else if ( i == 11 )
			{
				Comms_State = DES_C;
			}	
			break;
		case DES_C :
				putcUSART( slash3 );
				Comms_State = DES_D;	
				i = 0;
			break;
		case DES_D :
			switch ( UnsentJob.Destination )
			{
			case WEYMOUTH:
				if ( i < 3 )
				{
					putcUSART( Wey[i] );
					i++;
				}
				else if ( i == 3 )
				{
					Comms_State = DES_E;
				}
				break;
			case LONDON:
				if ( i < 3 )
				{
					putcUSART( Wat[i] );
					i++;
				}
				else if ( i == 3 )
				{
					Comms_State = DES_E;
				}
				break;
			default:
				Comms_State = DES_E;
			}
			break;
		case DES_E :
				putcUSART( slash1 );
				Comms_State = DES_F;	
				i = 0;
			break;
		case DES_F :
				putcUSART( slash2 );
				Comms_State = DES_G;	
				i = 0;
			break;
		case DES_G :
			if ( i < 11 )
			{
				putcUSART( DestinationString[i] );
				i++;
			}
			else if ( i == 11 )
			{
				Comms_State = DES_H;
			}	
			break;
		case DES_H :
				putcUSART( slash3 );
				Comms_State = PLATFORM_FOUND;	
				i = 0;
			break;
//--------------------------------------- Platform ----------------
		case PLATFORM_FOUND :
			if ( UnsentJob.Platform == DefaultValue ) //DeafultValue, no Des
			{
				//This is a new outgoing message
				Comms_State = TRAINTYPE_FOUND;
			}
			else
			{
				//This is a reply	
				Comms_State = PLAT_A;
			}
			break;
		case PLAT_A :
				putcUSART( slash1 );
				Comms_State = PLAT_B;	
				i = 0;
			break;
		case PLAT_B :
			if ( i < 8 )
			{
				putcUSART( PlatformString[i] );
				i++;
			}
			else if ( i == 8 )
			{
				Comms_State = PLAT_C;
			}	
			break;
		case PLAT_C :
				putcUSART( slash3 );
				Comms_State = PLAT_D;	
				i = 0;
			break;
		case PLAT_D :
			switch ( UnsentJob.Platform )
			{
			case PLAT1 :			
					putcUSART( One[0] );
					Comms_State = PLAT_E;	
					i = 0;
				break;

			case PLAT2 :
					putcUSART( Two[0] );
					Comms_State = PLAT_E;	
					i = 0;
				break;
			default:
				Comms_State = PLAT_E;
			}
		case PLAT_E :
				putcUSART( slash1 );
				Comms_State = PLAT_F;	
				i = 0;
			break;
		case PLAT_F :
				putcUSART( slash2 );
				Comms_State = PLAT_G;	
				i = 0;
			break;
		case PLAT_G :
			if ( i < 8 )
			{
				putcUSART( PlatformString[i] );
				i++;
			}
			else if ( i == 8 )
			{
				Comms_State = PLAT_H;
			}	
			break;
		case PLAT_H :
				putcUSART( slash3 );
				Comms_State = TRAINTYPE_FOUND;	
				i = 0;
			break;
//--------------------------------------- TrainType ----------------
		case TRAINTYPE_FOUND :
			if ( UnsentJob.TrainType == DefaultValue ) //DeafultValue, no Des
			{
				//This is a new outgoing message
				Comms_State = SPEED_FOUND;
			}
			else
			{
				//This is a Train Type
				Comms_State = TTYPE_A;
			}
			break;
		case TTYPE_A : 
				putcUSART( slash1 );
				Comms_State = TTYPE_B;	
				i = 0;
			break;
		case TTYPE_B :
			if ( i < 9 )
			{
				putcUSART( TraintypeString[i] );
				i++;
			}
			else if ( i == 9 )
			{
				Comms_State = TTYPE_C;
			}	
			break;
		case TTYPE_C :
				putcUSART( slash3 );
				Comms_State = TTYPE_D;	
				i = 0;
			break;
		case TTYPE_D :
			//TODO Needs to be expanded to output more types
			switch ( UnsentJob.TrainType )
			{
			case EMU2:
				if ( i < 4 )
				{
					putcUSART( Emu2[i] );
					i++;
				}
				else if ( i == 4 )
				{
					Comms_State = TTYPE_E;
				}
				break;
			case BR47C1:
				if ( i < 6 )
				{
					putcUSART( Br47c1[i] );
					i++;
				}
				else if ( i == 6 )
				{
					Comms_State = TTYPE_E;
				}
				break;
			case BR47:
				if ( i < 4 )
				{
					putcUSART( Br47[i] );
					i++;
				}
				else if ( i == 4 )
				{
					Comms_State = TTYPE_E;
				}
				break;
			default:
				Comms_State = TTYPE_E;
			}
			break;
		case TTYPE_E :
				putcUSART( slash1 );
				Comms_State = TTYPE_F;	
				i = 0;
			break;
		case TTYPE_F :
				putcUSART( slash2 );
				Comms_State = TTYPE_G;	
				i = 0;
			break;
		case TTYPE_G :
			if ( i < 9 )
			{
				putcUSART( TraintypeString[i] );
				i++;
			}
			else if ( i == 9 )
			{
				Comms_State = TTYPE_H;
			}	
			break;
		case TTYPE_H :
				putcUSART( slash3 );
				Comms_State = SPEED_FOUND;	
				i = 0;
			break;
//--------------------------------------- Speed ----------------
		case SPEED_FOUND :
			if ( UnsentJob.Speed == DefaultValue ) //DeafultValue, no Des
			{
				//This is a new outgoing message
				Comms_State = ORGPLAT_FOUND;
			}
			else
			{
				//This is a Train Type
				Comms_State = SPEED_A;
			}
			break;
		case SPEED_A :
				putcUSART( slash1 );
				Comms_State = SPEED_B;	
				i = 0;
			break;
		case SPEED_B :
			if ( i < 5 )
			{
				putcUSART( SpeedString[i] );
				i++;
			}
			else if ( i == 5 )
			{
				Comms_State = SPEED_C;
			}	
			break;
		case SPEED_C :
				putcUSART( slash3 );
				Comms_State = SPEED_D;	
				i = 0;
			break;
		case SPEED_D :
			Comms_State = SPEED_E;
		case SPEED_E :
				putcUSART( slash1 );
				Comms_State = SPEED_F;	
				i = 0;
			break;
		case SPEED_F :
				putcUSART( slash2 );
				Comms_State = SPEED_G;	
				i = 0;
			break;
		case SPEED_G :
			if ( i < 5 )
			{
				putcUSART( SpeedString[i] );
				i++;
			}
			else if ( i == 5 )
			{
				Comms_State = SPEED_H;
			}	
			break;
		case SPEED_H :
				putcUSART( slash3 );
				Comms_State = ORGPLAT_FOUND;	
				i = 0;
			break;		
//--------------------------------------- OriginPlatform ----------------
		case ORGPLAT_FOUND :
			if ( UnsentJob.Origin == DefaultValue ) //DeafultValue, no Des
			{
				//This is a new outgoing message
				Comms_State = UPDATE_RECORD;
			}
			else
			{
				//This is a reply	
				Comms_State = ORGPLAT_A;
			}
			break;
		case ORGPLAT_A :
				putcUSART( slash1 );
				Comms_State = ORGPLAT_B;	
				i = 0;
			break;
		case ORGPLAT_B :
			if ( i < 14 )
			{
				putcUSART( OriginPlatform[i] );
				i++;
			}
			else if ( i == 14 )
			{
				Comms_State = ORGPLAT_C;
			}	
			break;
		case ORGPLAT_C :
				putcUSART( slash3 );
				Comms_State = ORGPLAT_D;	
				i = 0;
			break;
		case ORGPLAT_D :
			switch ( UnsentJob.Origin )
			{
			case PLAT1 :			
					putcUSART( One[0] );
					Comms_State = ORGPLAT_E;	
					i = 0;
				break;

			case PLAT2 :
					putcUSART( Two[0] );
					Comms_State = ORGPLAT_E;	
					i = 0;
				break;
			default:
				Comms_State = ORGPLAT_E;
			}
		case ORGPLAT_E :
				putcUSART( slash1 );
				Comms_State = ORGPLAT_F;	
				i = 0;
			break;
		case ORGPLAT_F :
				putcUSART( slash2 );
				Comms_State = ORGPLAT_G;	
				i = 0;
			break;
		case ORGPLAT_G :
			if ( i < 14 )
			{
				putcUSART( OriginPlatform[i] );
				i++;
			}
			else if ( i == 14 )
			{
				Comms_State = ORGPLAT_H;
			}	
			break;
		case ORGPLAT_H :
				putcUSART( slash3 );
				Comms_State = UPDATE_RECORD;	
				i = 0;
			break;
		case UPDATE_RECORD:
			putcUSART( NullChar ); // NULL CHAR
			SetJobSent( UnsentJob.Whishid ); //updates records that this job has been sent
			Comms_State = ANY_UNSENT_JOBS;
			ReturnStatus = Command_Complete;
		break;
	}
}

return ReturnStatus;
}		