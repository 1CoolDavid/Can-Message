//
// Created by david on 1/31/2021.
//

#include <stdbool.h>
#include <string.h>

#ifndef CAN_MESSAGE_BINMATRIX_H
#define CAN_MESSAGE_BINMATRIX_H

char bin_array_to_char(bool bits[8]);

char* bin_matrix_to_string(bool **matrix, int letters);

void char_to_bin_array(char character, bool bits[8]);

void string_to_bin_matrix(char *string, bool **output);

#endif //CAN_MESSAGE_BINMATRIX_H



