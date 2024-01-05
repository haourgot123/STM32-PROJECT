#include "gettemperature_ci.h"
#include "response_ci.h"
#include "lm35.h"
#include "stdlib.h"
void gettemperature(char **argv, uint8_t arg_num)
{
	if(arg_num < 2)
	{
		response_print("don't enough arg, arg = %d",arg_num);
	}
	if(arg_num > 2)
	{
		response_print("too much arg, arg = %d",arg_num);
	}
	if(arg_num == 2)
	{
		uint8_t channel = atoi(argv[1]);
		response_print("Temperature =  %f",LM35_Gettemp(channel));
	}
}
