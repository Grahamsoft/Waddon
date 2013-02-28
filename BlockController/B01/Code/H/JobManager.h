/* ----------------------------- */
/*              Jobs             */
/* ----------------------------- */

typedef struct AMessagecomms
{
	BOOLEAN Empty;
	BOOLEAN Sent;
	NODE To;
	NODE From;
	TARGET Destination;
	int Whishid;
	PLATFORMS Platform;
	int Speed;
	T_TYPE TrainType;		
	REPLY_TYPE Reply;
	PLATFORMS Origin;
	ACTION_TYPE Action;
} AJob;

int FindEmptyRecord( void );
/* ----------Publics------------ */

void ClearJobs( void );
void AddJob( NODE TO, NODE FROM, TARGET DESTINATION, int WHISHID, PLATFORMS PLATFORM, T_TYPE TRAINTYPE, int SPEED, PLATFORMS ORIGIN );
void AddJobReply( NODE TO, NODE FROM, int WHISHID, REPLY_TYPE REPLY );
void AddJobAction( NODE TO, NODE FROM, ACTION_TYPE ACTION, PLATFORMS PLATFORM, TARGET DESTINATION, T_TYPE TRAINTYPE, PLATFORMS ORIGIN );
void RemoveJob( int WHISHID );
BOOLEAN JobReady( void );
void GrantJob( int WHISHID );
void GrantAnyJob( void );
AJob GetJob( void );
BOOLEAN UnSentJobs( void );
AJob GetUnSentJob( void );
void SetJobSent( int WHISHID );
int GetNewJobID( void );

/* ----------------------------- */
/*          Overrides            */
/* ----------------------------- */

typedef struct AOverridecomms
{
	BOOLEAN Empty;
	SIGNAL_ID Signalid;
	SIGNAL_COLOUR Signalcr;
	int Pointid;
	POINT_STATE Pointstate;
} OverrideRecord;

/* ----------Publics------------ */

void NewOverrideRequest( SIGNAL_ID Signal_id , SIGNAL_COLOUR Signal_colour, int Point_id, POINT_STATE Point_state );
OverrideRecord GetOverrideRequest( void );
