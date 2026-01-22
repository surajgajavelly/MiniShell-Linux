#include "main.h"

// Function for getting command from the input 
char *get_command(const char *input_string)
{
    // 1. Find the length of the first word only
    int len = 0;
    while (input_string[len] != ' ' && input_string[len] != '\0')
    {
        len++;
    }

    // 2. Allocate memory dynamically (Requirement: DMA)
    char *command = (char *)malloc((len + 1) * sizeof(char));
    if (command == NULL)
    {
        printf("Memory Not Allocated\n");
        return NULL;
    }

    // 3. Copy the characters into the new memory
    int i;
    for (i = 0; i < len; i++)
    {
        command[i] = input_string[i];
    }

    // 4. Null terminate the string
    command[i] = '\0';

    return command;
}