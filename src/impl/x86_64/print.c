#include "print.h"

// VGA text mode buffer
const static size_t VGA_WIDTH = 80;
const static size_t VGA_HEIGHT = 25;

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
* @brief Write a byte to a port
*
* @param value The value to write
* @param port The port to write to
*/
static inline void outb_c(uint16_t port, uint8_t value) {
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port) : "memory");
}

/*
* @brief Move the cursor to a specific position
*
* @param x The x position
* @param y The y position
*/
void move_cursor(uint8_t x, uint8_t y) {
    uint16_t pos = y * VGA_WIDTH + x;
	outb_c(0x3D4, 0x0F);
	outb_c(0x3D5, (uint8_t)(pos & 0xFF));
	outb_c(0x3D4, 0x0E);
	outb_c(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}


/*
* @brief Clear the entire screen
*/
void print_clear() {
    struct Char empty_char = (struct Char){character: ' ', color: color,};

    for (size_t row=0; row<VGA_HEIGHT; row++) {
        for (size_t col=0; col<VGA_WIDTH; col++) {
            buffer[VGA_WIDTH*row + col] = empty_char;
        }
    }
    col = 0;
    row = 0;
    move_cursor(0, 0);
}

/*
* @brief Move the cursor to the next line
*/
void print_newline() {
    col = 0;

    if (row < VGA_HEIGHT-1) {
        row++;
        move_cursor(col, row);
        return;
    }

    // Shift the rows up
    for (size_t row=1; row<VGA_HEIGHT; row++) {
        for (size_t col=0; col<VGA_WIDTH; col++) {
            struct Char c = buffer[VGA_WIDTH*row + col];
            buffer[VGA_WIDTH*(row-1) + col] = c;
            buffer[VGA_WIDTH*row + col] = (struct Char){character: ' ', color: color,};
        }
    }
    move_cursor(col, row);
}

/*
* @brief Move the cursor to the next line and adds a "> " at the beginning
*/
void print_new_command_line() {
    print_newline();
    print_str("> ");
}

/*
* @brief Delete the last character if possible
*/
void print_del_char() {
    uint8_t deletable = 1;
    if (col == 0 && row == 0) deletable = 0;
    if (col == 2 && buffer[row*VGA_WIDTH].character == '>') deletable = 0;

    if (!deletable) return;

    if (col == 0) {
        col = VGA_WIDTH-1;
        row--;
    } else {
        col--;
    }
    buffer[VGA_WIDTH*row + col] = (struct Char){character: ' ', color: color,};
    move_cursor(col, row);
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

    if (col>=VGA_WIDTH) print_newline();

    buffer[VGA_WIDTH*row + col] = (struct Char){
        character: (uint8_t) c,
        color: color,
    };

    col++;
    move_cursor(col, row);
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
