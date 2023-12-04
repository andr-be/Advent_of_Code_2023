// Advent of Code - Day 3 - Gear Ratios
// andr-be 12/2023
/*
    Part 1: 530849
    Part 2: 84900879
*/

#include "engine.h"

#define DEBUG false

int main(int argc, char const *argv[])
{
    char *filename;
    if (DEBUG || (argc > 1 && strcmp(argv[1], "-test") == 0)) {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");

    printf("\nSOLUTIONS:\nPart 1:\t%d\n", p1_solution(input));
    printf("Part 2:\t%d\n", p2_solution(input));

    fclose(input);
    return 0;
}

int p1_solution(FILE *input) 
{
    Schematic sch = build_schematic(input);
    calculate_schematic(&sch);
    fseek(input, 0, SEEK_SET);
    return sch.Sum;
}

Schematic build_schematic(FILE *input)
{
    Schematic sch = {0};
    for(int line = 0; !feof(input); line++)
    {
        char line_buffer[MAX_WIDTH] = {0};
        fgets(line_buffer, MAX_WIDTH - 1, input);
        if (sch.Height == 0) 
        {
            sch.Height = sch.Width = strlen(line_buffer) - 1;
        }

        int position = 0;
        for (char *pC = line_buffer; *pC; pC++) 
        {
            sch.Schema[line][position++] = *pC;
        }
    }
    return sch;
}

void calculate_schematic(Schematic *sch)
{
    for (int y = 0; y < (int) sch->Height; y++) 
    {
        for (int x = 0; x < (int) sch->Width; x++) 
        {
            char c = sch->Schema[y][x];
            if (is_symbol(c)) 
            {
                sch->Sum += adjacent_numbers(sch, x, y);
            }
        }
    }
}

bool is_symbol(char c)
{
    return !(isalnum(c) || c == '.' || isspace(c));
}

int adjacent_numbers(Schematic *sch, int x, int y)
{
    int sum = 0, previous = 0;

    for (int i_y = -1; i_y < 2; i_y++) 
    {
        for (int i_x = -1; i_x < 2; i_x++) 
        {
            int new = number_at(sch, x + i_x, y + i_y);
            if (previous != new) 
            {
                sum += new;
                previous = new;
            }
        }
    }
    return sum;
}

int number_at(Schematic *sch, int x, int y)
{
    if ( y > (int) sch->Height || y < 0 || 
         x > (int) sch->Width  || x < 0    ) 
        return 0;

    char number_buffer[NUM_LENGTH] = {0};
    if (isdigit(sch->Schema[y][x])) 
    {
        while (isdigit(sch->Schema[y][x - 1]) && x > 0)
            x--;

        for (int i = 0; isdigit(sch->Schema[y][x]) && x < (int) sch->Width;)
            number_buffer[i++] = sch->Schema[y][x++];
    }
    return atoi(number_buffer);
}

int p2_solution(FILE *input) 
{
    Schematic sch = build_schematic(input);
    calculate_gears(&sch);
    return sch.GearRatio;
}

void calculate_gears(Schematic *sch)
{
    for (int y = 0; y < (int) sch->Height; y++) 
    {
        for (int x = 0; x < (int) sch->Width; x++) 
        {
            char c = sch->Schema[y][x];
            if (c == '*')
                { sch->GearRatio += gear_numbers(sch, x, y); }
        }
    }
}

int gear_numbers(Schematic *sch, int x, int y)
{
    int previous = 0,
        gears[GEAR_NUM] = {0},
        i = 0;

    for (int i_y = -1; i_y < GEAR_NUM; i_y++) 
    {
        for (int i_x = -1; i_x < GEAR_NUM; i_x++) 
        {
            int new = number_at(sch, x + i_x, y + i_y);

            if (previous != new && new > 0 && i < GEAR_NUM) 
            {
                gears[i++] = new;
                previous = new;
            }
        }
    }
    if (gears[0] == 0 || gears[1] == 0) return 0;

    else return gears[0] * gears[1];
}