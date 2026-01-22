#include "main.h"

void execute_internal_commands(char *cmd)
{
    // exit → terminate the program
    if (strcmp(cmd, "exit") == 0) 
    {
        exit(0);
    }

    // cd → change directory
    else if (strcmp(cmd, "cd") == 0) 
    {
        if (chdir(input_string + 3)== -1)
        {
            printf("Invalid Directory\n");
        }    
    }

    // pwd → print current directory
    else if (strcmp(cmd, "pwd") == 0) 
    {
        char buffer[SIZE];
        if (getcwd(buffer, sizeof(buffer)) != NULL) 
        {
            printf("%s\n", buffer);
        } else 
        {
            perror("pwd");
        }
    }

    // echo → handle $$, $?, $SHELL, or print message
    else if (strcmp(cmd, "echo") == 0) 
    {
        echo(input_string, status);
    }

}


// #include "main.h"

// void execute_internal_command(char *input_string)
// {
//     //exit-->terminate the program
//     if(strncmp("exit",input_string,4) == 0)
//     {
//         exit(2);
//     }
//     //pwd->print the current location
//     if(strncmp("pwd",input_string,3) == 0)
//     {
//         system("pwd");
//     }
//     //cd-->change the directory
//     //input_string -> cd abc
//     if(strncmp("cd",input_string,2) == 0) 
//     {
//         //implement cd command with mulitiple spaces
//         //varible declartion
//         int i,count=0;
//         for(i = 2 ; input_string[i] == ' ' ; i++)
//         {
//             count++;
//         }
//         chdir(&input_string[2+count]);
//     }    
// }

// #include "main.h"

// void execute_internal_commands(char *input_string)
// {
//     // exit --> terminate the program
//     if (strncmp("exit", input_string, 4) == 0) {
//         exit(0);
//     }
//     // pwd -> print the current location
//     else if (strncmp("pwd", input_string, 3) == 0) {
//         system("pwd");
//     }
//     // cd --> change the directory
//     else if (strncmp("cd", input_string, 2) == 0) {
//         // implement cd command with multiple spaces
//         int i, count = 0;
//         for (i = 2; input_string[i] == ' '; i++) {
//             count++;
//         }
//         if (chdir(&input_string[2 + count]) != 0) {
//             perror("cd");
//         }
//     }
//     // echo $$
//     else if (strcmp(input_string, "echo $$") == 0) {
//         printf("%d\n", shell_pid);
//     }
//     // echo $?
//     else if (strcmp(input_string, "echo $?") == 0) {
//         printf("%d\n", WEXITSTATUS(status));
//     }
//     // echo $SHELL
//     else if (strcmp(input_string, "echo $SHELL") == 0) {
//         char *shell_path = getenv("SHELL");
//         if (shell_path != NULL) {
//             printf("%s\n", shell_path);
//         } else {
//             printf("SHELL variable not set\n");
//         }
//     }
// }


// #include "main.h"

// void execute_internal_commands(char *input_string)
// {
//     // exit --> terminate the program
//     if (strcmp(input_string, "exit") == 0) {
//         exit(0);
//     }
//     // cd --> change the directory
//     else if (strncmp(input_string, "cd", 2) == 0) {
//         char *token = strtok(input_string, " "); // "cd"
//         token = strtok(NULL, " ");               // next token = path
//         if (token != NULL) {
//             if (chdir(token) == -1) {
//                 printf("-bash: cd: %s: No such file or directory\n", token);
//             }
//         } else {
//             // No argument: default to HOME
//             char *home = getenv("HOME");
//             if (home != NULL) {
//                 chdir(home);
//             }
//         }
//     }
//     // pwd -> print the current location
//     else if (strcmp(input_string, "pwd") == 0) {
//         char buffer[SIZE];
//         if (getcwd(buffer, sizeof(buffer)) != NULL) {
//             printf("%s\n", buffer);
//         } else {
//             perror("pwd");
//         }
//     }
//     // echo
//     else if (strncmp(input_string, "echo", 4) == 0) {
//         if (strstr(input_string, "$$") != NULL) {
//             printf("%d\n", shell_pid);
//         } else if (strstr(input_string, "$?") != NULL) {
//             printf("%d\n", WEXITSTATUS(status));
//         } else if (strstr(input_string, "$SHELL") != NULL) {
//             char *shell_path = getenv("SHELL");
//             if (shell_path != NULL) {
//                 printf("%s\n", shell_path);
//             } else {
//                 printf("SHELL variable not set\n");
//             }
//         } else {
//             // Print everything after "echo "
//             char *msg = input_string + 5;
//             printf("%s\n", msg);
//         }
//     }
// }
