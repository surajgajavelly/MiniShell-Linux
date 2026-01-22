#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdio_ext.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#define _POSIX_C_SOURCE 200809L
#include <sys/wait.h>
 

#define BUILTIN		1
#define EXTERNAL	2
#define NO_COMMAND  3

#define SIZE 1024

/* Process structure */
typedef struct process
{
    int pid;
    char input_string[SIZE];
    struct process *next;
}job_list;

/* Global Variables (To be defined in main.c) */
extern char prompt[SIZE];             // Default "Minishell$:"
extern int shell_pid;                 // PID of the Minishell itself
extern int child_pid;                 // PID of the currently running child
extern int status;                    // Exit status for echo $?
extern job_list *process_head;  // Head of the jobs linked list
extern char *external_commands[155];  // Array of pointers for external commands
extern char input_string[SIZE];

/* Function Prototypes */


// Input handling functions
void scan_input(char *prompt, char *input_string);
char *get_command(const char *input_string);

// Execution functions
int check_command_type(char *command);
void extract_external_commands(char **external_commands);
void execute_internal_commands(char *input_string);
void execute_external_commands(char *input_string);
void echo(char *input_string, int status);

// Signal handling
void signal_handler(int sig_num);

// Pipe implementation
int implement_pipe(int argc, char *argv[]);

// Linkedlist functions for job control
void insert_jobs_to_list(job_list **process_head);
void delete_jobs_from_list(job_list **process_head);
void print_jobs(job_list *process_head);

#endif 