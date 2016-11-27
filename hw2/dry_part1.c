//
// Created by ohad on 26-Nov-16.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/*
char* partialCopyStringOld(char* str, bool copy_even, int* out_len) {
    char* OUT;
    if (copy_even) {
        out_len = malloc(sizeof(int));
        *out_len = strlen(str) / 2;

        OUT = malloc(*out_len);

        for (int i = 0; i < strlen(str); i += 2) {
            OUT[i / 2] = str[i + 1];
        }
    }
    else
    {
        out_len = malloc(sizeof(int));
        *out_len = strlen(str) / 2 + strlen(str) % 2;

        OUT = malloc(*out_len);

        for (int i = 0; i < strlen(str); i += 2)
        {
            OUT[i / 2] = str[i];
        }
    }

    return OUT;
}
*/

char* partialCopyString(char* str, bool copy_even, int* out_len) {
    char* out = NULL;
    int str_length, i=1;

    if (str == NULL || out_len == NULL) {
        return NULL;
    }

    str_length = (int)strlen(str);
    *out_len = (str_length / 2);

    if (!copy_even) {
        *out_len += (str_length % 2) ;
        i--;
    }

    out = malloc((*out_len + 1) * sizeof(char));

    if (out != NULL) {
        for (; i < str_length; i += 2) {
            out[i / 2] = str[i];
        }
        out[*out_len] = 0;
    }

    return out;
}

int main() {
    int* output_len = malloc(sizeof(int));
    printf("start\n");
    printf("1\n");
    char *out = partialCopyString("abcdef",false, output_len);
    printf("%s\n",out);
    free(out);
    printf("out_len:%d\n", *output_len);
    free(output_len);

    int* output_len2 = malloc(sizeof(int));
    printf("2\n");
    char *out2 = partialCopyString("abcdef",true, output_len2);
    printf("%s\n",out2);
    free(out);
    printf("out_len:%d\n", *output_len2);
    free(output_len2);

    printf("end");
    return 0;
}