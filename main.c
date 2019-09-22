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

    return splits;
}

// These commands are for the parent shell,
int simpleCommands(char **arguments) {
    if (arguments[0] != NULL) {
        if (!strcmp(arguments[0],"help")) {
            // User wants help
            printf("FS supports the following commands:\n\n"
                   "> help\n"
                   "> cd [path]\n"
                   "> exit");
        } else if(!strcmp(arguments[0],"cd")) {
            // User wants to change directory

        } else if(!strcmp(arguments[0],"exit")) {
            return 0; // User wants to exit
        } else {
            printf("Unknown command, type 'help' for a list of supported commands.\n");
        }
    } else {
        return 1; // No argument given
    }
    return executer(arguments); //
}

int executer(char **arguments) {

}
