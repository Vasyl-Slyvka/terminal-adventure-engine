#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#include "parser.h"

static char* copy_text(const char* text){
    if(text == NULL){
        return NULL;
    }

    size_t length = strlen(text);
    char* copy = malloc((length + 1) * sizeof(char));

    if(copy == NULL){
        return NULL;
    }

    for(size_t i = 0; i <= length; i = i + 1){
        copy[i] = text[i];
    }

    return copy;
}

static int same_word(const char* a, const char* b){
    if(a == NULL || b == NULL){
        return 0;
    }

    size_t i = 0;

    while(a[i] != '\0' && b[i] != '\0'){
        if(tolower((unsigned char)a[i]) != tolower((unsigned char)b[i])){
            return 0;
        }

        i = i + 1;
    }

    return a[i] == '\0' && b[i] == '\0';
}

static char* trimmed_copy(const char* input){
    if(input == NULL){
        return NULL;
    }

    size_t begin = 0;
    size_t end = strlen(input);

    while(input[begin] != '\0' && isspace((unsigned char)input[begin]) != 0){
        begin = begin + 1;
    }

    while(end > begin && isspace((unsigned char)input[end - 1]) != 0){
        end = end - 1;
    }

    size_t length = end - begin;
    char* result = malloc((length + 1) * sizeof(char));

    if(result == NULL){
        return NULL;
    }

    for(size_t i = 0; i < length; i = i + 1){
        result[i] = input[begin + i];
    }

    result[length] = '\0';

    return result;
}

static char* take_first_word(const char* line){
    if(line == NULL){
        return NULL;
    }

    size_t length = 0;

    while(line[length] != '\0' && isspace((unsigned char)line[length]) == 0){
        length = length + 1;
    }

    char* word = malloc((length + 1) * sizeof(char));

    if(word == NULL){
        return NULL;
    }

    for(size_t i = 0; i < length; i = i + 1){
        word[i] = line[i];
    }

    word[length] = '\0';

    return word;
}

static char* take_rest_after_first_word(const char* line){
    if(line == NULL){
        return NULL;
    }

    size_t i = 0;

    while(line[i] != '\0' && isspace((unsigned char)line[i]) == 0){
        i = i + 1;
    }

    while(line[i] != '\0' && isspace((unsigned char)line[i]) != 0){
        i = i + 1;
    }

    if(line[i] == '\0'){
        return NULL;
    }

    return trimmed_copy(line + i);
}

static void reset_groups(struct command* command){
    if(command == NULL || command->groups == NULL){
        return;
    }

    for(size_t i = 0; i < command->nmatch; i = i + 1){
        free(command->groups[i]);
        command->groups[i] = NULL;
    }
}

static int write_group(struct command* command, size_t index, const char* value){
    if(command == NULL || command->groups == NULL){
        return 1;
    }

    if(index >= command->nmatch){
        return 1;
    }

    if(value == NULL){
        return 1;
    }

    command->groups[index] = copy_text(value);

    if(command->groups[index] == NULL){
        return 0;
    }

    return 1;
}

static struct command* find_parser_command(struct parser* parser, const char* name){
    if(parser == NULL || name == NULL){
        return NULL;
    }

    return get_from_container_by_name(parser->commands, name);
}

static int insert_command(struct parser* parser, struct command* command){
    if(parser == NULL || command == NULL){
        command = destroy_command(command);
        return 0;
    }

    struct container* created = create_container(parser->commands, COMMAND, command);

    if(created == NULL){
        command = destroy_command(command);
        return 0;
    }

    if(parser->commands == NULL){
        parser->commands = created;
    }

    return 1;
}

static int save_history_line(struct parser* parser, const char* line){
    if(parser == NULL || line == NULL || line[0] == '\0'){
        return 0;
    }

    char* copy = copy_text(line);

    if(copy == NULL){
        return 0;
    }

    struct container* created = create_container(parser->history, TEXT, copy);

    if(created == NULL){
        free(copy);
        return 0;
    }

    if(parser->history == NULL){
        parser->history = created;
    }

    return 1;
}

