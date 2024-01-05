#include "handle_cmd.h"
#include "led_control.h"
#include <string.h>
void handle_cmd(char *buff, char *cmd, int sta)
{
    char *pcmd = strstr(buff,cmd);
    if(pcmd != NULL)
    {
       pcmd += strlen(cmd);
       if(*pcmd == ':')
       {
           pcmd++;
           int num = 0;
           while(1)
           {
               if(*pcmd >= '0' && *pcmd <= '9')
               {
                   num = num * 10 + (*pcmd -'0');
               }
               else if(*pcmd == ',')
               {
                   led_control(num,sta);
                   num = 0;
               }
               else if(*pcmd == ';')
               {
                   led_control(num,sta);
                   break;
               }
               pcmd++;
           }
       }
    }
}
