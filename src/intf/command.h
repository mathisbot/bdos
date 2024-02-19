#ifndef COMMAND_H
#define COMMAND_H

#include "print.h"
#include "utils.h"


// Temporary way of handling commands

void extract_command(char* input, char* command, char* args);

// Command functions
void help();

#endif
