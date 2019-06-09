/******************************************************************************
 *
 *			Sell Project
 *
 ******************************************************************************
 *
 * File :   defs.h
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
 * Defines for for shell "wish"
 *
 *****************************************************************************/
#ifndef _MAIN_
#define _MAIN_

#include <stdlib.h>

/************************ Defines and typedefs *******************************/
#define MAX_STRING_LEN  (256)
#define SHELL_STARTUP   "wish> "

typedef struct{
    size_t length;
    char* line;
} T_Line;

typedef enum {
    NOACT,
    NEWLINE,
    EXIT //This is the last command
} T_SHELL_COMMANDS;

typedef struct {
    T_SHELL_COMMANDS command;
    char commandName[MAX_STRING_LEN];
} T_SHELL_TABLE;


/************************** Function Definitions **************************/



#endif //_MAIN_