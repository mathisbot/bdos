#include "command.h"


/**
 * @brief Extract the command and its arguments from the input
 * 
 * @param input The input string
 * @param command The command
 * @param args The arguments
 *
 * @note Sizes are not checked
 */
void extract_command(char* input, char* command, char* args) {
    char* last_command_line = input;
    while (*input != '\0') {
        if (*input == '>') last_command_line = input+2;
        input++;
    }
    string_split(last_command_line, command, args, ' ');
}

// Must be ordered alphabetically
static const command_t command_list[] = {
    {name:"HELP", desc:"Shows this message.", long_desc:"HELP <command> to show more information about <command>.", function:help},
    {name:"ECHO", desc:"ECHO <args> to print <args> on the screen.", long_desc:"", function:echo},
};


/* ----- COMMANDS ----- */

void help(char *args) {
    if (args[0] != '\0') {
        for (int i = 0; i < sizeof(command_list) / sizeof(command_list[0]); i++) {
            if (string_compare(command_list[i].name, args) == 1) {
                print_str(command_list[i].name);
                print_str(": ");
                print_str(command_list[i].desc);
                print_newline();
                print_str(command_list[i].long_desc);
                return;
            }
        }
        print_str("Command not found.");
        return;
    }
    ("Available commands:\n");
    for (int i = 0; i < sizeof(command_list) / sizeof(command_list[0]); i++) {
        print_str("  - ");
        print_str(command_list[i].name);
        print_str(": ");
        print_str(command_list[i].desc);
        print_newline();
    }
    print_str("Some commands may provide more information using HELP <command>.");
}

void echo(char *args) {
    print_str(args);
}
