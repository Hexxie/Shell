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
#include <stdbool.h>
#include <unistd.h>


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
    char* externalCommand = NULL;
    char** params = NULL;
    char* env_p = NULL;
    char* env_path = NULL;
    char* path = NULL;
    int access_res = 0;
    bool isExec = false;

    if((0 < argc) && (NULL != argv)) {

        printf(SHELL_STARTUP);
        
        while(EXIT != currentCommand) {
            //TBD stdin or fd of file
            result = getline(&inputLine.line, &inputLine.length, stdin);

            if(EINVAL != result) {

                //Check that the command is built-in
                for(int i = 0; i < tableSize; i++) {
                    if(0 == strncmp(inputLine.line, shell_table[i].commandName, strlen(shell_table[i].commandName))){
                        currentCommand = shell_table[i].command;
                    }//if
                }//for

                //If the command not found in the table - this mean that it's not a built-in command

                if(NOACT == currentCommand) {
                    //Parse the command
                    externalCommand = strsep(&inputLine.line, " ");
                    
                    printf("External command: %s\n", externalCommand);                
                    printf("Params: %s", inputLine.line);

                    //Go through the PATH and check that the command exists via https://www.opennet.ru/man.shtml?topic=access&category=2&russian=0
                    env_p = getenv("PATH");
                    

                    env_path = (char*) malloc(strlen(env_p));
                    if(NULL != env_path) {
                        memcpy(env_path, env_p, strlen(env_p));
                        printf("PATH: %s\n", env_path);
                        
                        path = strsep(&env_path, ":");
                        while(path != env_path) {
                            path = (char*) realloc(path, strlen(path) + strlen(externalCommand)+1);
                            strcat(path, "/");
                            strcat(path, externalCommand);
                            printf("Checking %s\n", path);
                            access_res = access(path, X_OK);
                            if(-1 != access_res) {
                                isExec = true;
                                break;
                            } else {
                                printf("access returns an error %d\n", access_res);                                
                            }
                            free(path);
                            path = strsep(&env_path, ":");
                        }//while
                    }//if

                    //Fork a new process and start the command


                    //Freeing all used memory
                    if(NULL != externalCommand) {
                        free(externalCommand);
                    }//if                    

                } else {
                    switch(currentCommand) {
                    case EXIT: {
                        exit(0);
                        break;
                    }
                }//switch  
                }//if
                

                printf(SHELL_STARTUP);

                              

            }//if

        }//while

        free(inputLine.line);

    }//if

}//main