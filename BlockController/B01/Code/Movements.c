/******************************************************************************
* Filename		:	Movements.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	-> While no movements are in progress this checks for any
*					   jobs that have been granted by another Block Controller
*					   and sets up the movement routine if one if found. (Away)
*					-> When no granted Jobs are found it grants any jobs waiting
*					   to be granted by this Block Controller. Then sets up the 
*					   movement routine. (Home)
*					The Movement Routines are:
*					A. It takes the train away out of platform 1.
*					B. It takes the train away out of platform 2.
*					C. It takes the train home into platform 1, a new job is
*					   created if this is part of a 'rap around'.
*					D. It takes the train away out of platform 1 BUT via the
*					   siding. This is a 'rap around' routine.
*					E. It takes the train home to platform 2.
*********************************************************************************/
#include <string.h>
#include "Types.h"
#include "Movements.h"
#include "MovementRoutineA.h"
#include "MovementRoutineB.h"
#include "MovementRoutineC.h"
#include "MovementRoutineD.h"
#include "MovementRoutineE.h"
#include "JobManager.h"
#include "PlatformManger.h"
#include "Identification.h"
#include <usart.h>

void Manage_Movements( void )
{
	static AJob Job;
	typedef enum
	{
		NO_MOVEMENTS_IN_PROGRESS,
		MOVEMENT_IN_PROGRESS,
		TRAIN_TO_HOME,
		TRAIN_TO_AWAY,
		TRAIN_AWAY_PLATFORM1,
		ROUTINE_A,
		ROUTINE_B,
		ROUTINE_C,
		ROUTINE_C_RAP_AROUND_JOB,
		ROUTINE_D,
		ROUTINE_E,
		REMOVE_JOB
	} MOVEMENT_STATE;

	static MOVEMENT_STATE MovementState = NO_MOVEMENTS_IN_PROGRESS;

	switch ( MovementState )
	{
		case NO_MOVEMENTS_IN_PROGRESS :
	
		// * Grant any Whishes for 'ME' ( And set up Routine )
		// OR
		// * Check pending Whishes from 'ME' ( If granted do routine )
			if ( JobReady() == true )
			{
				MovementState = MOVEMENT_IN_PROGRESS;
			}
			else 
			{
				GrantAnyJob();
			}

		break;
		case MOVEMENT_IN_PROGRESS :
		
			Job = GetJob();
			#ifdef DEBUG
			putrsUSART( "E17\r\n" );
			#endif
		

			if ( Job.Destination == GetMyID() )
			{
				if ( doRapAround( PLAT1 ) == true )
				{		
					MovementState = TRAIN_TO_AWAY;
				}
				else
				{
					MovementState = TRAIN_TO_HOME;
				}
			}
			else //AWAY
			{
				if ( Job.To == GetNodeID() )
				{
					MovementState = TRAIN_TO_HOME; // Has been sent to this block but not for this block.
				}
				else
				{
					MovementState = TRAIN_TO_AWAY;
				}
			}

		break;
		case TRAIN_TO_HOME :
			// What platform does the train want to go to?
			if ( Job.Platform == PLAT1 )
			{
				SetPlatformTrainPresent( PLAT1 );
				SetPlatformTrainType( PLAT1, Job.TrainType );
				if ( Job.TrainType == BR47C1 )
				{
					ToggleRapAround ( PLAT1 ); //Rap Around Required
				}
				if ( Job.TrainType == BR47 ) //The train will couple upto the carriage
				{
					SetPlatformTrainType( PLAT1, BR47C1 ); // It is now a BR47C1
				}
				MovementState = ROUTINE_C;
			}
			else if ( Job.Platform == PLAT2 )
			{
				SetPlatformTrainPresent( PLAT2 );
				SetPlatformTrainType( PLAT2, Job.TrainType );
				MovementState = ROUTINE_E;
			}

		break;
		case TRAIN_TO_AWAY :
			// What platform is the train coming from?
			if ( Job.Origin == PLAT1 )
			{
				MovementState = TRAIN_AWAY_PLATFORM1;
			}
			else //Platform 2
			{
				ClearPlatform( PLAT2 );
				MovementState = ROUTINE_B;
			}
		break;

		case TRAIN_AWAY_PLATFORM1 :
			// IS this a two ended two
			if ( doRapAround( PLAT1 ) == true )
			{
				SetPlatformTrainType( PLAT1, C1 ); //A Carriage has been left at the platform
				ToggleRapAround ( PLAT1 ); //Doing Rap Around so  dont flag it anymore
				MovementState = ROUTINE_D;
			}
			else
			{	
				ClearPlatform( PLAT1 );
				MovementState = ROUTINE_A;
			}
			break;

		case ROUTINE_A :
			if ( RoutineA() == Command_Complete )
			{
				MovementState = REMOVE_JOB;
			}
		break;

		case ROUTINE_B :
			if ( RoutineB() == Command_Complete )
			{
				MovementState = REMOVE_JOB;
			}
		break;

		case ROUTINE_C :

			if ( RoutineC() == Command_Complete )
			{
				MovementState = ROUTINE_C_RAP_AROUND_JOB;
			}
		break;
	
		case ROUTINE_C_RAP_AROUND_JOB :

			if ( doRapAround( PLAT1 ) == true )
			{
				// The train need to be rapped around as it is a single ended train
				AddJob( GetNeighbourNode(), GetNodeID(), GetMyID(), 0, PLAT1, BR47, 10, PLAT1 );			
			}
			if ( GetMyID() != Job.Destination ) 
			{			
				// The train has come to this block but it has not finished its journey.
				// The train needs to be moved out of this block as its destination is not this block. (Normally in a rap around situation)
				AddJob( GetNeighbourNode(), GetNodeID(), Job.Destination, 0, PLAT1, Job.TrainType, 10, PLAT1 );
			}
			MovementState = REMOVE_JOB;
		break;

		case ROUTINE_D :
			if ( RoutineD() == Command_Complete )
			{
				MovementState = REMOVE_JOB;
			}
		break;

		case ROUTINE_E :
			if ( RoutineE() == Command_Complete )
			{
				MovementState = REMOVE_JOB;
			}
		break;
		
		case REMOVE_JOB :
			#ifdef DEBUG
			putrsUSART( "E32\r\n" );
			#endif
			RemoveJob( Job.Whishid );
			MovementState = NO_MOVEMENTS_IN_PROGRESS;
		break;
	}
}