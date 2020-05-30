#include "point.h"

struct Point_ {
	int dimention, size;
	PList coordinates;
};

/*
 static coordinate manipulation methods
*/
static BOOL compare_coor(int* coor1, int* coor2) {
	return (*coor1 == *coor2)?TRUE:FALSE;
}

static int* copy_coor(int* coor) {
	int* cpy_coor;
	cpy_coor = (int*)malloc(sizeof(int));
	if (!cpy_coor)
		return NULL;
	*cpy_coor = *coor;
	return cpy_coor;
}

static void print_coor(int* coor) {
	printf("%d ", *coor);
}

static void del_coor(int* coor) {
	free(coor);
}


/*
 iterfacce function implementation
*/
PPoint PointCreate(int dim) {
	PList new_coord_list = ListCreate(copy_coor, del_coor, compare_coor, print_coor);
	if (!new_coord_list)
		return NULL;
	PPoint new_point;
	new_point = (PPoint)malloc(sizeof(struct Point_));
	if (!new_point) {
		return NULL;
	}
	new_point->coordinates = new_coord_list;
	new_point->dimention = dim;
	new_point->size = 0;
	return new_point;
}

void PointDestroy(PPoint pPoint) {
	ListDestroy(pPoint->coordinates);
	free(pPoint);
}

Result PointAddCoordinate(PPoint pPoint, int n_coordinate) {
	if (pPoint->size != pPoint->dimention) {
		int* new_coor;
		new_coor = (int*)malloc(sizeof(int));
		if (!new_coor)
			return FAIL;
		*new_coor = n_coordinate;
		if (ListAdd(pPoint->coordinates, new_coor) == SUCCESS) {
			free(new_coor);
			pPoint->size++;
			return SUCCESS;
		}
		else {
			free(new_coor);
			return FAIL;
		}
	}
	return FAIL;
}

int PointGetFirstCoordinate(PPoint pPoint) {
	int* coor = (int*)ListGetFirst(pPoint->coordinates);
	return (coor) ? *coor : 0;
}

int PointGetNextCoordinate(PPoint pPoint) {
	int* coor = (int*)ListGetNext(pPoint->coordinates);
	return (coor) ? *coor : 0;
}

void PointPrint(PPoint pPoint) {
	printf("Point Dimention: %d, Size: %d, Coordinates: ", pPoint->dimention, pPoint->size);
	ListPrint(pPoint->coordinates);
	printf("\n");
}

BOOL PointCompare(PPoint point1, PPoint point2) {
	return ((point1->dimention == point2->dimention) &&
		(point1->size == point2->size) &&
		(ListCompare(point1->coordinates, point2->coordinates))) ? TRUE : FALSE;
}

PPoint PointCopy(PPoint point) {
	PPoint New_point = PointCreate(point->dimension);

	int tmp_coor = PointGetFirstCoordinate(point);
	int i;
	for (i = 0; i < point->size; i++, tmp_coor = PointGetNextCoordinate(point))
	{
		PointAddCoordinate(point, tmp_coor);
	}

	return New_point;
}