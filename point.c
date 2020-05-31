#include "point.h"

struct Point_ {
	int dimention, size;
	PList coordinates;
};

/*
 static coordinate manipulation methods
*/
static BOOL compare_coor(void* coor1, void* coor2) {
	return (*(int*)coor1 == *(int*)coor2)?TRUE:FALSE;
}

static void* copy_coor(void* coor) {
	int* cpy_coor;
	cpy_coor = (int*)malloc(sizeof(int));
	if (!cpy_coor)
		return NULL;
	*cpy_coor = *(int*)coor;
	return (void*)cpy_coor;
}

static void print_coor(void* coor) {
	printf("%d ", *(int*)coor);
}

static void del_coor(void* coor) {
	free((int*)coor);
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

void PointDestroy(void* pPoint) {
	PPoint point = (PPoint)pPoint;
	ListDestroy(point->coordinates);
	free(point);
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

void PointPrint(void* point) {
	PPoint pPoint = (PPoint)point;
	printf("Point Dimention: %d, Size: %d, Coordinates: ", pPoint->dimention, pPoint->size);
	ListPrint(pPoint->coordinates);
	//printf("\n");
}

BOOL PointCompare(void* pPoint1, void* pPoint2) {
	PPoint point1 = (PPoint)pPoint1;
	PPoint point2 = (PPoint)pPoint2;
	return ((point1->dimention == point2->dimention) &&
		(point1->size == point2->size) &&
		(ListCompare(point1->coordinates, point2->coordinates))) ? TRUE : FALSE;
}

void* PointCopy(void* pPoint) {
	PPoint point = (PPoint)pPoint;
	PPoint New_point = PointCreate(point->dimention);
	int tmp_coor = PointGetFirstCoordinate(point);
	int i;
	for (i = 0; i < point->size; i++, tmp_coor = PointGetNextCoordinate(point)) {
		PointAddCoordinate(New_point, tmp_coor);
	}
	return (void*)New_point;
}

int PointGetAttribute(PPoint pPoint, char* attribute) {
	if (!strcmp(attribute,"dimention")) {
		return pPoint->dimention;
	}
	else if (!strcmp(attribute,"size")) {
		return pPoint->size;
	}
	else {
		return -1;
	}
}