#include "print.h"

// VGA text mode buffer
const static size_t NUM_COLS = 80;
const static size_t NUM_ROWS = 25;

// Characters are 2 bytes, first byte is the character, second byte is the color
struct Char {
    uint8_t character;
    uint8_t color;
};

// VGA text mode buffer starts at 0xb8000
struct Char* buffer = (struct Char*) 0xb8000;
size_t col = 0;
size_t row = 0;
uint8_t color = PRINT_COLOR_WHITE | PRINT_COLOR_BLACK << 4;

/*
* @brief Clear one row of the screen
*
* @param row The row to clear
*/
void clear_row(size_t row) {
    struct Char empty_char = (struct Char){character: ' ', color: color,};

    for (size_t col=0; col<NUM_COLS; col++) {
        buffer[NUM_COLS*row + col] = empty_char;
    }
}

/*
* @brief Clear the entire screen
*/
void print_clear() {
    for (size_t i = 0; i < NUM_ROWS; i++) {
        clear_row(i);
    }
}

/*
* @brief Move the cursor to the next line
*/
void print_newline() {
    col = 0;

    if (row < NUM_ROWS-1) {
        row++;
        return;
    }

    // Shift the rows up
    for (size_t row=1; row<NUM_ROWS; row++) {
        for (size_t col=0; col<NUM_COLS; col++) {
            struct Char c = buffer[NUM_COLS*row + col];
            buffer[NUM_COLS*(row-1) + col] = c;
        }
    }

    clear_row(NUM_COLS - 1);
}

/*
* @brief Print a character to the screen
*
* @param character The character to print
*/
void print_char(char c) {
    if (c == '\n') {
        print_newline();
        return;
    }

    if (col>NUM_COLS) {
        print_newline();
    }

    buffer[NUM_COLS*row + col] = (struct Char){
        character: (uint8_t) c,
        color: color,
    };

    col++;
}

/*
* @brief Print a string to the screen
*
* @param str The string to print
*/
void print_str(char* str) {
    for (size_t i = 0; 1; i++) {
        char c = (uint8_t) str[i];
        if (c == '\0') return;
        print_char(c);
    }
}

/*
* @brief Set the current color
*
* @param foreground The foreground color
* @param background The background color
*/
void print_set_color(uint8_t foreground, uint8_t background) {
    color = foreground + (background << 4);
}
