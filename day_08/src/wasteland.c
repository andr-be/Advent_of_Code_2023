// Advent of Code Day xx - Title
// andr-be 12/2023
/*
    Part 1: 19099
    Part 2:
*/

#include "wasteland.h"

#define DEBUG false

int main(void)
{
    char *filename;
    if (DEBUG) 
    {
        filename = "../test_input2.txt";
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
    return calculate_steps(&tree);
}

Tree parse_tree(FILE *input)
{
    Tree n_tree = {0};

    char pattern_buffer[PATTERN_MAX + 1] = {0};
    fgets(pattern_buffer, PATTERN_MAX, input);
    strncpy(n_tree.Pattern, pattern_buffer, PATTERN_MAX);
    n_tree.PatternLength = (int) strlen(pattern_buffer) - 1;

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
    char delimiters[] = " =(,)";

    char *pN = strtok(line, delimiters);
    strncpy(n_node.Name, pN, GROUP_SIZE);

    pN = strtok(NULL, delimiters);
    strncpy(n_node.Left, pN, GROUP_SIZE);

    pN = strtok(NULL, delimiters);
    strncpy(n_node.Right, pN, GROUP_SIZE);

    tree->Nodes[tree->Count++] = n_node;
}

Node find_start(Tree *tree)
{
    return find(tree, "AAA");
}

Node find(Tree *tree, char *name)
{
    for (int i = 0; i < tree->Count; i++)
    {
        if (strcmp(tree->Nodes[i].Name, name) == 0)
        {
            return tree->Nodes[i];
        }
    }

    Node error = {0};
    return error;
}

int calculate_steps(Tree *tree)
{
    Node current = find_start(tree);

    bool stop = false;
    int instruction = 0,
        steps = 0;

    while (!stop)
    {
        switch (tree->Pattern[instruction++])
        {
        case 'L':
            current = find(tree, current.Left);
            break;
        
        case 'R':
            current = find(tree, current.Right);
            break;

        default:    
            break;
        }

        if (instruction >= tree->PatternLength)
        {
            instruction = 0;
        }

        stop = (strcmp(current.Name, "ZZZ") == 0);
        steps++;
    }

    return steps;
}

int p2_solution(FILE *input) 
{

    return 0;
}