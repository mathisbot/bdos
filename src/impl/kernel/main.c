#include "print.h"


void kernel_main() {
    print_clear();
    print_set_color(PRINT_COLOR_CYAN, PRINT_COLOR_YELLOW);
    print_str("Welcome to B-DOS!\nA simple very simple 64-bit operating system");
}
