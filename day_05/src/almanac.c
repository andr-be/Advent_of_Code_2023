// Advent of Code Day 5 - Farmers Almanac
// andr-be 12/2023
/*
    Part 1: 157211394
    Part 2:
*/

#include "almanac.h"

#define DEBUG true

int main(int argc, char const *argv[])
{
    char *filename;
    if (DEBUG || (argc > 1 && strcmp(argv[1], "-test") == 0)) 
    {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");
    if (input != NULL) 
    {
        printf("\nSOLUTIONS:\nPart 1:\t%lld\n", p1_solution(input));
        printf("Part 2:\t%lld\n", p2_solution(input));
    } 
    else 
    {
        fprintf(stderr, "FILE ERROR: FILE %s COULD NOT BE OPENED", filename);
    }
    return 0;
}

int64_t p1_solution(FILE *input) 
{
    Almanac al = gather_seeds(input);
    while (!feof(input)) 
    {
        calculate_next_stage(input, &al);
    }
    if (DEBUG) debug_alm(&al);

    fseek(input, 0, SEEK_SET);
    return lowest_location(&al);
}

Almanac gather_seeds(FILE *input)
{
    Almanac new_alm = {.current_stage = SEED};
    char buffer[LINE_MAX] = {0};
    fgets(buffer, LINE_MAX - 1, input);
    
    int64_t i = 0;
    for (char *pS = strtok(buffer, ":"); pS != NULL; pS = strtok(NULL, " "))
    {
        if (isdigit(*pS))
        {
            new_alm.almanac[0][i++] = atoll(pS);
            new_alm.count += 1;
        }
    }
    return new_alm;
}

void calculate_next_stage(FILE *input, Almanac *alm)
{
    char buffer[LINE_MAX] = {0};
    fgets(buffer, LINE_MAX - 1, input);
    if (buffer[0] == '\n') 
    {
        alm->current_stage++;
    }
    else if (isdigit(buffer[0]))
    {
        int64_t destination, source, range; 

        char *pS = strtok(buffer, " ");
        destination = atoll(pS);
        
        pS = strtok(NULL, " ");
        source = atoll(pS);
        
        pS = strtok(NULL, " ");
        range = atoll(pS);

        for (int64_t i = 0; i < alm->count; i++)
        {
            int64_t stage = alm->current_stage, 
                    current = alm->almanac[stage - 1][i];

            if (current >= source && current < source + range)
            {
                alm->almanac[stage][i] = map(current, destination, source);
            } 
        }

        for (int64_t i = 0; i < alm->count; i++)
        {
            int64_t stage = alm->current_stage, 
                    current = alm->almanac[stage - 1][i];

            if (alm->almanac[stage][i] == 0)
            {
                alm->almanac[stage][i] = current;
            }
        }
    }
}

int64_t map(int64_t current, int64_t destination, int64_t source)
{
    current += (destination - source);
    return current; 
}

int64_t lowest_location(Almanac *alm)
{
    int64_t lowest = alm->almanac[LOCATION][0],
        candidate;

    for (int64_t i = 0; i < alm->count; i++) 
    {
        candidate = alm->almanac[LOCATION][i];
        if (candidate < lowest) 
        {
            lowest = candidate;
        }
    }

    return lowest;
}

void debug_alm(Almanac *al)
{
    printf("STAGE %d\n", al->current_stage);
    for (int64_t i = 0; i < al->count; i++)
    {
        for (int64_t j = 0; j <= LOCATION; j++)
        {
            if (al->almanac[j][i] != 0)
            {
                printf("%2lld ", al->almanac[j][i]);
                if (j < LOCATION) 
                {
                    printf("-> ");
                }
            }
        }
        printf("\n");
    }
    printf("\n");
}


int64_t p2_solution(FILE *input) 
{
    RangeAlmanac ra = gather_more_seeds(input);
    int64_t solution = 0;

    return solution;
}

RangeAlmanac gather_more_seeds(FILE *input)
{
    RangeAlmanac new_alm = {.current_stage = SEED};
    char buffer[LINE_MAX] = {0};
    fgets(buffer, LINE_MAX - 1, input);

    int64_t i = 0;
    for (char *pS = strtok(buffer, ":"); pS != NULL; pS = strtok(NULL, " "))
    {
        if (isdigit(*pS))
        {
            Range new_range = {.start = atoll(pS)};
            pS = strtok(NULL, " ");
            new_range.length = atoll(pS);
            new_alm.almanac[0][i++] = new_range;
            new_alm.count++;
        }
    }
    return new_alm;
}

/// @brief Tests whether the two ranges a and b overlap at all
/// @param a first range
/// @param b second range
/// @return true if any overlap, false if none
bool overlaps(Range a, Range b)
{
    bool result = ((a.start >= b.start && a.start < b.start + b.length) || 
                   (b.start >= a.start && b.start < a.start + a.length));

    return result;
}

/// @brief tests whether range a contains range b
/// @param a container range
/// @param b containee range
/// @return true if b is wholly contained by or identical to a, false otherwise
bool contains(Range a, Range b)
{
    return (a.start <= b.start && a.start + a.length >= b.start + b.length);
}

void calculate_next_range(FILE *input, RangeAlmanac *ra)
{
    char buffer[LINE_MAX] = {0};
    fgets(buffer, LINE_MAX - 1, input);
    if (buffer[0] == '\n') 
    {
        ra->current_stage++;
    }
    else if (isdigit(buffer[0]))
    {
        int64_t destination, source, range; 

        char *pS = strtok(buffer, " ");
        destination = atoll(pS);
        
        pS = strtok(NULL, " ");
        source = atoll(pS);
        
        pS = strtok(NULL, " ");
        range = atoll(pS);

        Range source_r = {.start = source, .length = range};
        for (int i = 0; i < ra->count; i++)
        {
            Range current = ra->almanac[ra->current_stage - 1][i];
            if (contains(source_r, current))
            {
                Range mapped = {
                    .start = map(current.start, destination, source), 
                    .length = current.length
                };
                ra->almanac[ra->current_stage][i] = mapped;
            } 
            else if (overlaps(source_r, current))
            {
                // split the range into matching vs. non matching ranges
                // append the new ranges to the end of the current set
                split_and_append(ra, &ra->almanac[ra->current_stage][i], source_r);
            }
            else 
            {
                ra->almanac[ra->current_stage][i] = current;
            }
        }
    }
}

/// @brief splits seeds into additional ranges; the overlapping sections of seeds and source, and the remaining sections
/// @param ra the almanac containing seeds
/// @param seeds the range to be split
/// @param source the overlapping section that dictates the split
void split_and_append(RangeAlmanac *ra, Range *seeds, Range source)
{

}