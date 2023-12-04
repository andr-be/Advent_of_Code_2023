#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define MAX_WIDTH 150
#define MAX_HEIGHT 150

typedef struct Schematic {
    size_t Height;
    size_t Width;
    int Sum;
    int GearRatio;
    char Schematic[MAX_HEIGHT][MAX_WIDTH];
} Schematic;

int p1_solution(FILE *input);
Schematic build_schematic(FILE *input);
void print_schematic(Schematic *sch, char *mode);
void calculate_schematic(Schematic *sch);
bool is_symbol(char c);
int adjacent_numbers(Schematic *sch, int x, int y);
int number_at(Schematic *sch, int x, int y);

int p2_solution(FILE *input);
void calculate_gears(Schematic *sch);
int gear_numbers(Schematic *sch, int x, int y);
