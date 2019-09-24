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
int pipeHandler(char **argsLeft, char **argsRight);

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
        printf("\033[1;34m"
               "\n%s\n"
               "\033[1;31m"
               "FS > "
               "\033[0m", cwd);
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
    char **splits = malloc(64 * sizeof(char *));
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

    // Searching for a pipe
    char **argsLeft = malloc(64 * sizeof(arguments));
    char **argsRight = malloc(64 * sizeof(arguments));
    int pipePlacement = 0;
    for (int m = 0; m < sizeof(arguments); m++) {
        if (arguments[m] == NULL) {
            break;
        }
        if (!strcmp(arguments[m], "|")) {
            pipePlacement = m;
            break;
        }
    }

    // Splits arguments around the pipe ( argsLeft | argsRight)
    if (pipePlacement) {
        for (int i = 0; i < pipePlacement; i++) {
            argsLeft[i] = arguments[i];
        }
        int index = 0;
        for (int j = pipePlacement + 1; j < sizeof(arguments); j++) {
            if (arguments[j] != NULL) {
                argsRight[index++] = arguments[j];
            } else {
                break;
            }
        }
        return pipeHandler(argsLeft, argsRight);
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
               "> exit | stops the program\n"
               "> [system calls] | forks and executes entered system call (ls, cat, cp, etc.)\n\n");
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
        waitpid(pid, &status, 0); // (-1 = wait for any child, child exit status, options)
    } else {
        // Executes child process
        execvp(arguments[0], arguments); // (filename to be executed, user's arguments)
    }
    return 1;
}

int pipeHandler(char **argsLeft, char **argsRight) {

    int fds[2];
    pid_t pid1, pid2;
    int status;

    pid1 = fork();
    if (pid1 > 0) {
        // Parent parent wait for execution
        waitpid(pid1, &status, 0);
    } else if (pid1 == 0) {
        // 1. child
        pipe(fds);
        pid2 = fork();

        if (pid2 > 0) {
            // 1. child now parent
            dup2(fds[0],0);
            close(fds[1]);
            execvp(argsRight[0], argsRight);
        } else if (pid2 == 0) {
            // 1. child's child
            dup2(fds[1],1);
            close(fds[0]);
            execvp(argsLeft[0], argsLeft);
        }
    }

    return 1;
}