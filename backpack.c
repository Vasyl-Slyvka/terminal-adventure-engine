#include <stdbool.h>
#include <stdlib.h>

#include "backpack.h"

static bool item_is_inside(const struct backpack* backpack, const struct item* searched_item){
    if(backpack == NULL || searched_item == NULL){
        return false;
    }

    struct container* node = backpack->items;

    while(node != NULL){
        if(node->type == ITEM && node->item == searched_item){
            return true;
        }

        node = node->next;
    }

    return false;
}

struct backpack* create_backpack(const int capacity){
    if(capacity <= 0){
        return NULL;
    }

    struct backpack* backpack = malloc(sizeof(struct backpack));

    if(backpack == NULL){
        return NULL;
    }

    backpack->capacity = capacity;
    backpack->size = 0;
    backpack->items = NULL;

    return backpack;
}

struct backpack* destroy_backpack(struct backpack* backpack){
    if(backpack == NULL){
        return NULL;
    }

    backpack->items = destroy_containers(backpack->items);

    free(backpack);

    return NULL;
}

bool add_item_to_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL){
        return false;
    }

    if(backpack->size >= backpack->capacity){
        return false;
    }

    if((item->properties & MOVABLE) == 0u){
        return false;
    }

    if(item_is_inside(backpack, item) == true){
        return false;
    }

    struct container* added = create_container(backpack->items, ITEM, item);

    if(added == NULL){
        return false;
    }

    if(backpack->items == NULL){
        backpack->items = added;
    }

    backpack->size = backpack->size + 1;

    return true;
}

void delete_item_from_backpack(struct backpack* backpack, struct item* item){
    if(backpack == NULL || item == NULL){
        return;
    }

    if(item_is_inside(backpack, item) == false){
        return;
    }

    backpack->items = remove_container(backpack->items, item);

    if(backpack->size > 0){
        backpack->size = backpack->size - 1;
    }
}

struct item* get_item_from_backpack(const struct backpack* backpack, const char* name){
    if(backpack == NULL || name == NULL){
        return NULL;
    }

    return get_from_container_by_name(backpack->items, name);
}
