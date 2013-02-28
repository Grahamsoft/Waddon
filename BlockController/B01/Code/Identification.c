/******************************************************************************
* Filename		:	Indentification.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.0
*					This versions only forms part of University coursework.
* Copyright		:	(c) David A. Graham 2008
* Date			:	March 2008
*					Copyright laws prohibit making additional copies of this 
*					software for any reason.
* Contact		:	david@grahamsoft.co.uk
* Description	:	Change this file to alter the block controller's
*					indentification.
*********************************************************************************/
#include "Identification.h"

TARGET GetMyID( void )
{
	return WEYMOUTH; 
	// Can also be LONDON
}
NODE GetNodeID( void )
{
	return WEYMOUTH_CONTROLLER; 
	// Can also be LONDON_CONTROLLER
}
NODE GetNeighbourNode( void )
{
	return LONDON_CONTROLLER; 
	// Can also be WEYMOUTH_CONTROLLER

}

