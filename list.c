#include "list.h"

/*
   Types
 */
/*
  list node struct holds the list element 
  and pointer to the next node to keep them conncted
 */
typedef struct node_ {
    struct node_* next;
    PElem element;
} Node_;
/*
  list struct that holds the list head tail and iterator for element access
  holds element specific functions for element manipulation
 */
struct List_ {
    Node_ *head, *iterator, *tail;

    compare_func compareFunc;
    copy_func copyFunc;
    print_func printFunc;
    delete_func deleteFunc;
};

/*
 Function: ListCreate
 Abstract: creats a new empty list with relevant element manipulators
 Parameters: cpy_f - a function to copy list elements
             del_f - a function to delete list elements
             cmp_f - a function to compare list elements
             prt_f - a function to print list elements
 Return: pointer to new empty list with defined manipulation functions
 */
PList ListCreate(copy_func cpy_f, delete_func del_f, compare_func cmp_f, print_func prt_f){
    PList new_list;
    new_list = (PList)malloc(sizeof(struct List_));
    if(!new_list){
        exit(-1);
    }
    new_list->head = NULL;
    new_list->iterator = new_list->head;
    new_list->tail = NULL;
    new_list->compareFunc = cmp_f;
    new_list->copyFunc = cpy_f;
    new_list->deleteFunc = del_f;
    new_list->printFunc = prt_f;

    return new_list;
}

/*
 Function: ListDestroy
 Abstract: deletes all elements and nodes in a list and deletes the list (free)
 Parameters: pList - a a list to delete
 Return: N/A
 */
void ListDestroy(PList pList){
    pList->iterator = pList->head;
    while(pList->iterator){
        Node_* tmp = pList->iterator;
        pList->iterator = pList->iterator->next;
        pList->deleteFunc(tmp->element);
        free(tmp);
    }
    free(pList);
}

/*
 Function: ListAdd
 Abstract: adds a copy of an element to the list
 Parameters: pList - a pointer to a list to add the new element to
             pElem - a pointer to the element to be added to the list
 Return: SUCCESS or FAIL depending on the success of the addition to the list operation
 */
Result ListAdd(PList pList, PElem pElem){
    PElem elem = (PElem)pList->copyFunc(pElem);
    if(!elem){
        return FAIL;
    }
    Node_* new_node = (Node_*)malloc(sizeof(Node_));
    if(!new_node){
        free(elem);
        return FAIL;
    }
    new_node->element = elem;
    new_node->next = NULL;
    if(!(pList->head)){
        pList->tail = new_node;
        pList->head = new_node;
    }
    else {
        pList->tail->next = new_node;
        pList->tail = new_node;
    }
    return SUCCESS;
}

/*
 Function: ListRemove
 Abstract: removes the item in the list that matches the givven element.
            if element is not in list it won't remove anything
 Parameters: pList - a pointer to a list to remove the element from
             pElem - a pointer to an element the is to be removed from the list
 Return: SUCCESS or FAIL depending on the success of the removal from the list
 */
Result ListRemove(PList pList, PElem pElem){
    // check if first element is the one to delet and if so shorten the list
    if (pList->compareFunc(pList->head->element,pElem) == TRUE) {
        Node_* tmp = pList->head;
        pList->head = pList->head->next;
        pList->iterator = pList->head;
        pList->deleteFunc(tmp->element);
        free(tmp);
        return SUCCESS;
    }
    // if not run through the list to find the node with the element and remove it
    pList->iterator = pList->head;
    while(pList->iterator->next){
        if(pList->compareFunc(pList->iterator->next->element,pElem)){
            Node_* tmp = pList->iterator->next;
            pList->iterator->next = pList->iterator->next->next;
            pList->deleteFunc(tmp->element);
            free(tmp);
            return SUCCESS;
        }
        else {
            pList->iterator = pList->iterator->next;
        }
    }
    return FAIL;
}

/*
 Function: ListGetFirst
 Abstract: a getter method for the first element in the list.
            moves the list iterator to the head node
 Parameters: pList - a pointer to the list to get the first element of
 Return: pointer to the element of the first node in the list
 */
PElem ListGetFirst(PList pList){
    pList->iterator = pList->head;
    if (pList->head)
        return pList->head->element;
    else
        return NULL;
}

/*
 Function: ListGetNext
 Abstract: a getter method for the next element in the list 
            depending on the list iterator position.
            moves the list iterator to the next node and gets it's element.
 Parameters: pList - a pointer to the list to get the next element of
 Return: pointer to the element of the next node in the list
 */
PElem ListGetNext(PList pList){
    if (!(pList->iterator) || !(pList->iterator->next)) {
        return NULL;
    }
    pList->iterator = pList->iterator->next;
    return pList->iterator->element;
}

/*
 Function: ListCompare
 Abstract: compares 2 lists element by element
 Parameters: pList1 - a pointer to the first list to compare
             pList2 - a pointer to the second list to compare
 Return: TRUE or FALSE depending on whether the lists are equal per element or not.
 */
BOOL ListCompare(PList pList1, PList pList2){
    PElem elem1 = (PElem)ListGetFirst(pList1);
    PElem elem2 = (PElem)ListGetFirst(pList2);
    while (elem1 && elem2) {
        if (!(pList1->compareFunc(elem1, elem2))) {
            return FALSE;
        }
        elem1 = (PElem)ListGetNext(pList1);
        elem2 = (PElem)ListGetNext(pList2);
    }
    if (!(pList1->compareFunc(elem1, elem2))) {
        return FALSE;
    }
    return TRUE;
}

/*
 Function: ListPrint
 Abstract: prints all elements in the list by order of addition 
                and via the print_func of the list
 Parameters: pList - a pointer to a list to print it's elements
 Return: N/A
 */
void ListPrint(PList pList){
    PElem prt_elem = (PElem)ListGetFirst(pList);
    printf("[");
    while (prt_elem) {
        pList->printFunc(prt_elem);
        prt_elem = (PElem)ListGetNext(pList);
    }
    printf("]\n");
}