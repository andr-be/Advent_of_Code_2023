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
    Schematic new = {0};
    for(int line = 0; !feof(input); line++)
    {
        char line_buffer[MAX_WIDTH] = {0};
        fgets(line_buffer, MAX_WIDTH - 1, input);
        if (new.Height == 0) {
            new.Height = strlen(line_buffer) - 1;
            new.Width = new.Height;
        }

        int position = 0;
        for (char *pC = line_buffer; *pC; pC++) 
        {
            new.Schematic[line][position++] = *pC;
        }
    }
    return new;
}

void print_schematic(Schematic *sch, char *mode)
{
    for (size_t y = 0; y < sch->Height; y++) 
    {
        for (size_t x = 0; x < sch->Width; x++) 
        {
            char current = sch->Schematic[y][x];
            if (strcmp(mode, "r") == 0) {
                printf("%c", current);    
            } 
            else if (strcmp(mode, "p") == 0) {
                printf("%c", (current == '.') ? ' ' : current);
            } 
            else if (strcmp(mode, "s") == 0) {
                if (!isalnum(current) && current != '.')
                    printf("%c", current);
            } 
            else {
                printf("ERROR: INVALID MODE\n");
            }
        }
        putchar('\n');
    }
}

void calculate_schematic(Schematic *sch)
{
    for (int y = 0; y < (int) sch->Height; y++) 
    {
        for (int x = 0; x < (int) sch->Width; x++) 
        {
            char c = sch->Schematic[y][x];
            if (is_symbol(c)) 
            {
                sch->Sum += adjacent_numbers(sch, x, y);
            }
        }
    }
}

bool is_symbol(char c)
{
    if (isalnum(c) || c == '.' || isspace(c)) return false;
    else return true;
}

int adjacent_numbers(Schematic *sch, int x, int y)
{
    int sum = 0, previous = 0;

    for (int i_y = -1; i_y < 2; i_y++) {
        for (int i_x = -1; i_x < 2; i_x++) {
            int new = number_at(sch, x + i_x, y + i_y);
            if (previous != new) {
                sum += new;
                previous = new;
            }
        }
    }
    return sum;
}

int number_at(Schematic *sch, int x, int y)
{
    if (y > (int) sch->Height || y < 0 || x > (int) sch->Width || x < 0) 
        return 0;

    char number_buffer[4] = {0};
    if (isdigit(sch->Schematic[y][x])) 
    {
        int o_x = x;
        while(isdigit(sch->Schematic[y][o_x - 1]) && o_x > 0) 
            o_x--;

        for (int i = 0; isdigit(sch->Schematic[y][o_x]) && o_x < (int) sch->Width; i++, o_x++)
            number_buffer[i] = sch->Schematic[y][o_x];
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
            char c = sch->Schematic[y][x];
            if (c == '*') 
            {
                sch->GearRatio += gear_numbers(sch, x, y);
            }
        }
    }
}

int gear_numbers(Schematic *sch, int x, int y)
{
    int previous = 0,
        gears[2] = {0},
        i = 0;

    for (int i_y = -1; i_y < 2; i_y++) 
    {
        for (int i_x = -1; i_x < 2; i_x++) 
        {
            int new = number_at(sch, x + i_x, y + i_y);

            if (previous != new && new > 0) {
                gears[i++] = new;
                previous = new;
            }
        }
    }

    if (gears[0] == 0 || gears[1] == 0)
        return 0;

    else return gears[0] * gears[1];
}