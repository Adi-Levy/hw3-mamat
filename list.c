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
 Parameters: cpy_f - a function to copy 
 Return: 
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

Result ListRemove(PList pList, PElem pElem){
    // check if first element is the one to delet and if so shorten the list
    if (pList->head->element == pElem) {
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

PElem ListGetFirst(PList pList){
    pList->iterator = pList->head;
    return pList->head->element;
}

PElem ListGetNext(PList pList){
    if (!(pList->iterator) || !(pList->iterator->next)) {
        return NULL;
    }
    pList->iterator = pList->iterator->next;
    return pList->iterator->element;
}

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

void ListPrint(PList pList){
    PElem prt_elem = (PElem)ListGetFirst(pList);
    printf("[");
    while (prt_elem) {
        pList->printFunc(prt_elem);
        prt_elem = (PElem)ListGetNext(pList);
    }
    printf("]\n");
}