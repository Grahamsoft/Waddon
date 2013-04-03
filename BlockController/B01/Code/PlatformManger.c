/******************************************************************************
* Filename		:	PlatformManger.c (Spelt wrong i know..)
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
* Description	:	Keeps the states of the platfroms.
*********************************************************************************/

#include <string.h>
#include "Types.h"
#include "PlatformManger.h"
#include "JobManager.h"
#include "Identification.h"
#include <usart.h>
#include "H/Sensors.h"

static int DefaultValue = -10;

static PlatformRecord PlatformTable[2];
static int NoPlatforms = 2;

void ClearPlatforms( void )
{
//------------------------------------------------------------------------------*/
// Function: Initialises the Platform Table.
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < NoPlatforms;i++)
	{
		PlatformTable[i].Empty			= true;
		PlatformTable[i].DepartNow		= false;
		PlatformTable[i].Platform		= DefaultValue;
		PlatformTable[i].Destination	= DefaultValue;
		PlatformTable[i].TrainType		= DefaultValue;
		PlatformTable[i].RapAroundReq	= false;
	}
	PlatformTable[0].MyNumber			= PLAT1;
	PlatformTable[1].MyNumber			= PLAT2;

}
void ClearPlatform( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Sets that there is no train at platform 'WhichPlatform'.
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( PlatformTable[i].MyNumber == WhichPlatform )
		PlatformTable[i].Empty			= true;
		PlatformTable[i].DepartNow		= false;
		PlatformTable[i].Platform		= DefaultValue;
		PlatformTable[i].Destination	= DefaultValue;
		PlatformTable[i].TrainType		= DefaultValue;
		PlatformTable[i].RapAroundReq	= false;
	}
}

void SetPlatformDestination( PLATFORMS WhichPlatform, TARGET TheDestination, PLATFORMS DesPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Sets the destination of the train at platform 'WhichPlatfrom'.
//------------------------------------------------------------------------------*/

	int i;

	if ( PlatformAvailable( WhichPlatform ) == true )
	{
		ReCheckPlatform( WhichPlatform );
	}

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( ( PlatformTable[i].Empty == false ) &&
			 ( PlatformTable[i].MyNumber == WhichPlatform ) )
		{
			PlatformTable[i].Platform		= DesPlatform;
			PlatformTable[i].Destination	= TheDestination;
			#ifdef DEBUG
			putrsUSART( "E34\r\n" );
			#endif	
		}
	}
}

void SetPlatformTrainType( PLATFORMS WhichPlatform, T_TYPE TheTraintype )
{
//------------------------------------------------------------------------------*/
// Function: Sets the Train Type of the train at platform 'WhichPlatfrom'.
//------------------------------------------------------------------------------*/

	int i;

	if ( PlatformAvailable( WhichPlatform ) == true )
	{
		ReCheckPlatform( WhichPlatform );
	}

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( ( PlatformTable[i].Empty == false ) &&
			 ( PlatformTable[i].MyNumber == WhichPlatform ) )
		{
			PlatformTable[i].TrainType		= TheTraintype;
			#ifdef DEBUG
			putrsUSART( "E35\r\n" );
			#endif
		}
	}
}

void DepartPlatform ( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Commands the train at platform 'WhichPlatfrom' to depart.
//------------------------------------------------------------------------------*/

	int i;
	NODE TO;
	static int jobid = 1000;	//TODO 

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( ( PlatformTable[i].Empty		== false ) &&
			 ( PlatformTable[i].MyNumber	== WhichPlatform ) &&
			 ( PlatformTable[i].Destination	!= DefaultValue ) &&
			 ( PlatformTable[i].Platform	!= DefaultValue ) )
		{
			PlatformTable[i].DepartNow		= true;
				
			switch( GetNodeID() )
			{
				case WEYMOUTH_CONTROLLER :
				TO = LONDON_CONTROLLER;
				break;
				case LONDON_CONTROLLER :
				TO = WEYMOUTH_CONTROLLER;
				break;
			}
			#ifdef DEBUG
			putrsUSART( "E36\r\n" );
			#endif
			AddJob( TO, GetNodeID(), PlatformTable[i].Destination, GetNewJobID(), PlatformTable[i].Platform, PlatformTable[i].TrainType, 60, PlatformTable[i].MyNumber );
			jobid++;
		}
	}
}

void SetPlatformTrainPresent( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Sets that there is a train present at platfrom 'WhichPlatform'.
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( PlatformTable[i].MyNumber == WhichPlatform )
		{
			PlatformTable[i].Empty = false;
		}
	}
}

BOOLEAN PlatformAvailable ( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Returns if a platfrom is empty.
//------------------------------------------------------------------------------*/
	int i;
	BOOLEAN ToReturn = false;

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( PlatformTable[i].MyNumber == WhichPlatform )
		{
			switch ( PlatformTable[i].Empty )
			{
			case true :
				ToReturn = true;
				break;
			case false :
				ToReturn = false;
				break;
			}
		break;
		}
	}
return ToReturn;
}

void ToggleRapAround ( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Sets 'rap around' is in progress.
//------------------------------------------------------------------------------*/
	int i;

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( PlatformTable[i].MyNumber == WhichPlatform )
		{
			switch( PlatformTable[i].RapAroundReq )
			{
			case true :
				PlatformTable[i].RapAroundReq  = false;
				break;
			case false :
				PlatformTable[i].RapAroundReq  = true;
				break;
			}
		}
	}
}

BOOLEAN doRapAround ( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Find out if a 'rap around' is required.
//------------------------------------------------------------------------------*/
	BOOLEAN Returning = false;
	int i;

	for(i = 0;i < NoPlatforms;i++)
	{
		if ( PlatformTable[i].MyNumber == WhichPlatform )
		{
			switch( PlatformTable[i].RapAroundReq )
			{
			case true :
				Returning = true;
				break;
			case false :
				Returning = false;
				break;
			}
		}
	}
return Returning;
}

void ReCheckPlatform ( PLATFORMS WhichPlatform )
{
//------------------------------------------------------------------------------*/
// Function: Rechecks if a train can be found at the platforms.
//------------------------------------------------------------------------------*/
	switch ( WhichPlatform )
	{
	case PLAT1 :
		if ( TrainPresent( 2 ) == true )
		{
			// Is there a train at platform 1?
			SetPlatformTrainPresent( PLAT1 );
		}
		break;
	case PLAT2 :
		if ( TrainPresent( 5 ) == true )		
		{
			// Is there a train at platform 2?
			SetPlatformTrainPresent( PLAT2 );
		}
		break;
	}
}
