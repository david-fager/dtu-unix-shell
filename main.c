#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>

char **tokenizeArguments(char *line);

int main(int argc, char *argv[]) {

    char **arguments = NULL;
    char *line = NULL;
    size_t bufsize = 0;

    printf("--------------\n"
           "Shell started.\n"
           "--------------\n");

    do {
        printf("FS > ");
        getline(&line, &bufsize, stdin);

        arguments = tokenizeArguments(line);



        for(int i = 0; i < sizeof(arguments); i++) {
            printf("%s\n", arguments[i]);
        }

        if (!strcmp(line, "exit\n")) {
            break;
        }

        free(line);
        free(arguments);
    } while (1);

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

