#include <stdlib.h>
#include <string.h>

#include "command.h"

static char* clone_text(const char* source){
    if(source == NULL){
        return NULL;
    }

    size_t length = strlen(source);
    char* copy = malloc((length + 1) * sizeof(char));

    if(copy == NULL){
        return NULL;
    }

    size_t i = 0;

    while(i <= length){
        copy[i] = source[i];
        i = i + 1;
    }

    return copy;
}

static void clear_command_memory(struct command* command){
    if(command == NULL){
        return;
    }

    if(command->groups != NULL){
        for(size_t i = 0; i < command->nmatch; i = i + 1){
            free(command->groups[i]);
        }

        free(command->groups);
    }

    free(command->description);
    free(command->name);
    free(command);
}

struct command* create_command(const char* name, const char* description, size_t nmatch){
    if(name == NULL || description == NULL){
        return NULL;
    }

    if(name[0] == '\0' || description[0] == '\0'){
        return NULL;
    }

    struct command* command = malloc(sizeof(struct command));

    if(command == NULL){
        return NULL;
    }

    command->name = NULL;
    command->description = NULL;
    command->groups = NULL;
    command->nmatch = nmatch;
    command->name = clone_text(name);

    if(command->name == NULL){
        clear_command_memory(command);
        return NULL;
    }

    command->description = clone_text(description);

    if(command->description == NULL){
        clear_command_memory(command);
        return NULL;
    }

    if(nmatch > 0){
        command->groups = malloc(nmatch * sizeof(char*));

        if(command->groups == NULL){
            clear_command_memory(command);
            return NULL;
        }

        for(size_t i = 0; i < nmatch; i = i + 1){
            command->groups[i] = NULL;
        }
    }

    return command;
}

struct command* destroy_command(struct command* command){
    clear_command_memory(command);

    return NULL;
}
