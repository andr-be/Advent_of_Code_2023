// Advent of Code 2023 - Day 2 - Cube Conundrum
// andr-be 12/2023
/*
    Part 1: 2541
    Part 2: 66016
*/

#include "cubes.h"

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
    char line_buffer[LINE_MAX] = {0};
    int possible_games[GAMES_MAX] = {0};
    int total_possible = 0;

    for (int current_game = 0; !feof(input); current_game++) 
    {
        fgets(line_buffer, LINE_MAX - 1, input);
        char *a, *b;

        a = strtok_s(line_buffer, ":", &b);
        // if (DEBUG) printf("GAME %d\n", current_game + 1);
        for (a = strtok_s(NULL, ";", &b); a != NULL; a = strtok_s(NULL, ";", &b))
        {
            char round_buffer[LINE_MAX] = {0};
            strcpy(round_buffer, a);
            if((possible_games[current_game] = valid_round(round_buffer)) == 0) {
                break;
            }
        }
    }
    for (int i = 0; i < GAMES_MAX; i++)
    {
        if (possible_games[i]) {
            total_possible += i + 1;
            // if (DEBUG) printf("GAME %d: VALID\n", i + 1);
        }
    }
    fseek(input, 0, SEEK_SET);
    return total_possible;
}

bool valid_round(char *round)
{
    // if (DEBUG) printf("%s\n", round);
    char *count = strtok(round, ",");
    while (count != NULL) {
        if (!valid_count(count)) 
            return false;

        count = strtok(NULL, ",");
    }
    return true;
}

bool valid_count(char *count)
{
    char colour = 0;
    int number = 0;

    sscanf(count, "%d %c", &number, &colour);
    // if (DEBUG) printf(" -> %s\t%d%c\n", count, number, colour);

    switch (colour)
    {
    case 'r': return number <= MAX_RED;
    case 'g': return number <= MAX_GREEN;
    case 'b': return number <= MAX_BLUE;

    default: return true;
    }
}

int p2_solution(FILE *input)
{
    int solution = 0;
    char line_buffer[256];

    for (int current_game = 0; !feof(input); current_game++) 
    {
        char *a, *b;
        int power = 0;
        Count game_count = {0};

        fgets(line_buffer, LINE_MAX - 1, input);
        a = strtok_s(line_buffer, ":", &b);

        for (a = strtok_s(NULL, ";", &b); a != NULL; a = strtok_s(NULL, ";", &b))
        {
            char round_buffer[LINE_MAX] = {0};
            strcpy(round_buffer, a);
            update_count(&game_count, round_buffer);
        }

        power = ( game_count.Red * game_count.Green * game_count.Blue );
        solution += power;
        if (DEBUG) printf("GAME %3d -> POWER: %4d  (%5d)\n", current_game + 1, power, solution);
    }
    
    return solution;
}

void update_count(Count *game_count, char* round_buffer)
{
    for (char *count = strtok(round_buffer, ","); count != NULL; count = strtok(NULL, ","))
    {
        char colour = 0;
        int number = 0;
        sscanf(count, "%d %c", &number, &colour);
        switch (colour)
        {
        case 'r': if (number > game_count->Red) game_count->Red = number; 
                  break;

        case 'g': if (number > game_count->Green) game_count->Green = number; 
                  break;

        case 'b': if (number > game_count->Blue) game_count->Blue = number; 
                  break;
        }
    } 
}
