//
// Created by ohad on 01-Jan-17.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef void* Element;
typedef Element (*CopyFunction)(Element);
typedef int (*CompareFunction)(Element, Element);
typedef void (*FreeFunction)(Element);

#define EQUAL 0
#define LEFT_FIRST 1
#define RIGHT_FIRST -1

void merge(Element* elements_array1,int array_size1,Element* elements_array2,
           int array_size2, Element* helper_array ,
           CompareFunction compare_element_function,
           CopyFunction copy_element_function,
           FreeFunction free_element_function) {
    int index_array1=0, index_array2=0, i_helper=0;

    for(; (index_array1 < array_size1) && (index_array2 < array_size2);
          helper_array++) {
        if (compare_element_function(elements_array1[index_array1],
                                     elements_array2[index_array2])
            == LEFT_FIRST) {
            helper_array[i_helper] =
                    copy_element_function(elements_array1[index_array1]);
            free_element_function(elements_array1[index_array1]);
            elements_array1[index_array1] = NULL;
            index_array1++;
        }
        else {
            helper_array[i_helper] =
                    copy_element_function(elements_array2[index_array2]);
            free_element_function(elements_array2[index_array2]);
            elements_array2[index_array2] = NULL;
            index_array2++;
        }
    }

    for(; index_array1 < array_size1; index_array1++, helper_array++)
        helper_array[i_helper] =
                copy_element_function(elements_array1[index_array1]);

    for(; index_array2 < array_size2; index_array2++, helper_array++)
        helper_array[i_helper] =
                copy_element_function(elements_array2[index_array2]);

    //for (int i=0; i<array_size1+array_size2; i++)
    //    free_element_function(helper_array[i]);
}


void internal_msort(Element* elements_array, int array_size,
                    Element* helper_array,CopyFunction copy_element_function,
                    CompareFunction compare_element_function,
                    FreeFunction free_element_function)
{
    int left = array_size / 2, right = array_size - left;
    if (array_size < 2)
        return;
    internal_msort(elements_array, left, helper_array, copy_element_function,
                   compare_element_function, free_element_function);
    internal_msort(elements_array + left, right, helper_array ,
                   copy_element_function, compare_element_function,
                   free_element_function);
    //merge
    merge(elements_array, left, elements_array + left, right, helper_array,
          compare_element_function, copy_element_function,
          free_element_function);

    // memcpy and free
    for (int i=0; i<array_size ; i++) {
        free_element_function(elements_array[i]);
        elements_array[i] = NULL;
        elements_array[i] = copy_element_function(helper_array[i]);
        free_element_function(helper_array[i]);
        helper_array[i] = NULL;
    }

}


void merge_sort(Element* elements_array, int array_size,
                CopyFunction copy_element_function,
                CompareFunction compare_element_function,
                FreeFunction free_element_function)
{
    Element *tmp_array = malloc(sizeof(Element) * array_size);
    internal_msort(elements_array, array_size, tmp_array,copy_element_function,
                   compare_element_function, free_element_function);

    //for (int i=0; i< array_size; i++) {
    //    free_element_function(tmp_array[i]);
    //}

    free(tmp_array);
}



/************* DELETE ********/
typedef void* intElement;
//typedef intElement integer

typedef struct integ_t* integer;
struct integ_t  {
    int n;
};

int int_copmare(integer n1, integer n2) {
    if (n1->n < n2->n) return LEFT_FIRST;
    if (n1->n > n2->n) return RIGHT_FIRST;
    return EQUAL;
}

void int_free(integer n) {
    if (n != NULL)
        free(n);
}

integer int_copy(integer n) {
    integer new_n = malloc(sizeof(integer));
    new_n->n = n->n;
    return new_n;
}

intElement intCopyElement( intElement n ) {
    return int_copy( (integer) n );
}

void intDestroyElement( intElement n ) {
    int_free( (integer)n );
}

int intCompareElement(intElement n1,intElement n2){
    return int_copmare( (integer)n1 , (integer)n2 );
}




int main() {

    integer* arr1 = malloc(sizeof(integer)*7);
    arr1[0] = malloc(sizeof(integer));
    arr1[0]->n = 1;
    arr1[1] = malloc(sizeof(integer));
    arr1[1]->n = -1;
    arr1[2] = malloc(sizeof(integer));
    arr1[2]->n = 11;
    arr1[3] = malloc(sizeof(integer));
    arr1[3]->n = 17;
    arr1[4] = malloc(sizeof(integer));
    arr1[4]->n = 100;
    arr1[5] = malloc(sizeof(integer));
    arr1[5]->n = 0;
    arr1[6] = malloc(sizeof(integer));
    arr1[6]->n = 1;
    //arr2[10] = {1,0,3,13,5,-6,16,8,9,100};
    printf("original:\t");
    for (int i=0; i<7; i++)
        printf("%d\t",arr1[i]->n);
    printf("\n");

    merge_sort( (void**)arr1, 7, intCopyElement,
                intCompareElement, intDestroyElement );

    printf("sorted:\t\t");
    for (int i=0; i<7; i++) {
        printf("%d\t",arr1[i]->n);
        int_free(arr1[i]);
    }

    printf("\n");

    free(arr1);

    return 0;
}