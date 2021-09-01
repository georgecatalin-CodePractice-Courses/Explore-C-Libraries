#include <signal.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <stdbool.h>
#include <stdint.h>


typedef struct Timer_
{
	timer_t posix_timer;
	void *user_argument;
	unsigned long exp_timer; //in milliseconds
	unsigned long secondary_exp_timer; //in milliseconds the 2nd,3rd,4th... expiration time will happen ->applies to periodic timers. For one-off timers should be 0
	uint32_t threshold_max_times_executed_timer;
	void (*cb) (struct Timer_ *,void *); //the timer callback 
	bool exponential_backoff_timer;
	
	//place holder to store dynamic attributes of the timer
	unsigned long time_remaining;
	uint32_t invocation_counter_of_timer;
	struct itimerspec ts; //here to store the expiration time of the timer
	unsigned long exponential_backoff_time;
	TIMER_STATE_T timer_state;
	
} Timer_t


//This function return NULL when the timer creation fails, or it returns a pointer to the Timer object if it succeeds
Timer_t *setup_timer(
	// Timer Callback with user data and user size. This function pointer will be invoked when the timer fires
	void (*) (Timer_t *,void *),
	// First expiration time interval in milliseconds
	unsigned long,
	//Subsequent expiration time interval in milliseconds
	unsigned long,
	// Max number of expirations, 0 for infinite
	uint32_t,
	//Argument to timer callback function
	void *,
	//is this timer an exponential backoff timer?
	bool);
