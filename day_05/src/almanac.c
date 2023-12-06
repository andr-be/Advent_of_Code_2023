// Advent of Code Day xx - Title
// andr-be 12/2023
/*
    Part 1:
    Part 2:
*/

#include "almanac.h"

#define DEBUG true

int main(int argc, char const *argv[])
{
    char *filename;
    if (DEBUG || (argc > 1 && strcmp(argv[1], "-test")) == 0) 
    {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");
    if (input != NULL) 
    {
        printf("\nSOLUTIONS:\nPart 1:\t%d\n", p1_solution(input));
        printf("Part 2:\t%d\n", p2_solution(input));
    } 
    else 
    {
        fprintf(stderr, "FILE ERROR: FILE %s COULD NOT BE OPENED", filename);
    }
    return 0;
}

int p1_solution(FILE *input) 
{
    Almanac al = gather_seeds(input);
    while (al.current_stage < LOCATION) 
    {
        calculate_next_stage(input, &al);
    }
    return lowest_location(&al);
}

Almanac gather_seeds(FILE *input)
{
    Almanac new_alm = {.current_stage = SEED};
    char buffer[LINE_MAX] = {0};
    fgets(buffer, LINE_MAX - 1, input);
    
    int i = 0;
    for (char *pS = strtok(buffer, ":"); pS != NULL; pS = strtok(NULL, " "))
    {
        if (isdigit(*pS))
        {
            new_alm.almanac[0][i++] = atoi(pS);
            new_alm.count += 1;
        }
    }
    return new_alm;
}

void seek_next_digit(FILE *file)
{
    while (!(isdigit(fgetc(file))))
        ;   // seek!
        
    fseek(file, -1L, SEEK_CUR);
}

void calculate_next_stage(FILE *input, Almanac *alm)
{
    if (alm->current_stage == LOCATION) return;
    seek_next_digit(input);

    char buffer[LINE_MAX] = {0};
    fgets(buffer, LINE_MAX - 1, input);

    int d_s_r[3] = {0};
    char *pS = strtok(buffer, " ");
    for (int i = 0; i < 3; i++)
    {
        d_s_r[i] = atoi(pS);
        pS = strtok(NULL, " ");
    }

    for (int i = 0; i < alm->count; i++)
    {
        int destination = d_s_r[0], 
            source = d_s_r[1],
            range = d_s_r[2],
            stage = alm->current_stage,
            current = alm->almanac[stage][i];

        if (current >= source && current < source + range)
        {
            alm->almanac[stage + 1][i] = map(current, destination, source);
        }
        else
        {
            alm->almanac[stage + 1][i] = current;
        }
    }
}

int map(int current, int destination, int source)
{
    current += (destination - source);
    return current; 
}

int lowest_location(Almanac *alm)
{
    int lowest = alm->almanac[LOCATION][0],
        candidate;

    for (int i = 0; i < alm->count; i++) 
    {
        candidate = alm->almanac[LOCATION][i];
        if (candidate < lowest) 
        {
            lowest = candidate;
        }
    }

    return lowest;
}

int p2_solution(FILE *input) 
{
    int solution = 0;

    return solution;
}