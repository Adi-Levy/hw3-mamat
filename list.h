#ifndef _LIST_H_
#define _LIST_H_
#include "defs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct List_* PList;
typedef void* PElem;


/*User functions*/
typedef BOOL (*compare_func)(PElem,PElem);
typedef PElem (*copy_func)(PElem);
typedef void (*print_func)(PElem);
typedef Result (*delete_func)(PElem);

/*Interface functions*/
PList ListCreate(copy_func, delete_func, compare_func, print_func);
void ListDestroy(PList);
Result ListAdd(PList, PElem);
Result ListRemove(PList, PElem);
PElem ListGetFirst(PList);
PElem ListGetNext(PList);
BOOL ListCompare(PList, PList);
void ListPrint(PList);

#endif
