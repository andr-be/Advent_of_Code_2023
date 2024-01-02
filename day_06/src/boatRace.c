// Advent of Code Day 6 - Wait For It
// andr-be 12/2023
/*
    Part 1: 1312850
    Part 2:
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

    printf("\nSOLUTIONS:\nPart 1:\t%d\n", p1_solution(input));
    printf("Part 2:\t%d\n", p2_solution(input));

    return 0;
}

int p1_solution(FILE *input) 
{
    Race races[MAX_RACES] = {0};
    int race_count = parse_races(races, input);
    int solution = 0;

    for (int i = 0; i < race_count; i++)
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
    return solution;
}

int parse_races(Race *races, FILE *input)
{
    char times[MAX_LINE_LEN] = {0};
    fgets(times, MAX_LINE_LEN, input);
    int i = 0;
    for (char *pT = strtok(times, ":"); pT != NULL; pT = strtok(NULL, " "))
    {
        if (isdigit(*pT)) 
        {
            races[i++].time = atoi(pT);
        }
    }

    char dists[MAX_LINE_LEN] = {0};
    fgets(dists, MAX_LINE_LEN, input);
    i = 0;
    for (char *pD = strtok(dists, ":"); pD != NULL; pD = strtok(NULL, " "))
    {
        if (isdigit(*pD)) 
        {
            races[i++].distance = atoi(pD);
        }
    }

    return i;
}

void calculate_solutions(Race *race)
{
    for (int hold_time = 0; hold_time < race->time; hold_time++)
    {
        int travel_time = race->time - hold_time;
        if (travel_time * hold_time > race->distance)
        {
            race->solutions[race->solution_count++] = hold_time;
        }
    }
}


int p2_solution(FILE *input) 
{
    int solution = 0;

    return solution;
}