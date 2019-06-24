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


TEST example_test_case(void) {
    int r = 0;
    ASSERT(1 == 1);

    r = rand() % 10;
    if (r == 1) SKIP();
    ASSERT(r >= 1);
    PASS();
}

TEST expect_equal(void) {
    int i = 9;
    ASSERT_EQ(10, i);
    PASS();
}

SUITE(utils) {
    RUN_TEST(example_test_case);
    RUN_TEST(expect_equal);
}