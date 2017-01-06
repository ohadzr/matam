
/**************************************
 *       Header files include         *
 **************************************/

#include <stdio.h>
#include <stdlib.h>

/**************************************
 *              Defines               *
 **************************************/

typedef int (*IntOperatorElement)(int, int);
//#define EMPTY_LIST -1 //TODO: add line.
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
//TODO: check one last time in t2 and delete

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
 * list length. //TODO: add: or -1 if list is empty.
 */
static int getListSize(Node list) {
    //if ( list == NULL ) return EMPTY_LIST; // TODO: add check.
    int counter = 0;
    Node next_node = list;
    while (next_node) {
        counter++;
        next_node = next_node->next;
    }
    return counter;
}

/**
 * function create new Node.
 * @param n - the node's data argument.
 * @param next_node - pointer to the next node in list
 * @return
 * NULL - if memory allocation failed, else a new Node.
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
 * function copies a node.
 * @param node - the node to be copyed.
 * @return
 * NULL - if memory allocation failed or if parameter NULL.
 */
static Node nodeCopy(Node node) {
    if (node == NULL) return NULL;
    Node new_node = nodeCreate(node->n, node->next);

    return new_node;
}

/**
 * function destroy all memory allocated to node.
 * @param node
 */
static void nodeDestroy(Node node) {
    if (node != NULL) {
        free(node);
        node = NULL;//TODO: redundant
    }
}

/**
 * function free all memory allocated to list, if list is NULL do nothing.
 * @param list - the list to be destroyed.
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
 * function add a node to list.
 * @param list - to list to add node to.
 * @param node - the node to be added to list.
 * @return
 * NULL - if two parameters is NULL, or the head of the list.
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
 * function activates the given operator on lists.
 * @param node1 - the head of first list.
 * @param node2 - the head of the second list.
 * @param operator - the operator to activate between suitable by index Nodes.
 * @return
 * NULL - if one or more of the parameters is NULL, or if memory allocation,
 * problem or if lists are empty.
 */
Node listOperate(Node node1, Node node2, IntOperatorElement operator) {
    if (getListSize(node1) != getListSize(node2)) return NULL;
    if (getListSize(node1) == EMPTY_LIST) return NULL;

    Node list = NULL;

    while (node1) {
        int n = operator(node1->n, node2->n);

        Node new_node = nodeCreate(n , NULL);
        if (new_node == NULL) {
            listDestroy(list);
            return NULL;
        }

        list = listInsertLast(list, new_node);
        //nodeDestroy(new_node); //TODO: remove

        node1 = node1->next;
        node2 = node2->next;
    }

    return list;
}


//TODO: remove after check
/********** DELETE ***********/

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
