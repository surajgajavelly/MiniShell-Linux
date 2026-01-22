#include "main.h"

int check_command_type(char *command)
{
    // 1. Handle NULL or Empty Command immediately
    if (command == NULL || strlen(command) == 0)     
    {
        return NO_COMMAND;       
    }

    // 2. Check Built-ins
    char *builtins[] = {"echo","printf","read","cd","pwd","pushd","popd","dirs","let","eval","set","unset","export","declare","typeset","readonly","getopts","source","exit","exec","shopt","caller","true","type","hash","bind","help",NULL};
    
    for(int i = 0 ; builtins[i] != NULL ; i++)
    {
        if(strcmp(command, builtins[i]) == 0)
        {
            return BUILTIN;
        }
    }   

    // 3. Check External Commands using the GLOBAL array
    // (This array was already populated in scan_input.c at startup)
    for(int i = 0 ; external_commands[i] != NULL ; i++)
    {
        if(strcmp(command, external_commands[i]) == 0)
        {
            return EXTERNAL;
        }
    }

    return NO_COMMAND;
}