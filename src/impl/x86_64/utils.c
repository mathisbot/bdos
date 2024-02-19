#include "utils.h"


/**
* @brief Compare two strings
*
* @param str1 The first string
* @param str2 The second string
* @return 1 if the strings are equal, 0 otherwise, -1 if an error occured
*
* @note This function assumes str1 and str2 are 65536 characters long, null-terminator included.
*/
int8_t string_compare(char *str1, char *str2) {
    for (int i=0; 1; i++) {
        if (str1[i] != str2[i]) return 0;
        if (str1[i] == '\0') return 1;
    }
    return 2;  // Should never happen
}


/**
 * @brief Extract two strings from the input
 * 
 * @param input The input string
 * @param first The first string
 * @param second The second string
 * @param delimiter The delimiter
 *
 * @note Sizes are not checked
*/
void string_split(char *input, char *first, char *second, char delimiter) {
    int i = 0;
    while (input[i] != delimiter && input[i] != '\0') {
        first[i] = input[i];
        i++;
    }
    first[i] = '\0';
    if (input[i] == '\0') {
        second[0] = '\0';
        return;
    }
    i++;  // Skip delimiter
    int j = 0;
    while (input[i] != '\0') {
        second[j] = input[i];
        i++;
        j++;
    }
    second[j] = '\0';
}
