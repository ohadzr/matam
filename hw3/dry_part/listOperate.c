
/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

/**************************************
 *              Defines               *
 **************************************/

typedef int (*IntOperatorElement)(int, int);
#define EMPTY_LIST 0

/**************************************
 *              Structs               *
 **************************************/

typedef struct node_t* Node;
struct node_t {
    int n;
    Node next;
};

/********** DELETE ***********/

void print_list(Node node) {
    printf("Node:\t");
    Node next_node = node;
    while(next_node) {
        printf("%d\t", next_node->n);
        next_node = next_node->next;
    }
    printf("\n");
}

int plus(int n1, int n2) {
    return n1+n2;
}

int minus(int n1, int n2) {
    return n1-n2;
}
/********************/

/**************************************
 *         Static Functions           *
 **************************************/

/**
 * function compare two integers and find witch one is bigger.
 * @param number1 - first integer.
 * @param number2 - second integer.
 * @return
 * the max integer value within the two integers.
 */

static int max(int number1, int number2) {
    if (number1 > number2) return number1;
    return number2;
}

/**
 * function count how many nodes exist in list.
 * @param list - the list to measure length .
 * @return
 * list length.
 */
static int getListSize(Node list) {
    int counter = 0;
    Node next_node = list;
    while (next_node) {
        counter++;
        next_node = next_node->next;
    }
    return counter;
}


/**
 * Allocate a new Node struct. Node has a n property and next node property
 *
 * @return
 *  New Allocated Node.
 *  NULL if allocation failed
 *
 */
static Node nodeCreate(int n, Node next_node) {
    Node new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
        return NULL;
    new_node->n = n;
    new_node->next = next_node;

    return new_node;
}

/**
 * Allocate a new node as a copy of a given node.
 *
 * @return
 *  New Allocated Node.
 *  NULL if allocation failed, or given node is NULL
 *
 */
static Node nodeCopy(Node node) {
    if (node == NULL) return NULL;
    Node new_node = nodeCreate(node->n, node->next);

    return new_node;
}

static void nodeDestroy(Node node) {
    if (node != NULL) {
        free(node);
    }
}

/**
 * Free all allocated memory of a list of nodes
 *
 */
void listDestroy(Node list) {
    if (list == NULL) return;

    Node next_node = list;

    while (next_node) {
        next_node = next_node->next;
        nodeDestroy(list);
        list = next_node;
    }

}


/**
 * Insert a node to the end of a list.
 *
 * @return
 *  NULL if both list and node are NULL
 *  node if list is NULL
 *  list if node is NULL, or if success
 *
 */
static Node listInsertLast(Node list, Node node) {
    if (list == NULL && node == NULL) return NULL;
    if (list == NULL) return node;
    if (node == NULL) return list;
    Node next_node = list;
    while(next_node->next) {

        next_node = next_node->next;
    }

    next_node->next = node;

    return list;
}

/**
 *  Get 2 lists of ints of the same size and an int operator function that
 *  calc a new int. Create a new list that every int in the list is the new
 *  int that was claculated in the operator list.
 *
 * @return
 *  NULL lists are not the same size, size is zero or if allocation fails
 *  Node list - of new ints
 *
 */
Node listOperate(Node list1, Node list2, IntOperatorElement operator) {
    if (getListSize(list1) != getListSize(list2)) return NULL;
    if (getListSize(list1) == EMPTY_LIST) return NULL;

    Node list = NULL;

    while (list1) {
        int n = operator(list1->n, list2->n);

        Node new_node = nodeCreate(n , NULL);
        if (new_node == NULL) {
            listDestroy(list);
            return NULL;
        }

        list = listInsertLast(list, new_node);

        list1 = list1->next;
        list2 = list2->next;
    }

    return list;
}


/**
 *  Get an array of Node lists at the same size and the array size and
 *  return a new allocated list of the same size that every n inside of it
 *  is the maximum value between all lists in that index
 *  using @listOperte function for comparing
 *
 * @return
 *  NULL if array size is zero or if allocation fails
 *  Node list - of new max ints
 *
 */
Node maxElements(Node* list_array, int array_size) {
    if (array_size <= 0) return NULL;
    if (array_size == 1) return nodeCopy(list_array[0]);

    Node max_list = listOperate(list_array[0], list_array[1], max);
    Node temp_list = NULL;

    for (int i=2; i<array_size; i++) {
        temp_list = listOperate(max_list, list_array[i], max);
        listDestroy(max_list);
        max_list = listOperate(temp_list, list_array[i], max);
        listDestroy(temp_list);
    }

    return max_list;

}



int main() {
    Node node1 = malloc(sizeof(*node1));
    Node node2 = malloc(sizeof(*node2));
    Node node3 = malloc(sizeof(*node3));

    if (node1 == NULL) {
        printf("node1 out of mem\n");
        return 0;
    }

    if (node2 == NULL) {
        printf("node2 out of mem\n");
        return 0;
    }

    if (node3 == NULL) {
        printf("node3 out of mem\n");
        return 0;
    }

    node1->n=1;
    node2->n=2;
    node3->n=3;

    Node last_node1 = node1;
    Node last_node2 = node2;
    Node last_node3 = node3;

    for (int i=2; i<10; i++) {
        last_node1->next = malloc(sizeof(*node1));
        last_node2->next = malloc(sizeof(*node2));
        last_node3->next = malloc(sizeof(*node3
                                  ));
        if (node1->next == NULL) {
            listDestroy(node1);
            listDestroy(node2);
            listDestroy(node3);
            printf("node1 out of mem\n");
            return 0;
        }

        if (node2->next == NULL) {
            listDestroy(node1);
            listDestroy(node2);
            listDestroy(node3);
            printf("node2 out of mem\n");
            return 0;
        }

        if (node3->next == NULL) {
            listDestroy(node1);
            listDestroy(node2);
            listDestroy(node3);
            printf("node3 out of mem\n");
            return 0;
        }
        last_node1->next->n = i;

        if (i%3 == 0)
            last_node2->next->n = 0;
        else
            last_node2->next->n = i*2;

        if (i%2 == 0)
            last_node3->next->n = 0;
        else
            last_node3->next->n = i*3;

        last_node1 = last_node1->next;
        last_node2 = last_node2->next;
        last_node3 = last_node3->next;

    }
    print_list(node1);
    print_list(node2);
    print_list(node3);

    printf("\nplus: \n");
    Node plus_node = listOperate(node1, node2, plus);
    print_list(plus_node);

    printf("\nminus: \n");
    Node minus_node = listOperate(node1, node2, minus);
    print_list(minus_node);



    Node list[5] = {node1, node2, node3, plus_node, minus_node};

    printf("\nmax: \n");
    Node max_node = maxElements(list, 5);
    print_list(max_node);
    listDestroy(max_node);


    listDestroy(node1);
    listDestroy(node2);
    listDestroy(node3);
    listDestroy(plus_node);
    listDestroy(minus_node);

     return 0;
}
/********************/
