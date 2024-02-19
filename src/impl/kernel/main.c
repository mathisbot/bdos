#include "print.h"


// QWERTY keymap
// struct {
//     unsigned char scancode;
//     char key;
// } keymap[] = {
//     {0x1E, 'A'}, {0x30, 'B'}, {0x2E, 'C'}, {0x20, 'D'}, {0x12, 'E'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'},
//     {0x17, 'I'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x32, 'M'}, {0x31, 'N'}, {0x18, 'O'}, {0x19, 'P'},
//     {0x10, 'Q'}, {0x13, 'R'}, {0x1F, 'S'}, {0x14, 'T'}, {0x16, 'U'}, {0x2F, 'V'}, {0x11, 'W'}, {0x2D, 'X'},
//     {0x15, 'Y'}, {0x2C, 'Z'}, {0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'},
//     {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'}, {0x1C, '\n'}, {0x39, ' '}, {0xE, '\b'} // Enter, Space, Backspace
// };

// AZERTY keymap
struct {
    unsigned char scancode;
    char key;
} keymap[] = {
    {0x1E, 'Q'}, {0x30, 'B'}, {0x2E, 'C'}, {0x20, 'D'}, {0x12, 'E'}, {0x21, 'F'}, {0x22, 'G'}, {0x23, 'H'},
    {0x17, 'I'}, {0x24, 'J'}, {0x25, 'K'}, {0x26, 'L'}, {0x27, 'M'}, {0x31, 'N'}, {0x18, 'O'}, {0x19, 'P'},
    {0x10, 'A'}, {0x13, 'R'}, {0x1F, 'S'}, {0x14, 'T'}, {0x16, 'U'}, {0x2F, 'V'}, {0x11, 'Z'}, {0x2D, 'X'},
    {0x15, 'Y'}, {0x2C, 'W'}, {0x02, '1'}, {0x03, '2'}, {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'},
    {0x08, '7'}, {0x09, '8'}, {0x0A, '9'}, {0x0B, '0'}, {0x1C, '\n'}, {0x39, ' '}, {0xE, '\b'} // Enter, Space, Backspace
};


void kernel_main() {

    // Welcome message
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Welcome to B-DOS! A very simple 64-bit operating system\nPress any key :\n");
}


int print_key(char scancode) {
    // Find the key corresponding to the scancode
    int i;
    char key = '\0';
    for (int i=0; i<sizeof(keymap)/sizeof(keymap[0]); i++) {
        if (keymap[i].scancode == scancode) {
            key = keymap[i].key;
            break;
        }
    }

    if (key != '\0') print_char(key);

    return 0;
}