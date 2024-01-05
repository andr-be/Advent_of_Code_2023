#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

#define MAX_NODES 1024
#define PATTERN_MAX 512
#define LINE_MAX 128
#define GROUP_SIZE 3

typedef struct Node
{
    char Name[4];
    char Left[4];
    char Right[4];

} Node;

typedef struct Tree
{
    int Count;
    char Pattern[PATTERN_MAX];
    int PatternLength;
    Node Nodes[MAX_NODES];

} Tree;


int p1_solution(FILE *input);
Tree parse_tree(FILE *input);
void add_node(Tree *tree, char *line);
Node find_start(Tree *tree);
Node find(Tree *tree, char *name);
int calculate_steps(Tree *tree);

int p2_solution(FILE *input);
