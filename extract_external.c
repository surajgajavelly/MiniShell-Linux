#include "main.h"

void extract_external_commands(char **external_commands)
{
    char ch;
    char buffer[SIZE] = {'\0'}; 
    int i = 0, j = 0;

    int fd = open("external_commands.txt", O_RDONLY);
    if(fd == -1) {
        perror("open external_commands.txt");
        return;
    }

    while(read(fd, &ch, 1) > 0 && j < 154)
    {
        // Added the \r check from your friend's logic for safety
        if(ch != '\n' && ch != '\r') {
            buffer[i++] = ch;
        } else if (i > 0) {
            buffer[i] = '\0';
            external_commands[j] = calloc(strlen(buffer) + 1, sizeof(char));
            strcpy(external_commands[j++], buffer);
            memset(buffer, '\0', SIZE);
            i = 0;
        }
    }
    // Handle the last line
    if (i > 0) {
        buffer[i] = '\0';
        external_commands[j] = calloc(strlen(buffer) + 1, sizeof(char));
        strcpy(external_commands[j++], buffer);
    }
    external_commands[j] = NULL;
    close(fd);
}