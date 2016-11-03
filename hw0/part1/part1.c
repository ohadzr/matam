
#include <stdio.h>


/* Defines */
#define BASE 2

/*  Functions Declarations */

/** find the exponent of a given number and print it if exists */
int findExponent(int);

/** calculates the sum of all exponents */
void sumExponents(int[], int);

/** checks input validation */
void getInput(int);


/* Functions */


int findExponent(int input_number) {
    int temp_number, exponent = 0;

    temp_number = input_number;

    // devide by base (2) until reaches lowest odd number, if it's 1 then the
    // given number is a power of base (2)
    if (input_number > 0){
        while (temp_number % BASE == 0){
            exponent++;
            temp_number /= BASE;
        }
        if (temp_number == 1){
            printf("The number %d is a power of %d: %d = %d^%d\n",\
                   input_number, BASE, input_number, BASE, exponent);
            return exponent;
        }
    }
    return 0;
}

void sumExponents(int exponents[], int input_size){
    int sum=0;
    for (int i=0; i<input_size; i++){
        sum += exponents[i];
    }
    if (sum > 0){
        printf("Total exponent sum is %d\n",sum);
    }
    return;
}



void getInput(int input_size) {
    int exponents[input_size], numbers[input_size];
    int input_num, numbers_found=0;

    printf("Enter numbers:\n");
    for (int i=0; i<input_size; i++) {
        if (scanf("%d", &input_num) == 0) {
            printf("Invalid number\n");
            return;
        }
        numbers[i] = input_num;
        numbers_found++;
    }

    for (int i=0; i<input_size; i++)
    {
        exponents[i] = findExponent(numbers[i]);
    }
    sumExponents(exponents, input_size);
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
        printf("Invalid size\n");
    }

    return 0;
}
