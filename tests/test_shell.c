/******************************************************************************
 *
 *			Shell Test Project
 *
 ******************************************************************************
 *
 * File :   test_shell.c
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
 * Simple API for shell
 *
 *****************************************************************************/
#include "test_shell.h"

GREATEST_MAIN_DEFS();

int main(int argc, char **argv) {
    GREATEST_MAIN_BEGIN();      /* command-line arguments, initialization. */
    RUN_SUITE(utils);
    GREATEST_MAIN_END();        /* display results */
}