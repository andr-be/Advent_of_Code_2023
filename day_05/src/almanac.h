#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX 256
#define S_MAX 32
#define STAGES 8

typedef enum Stage {
    SEED,
    SOIL,
    FERTILISER,
    WATER,
    LIGHT,
    TEMPERATURE,
    HUMIDITY,
    LOCATION
} Stage;

typedef struct Almanac {
    int count;
    Stage current_stage;
    int almanac[STAGES][S_MAX];
} Almanac; 

int p1_solution(FILE *input);
Almanac gather_seeds(FILE *input);
void to_soil(FILE *input, Almanac *almanac);
void calculate_next_stage(FILE *input, Almanac *almanac);
int map(int current, int destination, int source);
int lowest_location(Almanac *alm);

int p2_solution(FILE *input);