/******************************************************************************
* Filename		:	Indentification.c
* Part of		:	Waddon - Modular Railway Control
* Version		:	1.1
* Copyright		:	(c) David A. Graham 2013
* Date			:	April 2013
* Contact		:	GitHub@grahamsoft.co.uk
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

