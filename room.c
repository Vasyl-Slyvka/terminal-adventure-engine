#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "room.h"

static char* duplicate_room_text(const char* text){
    if(text == NULL){
        return NULL;
    }

    size_t length = strlen(text);
    char* duplicated = malloc((length + 1) * sizeof(char));

    if(duplicated == NULL){
        return NULL;
    }

    for(size_t i = 0; i <= length; i = i + 1){
        duplicated[i] = text[i];
    }

    return duplicated;
}

static void clear_room_memory(struct room* room){
    if(room == NULL){
        return;
    }

    free(room->name);
    free(room->description);

    room->items = destroy_containers(room->items);

    free(room);
}

struct room* create_room(const char* name, const char* description){
    if(name == NULL || description == NULL){
        return NULL;
    }

    if(name[0] == '\0' || description[0] == '\0'){
        return NULL;
    }

    struct room* room = malloc(sizeof(struct room));

    if(room == NULL){
        return NULL;
    }

    room->name = NULL;
    room->description = NULL;
    room->north = NULL;
    room->south = NULL;
    room->east = NULL;
    room->west = NULL;
    room->items = NULL;

    room->name = duplicate_room_text(name);

    if(room->name == NULL){
        clear_room_memory(room);
        return NULL;
    }

    room->description = duplicate_room_text(description);

    if(room->description == NULL){
        clear_room_memory(room);
        return NULL;
    }

    return room;
}

struct room* destroy_room(struct room* room){
    clear_room_memory(room);

    return NULL;
}

void set_exits_from_room(struct room *room, struct room *north, struct room *south, struct room *east, struct room *west){
    if(room == NULL){
        return;
    }

    room->north = north;
    room->south = south;
    room->east = east;
    room->west = west;
}

void show_room(const struct room* room){
    if(room == NULL){
        return;
    }

    printf("\n");
    printf("Lokacia: %s\n", room->name);
    printf("%s\n", room->description);

    printf("Mozne vychody:");

    if(room->north != NULL){
        printf(" sever");
    }

    if(room->south != NULL){
        printf(" juh");
    }

    if(room->east != NULL){
        printf(" vychod");
    }

    if(room->west != NULL){
        printf(" zapad");
    }

    printf("\n");

    if(room->items != NULL){
        printf("Vidis:\n");

        struct container* item_node = room->items;

        while(item_node != NULL){
            if(item_node->type == ITEM && item_node->item != NULL){
                printf(" - %s\n", item_node->item->name);
            }

            item_node = item_node->next;
        }
    }
}

bool add_item_to_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL){
        return false;
    }

    struct container* new_node = create_container(room->items, ITEM, item);

    if(new_node == NULL){
        return false;
    }

    if(room->items == NULL){
        room->items = new_node;
    }

    return true;
}

struct item* get_item_from_room(const struct room* room, const char* name){
    if(room == NULL || name == NULL){
        return NULL;
    }

    return get_from_container_by_name(room->items, name);
}

void delete_item_from_room(struct room* room, struct item* item){
    if(room == NULL || item == NULL){
        return;
    }

    room->items = remove_container(room->items, item);
}
