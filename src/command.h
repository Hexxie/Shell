/**
 * @file command.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2020-03-28
 *
 * @copyright Copyright (c) 2020
 *
 */

#ifndef __COMMAND_H__
#define __COMMAND_H__

/**
 * @brief types of commands which shell coud accept
 *
 */
enum t_command{
    EXIT,
    CD,
    PATH,
    EXTERNAL,
    UNDEFINED
} typedef t_command;

/**
 * @brief structure for handling built-in commands
 *
 */
struct t_built_in_cmd {
    t_command type;
    char *value;
    int (*func)(char**, int);
} typedef t_built_in_cmd;

/**
 * @brief Calls system call with 0
 *
 * @param argc should be always 0
 * @param argv should be always null
 * @return int always 0
 */
int exit_builtin(int argc, char** argv);

/**
 * @brief Change directory
 *
 * @param argc Should be always 1
 * @param argv Path to the folder
 * @return int 0 if successfull, otherwise see chdir() errors
 */
int cd_builtin(int argc, char** argv);

/**
 * @brief Add a folder to the PATH envvar
 *
 * @param argc 0 or more
 * @param argv paths to the included folders
 * @return int 0 if path successfully added
 */
int path_builtin(int argc, char** argv);

/**
 * @brief Execute a command from the path
 *
 * @param argc 1 or more. First - command
 * @param argv 1 or more
 * @return int corresponding to the command output
 */
int external_exec(int argc, char** argv);

/**
 * @brief built-in commands mapping
 *
 */
t_built_in_cmd built_in_tbl[]  = {
    {PATH,       "path",         &exit_builtin},
    {CD,         "cd",           &cd_builtin  },
    {EXIT,       "exit",         &path_builtin}
};

#endif