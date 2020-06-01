#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"
#include "list.h"

typedef struct Point_* PPoint;
typedef enum { SIZE, DIMENSION } Attribute;

/*Interface functions*/
PPoint PointCreate(int);
void PointDestroy(void*);
Result PointAddCoordinate(PPoint, int);
int PointGetFirstCoordinate(PPoint);
int PointGetNextCoordinate(PPoint);
void PointPrint(void*);
BOOL PointCompare(void*, void*);
void* PointCopy(void*);
int PointGetAttribute(PPoint, Attribute);

#endif
