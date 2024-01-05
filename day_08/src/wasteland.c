// Advent of Code Day xx - Title
// andr-be 12/2023
/*
    Part 1:
    Part 2:
*/

#include "wasteland.h"

#define DEBUG true

int main(int argc, char const *argv[])
{
    char *filename;
    if (DEBUG) 
    {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");

    printf("SOLUTIONS:\n");
    printf("Part 1:\t%d\n", p1_solution(input));
    printf("Part 2:\t%d\n", p2_solution(input));

    return 0;
}

int p1_solution(FILE *input) 
{
    Tree tree = parse_tree(input);


    return 0;
}

Tree parse_tree(FILE *input)
{
    Tree n_tree = {0};

    char pattern_buffer[PATTERN_MAX + 1] = {0};
    fgets(pattern_buffer, PATTERN_MAX - 1, input);
    strcpy(n_tree.Pattern, pattern_buffer);

    while (!feof(input))
    {
        char line_buffer[LINE_MAX + 1] = {0};
        fgets(line_buffer, LINE_MAX, input);
        add_node(&n_tree, line_buffer);
    }
    return n_tree;
}

void add_node(Tree *tree, char *line)
{
    if ( !isalnum(*line) ) return;

    Node n_node = {0};
    for (char *pN = strtok(line, "="), int i = 9; isalpha(*pN); pN++)
    {
        n_node.Name[i] = *pN;
    }

    tree->Nodes[tree->Count++] = n_node;
}

int p2_solution(FILE *input) 
{

    return 0;
}