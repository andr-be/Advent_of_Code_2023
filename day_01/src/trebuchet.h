#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX 300
#define DIGIT_MAX 2
#define ARRAY_MAX 64

const char *numbers[] = {
    "one", "two", "three", "four", "five",
    "six", "seven", "eight", "nine"
};

int p1_solution(FILE *input);
char return_first_digit(char *input);
char return_last_digit(char *input);

int p2_solution(FILE *input);
int char_to_int(char c);
int first_number(char *string);
int last_number(char *string);