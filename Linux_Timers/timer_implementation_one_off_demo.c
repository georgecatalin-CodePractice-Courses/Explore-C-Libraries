#include <signal.h> //needed to use timers
#include <time.h> //needed to use timers

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <memory.h>
#include <unistd.h> //to use pause()
#include <stdint.h>
#include <stdbool.h>

static void print_system_time()
{
	time_t t;
	time(&t); //get the current system time and add the the current time in t


	printf("%s ", ctime(&t));
}

//Example data structure
typedef struct pair
{
	 int a;
	 int b;
} pair_t;

pair_t pair={10,20};

//This is ithe timer callback function which will be called every time the timer expires. 
//The signature of the function will be: void functioname (union sigval)

void timer_callback_function(union sigval arg)
{
	print_system_time();

	pair_t *pair=(pair_t *) arg.sival_ptr; //Extract the user data structure

	printf("the pair is :[ %u %u]\n", pair->a, pair->b);

}

//set the properties of the timer
void timer_demo()
{
	int return_value;
	struct sigevent evp;

	/*  you can take a local variable if you wish , and in this case we will not free it in time handler function */
	time_t timer;

	memset(&timer,0,sizeof(timer_t)); //initialize the timer variable to 0

	memset(&evp,0,sizeof(struct sigevent)); //initialize the evp variable to 0




	/* ***   Set the 3 members of the evp variable to the appropriate values *** */

    //Fill in the user data structure. When the timer expires, this will be passed as argument to the timer callback function
	evp.sigev_value.sival_ptr=(void *) &pair; //user defined object whose address is assigned to sival_ptr argument

	//On timer expiry, we want the linux kernel to launch the timer handler routine in a separate thread context
	evp.sigev_notify=SIGEV_THREAD;

	//Register the timer handler function. This function shall be invoked when the timer expires
	evp.sigev_notify_function=timer_callback_function;




	/* *** Create a timer *** */
	// Create a timer. It is just a timer initialization, and the creation of the appropriate data structure. Timer will not be started (alarmed) 
	return_value=timer_create(CLOCK_REALTIME,&evp,&timer);

    //the 3rd argument is the address of the timer variable we are creating


	if(return_value<0)
	{
		printf("Timer creation failed with errno=%d.\n",errno);
		exit(0);
	}

	/* *** Specify the expiration time of the timer , which is after how many seconds we want it to fire *** */
	struct itimerspec ts;

	//The timer will fire for the 1st time after 5 seconds and 0 nanoseconds
	ts.it_value.tv_sec=5;
	ts.it_value.tv_nsec=0;

    ts.it_interval.tv_sec=0;
	ts.it_interval.tv_nsec=0;




	/* ***  Start the timer *** */
	return_value=timer_settime(timer,0,&ts,NULL);

	if(return_value<0)
	{
		printf("Timer start failed , errno=%d.\n",errno);
		exit(0);
	}
	else
	{
		print_system_time();
		printf("Timer started(alarmed) correctly.");
	}

}

int main(int argc, char** argv)
{
	timer_demo();
	pause();
	return 0;
}


