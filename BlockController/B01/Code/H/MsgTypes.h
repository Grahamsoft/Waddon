	typedef enum
	{
		A_GET,
		A_SET,
		A_DEPART
	} ACTION_TYPE;

	typedef enum
	{
		EMU2,
		EMU3,
		EMU4,
		BR47,
		BR47C1,
		C1
	} T_TYPE;

	typedef enum
	{
		WEYMOUTH,
		LONDON
	} TARGET;

	typedef enum
	{
		PLAT1,
		PLAT2
	} PLATFORMS;

	typedef enum
	{
		SCHEDULER,
		WEYMOUTH_CONTROLLER,
		LONDON_CONTROLLER
	} NODE;

	typedef enum
	{
		GRANTED,
		DENIED,
		TRUE,
		FALSE,
		PENDING
	} REPLY_TYPE;

		
