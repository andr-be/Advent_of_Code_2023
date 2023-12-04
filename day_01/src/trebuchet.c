// Advent of Code 2023 - Day 1 - Trebuchet?!
// andr-be 12/2023
/*
    PART 1: 54644
    PART 2: 53348
*/
#include "trebuchet.h"

int main(int argc, char const *argv[])
{
    char *filename;
    if (argc > 1 && strcmp(argv[1], "-test") == 0) {
        filename = "../test_input_2.txt";
        printf("RUNNING IN TEST MODE\n");
    }
    else filename = "../input.txt";

    FILE *input = fopen(filename, "r");

    printf("SOLUTIONS:\nPart 1:\t%d\n", p1_solution(input));
    printf("\nPart 2:\t%d", p2_solution(input));

    return 0;
}

int p1_solution(FILE *input)
{
    int sum_of_numbers = 0;

    while(!feof(input))
    {
        char line_buffer[LINE_MAX],
             first_number = 0,
             second_number = 0,
             number_buffer[DIGIT_MAX + 1] = {0};

        fgets(line_buffer, LINE_MAX, input);

        first_number = return_first_digit(line_buffer);
        second_number = return_last_digit(line_buffer);

        snprintf(number_buffer, DIGIT_MAX + 1, "%c%c", 
                 first_number, (second_number != 0) ? second_number : first_number);

        sum_of_numbers += atoi(number_buffer);
    }
    fseek(input, 0, SEEK_SET);
    
    return sum_of_numbers;
}

char return_first_digit(char *input)
{
    for (char *p = input; *p; p++)
        if (isdigit(*p)) 
            return *p;

    return 0;
}

char return_last_digit(char *input)
{
    for (char *p = input + strlen(input); p > input; p--)
        if (isdigit(*p)) 
            return *p;

    return 0;
}

int p2_solution(FILE *input)
{
    int sum = 0;

    while (!feof(input))
    {
        char line_buffer[LINE_MAX],
             number_buffer[DIGIT_MAX + 1];
        
        int first_digit = 0,
            second_digit = 0;
        
        fgets(line_buffer, LINE_MAX, input);

        for (char *first = line_buffer; *first; first++) {
            if (isdigit(*first)) { 
                first_digit = char_to_int(*first); 
                break; 
            }
            else if (isalpha(*first)) { 
                first_digit = first_number(first);
                if (first_digit != -1) 
                    break; 
            }
        }

        for (char *last = line_buffer + strlen(line_buffer) - 1; last > line_buffer; last--) {
            if (isdigit(*last)) {
                second_digit = char_to_int(*last);
                break;
            }
            else if (isalpha(*last)) {
                second_digit = last_number(last);
                if (second_digit != -1) break;
            }
        }
        snprintf(number_buffer, DIGIT_MAX + 1, "%d%d", 
                (first_digit  != 0 && first_digit  != -1) ? first_digit : second_digit, 
                (second_digit != 0 && second_digit != -1) ? second_digit : first_digit
                );

        sum += atoi(number_buffer);
        #ifdef DEBUG
        printf("(%d, %d): %d -> %s", first_digit, second_digit, atoi(number_buffer), line_buffer);
        #endif // DEBUG
    }

    return sum;
}

int char_to_int(char c)
{
    switch (c)
    {
    case '0': return 0;  
    case '1': return 1;
    case '2': return 2;
    case '3': return 3;
    case '4': return 4;
    case '5': return 5;
    case '6': return 6;
    case '7': return 7;
    case '8': return 8;
    case '9': return 9;

    default: return -1;
    }
}

int first_number(char *string)
{
    int number;
    bool found = false;
    char *first = string + strlen(string);

    for (int i = 0; i < 9; i++) 
    {
        char *present = strstr(string, numbers[i]);
        if (present != NULL) 
        {
            found = true;
            if (present < first) 
            { 
                first = present;
                number = i + 1;    
            } 
        }
    }
    if (found) {
        for (char *check = string; check < first; check++) {
            if (isdigit(*check))  {
                number = char_to_int(*check);
                break;
            }
        }
        return number;
    }
    else return -1;
}

int last_number(char *string)
{
    int number;
    bool found = false;
    char *last = string;

    for (int i = 0; i < 9; i++) 
    {
        char *present = strstr(string, numbers[i]);
        if (present != NULL) 
        {
            found = true;
            if (present >= last) 
            {
                last = present;
                number = i + 1;
            }
        }
    }

    if (found) return number;
    else return -1;
}