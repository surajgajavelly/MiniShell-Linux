#include "main.h"

void execute_external_commands(char *input_string) {
    char *args[SIZE / 2];
    char temp_buff[SIZE];
    int i = 0, argc = 0, pipe_count = 0;

    // --- 1. Manual 1D to 2D Conversion with DMA ---
    for (int j = 0; input_string[j] != '\0'; j++) {
        if (input_string[j] == '|') pipe_count++;

        if (input_string[j] != ' ' && input_string[j] != '\0') {
            temp_buff[i++] = input_string[j];
        } 
        else if (i > 0) {
            temp_buff[i] = '\0';
            // Requirement: Use DMA (malloc) for the 2D array conversion
            args[argc] = malloc(strlen(temp_buff) + 1);
            strcpy(args[argc++], temp_buff);
            i = 0;
        }
    }
    // Handle the last token
    if (i > 0) {
        temp_buff[i] = '\0';
        args[argc] = malloc(strlen(temp_buff) + 1);
        strcpy(args[argc++], temp_buff);
    }
    args[argc] = NULL; // Requirement: Store NULL address in last index

    // --- 2. Dispatch Logic ---
    if (pipe_count > 0) {
        // Requirement 5: Call implement_n_pipe()
        implement_pipe(argc, args);
    } else {
        pid_t pid = fork();
        if (pid == 0) {
            execvp(args[0], args);
            perror("execvp");
            exit(1);
        } else if (pid > 0) {
            child_pid = pid;
            waitpid(pid, &status, WUNTRACED);
            child_pid = 0;
        }
    }
}