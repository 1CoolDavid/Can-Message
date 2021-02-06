#include "lib/binmatrix.h"
#include <stdio.h>
#include <malloc.h>
#include <ctype.h>


bool **read_complex_matrix_string(FILE *fp, int *r, int *c){
    char dimBuf[5];
    fp = fopen("../input.txt", "a+");
    if(fp == NULL) {
        return NULL;
    }
    int row = -1, col = -1;
    fscanf(fp, "%[^\n]", dimBuf); //Get dimension line

    bool splitter = false;

    for(int i = 4; i >= 0; i--) {
        if(!isdigit(dimBuf[i]) && dimBuf[i] != ',') {
            continue;
        }
        if(!splitter) {
            if(dimBuf[i] == ',') {
                splitter = true;
            } else {
                int entry = dimBuf[i] - '0';
                col = (col != -1) ? (entry*10) + col : entry;
            }
        } else {
            int entry = dimBuf[i] - '0';
            row = (row != -1) ? (entry*10) + row : entry;
        }
    }

    if(fgetc(fp) == '\n')
        fseek(fp, sizeof(dimBuf) + sizeof(char), SEEK_SET);
    else
        fseek(fp, sizeof(dimBuf), SEEK_SET);

    char matrixBuf[row*col + 1];
    fscanf(fp, "%[^\n]", matrixBuf); //Get matrix line
    fclose(fp);

    //bool **matrix = (bool **)malloc((row*(col)) * sizeof(bool));
    // Bad code, malloc() returns a contiguous block of memory
    // ^ was giving us a 1D array in memory (pointer to multiple bool) when we wanted pointer to pointer to bool
    // Hence, solution is below.

    //void *ptr = matrixBuf;
    //bool (*matrix)[row] = ptr;
    // dynamically set size based on matrix of pointers point to the void pointer of size matrixBuf
    // Dynamic set may be too much since there's no easy way of returning or setting it to a pointer :(
    // Would work if I knew dimensions before hand.


    bool **matrix = malloc(sizeof(bool*) * row);
    for(int i = 0; i<row; i++) {
        matrix[i] = malloc(sizeof(bool) * col);
    }

    for(int i = 0; i<row; ++i) {
        for(int j = 0; j<col; ++j) {
            bool addition = (matrixBuf[(i*row) + j] == '1');
            *(*(matrix + i) + j) = addition;
        }
    }
    *r = row;
    *c = col;

    return matrix;
}

char *read_and_convert_matrix_string(FILE *fp, int *r) {
    fp = fopen("../input.txt", "r");
    char dimBuf[2];
    *r = -1;

    if(fp == NULL) return NULL;

    fscanf(fp, "%[^\n]", dimBuf);

    for(int i = 1; i >= 0; i--) {
        if(!isdigit(dimBuf[i])) {
            continue;
        }
        int entry = dimBuf[i] - '0';
        *r = ((*r == -1) ? entry : *r + entry*10);
    }
    if(fgetc(fp) == '\n') {
        fseek(fp, sizeof(dimBuf) + sizeof(char), SEEK_SET);
    } else {
        fseek(fp, sizeof(dimBuf), SEEK_SET);
    }

    char matrixBuf[(*r * 8)];
    fread(matrixBuf, sizeof(char), (*r * 8) + 1, fp);

    bool **output = malloc(sizeof(bool *) * *r);
    for(int i = 0; i < *r; i++) {
        output[i] = malloc(sizeof(bool) * 8);
    }

    for(int i = 0; i < *r; i++) {
        for(int j = 0; j<8; j++) {
            char current = matrixBuf[(8*i) + j];
            bool addition = current == '1';
            output[i][j] = addition;
        }
    }

    char *word = bin_matrix_to_string(output, *r);

    return word;
}

bool **read_and_convert_string(FILE *fp, int *rows) {
    fp = fopen("../input.txt", "r");
    char buffer[20];
    char current;
    int i = 0;
    while(i < 20) {
        current = fgetc(fp);
        if(current != '\n' && current != EOF)
            buffer[i] = current;
        else
            break;
        i++;
    }
    buffer[i] = '\0';
    *rows = strlen(buffer);

    bool **matrix = malloc(sizeof(bool *) * *rows);

    for(int i = 0; i<*rows; i++) {
        matrix[i] = malloc(sizeof(bool) * 8);
    }

    string_to_bin_matrix(buffer, matrix);

    return matrix;
}

void write_string(FILE *fp, char *string) {
    fp = fopen("../output.txt", "w");
    fputs(string, fp);
    fclose(fp);
}

void write_simple_matrix(FILE *fp, bool **matrix, int row) {
    fp = fopen("../output.txt", "w");
    for(int i = 0; i<row; i++) {
        for(int j = 0; j<8; j++) {
            char output = matrix[i][j] ? '1' : '0';
            fputc(output, fp);
        }
    }
    fclose(fp);
}


int main() {
    FILE *fptr;
    int row = 0;

    bool **output = read_and_convert_string(fptr, &row);
    write_simple_matrix(fptr, output, row);


//    bool **matrix = read_matrix_string(fptr, &row);
//    char *string = bin_matrix_to_string(matrix, row);
    free(fptr);
    free(output);
    return  0;
}
