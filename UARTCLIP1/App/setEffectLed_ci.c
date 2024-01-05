#include "setEffectLed_ci.h"
#include "stdint.h"
#include "response_ci.h"
void setEffectLed(char **argv, uint8_t arg_num)
{
	if( arg_num < 2)
	{
			response_print("too argument, argument = %d",arg_num);
	}
	else if (arg_num > 2)
	{
		response_print("not enought argument, argument = %d", arg_num);
	}
	else
	{
		
	}
}