#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_RED 12
#define MAX_GREEN 13
#define MAX_BLUE 14

#define LINE_MAX 256
#define GAMES_MAX 512

typedef struct Count {
    int Red;
    int Green;
    int Blue;
} Count;

int p1_solution(FILE *input);
bool valid_round(char *round);
bool valid_count(char *count);

int p2_solution(FILE *input);
void update_count(Count *game_count, char* round_buffer);
