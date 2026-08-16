#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "game.h"
#include "world.h"
#include "item.h"

static int text_is(const char* left, const char* right){
    if(left == NULL || right == NULL){
        return 0;
    }

    const unsigned char* a = (const unsigned char*)left;
    const unsigned char* b = (const unsigned char*)right;

    while(*a != '\0' && *b != '\0'){
        if(tolower(*a) != tolower(*b)){
            return 0;
        }

        a = a + 1;
        b = b + 1;
    }

    return *a == '\0' && *b == '\0';
}

static const char* command_argument(const struct command* command){
    if(command == NULL || command->groups == NULL){
        return NULL;
    }

    if(command->nmatch <= 3){
        return NULL;
    }

    if(command->groups[3] == NULL || command->groups[3][0] == '\0'){
        return NULL;
    }

    return command->groups[3];
}

static int room_has_name(const struct room* room, const char* name){
    if(room == NULL){
        return 0;
    }

    return text_is(room->name, name);
}

static int player_is_in(const struct game* game, const char* room_name){
    if(game == NULL){
        return 0;
    }

    return room_has_name(game->current_room, room_name);
}

static struct item* item_in_bag(const struct game* game, const char* name){
    if(game == NULL || game->backpack == NULL || name == NULL){
        return NULL;
    }

    return get_item_from_backpack(game->backpack, name);
}

static int player_has(const struct game* game, const char* item_name){
    return item_in_bag(game, item_name) != NULL;
}

static int bag_is_empty(const struct game* game){
    if(game == NULL || game->backpack == NULL){
        return 1;
    }

    return game->backpack->items == NULL;
}

static int name_is_rune(const char* name){
    if(name == NULL){
        return 0;
    }

    if(text_is(name, "RUNE OF GODRICK") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF RENNALA") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF RADAHN") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF RYKARD") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF RANNI") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF MOHG") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF FIA") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF MORGOTT") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF THREE FINGERS") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF GOLDMASK") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF DEATH") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF DUNG EATER") != 0){
        return 1;
    }

    if(text_is(name, "RUNE OF MALENIA") != 0){
        return 1;
    }

    return 0;
}

static int count_player_runes(const struct game* game){
    if(game == NULL || game->backpack == NULL){
        return 0;
    }

    int runes = 0;
    struct container* node = game->backpack->items;

    while(node != NULL){
        if(node->type == ITEM && node->item != NULL){
            if(name_is_rune(node->item->name) != 0){
                runes = runes + 1;
            }
        }

        node = node->next;
    }

    return runes;
}

static void ending_quote(void){
    printf("\n");
    printf("Num fatum hominum lege arcana regitur?\n");
    printf("An manus ignota super mundum pendet?\n");
    printf("Homo tamen suae voluntatis dominus non semper est.\n");
}

static void game_intro(void){
    printf("Elden Ring TUKE Edition\n");
    printf("----------------------------------------\n");
    printf("The Lands Between are broken. The Elden Ring has been shattered,\n");
    printf("and the demigods hold fragments of its power.\n");
    printf("You are the Tarnished. Gather Great Runes, reach the Heart of the Erdtree,\n");
    printf("choose one rune at the Erdtree Forge, and become the TUKE Lord.\n");
    printf("Read VETERANS NOTES in the starting location for the rules.\n");
    printf("----------------------------------------\n");
}

static void list_commands(const struct game* game){
    if(game == NULL || game->parser == NULL){
        return;
    }

    printf("Dostupne prikazy:\n");

    struct container* node = game->parser->commands;

    while(node != NULL){
        if(node->type == COMMAND && node->command != NULL){
            printf(" - %s: %s\n", node->command->name, node->command->description);
        }

        node = node->next;
    }
}

static void list_inventory(const struct game* game){
    if(game == NULL || game->backpack == NULL){
        return;
    }

    if(game->backpack->items == NULL){
        printf("Batoh je prazdny.\n");
        return;
    }

    printf("V batohu mas:\n");

    struct container* node = game->backpack->items;

    while(node != NULL){
        if(node->type == ITEM && node->item != NULL){
            printf(" - %s\n", node->item->name);
        }

        node = node->next;
    }
}

static int locked_without_three_fingers(const struct game* game){
    return player_has(game, "RUNE OF THREE FINGERS") == 0;
}

