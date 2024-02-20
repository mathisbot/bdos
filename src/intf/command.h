#ifndef COMMAND_H
#define COMMAND_H

#include "print.h"
#include "utils.h"


typedef struct {
    char *name;
    char *desc;
    char *long_desc;
    void (*function)(char*);
} command_t;

// Temporary way of handling commands

void extract_command(char* input, char* command, char* args);

// Command functions
// All these function must take a char* as argument
void help(char* args);
void echo(char* args);

#endif
