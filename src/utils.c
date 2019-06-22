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
 * Date :   22.06.19
 *
 * History of modifications
 * Date       Rev.    Reason
 *
 ******************************************************************************
 * FILE DESCRIPTION *//** @file
 *	
 * Imlementation of shell commands
 *
 *****************************************************************************/
#include <stdio.h>

#include "utils.h"

/******************************************************************************
* userInput
**************************************************************************//**
* Query user an input
*
* @param[out]   line   filled with symbols
* @param[out]   length size of the line 
*
* @return 0 if input is valid symbols
*****************************************************************************/
int userInput(char** line, size_t* length) {
    int result = 0;
    result = getline(line, length, stdin);

    //remove the last input symbol - Enter (for user input)
    *line[*length-1] = '\0';

    return 0;
}//userInput