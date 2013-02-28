//Defines the system types
#include "MsgTypes.h"

typedef enum
	{	CONFIGURE,
		RUN
	} MAINLOOP_STATE;

typedef enum
	{	RED,	
		GREEN
	} SIGNAL_COLOUR;

typedef enum
	{	UNKNOWN,
		OPEN,	
		CLOSE
	} POINT_STATE;

typedef enum
	{	Command_Complete,	
		In_Progress,
		Failed,
		Error
	} PROCESS_STATE;

typedef enum
	{	SignalNo1,	
		SignalNo2
	} SIGNAL_ID;

typedef enum
	{	true,
		false
	} BOOLEAN;

typedef enum
	{	Set_Port_A,	
		Set_Port_B,
		Set_Port_C,
		Set_Oscillator,
		Set_PWM,
		Set_Timer0,
		Set_Timer2,
		Set_Interrupts,
		Set_USART,
		Finished
	} CONFIGURE_STATUS;

typedef enum
	{	SET,	
		UNSET,
		DO_CHARGE,
		MATURED
	} TIMER_STATUS;

typedef enum
	{	TRAIN_MOVEMENT,	
		POINT,
		GENERIC
	} TIMER_IDS;
