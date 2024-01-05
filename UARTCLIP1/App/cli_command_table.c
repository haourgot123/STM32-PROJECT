#include "cli_command_table.h"
#include "cli_types.h"
#include "gettemperature_ci.h"
#include "settemperature_ci.h"
const cli_command_info_t command_info_gettemp =
{
	gettemperature,
	"get temp from LM35"
};
const cli_command_info_t command_info_settempMax =
{
	setTemperatureMax,
	"set temperatue Max from LM35"
};
const cli_command_info_t command_info_settempMin =
{
	setTemperatureMin,
	"set temparature Min from LM35"
};
const cli_command_info_t command_info_setEffectLed =
{
	setEffectLed,
	"set effect led"
}
const cli_command_entry_t command_entry_table [] =
{
	{"gettemp", &command_info_gettemp},
	{"settempMax",&command_info_settempMax },
	{"settempMin", &command_info_settempMin},
	{"setEffectLed",&command_info_setEffectLed},
	{NULL, NULL}
};
