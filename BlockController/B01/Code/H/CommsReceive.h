#include "Types.h"

PROCESS_STATE Receive_Comms( void );
void Echo_String( void );
static void DetermineTo( char *ToString );
static void DetermineFrom( char *FromString );
static void DetermineAction( char *ActionString );
static void DetermineDestination( char *DestinationString );
static void DeterminePlatform( char *PlatformString );
static void DetermineOriginPlatform( char *PlatformString );
static void DetermineReply( char *ReplyString );
static void DetermineTrainType( char *TrainTypeString );
static void DetermineSpeed( char *SpeedString );
static void SetWhish( char *WhishString );


