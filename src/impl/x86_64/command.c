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
    string_split(input, command, args, ' ');
}


/* ----- COMMANDS ----- */

// Command list
// Must be ordered alphabetically
static struct {
    char* name;
    char* desc;
} const command_list[] = {
    {name:"help", desc:"Shows this message."},
};

void help() {
    ("Available commands:\n");
    for (int i = 0; i < sizeof(command_list) / sizeof(command_list[0]); i++) {
        print_str("  - ");
        print_str(command_list[i].name);
        print_str(": ");
        print_str(command_list[i].desc);
        print_newline;
    }
}
