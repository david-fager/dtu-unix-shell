#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

char **tokenizeArguments(char *line);
int simpleCommands(char **arguments);
int executer(char **arguments);

int main(int argc, char *argv[]) {

    int status = 1;
    char **arguments = NULL;
    char *line = NULL;
    size_t bufsize = 0;

    printf("--------------\n"
           "Shell started.\n"
           "--------------\n");

    // Main loop
    while (status) {
        // Awaits user input
        printf("FS > ");
        getline(&line, &bufsize, stdin);

        // Splits user input and handles it
        arguments = tokenizeArguments(line);
        status = simpleCommands(arguments);

        for(int i = 0; i < sizeof(arguments); i++) {
            printf("%s\n",arguments[i]);
        }

        // Frees allocated memory
        free(line);
        free(arguments);
    }

    return 0;
}

// Splits the line's arguments and saves each word (argument)
char **tokenizeArguments(char *line) {

    char *temp;
    char **splits = malloc(sizeof(char*));
    int index = 0;

    // Tokenize line and point to first token (argument)
    temp = strtok(line, " \n\r\t\a");

    // Loop through tokens and create pointers in 'split' array to each token
    while (temp != NULL) {
        splits[index++] = temp;
        temp = strtok(NULL, " \n\r\t\a"); // Makes pointer point to next token
    }
    splits[index] = NULL;
    return splits;
}

// These commands are for the parent shell,
int simpleCommands(char **arguments) {
    if (arguments[0] != NULL) {
        if (!strcmp(arguments[0],"help")) {
            // User wants help

            // If the user wrote more than 'help'
            if (arguments[1] != NULL) {
                printf("FS does not support specifics on help.\n\n");
            }

            // Supported commands
            printf("FS supports the following commands:\n"
                   "> help\n"
                   "> cd [path]\n"
                   "> exit\n\n");

        } else if(!strcmp(arguments[0],"cd")) {
            // User wants to change directory
            if (arguments[1] != NULL) {
                if (chdir(arguments[1]) != 0) {
                    printf("Unable to locate path.\n");
                }
            } else {
                printf("No path given. Write a path after command 'cd' to change directory.");
            }

        } else if(!strcmp(arguments[0],"exit")) {
            return 0; // User wants to exit
        } else {
            printf("Unknown command, type 'help' for a list of supported commands.\n");
            return 1;
        }
    } else {
        return 1; // No argument given
    }
    return executer(arguments); //
}

int executer(char **arguments) {

}
