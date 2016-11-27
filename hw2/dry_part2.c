//
// Created by ohad on 26-Nov-16.
//

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node_t* Node;
struct node_t {
    int data;
    Node next;
};

/*
void printCheckmarkOrderedAux(Node first_node , Node last_node) {
    printf("%d ", first_node->data);
    if (first_node == last_node) return; // if same pointer==same object in list

    printf("%d ", last_node->data);
    if (first_node->next == last_node) return;

    Node before_last=first_node;

    while (before_last->next != last_node) {
        before_last = before_last->next;
    }

    printCheckmarkOrderedAux(first_node->next, before_last);

}
*/

bool printCheckmarkOrderedAux(Node index_node, Node next_node,
                              bool checked_twice) {

    if (next_node == NULL) {
        return true;
    }

    Node middle_node = malloc(sizeof(*middle_node));
    if (middle_node == NULL) {
        return false;
    }

    middle_node->data = next_node->data;
    middle_node->next = index_node->next;
    index_node->next = middle_node;

    if (!checked_twice){
        return printCheckmarkOrderedAux(index_node, next_node->next, !checked_twice);
    }
    else {
        return printCheckmarkOrderedAux(middle_node, next_node->next, !checked_twice);
    }

}

bool printCheckmarkOrdered(Node node) {

    if (node == NULL) { //empty list
        return true;
    }

    if (node->next == NULL) { //list with one element
        printf("%d ", node->data);
        return true;
    }

    Node new_node = malloc(sizeof(*new_node));
    if (new_node == NULL) {
        return false;
    }
    new_node->data = node->data;

    // recursive aux function
    if (printCheckmarkOrderedAux(new_node, node->next, false)) {
        while(new_node != NULL) {
            printf("%d ", new_node->data);
            new_node = new_node->next;
        }
        return true;
    }

    return false;
}



int main() {
    Node ptr1 = malloc(sizeof(*ptr1));
    Node ptr2 = malloc(sizeof(*ptr2));
    Node ptr3 = malloc(sizeof(*ptr3));
    Node ptr4 = malloc(sizeof(*ptr4));
    Node ptr5 = malloc(sizeof(*ptr5));
    Node ptr6 = malloc(sizeof(*ptr6));
    Node ptr7 = malloc(sizeof(*ptr7));
    Node ptr8 = malloc(sizeof(*ptr8));
    Node ptr9 = malloc(sizeof(*ptr9));

    if(!ptr1) {
        return -1;
    }

    ptr1->data = 1;
    ptr1->next = ptr2;


    if(!ptr2) {
        return -1;
    }

    ptr2->data = 2;
    ptr2->next = ptr3;

    if(!ptr3) {
        return -1;
    }

    ptr3->data = 3;
    ptr3->next = ptr4;

    if(!ptr4) {
        return -1;
    }

    ptr4->data = 4;
    ptr4->next = ptr5;

    if(!ptr5) {
        return -1;
    }

    ptr5->data = 5;
    ptr5->next = ptr6;

    if(!ptr6) {
        return -1;
    }

    ptr6->data = 6;
    ptr6->next = ptr7;

    if(!ptr7) {
        return -1;
    }

    ptr7->data = 7;
    ptr7->next = ptr8;

    if(!ptr8) {
        return -1;
    }

    ptr8->data = 8;
    ptr8->next = ptr9;

    if(!ptr9) {
        return -1;
    }

    ptr9->data = 9;
    ptr9->next = NULL;


    printCheckmarkOrdered(ptr1) ? printf("true") : printf("false");

    return 0;
}