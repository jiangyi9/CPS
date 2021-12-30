#include "drone_simulation.c"
#include <stdio.h>

#define kp 0.8
#define ki 0.01
#define kd 27.0

static float error;
static float last_error;

//define a pid controller
float pid(float target, float current)
{
	error = target - current;
	float integral = 0.0;
	float derivative = 0.0;
	integral = integral + error;
	derivative = error - last_error;
	last_error = error;
	float output = (kp*error) + (ki*integral) + (kd*derivative);
	//printf("pidoutput:%f\n",output);

	//the output shouldn't over the limit
	if(output >= MAX_ACCELERATION)
	{
		output = MAX_ACCELERATION;
	}
	if(output <= MIN_ACCELERATION)
	{
		output = MIN_ACCELERATION;
	}
	//printf("pidoutputafter:%f\n",output);
	return output;
}

int main()
{    
	//the user defined height
	float target_height = 1.0;
	sim_set_user_data(target_height);

	//start the simulation
	sim_start("flight.log");

	while(sim_advance_time()<=30)
	{
		//calculate the acceleration using PID
		//printf("pidinthemain:%f\n",pid(target_height,sim_get_height()));
		sim_set_acceleration(pid(target_height,sim_get_height()));
		sim_advance_time();	
	}

	sim_end();

    return 0;
}