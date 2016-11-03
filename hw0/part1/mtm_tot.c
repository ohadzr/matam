//
// Created by ohad on 01-Nov-16.
//

#include <stdio.h>
#include <stdbool.h>

/* Defines */
#define MAX_INT_SIZE 10
#define MAX_INPUT_NUMBERS 1000

/*  Functions Declarations */
bool isDigit(char);
int turnCharsToInt(char[]);
void findExponent(char[], int[], int*);
void sumExponents(int[], int*);
void getInput(int);


/* Functions */

bool isDigit(char input_char) {
    /* many ors for avoiding problem in different encoding than ascii */
    if (input_char == '0' || input_char == '1' || input_char == '2' ||\
        input_char == '3' || input_char == '4' || input_char == '5' ||\
        input_char == '6' || input_char == '7' || input_char == '8' ||\
        input_char == '9' ){
        return true;
    }

    return false;
}


int turnCharsToInt(char num_string[MAX_INT_SIZE]) {
    /* This function turns array of chars into int */
    int num = 0, i=0, ten_power=1;
    bool is_negative = false;

    if (num_string[i] == '-') {
        is_negative = true;
        i++;
    }
    while(num_string[i]) {
        /* only works when assuming all numbers are following in encoding */
        num += (num_string[i]-'0')*(ten_power);
        ten_power *= 10;
        i++;
    }
    if (is_negative){
        return -num;
    }
    return num;
}


void findExponent(char num_string[MAX_INT_SIZE],\
                  int exponents[MAX_INPUT_NUMBERS],int *exponent_counter) {
    int input_number, temp_number, exponent = 0;
    input_number = turnCharsToInt(num_string);
    temp_number = input_number;

    /* devide by 2 until reaches lowest odd number, if it's 1 then the given
       number is a power of 2 */
    if (input_number > 0){
        while (temp_number % 2 == 0){
            exponent++;
            temp_number /= 2;
        }
        if (temp_number == 1){
            printf("The number %d is a power of 2: %d = 2^%d\n",\
                   input_number,input_number, exponent);
            exponents[*exponent_counter] = exponent;
            *exponent_counter += 1;
        }
    }
    return;
}

void sumExponents(int exponents[MAX_INPUT_NUMBERS], int *exponent_counter){
    /*/ This function calculates the sum of all exponents */
    int sum=0;
    for (int i=0; i<*exponent_counter; i++){
        sum += exponents[i];
    }
    printf("Total exponent sum is %d",sum);
}

void getInput(int input_size) {
    int exponents[MAX_INPUT_NUMBERS];
    int *exponent_counter = 0;
    char input_char, num_string[MAX_INT_SIZE];

    printf("Enter Numbers:\n");
    scanf("%c", &input_char); /* assumes that first char is \n */
    scanf("%c", &input_char); /* second scanf should be the first real char */

    /* the for make sure that not more than given input is checked */
    for (int i=0; i<input_size; i++) {
        int counter = 0;
        if (input_char == EOF) break; /*if end of file stop looking for input*/
        while (input_char != ' ' && input_char != '\n') {
            if (isDigit(input_char) || (input_char == '-' && counter == 0)) {
                num_string[counter] = input_char;
                counter++;
                scanf("%c", &input_char);
            }
            else {
                printf("Invalid number %c",input_char);
                return;
            }
        }
        num_string[counter]=0;
        printf("num:%s",num_string);
        findExponent(num_string, exponents, exponent_counter);
    }
    sumExponents(exponents, exponent_counter);
    return;
}



/* Main Program */

int main()
{
    int input_size;

    printf("Enter size of input:\n");
    scanf("%d", &input_size);

    if (input_size > 0) {
        getInput(input_size);
    }
    else {
        printf("Invalid size");
    }

    return 0;
}
