#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define LINE_MAX 256
#define S_MAX 32
#define R_MAX 128
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
    int64_t count;
    Stage current_stage;
    int64_t almanac[STAGES][S_MAX];
} Almanac;

typedef struct Range {
    int64_t start;
    int64_t length;
} Range;

typedef struct RangeAlmanac {
    int64_t count;
    Stage current_stage;
    Range almanac[STAGES][R_MAX];
} RangeAlmanac;

int64_t p1_solution(FILE *input);
Almanac gather_seeds(FILE *input);
void calculate_next_stage(FILE *input, Almanac *almanac);
int64_t map(int64_t current, int64_t destination, int64_t source);
int64_t lowest_location(Almanac *alm);
void debug_alm(Almanac *al);

int64_t p2_solution(FILE *input);
RangeAlmanac gather_more_seeds(FILE *input);
bool overlaps(Range a, Range b);
bool contains(Range a, Range b);
void split_and_append(RangeAlmanac *ra, Range seeds, Range source);