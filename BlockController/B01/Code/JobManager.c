/******************************************************************************
* Filename		:	JobManager.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	The JobManager stores the Jobs that are either:
*					-> Not sent and will be next the CommsManager is Called.
*						-> And this also consists of new Jobs from this
*						   BlockController.
*						-> And replys to other BlockController Jobs
*					-> Sent and Waiting for a reply.
*********************************************************************************/

#include <string.h>
#include "Types.h"
#include "JobManager.h"
#include "PlatformManger.h"
#include "Identification.h"
#include <usart.h>
static AJob JobTable[6];
static OverrideRecord OverrideRequest;
static int DefaultValue = -10;
static char ReplyNull[] = "          ";
static int RecordCount = 6;

int FindEmptyRecord( void )
{
//------------------------------------------------------------------------------*/
// Function: Returns the location of empty record in the JobTable[].
//------------------------------------------------------------------------------*/

	//TODO Fix this so is a empty record isnt found - do something
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ( JobTable[i].Empty == true )
		{
			break;
		}		
	}
return i;
}

void ClearJobs( void )
{
//------------------------------------------------------------------------------*/
// Function: Initialises the Message Table.
//------------------------------------------------------------------------------*/
	static int i;

	for(i = 0;i < RecordCount;i++)
	{
		JobTable[i].Empty		= true;
		JobTable[i].Sent		= false;
		JobTable[i].To			= DefaultValue;
		JobTable[i].From		= DefaultValue;
		JobTable[i].Destination = DefaultValue;
		JobTable[i].Platform	= DefaultValue;
		JobTable[i].TrainType	= DefaultValue;
		JobTable[i].Speed		= DefaultValue;
		JobTable[i].Reply		= DefaultValue;
		JobTable[i].Whishid		= DefaultValue;
		JobTable[i].Origin		= DefaultValue;
		JobTable[i].Action		= DefaultValue;
	}
}

void AddJob( NODE TO, NODE FROM, TARGET DESTINATION, int WHISHID, PLATFORMS PLATFORM, T_TYPE TRAINTYPE, int SPEED, PLATFORMS ORIGIN )
{
//------------------------------------------------------------------------------*/
// Function: Adds a new Job to the Jobs List.
//------------------------------------------------------------------------------*/
	int RN; //RN Record Number

	RN = FindEmptyRecord(); 

	JobTable[RN].Empty			= false;
	JobTable[RN].Sent			= false;
	JobTable[RN].To				= TO;
	JobTable[RN].From			= FROM;
	JobTable[RN].Destination	= DESTINATION;
	JobTable[RN].Platform		= PLATFORM;
	JobTable[RN].TrainType		= TRAINTYPE;
	JobTable[RN].Speed			= SPEED;
	JobTable[RN].Reply			= PENDING;
	JobTable[RN].Whishid		= WHISHID;
	JobTable[RN].Origin			= ORIGIN;
	
	if ( WHISHID == 0 ) // The job has been create by this Block Controller.
	{
		JobTable[RN].Whishid		= GetNewJobID();
	}
	
	#ifdef DEBUG
	//	ERROR CHECKING			
	if ( JobTable[RN].To == DefaultValue ) { putrsUSART( "E18\r\n" ); }
	if ( JobTable[RN].From == DefaultValue ) { putrsUSART( "E19\r\n" ); }
	if ( JobTable[RN].Destination == DefaultValue ) { putrsUSART( "E20\r\n" ); }
	if ( JobTable[RN].Platform == DefaultValue ) { putrsUSART( "E21\r\n" ); }
	if ( JobTable[RN].TrainType == DefaultValue ) { putrsUSART( "E22\r\n" ); }
	if ( JobTable[RN].Speed == DefaultValue ) { putrsUSART( "E23\r\n" ); }
	if ( JobTable[RN].Whishid == DefaultValue ) { putrsUSART( "E24\r\n" ); }
	// ERROR CHECKING ENDS
	#endif

	if ( JobTable[RN].To == GetNodeID() ) // As this has been recieved it dosn't need sending
	{
		JobTable[RN].Sent = true;
	}
	if ( ( JobTable[RN].To != GetNodeID() ) && ( JobTable[RN].From != GetNodeID() ) )
	{
		JobTable[RN].Reply = DefaultValue;	
		// Prevents this msg being granted. This msg will forwarded on.
	}
}

