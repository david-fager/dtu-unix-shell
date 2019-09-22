#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

char **tokenizeArguments(char *line);
int delegater(char **arguments);

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
        status = delegater(arguments);

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

// Delegates which method to run based on the user's entered arguments
int delegater(char **arguments) {
    if (arguments[0] != NULL) {
        if (!strcmp(arguments[0],"help")) {
            // User wants help

        } else if(!strcmp(arguments[0],"cd")) {
            // User wants to change directory

        } else if(!strcmp(arguments[0],"exit")) {
            exit(0); // User wants to exit
        }
    } else {
        return 1; // Nothing was given as argument
    }
    // If the given argument is not supported
    printf("Unknown command, write 'help' for a list of commands.\n");
    return 1;
}

int command_help(char **arguments) {

}

int command_cd(char **arguments) {

}
