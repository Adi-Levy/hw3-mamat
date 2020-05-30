#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"

typedef struct Point_* PPoint;

/*User functions*/
static BOOL compare_coor(int*, int*);
static int* copy_coor(int*);
static void print_coor(int*);
static void del_coor(int*);

/*Interface functions*/
PPoint PointCreate(int);
void PointDestroy(PPoint);
Result PointAddCoordinate(PPoint, int);
int PointGetFirstCoordinate(PPoint);
int PointGetNextCoordinate(PPoint);
void PointPrint(PPoint);
BOOL PointCompare(PPoint, PPoint);
PPoint PointCopy(PPoint);
int PointGetAttribute(PPoint, char*);

#endif
