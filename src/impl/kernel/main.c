/*
 **********************************************************************
 *                              B-DOS                                 *
 *                                                                    *
 * Description:                                                       *
 * This file contains the implementation of the kernel                *
 * And, at least for now, some basic other things                     *
 *                                                                    *
 * Authors:                                                           *
 * - mathisbot https://github.com/mathisbot                           *
 *                                                                    *
 * Copyright (c) [2024] [mathisbot]                                   *
 *                                                                    *
 * This software is licensed under the Apache-2.0.                    *
 * You may use, distribute, and modify this code under the terms      *
 * of the Apache-2.0.                                                 *
 **********************************************************************
*/

#include "print.h"
#include "utils.h"
#include "command.h"


/* ----- CONST ---- */

// QWERTY keymap
// struct {
//     unsigned char scancode;
//     char key;
// } const keymap[] = {
//     {0x1E, 'A'}, {0x30, 'B'}, {0x2E, 'C'}, {0x20, 'D'}, {0x12, 'E'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'},
//     {0x17, 'I'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x32, 'M'}, {0x31, 'N'}, {0x18, 'O'}, {0x19, 'P'},
//     {0x10, 'Q'}, {0x13, 'R'}, {0x1F, 'S'}, {0x14, 'T'}, {0x16, 'U'}, {0x2F, 'V'}, {0x11, 'W'}, {0x2D, 'X'},
//     {0x15, 'Y'}, {0x2C, 'Z'}, {0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'},
//     {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'}, {0x39, ' '}
// };

// AZERTY keymap
struct {
    unsigned char scancode;
    char key;
} const keymap[] = {
    {0x1E, 'Q'}, {0x30, 'B'}, {0x2E, 'C'}, {0x20, 'D'}, {0x12, 'E'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'},
    {0x17, 'I'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x27, 'M'}, {0x31, 'N'}, {0x18, 'O'}, {0x19, 'P'},
    {0x10, 'A'}, {0x13, 'R'}, {0x1F, 'S'}, {0x14, 'T'}, {0x16, 'U'}, {0x2F, 'V'}, {0x11, 'Z'}, {0x2D, 'X'},
    {0x15, 'Y'}, {0x2C, 'W'}, {0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'},
    {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'}, {0x39, ' '}
};

/*
Other important scancodes:
- 0x1C: Enter
- 0x0E: Backspace
*/

static char command_buffer[8192];
static int command_buffer_index = 0;
char command[1024];
char args[8192];

/* ----- KERNEL ---- */

void kernel_main() {

    // Welcome message
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Welcome to B-DOS! A very simple 64-bit operating system\nPress any key :");
    print_new_command_line();

    // Other setup
    // ...
}


/* ----- COMMANDS ----- */

/*
Must be the same as in command.c
This is a temporary solution of a problem I had with the linker
Currently, adding a command recquires to :
- Add it to the list down there
- Add it to the list of functions in command.c
- Add its function to the list of functions in command.c
- Add its function to the list of functions in command.h
*/
static const command_t command_list[] = {
    {name:"HELP", desc:"Shows this message.", long_desc:"HELP <command> to show more information about <command>.", function:help},
    {name:"ECHO", desc:"ECHO <args> to print <args> on the screen.", long_desc:"", function:echo},
};

void handle_command() {
    command_buffer[command_buffer_index] = '\0';
    extract_command(command_buffer, command, args);
    for (int i = 0; i < sizeof(command_list) / sizeof(command_list[0]); i++) {
        if (string_compare(command_list[i].name, command) == 1) {
            // A function always takes a char* as argument
            command_list[i].function(args);
            return;
        }
    }
    print_str("Command not found. Type HELP for a list of commands.");
}


/* ----- KEYBOARD ---- */

void handle_key(char scancode) {
    // Find the key corresponding to the scancode
    int i;
    char key = '\0';
    for (int i=0; i<sizeof(keymap)/sizeof(keymap[0]); i++) {
        if (keymap[i].scancode == scancode) {
            key = keymap[i].key;
            break;
        }
    }

    if (key != '\0') {
        if (command_buffer_index>=65534) return;
        print_char(key);
        command_buffer[command_buffer_index] = key;
        command_buffer_index++;
    }
    else if (scancode == 0x1C) {
        if (command_buffer_index != 0) {
            print_newline();
            handle_command();
            command_buffer_index = 0;
        }
        print_new_command_line();
    }
    else if (scancode == 0x0E) {
        print_del_char();
        command_buffer_index--;
    }
}
