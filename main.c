/******************************************************************************
 *
 *			Sell Project
 *
 ******************************************************************************
 *
 * File :   main.c
 * 
 * Author : A Rusakova
 *
 * Date :   08.06.19
 *
 * History of modifications
 * Date       Rev.    Reason
 *
 ******************************************************************************
 * FILE DESCRIPTION *//** @file
 *	
 * Main point for shell "wish"
 *
 *****************************************************************************/
#ifndef _MAIN_
#define _MAIN_

#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

/************************ Defines and typedefs *******************************/
#define MAX_STRING_LEN  (256)
#define SHELL_STARTUP   "\nwinsh> "

typedef struct{
    size_t length;
    char* line;
} T_Line;

typedef enum {
    NEWLINE,
    EXIT //This is the last command
} T_SHELL_COMMANDS;

typedef struct {
    T_SHELL_COMMANDS command;
    char commandName[MAX_STRING_LEN];
} T_SHELL_TABLE;

/************************** Global Data Definitions **************************/


/************************** Static Data Definitions **************************/

static T_SHELL_TABLE shell_table[] = 
{
  {NEWLINE, "\x0D"},  
  {EXIT,  "exit"}
};

static
/************************* Static Function Prototypes ************************/
//TBD create init - to clean terminal

/********************************** Functions ********************************/

/******************************************************************************
* main
**************************************************************************//**
* Entry point for shell "wish"
*
* @param[in]   argc   nr of arguments
* @param[in]   argv   array with arguments   
*
* @return 0 if main has ended successfully
*****************************************************************************/
int main(int argc, char **argv) {

    ssize_t result = 0;
    T_Line  inputLine = {0, NULL};

    if((0 < argc) && (NULL != argv)) {

        printf(SHELL_STARTUP);
        
        while(1) {
            //TBD stdin or fd of file
            result = getline(&inputLine.line, &inputLine.length, stdin);
            if(EINVAL != result) {

                //Find the command in the table

                //Run the command

            }//if

        }//while

    }//if

}//main

#endif