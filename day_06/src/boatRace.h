#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define MAX_SOLUTIONS 256
#define MAX_LINE_LEN 80
#define MAX_RACES 8

typedef struct Race {
    uint64_t time;
    uint64_t distance;
    uint64_t solution_count;
    uint64_t solutions[MAX_SOLUTIONS];
} Race;

uint64_t p1_solution(FILE *input);

/// @brief parses the file and fills out the race times and distances
/// @param races an empty array of races
/// @param input the file to parse
/// @return the total number of races
uint64_t parse_races(Race *races, FILE *input);

/// @brief calculcates the different possible solutions for a given race
/// @param race the race to calculate solutions for
void calculate_solutions(Race *race);


uint64_t p2_solution(FILE *input); 

/// @brief parses the input as one complete race, not multiple
/// @param input the input file
/// @return the parsed race
Race parse_races_p2(FILE *input);

/// @brief checks to see how many possible solutions there are for a race
/// @param race the race to be checked
/// @return the total number of solutions possible
uint64_t calculate_total_solutions(Race *race);
