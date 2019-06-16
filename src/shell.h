/******************************************************************************
 *
 *			Shell Project
 *
 ******************************************************************************
 *
 * File :   main.c
 * 
 * Author : A Rusakova
 *
 * Date :   16.06.19
 *
 * History of modifications
 * Date       Rev.    Reason
 *
 ******************************************************************************
 * FILE DESCRIPTION *//** @file
 *	
 * Simple API for shell
 *
 *****************************************************************************/
#ifndef _SHELL_H
#define _SHELL_H

/************************** Function Definitions **************************/
void shell_init(char* file);
void shell_run();
void shell_terminate();

#endif
