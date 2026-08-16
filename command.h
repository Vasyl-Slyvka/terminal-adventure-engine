#ifndef COMMAND_H
#define COMMAND_H

#include <stddef.h>

/**
 * Struct defining command
 *
 * Note that name and description are expected to be allocated on the heap,
 * and they should be freed on command destruction.
 */
struct command{
    char*   name;           /// command name, must be unique
    char*   description;    /// command description
    size_t  nmatch;         /// number of matches
    char**  groups;         /// matched groups
};


/**
 * Creates command with name and description
 *
 * This function creates new command. Every command is defined with at least
 * its name and description. The parser stores the recognized input fragments
 * in the requested number of groups.
 * Function returns reference to the newly created command, or NULL, if command
 * could not be created.
 * @param name command name
 * @param description command description for usage with HELP command
 * @param nmatch the number of input groups stored by the parser
 * @return The reference of the command in memory or NULL, if command could not be created or name or description were not provided.
 */
struct command* create_command(const char* name, const char* description, size_t nmatch);


/**
 * Destroys command
 *
 * Destroys (frees) command and all of its resources.
 * @param command command to be destroyed
 * @return Always returns NULL.
 */
struct command* destroy_command(struct command* command);

#endif
