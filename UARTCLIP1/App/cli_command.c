#include "cli_command.h"
#include "string.h"
#include "response_ci.h"
#include "gettemperature_ci.h"
#include "cli_command_table.h"
#include "cli_types.h"
extern const cli_command_entry_t command_entry_table[];
const cli_command_info_t *find_command_info(char *cmd)
{
	const cli_command_entry_t *command_entry = command_entry_table;
	while (command_entry->command_info != NULL)
	{
		if(strcmp(cmd, command_entry->name) == 0)
		{
			return command_entry->command_info;
		}
		command_entry++;
	}
	return NULL;
}
void cli_command_excute(char *uart_buff, uint8_t len)
{
		char *argv[10];
		uint8_t arg_num = 0;
		char *pch;
		pch = strtok((char *)uart_buff," ");
		while(pch != NULL)
		{
			argv[arg_num++] = pch;
			pch = strtok(NULL," ");
		}
		const cli_command_info_t  *command_info = find_command_info(argv[0]);
		if(command_info != NULL)
		{
				command_info->function(argv, arg_num);
		}
		else
		{
			response_print("find not found command\n");
		}
}
 