#include "print.h"


void kernel_main() {

    // Welcome message
    print_clear();
    print_set_color(PRINT_COLOR_WHITE, PRINT_COLOR_BLACK);
    print_str("Welcome to B-DOS! A very simple 64-bit operating system\nPress any key :\n");
}
