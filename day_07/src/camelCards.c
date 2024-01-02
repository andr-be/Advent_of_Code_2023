// Advent of Code Day 7 - Camel Cards
// andr-be 01/2024
/*
    Part 1: 250951660
    Part 2:
*/

#include "camelCards.h"

#define DEBUG false

int main(int argc, char const *argv[])
{
    char *filename;
    if ((argc > 1 && strcmp(argv[1], "-test") == 0) || DEBUG) {
        filename = "../test_input.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");

    printf("\nSOLUTIONS:\nPart 1:\t%I64i\n", p1_solution(input));
    printf("Part 2:\t%d\n", p2_solution(input));

    return 0;
}

uint64_t p1_solution(FILE *input) 
{
    uint64_t solution = 0;
    Collection pile = {0};

    while (!feof(input))
    {
        char line_buffer[LINE_MAX + 1] = {0};
        fgets(line_buffer, LINE_MAX, input);
        add_hand(&pile, line_buffer);
    }

    sort_hands(&pile);

    for (uint64_t i = 0; i < (uint64_t) pile.Count; i++)
    {
        Hand hand = pile.Hands[i];
        uint64_t card_score = (uint64_t) hand.Bid * (i + 1);
        solution += card_score;
        if (DEBUG) printf("%I64i:\t%s -> %I64i\t(B: %3d, H: %d)\tTOTAL = %I64i\n", i + 1, hand.String, card_score, hand.Bid, hand.HandType, solution);
    }

    return solution;
}

void add_hand(Collection *pile, char *line)
{
    Hand hand = {0};
    int card_no = 0;
    char *pL = strtok(line, " ");
    strcpy(hand.String, pL);
    for (; *pL; pL++)
    {
        hand.Cards[card_no++] = get_card(*pL);
    }
    pL = strtok(NULL, " ");
    hand.Bid = atoi(pL);
    assign_type(&hand);

    pile->Hands[pile->Count++] = hand;
}

void sort_hands(Collection *pile)
{
    qsort(pile->Hands, (size_t) pile->Count, sizeof(Hand), compare_hands);
}

CARD get_card(char symbol)
{
    switch (symbol)
    {
    case 'A': return ACE;
    case 'K': return KING;
    case 'Q': return QUEEN;
    case 'J': return JACK;
    case 'T': return TEN;
    case '9': return NINE;
    case '8': return EIGHT;
    case '7': return SEVEN;
    case '6': return SIX;
    case '5': return FIVE;
    case '4': return FOUR;
    case '3': return THREE;
    default:  return TWO;
    }
}

void assign_type(Hand *hand)
{
    int number_in_rank[RANKS] = {0};
    for (int i = 0; i < HAND_SIZE; i++)
    {
        number_in_rank[hand->Cards[i]]++;
    }

    int max_duplicates = 0,
        pairs = 0;
    for (int i = 0; i < RANKS; i++)
    {
        max_duplicates = (number_in_rank[i] > max_duplicates) ? number_in_rank[i] : max_duplicates;
        if (number_in_rank[i] == 2) pairs++;
    }

    switch (max_duplicates)
    {
    case 5: 
        hand->HandType = FIVE_OF_A_KIND; 
        break;
    
    case 4: 
        hand->HandType = FOUR_OF_A_KIND;
        break;
    
    case 3:
        switch (pairs)
        {
        case 0:  hand->HandType = THREE_OF_A_KIND; break;
        default: hand->HandType = FULL_HOUSE;      break;
        }
        break;
    
    case 2:
        switch (pairs)
        {
        case 2: hand->HandType = TWO_PAIR; break;
        case 1: hand->HandType = ONE_PAIR; break;
        }
        break;

    default:
        hand->HandType = HIGH_CARD;
        break;
    }
}

int compare_hands(const void *a, const void *b)
{
    Hand aH = *(const Hand*)a,
         bH = *(const Hand*)b;

    if (aH.HandType > bH.HandType) 
    {
        return 1;
    }

    else if (aH.HandType < bH.HandType)
    {
        return -1;
    }

    else if (aH.HandType == bH.HandType)
    {
        for (int i = 0; i < HAND_SIZE; i++)
        {
            if (aH.Cards[i] > bH.Cards[i])
            {
                return 1;
            }
            else if (aH.Cards[i] < bH.Cards[i])
            {
                return -1;
            }
            else
            {
                continue;
            }
        }
    }

    return 0;
}

void swap_hands(Hand *a, Hand *b)
{
    Hand temp = *a;
    *a = *b;
    *b = temp;
}


int p2_solution(FILE *input) 
{
    int solution = 0;

    return solution;
}