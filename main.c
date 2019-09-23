#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

char **tokenizeArguments(char *line);
int commandHandler(char **arguments);
int showHelp(char **arguments);
int changeDirectory(char **arguments);
int executer(char **arguments);

int main(int argc, char *argv[]) {

    char cwd[PATH_MAX];
    int status = 1;
    char **arguments = NULL;
    char *line = NULL;
    size_t bufsize = 0;

    // Startup text
    printf("--------------\n"
           "Shell started.\n"
           "--------------\n");

    // Set the beginning path for the shell to the HOME directory
    chdir(getenv("HOME"));

    // Main loop
    while (status) {
        // Prints current directory
        getcwd(cwd, sizeof(cwd));

        // Awaits user input (double backslash is coloring of the text)
        printf("\033[0;31m"
               "\n%s\n"
               "\033[0m"
               "FS > ", cwd);
        getline(&line, &bufsize, stdin);

        // Splits user input and handles it
        arguments = tokenizeArguments(line);
        status = commandHandler(arguments);
    }

    // Frees allocated memory
    free(arguments);
    free(line);
    return 0;
}

// Splits the line's arguments and saves each word (argument)
char **tokenizeArguments(char *line) {

    char *temp;
    char **splits = malloc(sizeof(char *));
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
int commandHandler(char **arguments) {
    if (arguments[0] == NULL) {
        return 1; // No argument given
    } else if (!strcmp(arguments[0], "help")) {
        return showHelp(arguments);
    } else if (!strcmp(arguments[0], "cd")) {
        return changeDirectory(arguments);
    } else if (!strcmp(arguments[0], "exit")) {
        return 0; // User wants to exit
    }
    return executer(arguments);
}

// For when the user wants help
int showHelp(char **arguments) {
    if (arguments[1] != NULL) {
        printf("Too many arguments.\n"); // If the user wrote more than 'help'
    } else {
        // Supported commands
        printf("FS supports the following commands:\n"
               "> help | shows a list of commands\n"
               "> cd [path] | changes directory\n"
               "> exit | stops the program\n\n");
    }
    return 1;
}

// For when the user wants to change directory
int changeDirectory(char **arguments) {
    if (arguments[1] != NULL && arguments[2] == NULL) {
        if (chdir(arguments[1]) != 0) {
            printf("Unable to locate path.\n");
        }
    } else {
        printf("Path missing. Command help: 'cd [path]'\n");
    }
    return 1;
}

// Executes system calls
int executer(char **arguments) {
    int status, pid;
    pid = fork();
    if (pid != 0) {
        // Parent waits for child to exit
        waitpid(-1, &status, 0); // (-1 = wait for any child, child exit status, options)
    } else {
        // executes child process
        execvp(arguments[0], arguments); // (filename to be executed, user's arguments)
    }
    return 1;
}
