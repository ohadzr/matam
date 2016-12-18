//
// Created by ohad on 01-Nov-16.
//

#include <stdio.h>
#define N 6


int main()
{
    int n;
    scanf("%d",&n);
    //double arr[n][n] = {0};

    float input, sum, arr[n][n], output[n][n];
    int  counter;
    int row, line;

    for (int i=0; i<n;i++) {
        for (int j=0; j<n; j++) {
            scanf("%f\n",&input);
            arr[i][j] = input;
            sum = 0;
            counter = 0;
            for (row=0; row<=i; row++) {
                for (line=0; line<=j; line++) {
                    sum += arr[row][line];
                    counter++;
                }
            }
            output[i][j] = sum/counter;
        }
    }

    for (int i=0; i<n; i++) {
        for(int j=0; j<n; j++) {
            printf("%.2f",output[i][j]);
            if ((j+1)%n != 0) {
                printf(" ");
            }
        }
        printf("\n");
    }

    return 0;
}

