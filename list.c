#include "list.h"

typedef struct node_ {
    struct node_* next;
    PElem element;
} Node_;

struct List_ {
    Node_ *head, *iterator, *tail;

    compare_func compareFunc;
    copy_func copyFunc;
    print_func printFunc;
    delete_func deleteFunc;
};

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
    PElem elem = pList->copyFunc(pElem);
    if(!elem){
        return FAIL;
    }
    Node_* new_node = (Node*)malloc(sizeof(Node_));
    if(!new_node){
        free(elem);
        return FAIL;
    }
    new_node->element = elem;
    new_node->next = NULL;
    if(!(pList->tail)){
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
    pList->iterator = pList->head;
    while(pList->iterator){
        if(pList->compareFunc(pList->iterator->element,pElem)){
            Node_* tmp = pList->iterator;
            pList->iterator = pList->iterator->next;
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

PElem ListGetNext(PList){

}

BOOL ListCompare(PList, PList){

}

void ListPrint(PList){

}