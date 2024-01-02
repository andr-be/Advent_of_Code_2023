#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_SOLUTIONS 256
#define MAX_LINE_LEN 80
#define MAX_RACES 8

typedef struct Race {
    int time;
    int distance;
    int solution_count;
    int solutions[MAX_SOLUTIONS];
} Race;

int p1_solution(FILE *input);

/// @brief parses the file and fills out the race times and distances
/// @param races an empty array of races
/// @param input the file to parse
/// @return the total number of races
int parse_races(Race *races, FILE *input);

/// @brief calculcates the different possible solutions for a given race
/// @param race the race to calculate solutions for
void calculate_solutions(Race *race);


int p2_solution(FILE *input); 