static int should_go_to_history(const char* command_name, const char* parameter){
    if(command_name == NULL){
        return 0;
    }

    if(same_word(command_name, "SEVER") != 0){
        return 1;
    }

    if(same_word(command_name, "JUH") != 0){
        return 1;
    }

    if(same_word(command_name, "VYCHOD") != 0){
        return 1;
    }

    if(same_word(command_name, "ZAPAD") != 0){
        return 1;
    }

    if(same_word(command_name, "VEZMI") != 0 ||
       same_word(command_name, "POLOZ") != 0 ||
       same_word(command_name, "POUZI") != 0){
        return parameter != NULL && parameter[0] != '\0';
    }

    return 0;
}

static struct command* make_parser_result(
    struct parser* parser,
    const char* command_name,
    const char* original_line,
    const char* keyword,
    const char* parameter
){
    struct command* command = find_parser_command(parser, command_name);

    if(command == NULL){
        return NULL;
    }

    reset_groups(command);

    if(write_group(command, 0, original_line) == 0){
        return NULL;
    }

    if(command->nmatch > 1){
        if(write_group(command, 1, keyword) == 0){
            return NULL;
        }
    }

    if(parameter != NULL && command->nmatch > 3){
        if(write_group(command, 2, parameter) == 0){
            return NULL;
        }

        if(write_group(command, 3, parameter) == 0){
            return NULL;
        }
    }

    if(should_go_to_history(command_name, parameter) != 0){
        (void)save_history_line(parser, original_line);
    }

    return command;
}

static struct command* parse_single_word_command(struct parser* parser, const char* line, const char* first_word){
    if(same_word(first_word, "KONIEC") != 0 ||
       same_word(first_word, "QUIT") != 0 ||
       same_word(first_word, "EXIT") != 0){
        return make_parser_result(parser, "KONIEC", line, first_word, NULL);
    }

    if(same_word(first_word, "SEVER") != 0 || same_word(first_word, "S") != 0){
        return make_parser_result(parser, "SEVER", line, first_word, NULL);
    }

    if(same_word(first_word, "JUH") != 0 || same_word(first_word, "J") != 0){
        return make_parser_result(parser, "JUH", line, first_word, NULL);
    }

    if(same_word(first_word, "VYCHOD") != 0 || same_word(first_word, "V") != 0){
        return make_parser_result(parser, "VYCHOD", line, first_word, NULL);
    }

    if(same_word(first_word, "ZAPAD") != 0 || same_word(first_word, "Z") != 0){
        return make_parser_result(parser, "ZAPAD", line, first_word, NULL);
    }

    if(same_word(first_word, "PRIKAZY") != 0 ||
       same_word(first_word, "HELP") != 0 ||
       same_word(first_word, "POMOC") != 0){
        return make_parser_result(parser, "PRIKAZY", line, first_word, NULL);
    }

    if(same_word(first_word, "VERZIA") != 0){
        return make_parser_result(parser, "VERZIA", line, first_word, NULL);
    }

    if(same_word(first_word, "RESTART") != 0){
        return make_parser_result(parser, "RESTART", line, first_word, NULL);
    }

    if(same_word(first_word, "ABOUT") != 0){
        return make_parser_result(parser, "O HRE", line, first_word, NULL);
    }

    if(same_word(first_word, "INVENTAR") != 0 || same_word(first_word, "I") != 0){
        return make_parser_result(parser, "INVENTAR", line, first_word, NULL);
    }

    return NULL;
}

static struct command* parse_two_word_command(
    struct parser* parser,
    const char* line,
    const char* first_word,
    const char* rest
){
    if(rest == NULL){
        return NULL;
    }

    if(same_word(first_word, "ROZHLIADNI") != 0 && same_word(rest, "SA") != 0){
        return make_parser_result(parser, "ROZHLIADNI SA", line, "ROZHLIADNI SA", NULL);
    }

    if(same_word(first_word, "O") != 0 && same_word(rest, "HRE") != 0){
        return make_parser_result(parser, "O HRE", line, "O HRE", NULL);
    }

    return NULL;
}

