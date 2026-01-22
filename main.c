#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

char prompt[SIZE] = "Minishell$:";
char input_string[SIZE];
int shell_pid;
int child_pid = 0;
int status = 0;
job_list *process_head = NULL;
char *external_commands[155];

int main()
{
	system("clear");

	shell_pid = getpid();
	
	scan_input(prompt, input_string);
	
	return 0;
}
