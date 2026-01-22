#include "main.h"

void signal_handler(int sig_num)
{
    // Requirement: We use child_pid as a global variable to track foreground process
    switch (sig_num) {
        case SIGINT: // Ctrl-C
            if (child_pid == 0) {
                // No foreground child, just reprint prompt as per Requirements
                printf("\n%s", prompt);
                fflush(stdout);
            } else {
                // Requirement 1: If child is running, send SIGINT to it
                kill(child_pid, SIGINT);
            }
            break;

        case SIGTSTP: // Ctrl-Z
            if (child_pid == 0) {
                // Requirement: No process to stop, just give a new prompt
                printf("\n%s", prompt);
                fflush(stdout);
            } else {
                // Requirement 9: Stop the foreground process
                kill(child_pid, SIGTSTP);
                // Requirement 7: Insert the process into the linked list
                insert_jobs_to_list(&process_head);
                child_pid = 0; // Reset so shell becomes the foreground again
            }
            break;

        case SIGCHLD: // Requirement: Clean up finished background processes
            // Requirement 10: Use waitpid with WNOHANG to avoid blocking the shell
            while (waitpid(-1, &status, WNOHANG) > 0);
            break;
    }
}