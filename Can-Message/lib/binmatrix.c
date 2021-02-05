//
// Created by david on 1/31/2021.
//

#include "binmatrix.h"
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <malloc.h>
#include <stdio.h>

char bin_array_to_char(bool* bits) {
    unsigned int code = 0;
    for (int i = 0; i<8; i++) {
        code += (*(bits + i)) ? pow(2, 7-i) : 0;
    }
    char result = code;
    return result;
}

char* bin_matrix_to_string(bool **matrix, int letters) {
    char *string = malloc((letters) * sizeof(char) + 1);
    for(int i = 0; i < letters; i++) {
        char addition = bin_array_to_char(*(matrix + i));
        string[i] = addition;
    }
    string[letters] = '\0';
    return string;
}

void char_to_bin_array(char character, bool bits[8]) {
    for (int bit_index = 7; bit_index >= 0; bit_index--, character >>= 1)
        bits[bit_index] = character & 1;
}

void string_to_bin_matrix(char *string, bool **output) {
    size_t len = strlen(string);
    for(size_t i = 0; i<len; ++i) {
        bool* temp = output[i];
        char_to_bin_array(string[i], temp);
    }
}
