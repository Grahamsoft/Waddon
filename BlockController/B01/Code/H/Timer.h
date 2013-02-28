void Increment_Timer( void );
TIMER_STATUS Check_Timer( TIMER_IDS TimerID );
int Get_Time( void );
void Set_Timer( TIMER_IDS TimerID, int Mins, int Seconds, int HalfSecond );
void timer_isr ( void );
