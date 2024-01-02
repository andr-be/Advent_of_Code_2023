#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

#define HAND_SIZE 5
#define LINE_MAX 16
#define MAX_HANDS 1024
#define TYPE_WEIGHT 100
#define RANKS 13

typedef enum HAND_TYPE
{
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIR,
    THREE_OF_A_KIND,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    FIVE_OF_A_KIND

} HAND_TYPE;

typedef enum CARD
{
    TWO, THREE, FOUR, FIVE, SIX, 
    SEVEN, EIGHT, NINE, TEN, 
    JACK, QUEEN, KING, ACE

} CARD;

typedef struct Hand 
{
    int Bid;
    HAND_TYPE HandType;
    CARD Cards[HAND_SIZE];
    char String[HAND_SIZE + 1];

} Hand;

typedef struct Collection
{
    int Count;
    Hand Hands[MAX_HANDS];

} Collection;

uint64_t p1_solution(FILE *input);
void add_hand(Collection *pile, char *line);
CARD get_card(char symbol);
void assign_type(Hand *hand);
void sort_hands(Collection *pile);
int compare_hands(const void *a, const void *b);
void swap_hands(Hand *a, Hand *b);

int p2_solution(FILE *input);
