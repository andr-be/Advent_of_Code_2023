// Advent of Code Day 6 - Wait For It
// andr-be 12/2023
/*
    Part 1: 1312850
    Part 2: 36749103
*/

#include "boatRace.h"

#define DEBUG false

int main(int argc, char const *argv[])
{
    char *filename;
    if ((argc > 1 && strcmp(argv[1], "-test") == 0) || DEBUG) {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");

    printf("\nSOLUTIONS:\nPart 1:\t%lld\n", p1_solution(input));
    printf("Part 2:\t%lld\n", p2_solution(input));

    return 0;
}

uint64_t p1_solution(FILE *input) 
{
    Race races[MAX_RACES] = {0};
    uint64_t race_count = parse_races(races, input);
    uint64_t solution = 0;

    for (uint64_t i = 0; i < race_count; i++)
    {
        calculate_solutions(&races[i]);
        if (solution == 0)
        {
            solution = races[i].solution_count;
        }
        else
        {
            solution *= races[i].solution_count;
        } 
    }

    fseek(input, 0, SEEK_SET);
    return solution;
}

uint64_t parse_races(Race *races, FILE *input)
{
    char times[MAX_LINE_LEN] = {0};
    fgets(times, MAX_LINE_LEN, input);
    uint64_t i = 0;
    for (char *pT = strtok(times, ":"); pT != NULL; pT = strtok(NULL, " "))
    {
        if (isdigit(*pT)) 
        {
            races[i++].time = (uint64_t) atoll(pT);
        }
    }

    char dists[MAX_LINE_LEN] = {0};
    fgets(dists, MAX_LINE_LEN, input);
    i = 0;
    for (char *pD = strtok(dists, ":"); pD != NULL; pD = strtok(NULL, " "))
    {
        if (isdigit(*pD)) 
        {
            races[i++].distance = (uint64_t) atoll(pD);
        }
    }

    return i;
}

void calculate_solutions(Race *race)
{
    for (uint64_t hold_time = 0; hold_time < race->time; hold_time++)
    {
        uint64_t travel_time = race->time - hold_time;
        if (travel_time * hold_time > race->distance)
        {
            race->solutions[race->solution_count++] = hold_time;
        }
    }
}


uint64_t p2_solution(FILE *input) 
{
    Race race = parse_races_p2(input);
    return calculate_total_solutions(&race);
}

Race parse_races_p2(FILE *input)
{
    char time_line[MAX_LINE_LEN] = {0},
         time_digs[MAX_LINE_LEN] = {0};
    
    fgets(time_line, MAX_LINE_LEN, input);
    for (uint64_t i = 0, j = 0; i < strlen(time_line); i++)
    {
        if (isdigit(time_line[i]))
        {
            time_digs[j++] = time_line[i];
        }
    }
    if (DEBUG) printf("TOTAL TIME: %s\n", time_digs);

    char dist_line[MAX_LINE_LEN] = {0},
         dist_digs[MAX_LINE_LEN] = {0};

    fgets(dist_line, MAX_LINE_LEN, input);
    for (uint64_t i = 0, j = 0; i < strlen(dist_line); i++)
    {
        if (isdigit(dist_line[i]))
        {
            dist_digs[j++] = dist_line[i];
        }
    }
    if (DEBUG) printf("TOTAL DIST: %s\n", dist_digs);

    Race new_race = {.time = (uint64_t) atoll(time_digs), .distance = (uint64_t) atoll(dist_digs)};
    return new_race;
}

uint64_t calculate_total_solutions(Race *race)
{
    for (size_t hold_time = 0; hold_time < race->time; hold_time++)
    {
        if ((hold_time) * (race->time - hold_time) > race->distance)
        {
            race->solution_count++;
            if (DEBUG) printf("NEW SOLUTION: %lld ms\n", hold_time);
        }
    }
    return race->solution_count;
}
