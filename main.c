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
#include <sys/wait.h>


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
T_RESULT findCommand(T_SHELL_COMMANDS *command, char* line);

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
    T_RESULT shell_result = SHELL_ERROR;
    char* externalCommand = NULL;
    char** params = NULL;
    char* env_p = NULL;
    char* env_path = NULL;
    char* path = NULL;
    int access_res = 0;
    bool isExec = false;
    char* fullPathToCmd = NULL;
    int rc_wait;

    if((0 < argc) && (NULL != argv)) {

        printf(SHELL_STARTUP);
        
        while(EXIT != currentCommand) {
            //TBD stdin or fd of file
            result = getline(&inputLine.line, &inputLine.length, stdin);

            //remove the last input symbol - Enter
            inputLine.line[strlen(inputLine.line)-1] = '\0';

            if(EINVAL != result) {

                //Check that the command is built-in
                shell_result = findCommand(&currentCommand, inputLine.line);

                //If the command not found in the table - this mean that it's not a built-in command

                if(NOACT == currentCommand) {
                    //Parse the command
                    externalCommand = strsep(&inputLine.line, " ");
                    
                    printf("External command: %s\n", externalCommand);                
                    printf("Params: %s\n", inputLine.line);

                    //Go through the PATH and check that the command exists via https://www.opennet.ru/man.shtml?topic=access&category=2&russian=0
                    env_p = getenv("PATH");                    

                    env_path = (char*) malloc(strlen(env_p));
                    if(path != env_path) {
                        memcpy(env_path, env_p, strlen(env_p));
                        
                        //get the first entity
                        path = strsep(&env_path, ":");                        

                        while(NULL != env_path) {
                            fullPathToCmd = (char*) malloc(strlen(path) + strlen(externalCommand)+2);

                            if(NULL != fullPathToCmd){
                                strcat(fullPathToCmd, path);
                                strcat(fullPathToCmd, "/");
                                strcat(fullPathToCmd, externalCommand);
                                access_res = access(fullPathToCmd, X_OK);
                                if(-1 != access_res) {
                                    isExec = true;
                                    break;
                                } else { 
                                    if(NULL != fullPathToCmd) {
                                        free(fullPathToCmd);  
                                        fullPathToCmd = NULL;
                                    }
                                                             
                                }
                            }
                            path = strsep(&env_path, ":");
                        }//while
                    }//if

                    if(NULL != fullPathToCmd) {
                        printf("Found the path %s\n", fullPathToCmd);       
                        execv(fullPathToCmd, inputLine.line);
                        rc_wait = wait(NULL);

                    } else {
                        printf("Command not found!\n");
                    }

                    //Fork a new process and start the command                  

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


/******************************************************************************
* findCommand
**************************************************************************//**
* Search in the command table for built-in command
*
* @param[out]   command   nr of arguments
* @param[in]    line   array with arguments   
*
* @return 0 if main has ended successfully
*****************************************************************************/
T_RESULT findCommand(T_SHELL_COMMANDS *command, char* line) {
    T_RESULT result = SHELL_ERROR;

    if(NULL == command) {
        printf("%s: command pointer is not valid", __func__);
    } else if (NULL == line) {
        printf("%s: line pointer is not valid", __func__);
    } else {

        for(int i = 0; i < tableSize; i++) {
            if(0 == strncmp(line, shell_table[i].commandName, strlen(shell_table[i].commandName))){
                *command = shell_table[i].command;
                result = SHELL_SUCCESS;
            }//if
        }//for

    }//if  

    return result;
}//getCommand