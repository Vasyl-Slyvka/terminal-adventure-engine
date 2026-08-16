#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "backpack.h"
#include "game.h"
#include "item.h"
#include "parser.h"
#include "room.h"
#include "world.h"

static size_t container_count(const struct container* first){
    size_t count = 0;

    while(first != NULL){
        count = count + 1u;
        first = first->next;
    }

    return count;
}

static void execute_line(struct game* game, const char* line){
    struct command* command = parse_input(game->parser, line);
    assert(command != NULL);
    execute_command(game, command);
}

static void test_item_room_and_backpack(void){
    struct room* room = create_room("Workshop", "A test room.");
    struct item* key = create_item("Key", "A small key.", MOVABLE | EXAMINABLE);
    struct item* wall = create_item("Wall", "It does not move.", EXAMINABLE);
    struct backpack* backpack = create_backpack(1);

    assert(room != NULL);
    assert(key != NULL);
    assert(wall != NULL);
    assert(backpack != NULL);
    assert(add_item_to_room(room, key));
    assert(get_item_from_room(room, "kEy") == key);

    delete_item_from_room(room, key);
    assert(get_item_from_room(room, "key") == NULL);
    assert(add_item_to_backpack(backpack, key));
    assert(backpack->size == 1);
    assert(get_item_from_backpack(backpack, "KEY") == key);
    assert(!add_item_to_backpack(backpack, wall));

    wall = destroy_item(wall);
    room = destroy_room(room);
    backpack = destroy_backpack(backpack);
    assert(room == NULL);
    assert(backpack == NULL);
}

static void test_world_structure(void){
    struct container* world = create_world();
    assert(world != NULL);
    assert(container_count(world) == 17u);

    struct room* start = get_room(world, "stranded graveyard");
    struct room* castle = get_room(world, "STORMVEIL CASTLE");
    struct room* heart = get_room(world, "heart of the erdtree");

    assert(start != NULL);
    assert(castle != NULL);
    assert(heart != NULL);
    assert(start->north == castle);
    assert(castle->south == start);
    assert(heart->south != NULL);
    assert(get_item_from_room(start, "TARNISHED SWORD") != NULL);

    struct room* duplicate = create_room("STORMVEIL CASTLE", "Duplicate.");
    assert(duplicate != NULL);
    assert(add_room_to_world(world, duplicate) == NULL);
    duplicate = destroy_room(duplicate);

    world = destroy_world(world);
    assert(world == NULL);
}

static void test_parser(void){
    struct parser* parser = create_parser();
    assert(parser != NULL);

    struct command* command = parse_input(parser, "  hElP  ");
    assert(command != NULL);
    assert(strcmp(command->name, "PRIKAZY") == 0);

    command = parse_input(parser, "rozhliadni   sa");
    assert(command != NULL);
    assert(strcmp(command->name, "ROZHLIADNI SA") == 0);

    command = parse_input(parser, "vezmi   Tarnished Sword ");
    assert(command != NULL);
    assert(strcmp(command->name, "VEZMI") == 0);
    assert(command->nmatch > 3u);
    assert(strcmp(command->groups[3], "Tarnished Sword") == 0);

    command = parse_input(parser, "s");
    assert(command != NULL);
    assert(strcmp(command->name, "SEVER") == 0);
    assert(container_count(parser->history) == 2u);

    assert(parse_input(parser, "SAVE slot1") == NULL);
    assert(parse_input(parser, "not-a-command") == NULL);

    parser = destroy_parser(parser);
    assert(parser == NULL);
}

static void test_game_rules(void){
    struct game* game = create_game();
    assert(game != NULL);

    struct room* start = game->current_room;
    execute_line(game, "sever");
    assert(game->current_room == start);

    execute_line(game, "vezmi tarnished sword");
    assert(game->backpack->size == 1);
    assert(get_item_from_room(start, "TARNISHED SWORD") == NULL);

    execute_line(game, "sever");
    assert(strcmp(game->current_room->name, "STORMVEIL CASTLE") == 0);

    execute_line(game, "vezmi rune of godrick");
    assert(get_item_from_backpack(game->backpack, "RUNE OF GODRICK") != NULL);

    execute_line(game, "restart");
    assert(game->state == RESTART);

    game = destroy_game(game);
    assert(game == NULL);
}

static void test_complete_scenario(void){
    struct game* game = create_game();
    FILE* scenario = fopen("scenario.txt", "r");
    char line[256];

    assert(game != NULL);
    assert(scenario != NULL);

    while(game->state == PLAYING && fgets(line, sizeof(line), scenario) != NULL){
        struct command* command = parse_input(game->parser, line);
        assert(command != NULL);
        execute_command(game, command);
    }

    assert(ferror(scenario) == 0);
    assert(fclose(scenario) == 0);
    assert(game->state == SOLVED);
    game = destroy_game(game);
    assert(game == NULL);
}

int main(void){
    test_item_room_and_backpack();
    test_world_structure();
    test_parser();
    test_game_rules();
    test_complete_scenario();

    puts("All core tests passed.");
    return 0;
}
