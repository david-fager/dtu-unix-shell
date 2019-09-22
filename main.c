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

    do {
        // Awaits user input
        printf("FS > ");
        getline(&line, &bufsize, stdin);

        // Splits user input and handles it
        arguments = tokenizeArguments(line);
        status = delegater(arguments);

        // Frees allocated memory
        free(line);
        free(arguments);
    } while (status);

    return 0;
}

char **tokenizeArguments(char *line) {

    char *temp;
    char **splits = malloc(sizeof(char*));
    if (splits == NULL) {
        printf("Memory allocation failed, exiting program.\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    temp = strtok(line, " \n\r\t\a");
    while (temp != NULL) {
        splits[index++] = temp;
        temp = strtok(NULL, " \n\r\t\a");
    }

    return splits;
}

int delegater(char **arguments) {
    if (arguments[0] != NULL) {
        if (!strcmp(arguments[0],"help")) {
            // User wants help

        } else if(!strcmp(arguments[0],"cd")) {
            // User wants to change directory

        } else if(!strcmp(arguments[0],"exit")) {
            return 0; // User wants to exit
        }
    } else {
        return 1; // Nothing was given as argument
    }
    // If the given argument is not supported
    printf("Unknown command, write 'help' for a list of commands.\n");
    return 1;
}

int command_help() {

}

int command_cd() {

}