static int can_walk_to(struct game* game, struct room* target){
    if(game == NULL || target == NULL){
        return 0;
    }

    if(locked_without_three_fingers(game) == 0){
        return 1;
    }

    if(player_is_in(game, "STRANDED GRAVEYARD") != 0 &&
       room_has_name(target, "STORMVEIL CASTLE") != 0 &&
       player_has(game, "TARNISHED SWORD") == 0){
        printf("You cannot leave the Stranded Graveyard without the Tarnished Sword.\n");
        return 0;
    }

    if(room_has_name(target, "LEYNDELL ROYAL CAPITAL") != 0 &&
       player_has(game, "MEDALLION") == 0){
        printf("The road to Leyndell is sealed. You need the MEDALLION.\n");
        return 0;
    }

    if(room_has_name(target, "CRUMBLING FARUM AZULA") != 0 &&
       player_has(game, "FLAME OF THE GIANTS") == 0){
        printf("The storm does not open. You need the FLAME OF THE GIANTS.\n");
        return 0;
    }

    if(room_has_name(target, "HALIGTREE") != 0 &&
       player_has(game, "INVERTED MEDALLION") == 0){
        printf("The hidden path to the Haligtree requires the INVERTED MEDALLION.\n");
        return 0;
    }

    if(room_has_name(target, "LEYNDELL ASHEN CAPITAL") != 0 &&
       player_has(game, "RUNE OF DEATH") == 0){
        printf("Leyndell cannot become ash without the RUNE OF DEATH.\n");
        return 0;
    }

    if(room_has_name(target, "FRENZIED FLAME PROSCRIPTION") != 0 &&
       bag_is_empty(game) == 0){
        printf("To enter the Frenzied Flame Proscription, you must abandon everything first.\n");
        return 0;
    }

    if(room_has_name(target, "HEART OF THE ERDTREE") != 0 &&
       count_player_runes(game) < 3){
        printf("The Heart of the Erdtree rejects you. You need at least three runes.\n");
        return 0;
    }

    return 1;
}

static void chaos_ending(struct game* game){
    if(game == NULL){
        return;
    }

    printf("\n");
    printf("The Frenzied Flame awakens before the Erdtree Forge.\n");
    printf("The Erdtree and the Lands Between burn to ash.\n");
    printf("The daughter of the Dark Moon will hunt you beyond the edge of the world.\n");
    printf("You became chaos itself, a flame that destroys all, hoping to melt the world into something new.\n");

    ending_quote();

    game->state = SOLVED;
}

static void check_automatic_ending(struct game* game){
    if(game == NULL){
        return;
    }

    if(player_is_in(game, "HEART OF THE ERDTREE") != 0){
        if(player_has(game, "RUNE OF THREE FINGERS") != 0 &&
           player_has(game, "MIQUELLAS CLEANSING") == 0){
            chaos_ending(game);
        }
    }
}

static void move_to_room(struct game* game, struct room* target){
    if(game == NULL){
        return;
    }

    if(target == NULL){
        printf("Tymto smerom sa neda ist.\n");
        return;
    }

    if(can_walk_to(game, target) == 0){
        return;
    }

    game->current_room = target;
    show_room(game->current_room);

    check_automatic_ending(game);
}

static struct item* visible_or_carried_item(struct game* game, const char* name){
    if(game == NULL || name == NULL){
        return NULL;
    }

    struct item* item = item_in_bag(game, name);

    if(item != NULL){
        return item;
    }

    return get_item_from_room(game->current_room, name);
}

static void take_item(struct game* game, const char* name){
    if(game == NULL || game->current_room == NULL){
        return;
    }

    if(name == NULL){
        printf("Neviem, co chces vziat.\n");
        return;
    }

    struct item* item = get_item_from_room(game->current_room, name);

    if(item == NULL){
        printf("Taky predmet tu nie je.\n");
        return;
    }

    if(add_item_to_backpack(game->backpack, item) == false){
        printf("Tento predmet nemozes vziat.\n");
        return;
    }

    delete_item_from_room(game->current_room, item);

    printf("Vzal si: %s\n", item->name);
}

static void drop_item(struct game* game, const char* name){
    if(game == NULL || game->current_room == NULL){
        return;
    }

    if(name == NULL){
        printf("Neviem, co chces polozit.\n");
        return;
    }

    if(text_is(name, "RUNE OF THREE FINGERS") != 0){
        printf("Tuto runu uz nemozes odhodit.\n");
        return;
    }

    struct item* item = item_in_bag(game, name);

    if(item == NULL){
        printf("Taky predmet v batohu nemas.\n");
        return;
    }

    if(add_item_to_room(game->current_room, item) == false){
        printf("Predmet sa nepodarilo polozit.\n");
        return;
    }

    delete_item_from_backpack(game->backpack, item);

    printf("Polozil si: %s\n", item->name);
}

