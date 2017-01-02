//
// Created by ohad on 24-Dec-16.
//

#include <stdlib.h>
#include <string.h>
#include <stdio.h>



char* stringCopy(char* str) {
    if (str == NULL) return NULL;
    char* dst_str = malloc(strlen(str)+1);
    if (dst_str != NULL) {
        if (strcmp("", str) == 0) {
            free(dst_str);
            return NULL;
        }
        strcpy(dst_str, str);
        dst_str[strlen(str)] = '\0';
        return dst_str;
    }
    return NULL;
}


void stringDestroy(char* str) {
    free(str);
}
