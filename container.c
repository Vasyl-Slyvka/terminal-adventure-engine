#include <ctype.h>
#include <stdlib.h>

#include "container.h"

static int letters_match(const char* left, const char* right){
    if(left == NULL || right == NULL){
        return 0;
    }

    while(*left != '\0' && *right != '\0'){
        unsigned char l = (unsigned char)*left;
        unsigned char r = (unsigned char)*right;

        if(tolower(l) != tolower(r)){
            return 0;
        }

        left++;
        right++;
    }

    return *left == '\0' && *right == '\0';
}

static int container_type_is_valid(enum container_type type){
    switch(type){
        case ROOM:
        case ITEM:
        case COMMAND:
        case TEXT:
            return 1;
        default:
            return 0;
    }
}

static void save_entry_to_container(struct container* node, enum container_type type, void* entry){
    if(type == ROOM){
        node->room = entry;
    }
    else if(type == ITEM){
        node->item = entry;
    }
    else if(type == COMMAND){
        node->command = entry;
    }
    else{
        node->text = entry;
    }
}

static void* entry_address(struct container* node){
    if(node == NULL){
        return NULL;
    }

    if(node->type == ROOM){
        return node->room;
    }

    if(node->type == ITEM){
        return node->item;
    }

    if(node->type == COMMAND){
        return node->command;
    }

    if(node->type == TEXT){
        return node->text;
    }

    return NULL;
}

static const char* entry_name(struct container* node){
    if(node == NULL){
        return NULL;
    }

    if(node->type == ROOM && node->room != NULL){
        return node->room->name;
    }

    if(node->type == ITEM && node->item != NULL){
        return node->item->name;
    }

    if(node->type == COMMAND && node->command != NULL){
        return node->command->name;
    }

    if(node->type == TEXT){
        return node->text;
    }

    return NULL;
}

static void destroy_entry(struct container* node){
    if(node == NULL){
        return;
    }

    if(node->type == ROOM){
        node->room = destroy_room(node->room);
    }
    else if(node->type == ITEM){
        node->item = destroy_item(node->item);
    }
    else if(node->type == COMMAND){
        node->command = destroy_command(node->command);
    }
    else if(node->type == TEXT){
        free(node->text);
        node->text = NULL;
    }
}

struct container* create_container(struct container* first, enum container_type type, void* entry){
    if(entry == NULL){
        return NULL;
    }

    if(container_type_is_valid(type) == 0){
        return NULL;
    }

    if(first != NULL && first->type != type){
        return NULL;
    }

    struct container* node = malloc(sizeof(struct container));

    if(node == NULL){
        return NULL;
    }

    node->type = type;
    node->next = NULL;
    save_entry_to_container(node, type, entry);

    if(first == NULL){
        return node;
    }

    struct container* last = first;

    while(last->next != NULL){
        last = last->next;
    }

    last->next = node;

    return node;
}

struct container* destroy_containers(struct container* first){
    struct container* node = first;

    while(node != NULL){
        struct container* next = node->next;

        destroy_entry(node);
        free(node);

        node = next;
    }

    return NULL;
}

void* get_from_container_by_name(struct container* first, const char* name){
    if(name == NULL){
        return NULL;
    }

    struct container* node = first;

    while(node != NULL){
        const char* current_name = entry_name(node);

        if(letters_match(current_name, name) != 0){
            return entry_address(node);
        }

        node = node->next;
    }

    return NULL;
}

struct container* remove_container(struct container* first, void* entry){
    if(first == NULL){
        return NULL;
    }

    if(entry == NULL){
        return first;
    }

    struct container* node = first;
    struct container* previous = NULL;

    while(node != NULL){
        if(entry_address(node) == entry){
            struct container* after_removed = node->next;

            if(previous == NULL){
                free(node);
                return after_removed;
            }

            previous->next = after_removed;
            free(node);

            return first;
        }

        previous = node;
        node = node->next;
    }

    return first;
}