static void examine_item(struct game* game, const char* name){
    if(name == NULL){
        printf("Neviem, co chces preskumat.\n");
        return;
    }

    struct item* item = visible_or_carried_item(game, name);

    if(item == NULL){
        printf("Taky predmet nevidis ani ho nemas v batohu.\n");
        return;
    }

    if((item->properties & EXAMINABLE) == 0u){
        printf("Tento predmet sa neda preskumat.\n");
        return;
    }

    printf("%s\n", item->description);
}

static void create_cleansing(struct game* game){
    if(game == NULL || game->backpack == NULL){
        return;
    }

    if(player_has(game, "MIQUELLAS CLEANSING") != 0){
        printf("Miquella's cleansing is already with you.\n");
        return;
    }

    struct item* cleansing = create_item(
        "MIQUELLAS CLEANSING",
        "A silent cleansing left by Miquella's Needle. The Frenzied Flame no longer owns your fate.",
        MOVABLE | EXAMINABLE
    );

    if(cleansing == NULL){
        printf("The cleansing failed.\n");
        return;
    }

    if(add_item_to_backpack(game->backpack, cleansing) == false){
        cleansing = destroy_item(cleansing);
        printf("The cleansing could not be carried.\n");
        return;
    }

    printf("Miquella's Needle stills the Frenzied Flame. You receive MIQUELLAS CLEANSING.\n");
}

static int standard_lord_rune(const char* rune){
    if(text_is(rune, "RUNE OF GODRICK") != 0){
        return 1;
    }

    if(text_is(rune, "RUNE OF RENNALA") != 0){
        return 1;
    }

    if(text_is(rune, "RUNE OF RADAHN") != 0){
        return 1;
    }

    if(text_is(rune, "RUNE OF MORGOTT") != 0){
        return 1;
    }

    return 0;
}

static void finish_with_rune(struct game* game, const char* rune){
    if(game == NULL || rune == NULL){
        return;
    }

    if(player_is_in(game, "HEART OF THE ERDTREE") == 0){
        printf("This rune has no final power here.\n");
        return;
    }

    if(count_player_runes(game) < 3){
        printf("You need at least three runes to claim an ending.\n");
        return;
    }

    if(player_has(game, rune) == 0){
        printf("You do not carry this rune.\n");
        return;
    }

    printf("\n");

    if(standard_lord_rune(rune) != 0){
        printf("You became the TUKE Lord, ruler of the Lands Between and servant of the Greater Will.\n");
    }
    else if(text_is(rune, "RUNE OF RANNI") != 0){
        printf("You became Ranni's consort. The Age of Stars begins, cold and distant, beyond the reach of the Greater Will.\n");
    }
    else if(text_is(rune, "RUNE OF MOHG") != 0){
        printf("You became the consort of Mohg. The Bloody Dynasty rises, and the Lands Between drown beneath a crimson oath.\n");
    }
    else if(text_is(rune, "RUNE OF RYKARD") != 0){
        printf("The world serpent awakens. It devours you, the Erdtree and the Lands Between. All becomes one inside the endless hunger.\n");
    }
    else if(text_is(rune, "RUNE OF FIA") != 0){
        printf("You became the lord of those who live in death. The dead are no longer rejected, and the world learns to breathe beside them.\n");
    }
    else if(text_is(rune, "RUNE OF GOLDMASK") != 0){
        printf("You restored the Golden Order and forged a colder, perfect law. No god, no passion, no contradiction may bend it again.\n");
    }
    else if(text_is(rune, "RUNE OF MALENIA") != 0){
        printf("You became the consort of Miquella. A world without suffering begins, a world of eternal deception.\n");
    }
    else if(text_is(rune, "RUNE OF DUNG EATER") != 0){
        printf("You became the lord of a cursed world. No soul will be born clean again.\n");
    }
    else if(text_is(rune, "RUNE OF THREE FINGERS") != 0){
        chaos_ending(game);
        return;
    }
    else{
        printf("This rune cannot shape a new age.\n");
        return;
    }

    ending_quote();

    game->state = SOLVED;
}

