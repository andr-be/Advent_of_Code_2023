// Advent of Code - Day 04 - Scratchcard
// andr-be 12/2023
/*
    Part 1: 25231
    Part 2: 9721255
*/

#include "scratchcard.h"

#define DEBUG false

int main(int argc, char const *argv[])
{
    char *filename;
    if (DEBUG || (argc > 1 && strcmp(argv[1], "-test") == 0)) 
    {
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
    int card_no = 1;

    while (!feof(input))
    {
        char line_buffer[LINE_MAX] = {0};
        fgets(line_buffer, LINE_MAX - 1, input);
        
        if (strlen(line_buffer) > 0) 
        {
            Scratchcard card = populate_card(line_buffer, card_no++);
            print_scratchcard(&card);
            solution += card.Points;
        }
    }

    fseek(input, 0, SEEK_SET);
    return solution;
}

Scratchcard populate_card(char* line, int id)
{
    char *p = strtok(line, ":"), 
          winning_numbers[LINE_MAX/2] = {0},
          scoring_numbers[LINE_MAX/2] = {0};

    Scratchcard new_card = {.ID = id, .Amount = 1};

    p = strtok(NULL, "|");
    strcpy(winning_numbers, p);

    p = strtok(NULL, "|");
    strcpy(scoring_numbers, p);

    int w = 0;
    for (char *w_s = strtok(winning_numbers, " "); w_s != NULL; w_s = (strtok(NULL, " "))) 
    {
        new_card.Winning[w++] = atoi(w_s);
    }
    new_card.WinCount = w;

    int s = 0;
    for (char *s_s = strtok(scoring_numbers, " "); s_s != NULL; s_s = (strtok(NULL, " "))) 
    {
        new_card.Scoring[s++] = atoi(s_s);
    }
    new_card.ScoreCount = s;

    new_card.Points = score_card(&new_card);
    return new_card;
}

void print_scratchcard(Scratchcard *card)
{
    printf("CARD %d:\nWINNING NUMBERS: ", card->ID);
    for (int i = 0; i < card->WinCount; i++) 
    {
        printf("%2d ", card->Winning[i]);
    }
    
    printf("\nSCORING NUMBERS: ");
    for (int i = 0; i < card->ScoreCount; i++)
    {
        printf("%2d ", card->Scoring[i]);
    }

    printf("\nSCORE: %d (x%d matching)\n\n", card->Points, card->Matches);
}

int score_card(Scratchcard *card)
{
    for (int i = 0; i < card->WinCount; i++) 
    {
        for (int j = 0; j < card->ScoreCount; j++) 
        {
            if (card->Winning[i] == card->Scoring[j]) 
            {
                card->Matches += 1;
                if (card->Points == 0) 
                { 
                    card->Points = 1; 
                }
                else 
                {
                    card->Points *= 2;
                    break;
                }
            }
        }
    }
    return card->Points;
}

int p2_solution(FILE *input) 
{
    int solution = 0;
    CardPile cards = {0};

    while (!feof(input))
    {
        char line_buffer[LINE_MAX] = {0};
        fgets(line_buffer, LINE_MAX - 1, input);
        
        if (strlen(line_buffer) > 0) 
        {
            Scratchcard card = populate_card(line_buffer, cards.Count);
            add_card(&cards, card);
        }
    }

    for (int i = 0; i < cards.Count; i++)
    {
        Scratchcard *pCurrent = &cards.Stack[i];

        for (int j = 1; j <= pCurrent->Matches && i + j < cards.Count; j++)
        {
            cards.Stack[i + j].Amount += pCurrent->Amount;
        }

        solution += pCurrent->Amount;
    }
    return solution;
}

void add_card(CardPile *cards, Scratchcard new_card)
{
    if (cards->Count < MAX_CARDS) 
    {
        cards->Stack[cards->Count] = new_card;
        cards->Count += 1;
    } 
    else 
    {
        fprintf(stderr, "ERROR: CARD MAX_CARDS REACHED (%d)\n", MAX_CARDS);
    }
}