void AddJobReply( NODE TO, NODE FROM, int WHISHID, REPLY_TYPE REPLY )
{
//------------------------------------------------------------------------------*/
// Function: Adds a new Job Reply to the Jobs List.
//------------------------------------------------------------------------------*/
	int RN; //RN Record Number

	RN = FindEmptyRecord(); 

	JobTable[RN].Empty			= false;
	JobTable[RN].Sent			= false;
	JobTable[RN].To				= TO;
	JobTable[RN].From			= FROM;
	JobTable[RN].Reply			= REPLY;
	JobTable[RN].Whishid		= WHISHID;
}

void AddJobAction( NODE TO, NODE FROM, ACTION_TYPE ACTION, PLATFORMS PLATFORM, TARGET DESTINATION, T_TYPE TRAINTYPE, PLATFORMS ORIGIN )
{
//------------------------------------------------------------------------------*/
// Function: Adds a new Job to the Jobs List with Action values.
//------------------------------------------------------------------------------*/
	int RN; //RN Record Number

	RN = FindEmptyRecord(); 

	if ( TO != GetNodeID() )
	{
		JobTable[RN].Empty		= false;
		JobTable[RN].Sent		= false;
		JobTable[RN].To			= TO;
		JobTable[RN].From		= FROM;
		JobTable[RN].Destination = DESTINATION;
		JobTable[RN].Platform	= PLATFORM;
		JobTable[RN].TrainType	= TRAINTYPE;
		JobTable[RN].Origin		= ORIGIN;
		JobTable[RN].Action		= ACTION;
	}
	else
	{

		switch( ACTION )
		{
		case A_GET:
			// This was never implemented...
			// TODO: GetTrainDector( Number );
			break;
		case A_SET:
			if ( ( PLATFORM 	!= DefaultValue ) &&
				 ( DESTINATION 	!= DefaultValue ) &&
				 ( ORIGIN		!= DefaultValue ) )
			{
				SetPlatformDestination( ORIGIN, DESTINATION, PLATFORM );

				if ( TRAINTYPE	!= DefaultValue )
				{
					SetPlatformTrainType( ORIGIN, TRAINTYPE );
				}
			}
			break;
		case A_DEPART:
			if ( ORIGIN	!= DefaultValue )
			{
				DepartPlatform ( ORIGIN );
				#ifdef DEBUG
				putrsUSART( "E6\r\n" );
				#endif
			}
		break;
		}	
	}
}

void RemoveJob( int WHISHID )
{
//------------------------------------------------------------------------------*/
// Function: Removes a Job from the Jobs List defined by 'WhishID'.
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ( JobTable[i].Whishid == WHISHID )
		{
			JobTable[i].Empty		= true;
			JobTable[i].Sent		= false;
			JobTable[i].To			= DefaultValue;
			JobTable[i].From		= DefaultValue;
			JobTable[i].Destination = DefaultValue;
			JobTable[i].Platform	= DefaultValue;
			JobTable[i].TrainType	= DefaultValue;
			JobTable[i].Speed		= DefaultValue;
			JobTable[i].Reply		= DefaultValue;
			JobTable[i].Whishid		= DefaultValue;
			JobTable[i].Origin		= DefaultValue;
			JobTable[i].Action		= DefaultValue;
			break;
		}		
	}
} 

