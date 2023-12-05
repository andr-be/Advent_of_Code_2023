#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX 256
#define MAX_WINNING 10
#define MAX_SCORING 25
#define MAX_CARDS 1024

typedef struct Scratchcard {
    int ID;
    int Amount;
    int Winning[MAX_WINNING];
    int Scoring[MAX_SCORING];
    int WinCount;
    int ScoreCount;
    int Matches;
    int Points;
} Scratchcard;

typedef struct CardPile {
    int Count;
    Scratchcard Stack[256];
} CardPile;

int p1_solution(FILE *input);
Scratchcard populate_card(char* line, int id);
void print_scratchcard(Scratchcard *card);
int score_card(Scratchcard *card);

int p2_solution(FILE *input);
void add_card(CardPile *cards, Scratchcard new_card);
