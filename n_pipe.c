#include "main.h"

int implement_pipe(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Error: No arguments passed, Provide at least one pipe or more\n");
        fprintf(stderr, "Usage: %s <command1> '|' <command2>\n", argv[0]);
        fprintf(stderr, "Usage: %s <command1> '|' <command2> '|' <command3> ...\n", argv[0]);
        return 1;
    }

    // Step 1: Find all pipe positions
    int cmd_idx[argc]; 
    int cmd_count = 0;
    cmd_idx[cmd_count++] = 0; // first command starts at argv[1]

    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "|") == 0) {
            argv[i] = NULL; // terminate previous command
            cmd_idx[cmd_count++] = i + 1; // next command starts after '|'
        }
    }

    if (cmd_count < 2) {
        fprintf(stderr, "Error: Insufficient arguments passed\n");
        fprintf(stderr, "Usage: %s <command1> '|' <command2> ...\n", argv[0]);
        return 1;
    }

    // Step 2: Backup stdin and stdout
    int backup_stdin = dup(STDIN_FILENO);
    int backup_stdout = dup(STDOUT_FILENO);

    int prev_fd = -1; // previous pipe read end

    // Step 3: Loop over commands
    for (int i = 0; i < cmd_count; i++) {
        int pipefd[2];
        if (i < cmd_count - 1) { // not last command
            if (pipe(pipefd) == -1) 
            {
                perror("pipe");
                return 1;
            }
        }

        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            return 1;
        }

        if (pid == 0) {
            // Child process
            if (prev_fd != -1) {
                dup2(prev_fd, STDIN_FILENO); // read from previous pipe
                close(prev_fd);
            }
            if (i < cmd_count - 1) {
                dup2(pipefd[1], STDOUT_FILENO); // write to next pipe
                close(pipefd[0]);
                close(pipefd[1]);
            }
            execvp(argv[cmd_idx[i]], &argv[cmd_idx[i]]);
            perror("execvp");
            return 1;
        } else {
            // Parent process
            if (prev_fd != -1) 
            {
                close(prev_fd);
            }
            if (i < cmd_count - 1) 
            {
                close(pipefd[1]); // parent keeps read end for next child
                prev_fd = pipefd[0];
            }
        }
    }

    // Step 4: Wait for all children
    for (int i = 0; i < cmd_count; i++) {
        wait(NULL);
    }

    // Step 5: Restore stdin and stdout
    dup2(backup_stdin, STDIN_FILENO);
    dup2(backup_stdout, STDOUT_FILENO);
    close(backup_stdin);
    close(backup_stdout);

    return 0;
}