static void use_item(struct game* game, const char* name){
    if(game == NULL){
        return;
    }

    if(name == NULL){
        printf("Neviem, co chces pouzit.\n");
        return;
    }

    struct item* item = visible_or_carried_item(game, name);

    if(item == NULL){
        printf("Taky predmet nemas ani ho nevidis.\n");
        return;
    }

    if((item->properties & USABLE) == 0u){
        printf("Tento predmet sa neda pouzit.\n");
        return;
    }

    if(text_is(item->name, "MIQUELLAS NEEDLE") != 0 &&
       player_is_in(game, "PLACIDUSAX ARENA") != 0){
        create_cleansing(game);
        return;
    }

    if(name_is_rune(item->name) != 0){
        finish_with_rune(game, item->name);
        return;
    }

    printf("Pouzil si: %s\n", item->name);
    printf("Nic zvlastne sa nestalo.\n");
}

void execute_command(struct game* game, struct command* command){
    if(game == NULL || command == NULL || game->current_room == NULL){
        return;
    }

    if(game->state != PLAYING){
        return;
    }

    if(text_is(command->name, "KONIEC") != 0){
        printf("Koniec hry.\n");
        game->state = GAMEOVER;
    }
    else if(text_is(command->name, "SEVER") != 0){
        move_to_room(game, game->current_room->north);
    }
    else if(text_is(command->name, "JUH") != 0){
        move_to_room(game, game->current_room->south);
    }
    else if(text_is(command->name, "VYCHOD") != 0){
        move_to_room(game, game->current_room->east);
    }
    else if(text_is(command->name, "ZAPAD") != 0){
        move_to_room(game, game->current_room->west);
    }
    else if(text_is(command->name, "ROZHLIADNI SA") != 0){
        show_room(game->current_room);
    }
    else if(text_is(command->name, "PRIKAZY") != 0){
        list_commands(game);
    }
    else if(text_is(command->name, "VERZIA") != 0){
        printf("Elden Ring TUKE Edition, verzia 1.0\n");
    }
    else if(text_is(command->name, "RESTART") != 0){
        printf("Restart hry.\n");
        game->state = RESTART;
    }
    else if(text_is(command->name, "O HRE") != 0){
        game_intro();
    }
    else if(text_is(command->name, "VEZMI") != 0){
        take_item(game, command_argument(command));
    }
    else if(text_is(command->name, "POLOZ") != 0){
        drop_item(game, command_argument(command));
    }
    else if(text_is(command->name, "INVENTAR") != 0){
        list_inventory(game);
    }
    else if(text_is(command->name, "POUZI") != 0){
        use_item(game, command_argument(command));
    }
    else if(text_is(command->name, "PRESKUMAJ") != 0){
        examine_item(game, command_argument(command));
    }
}

struct game* create_game(void){
    struct game* game = malloc(sizeof(struct game));

    if(game == NULL){
        return NULL;
    }

    game->state = PLAYING;
    game->parser = create_parser();
    game->world = create_world();
    game->backpack = create_backpack(64);
    game->current_room = NULL;

    if(game->world != NULL && game->world->type == ROOM){
        game->current_room = game->world->room;
    }

    if(game->parser == NULL || game->world == NULL || game->backpack == NULL || game->current_room == NULL){
        game = destroy_game(game);
        return NULL;
    }

    return game;
}

struct game* destroy_game(struct game* game){
    if(game == NULL){
        return NULL;
    }

    game->backpack = destroy_backpack(game->backpack);
    game->world = destroy_world(game->world);
    game->parser = destroy_parser(game->parser);

    free(game);

    return NULL;
}

void play_game(struct game* game){
    if(game == NULL){
        return;
    }

    char input[INPUT_BUFFER_SIZE + 2];

    game_intro();
    show_room(game->current_room);

    while(game->state == PLAYING){
        printf("> ");

        if(fgets(input, sizeof(input), stdin) == NULL){
            game->state = GAMEOVER;
            break;
        }

        if(strchr(input, '\n') == NULL && feof(stdin) == 0){
            int character = 0;

            do{
                character = getchar();
            }while(character != '\n' && character != EOF);

            printf("Prikaz je prilis dlhy.\n");
            continue;
        }

        struct command* command = parse_input(game->parser, input);

        if(command == NULL){
            printf("Nerozumiem prikazu.\n");
        }
        else{
            execute_command(game, command);
        }
    }

    if(game->state == SOLVED){
        printf("\nHra bola uspesne dokoncena.\n");
    }
}

int run_game_application(void){
    enum gamestate last_state = GAMEOVER;

    do{
        struct game* game = create_game();

        if(game == NULL){
            fprintf(stderr, "Hru sa nepodarilo vytvorit.\n");
            return 1;
        }

        play_game(game);
        last_state = game->state;
        game = destroy_game(game);
    }while(last_state == RESTART);

    return 0;
}
