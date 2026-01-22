#include "main.h"

void scan_input(char *prompt, char *input_string)
{
    extract_external_commands(external_commands);

    signal(SIGINT, signal_handler);
    signal(SIGTSTP, signal_handler);
    signal(SIGCHLD, signal_handler);

    char prompt_string[SIZE];
    strncpy(prompt_string, prompt, SIZE);

    while(1)
    {
        printf("%s", prompt_string);
        fflush(stdout);

        memset(input_string, 0, SIZE);
        char input_command[SIZE];
        if (fgets(input_command, SIZE, stdin) == NULL) continue;

        input_command[strcspn(input_command, "\n")] = '\0';

        if (strlen(input_command) == 0) 
        {
            continue;
        }

        // PS1 Logic (Simplified as per Requirement)
        if (strncmp(input_command, "PS1=", 4) == 0)
        {
            char *new_prompt = input_command + 4;
            if (strlen(new_prompt) > 0 && strchr(new_prompt, ' ') == NULL)
            {
                snprintf(prompt_string, SIZE, "%s$:", new_prompt);
            }
            else
            {
                printf("Error: Invalid PS1\n");
            }
            continue;
        }

        strncpy(input_string, input_command, SIZE);
        char *command = get_command(input_string);
        int command_type = check_command_type(command);

        switch(command_type)
        {
            case BUILTIN:
                execute_internal_commands(command);
                break;

            case EXTERNAL:
            {
                // Check for pipe before forking
                if (strstr(input_string, "|")) 
                {
                    // For pipes, we handle the forks inside n_pipe
                    execute_external_commands(input_string); 
                } 
                else 
                {
                    pid_t pid = fork();
                    if (pid == 0) 
                    {
                        signal(SIGINT, SIG_DFL);
                        signal(SIGTSTP, SIG_DFL);
                        execute_external_commands(input_string);
                        exit(0);
                    } 
                    else if (pid > 0) 
                    {
                        child_pid = pid;
                        waitpid(child_pid, &status, WUNTRACED);
                        child_pid = 0;
                    }
                }
                break;
            }

            case NO_COMMAND:
                if(strcmp(command, "jobs") == 0)
                    print_jobs(process_head);
                else if (strcmp(command, "fg") == 0 && process_head != NULL)
                {
                    child_pid = process_head->pid;
                    kill(child_pid, SIGCONT);
                    waitpid(child_pid, &status, WUNTRACED);
                    delete_jobs_from_list(&process_head);
                    child_pid = 0;
                }
                else if (strcmp(command, "bg") == 0 && process_head != NULL)
                {
                    kill(process_head->pid, SIGCONT);
                    delete_jobs_from_list(&process_head);
                }
                else
                    echo(input_string, status);
                break;
        }
        free(command);
    }
}