BOOLEAN JobReady( void )
{
//------------------------------------------------------------------------------*/
// Function: Searches to see if there are any Jobs that have a 'Reply' of Granted.
//------------------------------------------------------------------------------*/
	int found = 0;
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ( JobTable[i].Reply == GRANTED ) 
		{
			found = 1;
			break;
		}		
	}
	if ( found == 0 )
	{
		return false;
	}
	else
	{
		return true;
	}
}

void GrantJob( int WHISHID )
{
//------------------------------------------------------------------------------*/
// Function: Set the 'Reply' to any waiting job to 'Granted'.
//------------------------------------------------------------------------------*/
	int i;
	// TODO: Make sure the platform is empty before granting a movemnt.
	for(i = 0;i < RecordCount;i++)
	{
		if ( JobTable[i].Whishid == WHISHID )
		{
			JobTable[i].Reply = GRANTED;
			#ifdef DEBUG
			putrsUSART( "E33\r\n" );
			#endif
			break;
		}		
	}
}

void GrantAnyJob( void )
{
//------------------------------------------------------------------------------*/
// Function: Grants any job that has been sent by another node that is waiting
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ( ( JobTable[i].To	 == GetNodeID() ) &&
			 ( JobTable[i].Reply == PENDING ) &&
			 ( JobTable[i].Sent  == true) )
		{
			if ( PlatformAvailable( JobTable[i].Platform ) == true )
			{
				JobTable[i].Reply = GRANTED;
				JobTable[i].Sent  = false;
				break;
			}
			else
			{
				if( JobTable[i].TrainType == BR47 ) //This is a train doing a rap around
				{
					JobTable[i].Reply = GRANTED;
					JobTable[i].Sent  = false;
				}
			}
		}		
	}
}

AJob GetJob( void )
{
//------------------------------------------------------------------------------*/
// Function: Returns a Job that has a reply of 'Granted'.
//------------------------------------------------------------------------------*/
	AJob MsgRec;
	int RN;
	int found = 0;
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ( JobTable[i].Reply == GRANTED )
		{
			RN = i;
			found = 1;
			break;
		}		
	}

	return JobTable[RN];
}

BOOLEAN UnSentJobs( void )
{
//------------------------------------------------------------------------------*/
// Function: Finds any jobs that havn't been sent
//------------------------------------------------------------------------------*/
	int i;
	BOOLEAN found = false;

	for(i = 0;i < RecordCount;i++)
	{
		if ((	JobTable[i].Sent 	== false	  ) &&
			(	JobTable[i].Empty	== false	  ))
		{
			found = true;
			#ifdef DEBUG
			putrsUSART( "E26\r\n" );
			#endif
			break;
		}		
	}
return found;
}

AJob GetUnSentJob( void )
{
//------------------------------------------------------------------------------*/
// Function: Gets a Job record that hasn't been sent
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ((	JobTable[i].Sent 	== false	  ) &&
			(	JobTable[i].Empty	== false	  ))
		{
			break;
		}		
	}

	return JobTable[i];
}

void SetJobSent( int WHISHID )
{
//------------------------------------------------------------------------------*/
// Function: Updates a record of the JobTable that it has been sent.
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < RecordCount;i++)
	{
		if ( JobTable[i].Whishid == WHISHID )
		{
			JobTable[i].Sent = true;

			if( ( JobTable[i].To != GetNodeID() ) && ( JobTable[i].From != GetNodeID() ) )
			{
				RemoveJob( JobTable[i].Whishid );
			}
			break;
		}		
	}
}

int GetNewJobID( void )
{
//------------------------------------------------------------------------------*/
// Function: Generates a new Job ID number.
//------------------------------------------------------------------------------*/
	
	int startvalue;
	static int andadd = 0;
	NODE myNode = GetNodeID();

	switch ( myNode )
	{
		case LONDON_CONTROLLER:
			startvalue = 1000;
			break;
		case WEYMOUTH_CONTROLLER:
			startvalue = 2000;
			break;
		default:
			startvalue = 5000;		
	}
	andadd = andadd + 1;

	startvalue = startvalue + andadd;

	return startvalue;
}
	
