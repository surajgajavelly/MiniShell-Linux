#include "main.h"

void echo(char *input_string, int status)
{
    // Requirement 8: echo $$ -> Print the PID of the shell
    if (strstr(input_string + 5, "$$"))
    {
        // Using getpid() as per your requirement doc point 8
        printf("%d\n", getpid());
    }
    // Requirement 9 & 10: echo $? -> Print exit code using WEXITSTATUS
    else if (strstr(input_string + 5, "$?"))
    {
        // Extracts the 8-bit exit code from the status variable
        printf("%d\n", WEXITSTATUS(status));
    }
    // Requirement 11 & 12: echo $SHELL -> Print path using getenv
    else if (strstr(input_string + 5, "$SHELL"))
    {
        char *path = getenv("SHELL");
        if (path != NULL)
            printf("%s\n", path);
        else
            printf("/bin/bash\n"); // Default fallback
    }
    // Standard string printing (everything after "echo ")
    else
    {
        printf("%s\n", input_string + 5);
    }
}