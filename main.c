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

#define _GNU_SOURCE

#include "defs.h"

#include <stdio.h>
#include <errno.h>
#include <string.h>


/************************** Static Data Definitions **************************/

static T_SHELL_TABLE shell_table[] = 
{
  {NOACT,   ""},
  {NEWLINE, "\n"},  
  {EXIT,    "exit"},
};

static size_t tableSize = sizeof(shell_table)/sizeof(shell_table[0]);

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
int main(int argc, char *argv[]){

    ssize_t result = 0;
    T_Line  inputLine = {0, NULL};
    T_SHELL_COMMANDS currentCommand = NOACT;

    if((0 < argc) && (NULL != argv)) {

        printf(SHELL_STARTUP);
        
        while(EXIT != currentCommand) {
            //TBD stdin or fd of file
            result = getline(&inputLine.line, &inputLine.length, stdin);
            if(EINVAL != result) {

                printf("Entered command: %s\n", inputLine.line );

                for(int i = 0; i < tableSize; i++) {
                    if(0 == strncmp(inputLine.line, shell_table[i].commandName, strlen(shell_table[i].commandName))){
                        currentCommand = shell_table[i].command;
                    }
                }//for

                printf(SHELL_STARTUP);

                switch(currentCommand) {
                    case EXIT: {
                        exit(0);
                        break;
                    }
                }//switch                

            }//if

        }//while

    }//if

}//main