#ifndef _POINT_H_
#define _POINT_H_

#include "defs.h"

typedef struct Point_* PPoint;

/*Interface functions*/
PPoint PointCreate(int);
void PointDestroy(PPoint);
Result PointAddCoordinate(PPoint, int);
int PointGetFirstCoordinate(PPoint);
int PointGetNextCoordinate(PPoint);
void PointPrint(PPoint);

#endif