static struct command* parse_parameter_command(
    struct parser* parser,
    const char* line,
    const char* first_word,
    const char* rest
){
    if(same_word(first_word, "VEZMI") != 0){
        return make_parser_result(parser, "VEZMI", line, first_word, rest);
    }

    if(same_word(first_word, "POLOZ") != 0){
        return make_parser_result(parser, "POLOZ", line, first_word, rest);
    }

    if(same_word(first_word, "POUZI") != 0){
        return make_parser_result(parser, "POUZI", line, first_word, rest);
    }

    if(same_word(first_word, "PRESKUMAJ") != 0){
        return make_parser_result(parser, "PRESKUMAJ", line, first_word, rest);
    }

    return NULL;
}

struct parser* create_parser(void){
    struct parser* parser = malloc(sizeof(struct parser));

    if(parser == NULL){
        return NULL;
    }

    parser->commands = NULL;
    parser->history = NULL;

    if(insert_command(parser, create_command("KONIEC", "Ukonci rozohratu hru.", 2)) == 0 ||
       insert_command(parser, create_command("SEVER", "Presun na sever.", 2)) == 0 ||
       insert_command(parser, create_command("JUH", "Presun na juh.", 2)) == 0 ||
       insert_command(parser, create_command("VYCHOD", "Presun na vychod.", 2)) == 0 ||
       insert_command(parser, create_command("ZAPAD", "Presun na zapad.", 2)) == 0 ||
       insert_command(parser, create_command("ROZHLIADNI SA", "Zobrazi aktualnu miestnost.", 2)) == 0 ||
       insert_command(parser, create_command("PRIKAZY", "Zobrazi zoznam prikazov.", 2)) == 0 ||
       insert_command(parser, create_command("VERZIA", "Zobrazi verziu hry.", 2)) == 0 ||
       insert_command(parser, create_command("RESTART", "Restartuje hru.", 2)) == 0 ||
       insert_command(parser, create_command("O HRE", "Zobrazi informacie o hre.", 2)) == 0 ||
       insert_command(parser, create_command("VEZMI", "Vezme predmet.", 4)) == 0 ||
       insert_command(parser, create_command("POLOZ", "Polozi predmet.", 4)) == 0 ||
       insert_command(parser, create_command("INVENTAR", "Zobrazi obsah batohu.", 2)) == 0 ||
       insert_command(parser, create_command("POUZI", "Pouzije predmet.", 4)) == 0 ||
       insert_command(parser, create_command("PRESKUMAJ", "Preskuma predmet.", 4)) == 0){
        parser = destroy_parser(parser);
        return NULL;
    }

    return parser;
}

struct parser* destroy_parser(struct parser* parser){
    if(parser == NULL){
        return NULL;
    }

    parser->commands = destroy_containers(parser->commands);
    parser->history = destroy_containers(parser->history);

    free(parser);

    return NULL;
}

struct command* parse_input(struct parser* parser, const char* input){
    if(parser == NULL || input == NULL){
        return NULL;
    }

    char* line = trimmed_copy(input);

    if(line == NULL){
        return NULL;
    }

    if(line[0] == '\0'){
        free(line);
        return NULL;
    }

    char* first_word = take_first_word(line);
    char* rest = take_rest_after_first_word(line);

    if(first_word == NULL){
        free(rest);
        free(line);
        return NULL;
    }

    struct command* result = NULL;

    if(rest == NULL){
        result = parse_single_word_command(parser, line, first_word);
    }

    if(result == NULL){
        result = parse_two_word_command(parser, line, first_word, rest);
    }

    if(result == NULL){
        result = parse_parameter_command(parser, line, first_word, rest);
    }

    free(first_word);
    free(rest);
    free(line);

    return result;
}
