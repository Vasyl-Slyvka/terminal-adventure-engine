#include <stdlib.h>
#include <string.h>

#include "item.h"

static char* clone_text(const char* source){
    if(source == NULL){
        return NULL;
    }

    size_t length = strlen(source);
    char* result = malloc((length + 1) * sizeof(char));

    if(result == NULL){
        return NULL;
    }

    for(size_t i = 0; i <= length; i = i + 1){
        result[i] = source[i];
    }

    return result;
}

struct item* create_item(const char* name, const char* description, unsigned int properties){
    if(name == NULL){
        return NULL;
    }

    if(description == NULL){
        return NULL;
    }

    if(name[0] == '\0'){
        return NULL;
    }

    if(description[0] == '\0'){
        return NULL;
    }

    struct item* item = malloc(sizeof(struct item));

    if(item == NULL){
        return NULL;
    }

    item->name = NULL;
    item->description = NULL;
    item->properties = properties;

    item->name = clone_text(name);

    if(item->name == NULL){
        free(item);
        return NULL;
    }

    item->description = clone_text(description);

    if(item->description == NULL){
        free(item->name);
        free(item);
        return NULL;
    }

    return item;
}

struct item* destroy_item(struct item* item){
    if(item == NULL){
        return NULL;
    }

    free(item->name);
    free(item->description);
    free(item);

    return NULL;
}
