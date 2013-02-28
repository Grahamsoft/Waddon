typedef struct APlatformRecord
{
	BOOLEAN Empty;
	BOOLEAN DepartNow;
	PLATFORMS MyNumber;
	PLATFORMS Platform;
	TARGET Destination;
	T_TYPE TrainType;
	BOOLEAN RapAroundReq;
} PlatformRecord;

void ClearPlatforms( void );
void ClearPlatform( PLATFORMS WhichPlatform );
void SetPlatformDestination( PLATFORMS WhichPlatform, TARGET TheDestination, PLATFORMS DesPlatform );
void SetPlatformTrainType( PLATFORMS WhichPlatform, T_TYPE TheTraintype );
void SetPlatformTrainPresent( PLATFORMS WhichPlatform );
void DepartPlatform ( PLATFORMS WhichPlatform );
BOOLEAN PlatformAvailable ( PLATFORMS WhichPlatform );
void ToggleRapAround ( PLATFORMS WhichPlatform );
BOOLEAN doRapAround ( PLATFORMS WhichPlatform );
void ReCheckPlatform ( PLATFORMS WhichPlatform );

