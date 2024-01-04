// Advent of Code Day xx - Title
// andr-be 12/2023
/*
    Part 1:
    Part 2:
*/

#include "template.h"

int main(int argc, char const *argv[])
{
    char *filename;
    if (argc > 1 && strcmp(argv[1], "-test") == 0) {
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
    int solution = 0;

    return solution;
}

int p2_solution(FILE *input) 
{
    int solution = 0;

    return solution;
}