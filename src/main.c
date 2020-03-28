/**
 * @file main.c
 * @author arusakova (arusakova917@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-03-28
 *
 * Shell -
 *
 * @copyright Copyright (c) 2020
 *
 */

#include "defines.h"
#include "command.h"

#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <errno.h>

/**
 * @brief User can enter only one file with commands
 *
 */
#define MAX_NR_ARGC 2

struct t_input {
    char *line;
    size_t line_size;
} typedef t_input;

/**
 * @brief Print prompt before user enter a new command
 *  Prints only for interactive mode
 */
void printfPrompt(FILE *stream) {
    if(stream == stdin) {
        printf("%s", prompt);
        fflush(stdout);
    }
}

/**
 * @brief Main loop for shell executing
 *
 * @param argc nr of console arguments (max 2)
 * @param argv name of file for batch mode
 * @return int successfullness of execution
 */
int main(int argc, char **argv) {
    t_command cmd = UNDEFINED;
    t_input input_line = {NULL, 0};
    FILE *stream = NULL;
    ssize_t nr_char = 0;

    //If user entered more then one argument - print prompt
    if(argc > MAX_NR_ARGC) {
        printf("Usage: ./wish <file>");

    //Try to open the file with commands
    } else if(argc == 2) {
        stream = fopen(argv[1], "r");

        if(NULL == stream) {
            printf("Invalid file\n");
            return 0;
        }

    //If filename were not provided - readlines from stdin
    } else {
        stream = stdin;
    }

    printfPrompt(stream);

    while ((nr_char = getline(&input_line.line, &input_line.line_size, stream)) != -1) {
        if(nr_char < 0) {
            int errsv = errno;
            if(stream == stdin) {
                printf("getline error: %d", errsv);
            }
            return errsv;
        }

        printf("output: %s", input_line.line);
        free(input_line.line);
        input_line.line = NULL;

        printfPrompt(stream);
    }

    return 0;
}