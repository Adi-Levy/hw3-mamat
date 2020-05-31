#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"

typedef struct Point_* PPoint;

/*User functions*/
/*static BOOL compare_coor(void*, void*);
static void* copy_coor(void*);
static void print_coor(void*);
static void del_coor(void*);*/

/*Interface functions*/
PPoint PointCreate(int);
void PointDestroy(void*);
Result PointAddCoordinate(PPoint, int);
int PointGetFirstCoordinate(PPoint);
int PointGetNextCoordinate(PPoint);
void PointPrint(void*);
BOOL PointCompare(void*, void*);
void* PointCopy(void*);
int PointGetAttribute(PPoint, char*);

#endif
