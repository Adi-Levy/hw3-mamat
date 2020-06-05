#include "point.h"

struct Point_ {
	int dimension, size;
	PList coordinates;
};

/*
 static coordinate manipulation methods
*/
/*
 Function: compare_coor
 Abstract: compares 2 coordinets
 Parameters: coor1 - a pointer to the first coordinet to compare
			 coor2 - a pointer to the second coordinet to compare
 Return: TRUE if coordinets are equal, FLASE if not
 */
static BOOL compare_coor(void* coor1, void* coor2) {
	if (!coor1 || !coor2) {
		if (!coor1 && !coor2)
			return TRUE;
		return FALSE;
	}
	return (*(int*)coor1 == *(int*)coor2)?TRUE:FALSE;
}

/*
 Function: copy_coor
 Abstract: copies a coordinet
 Parameters: coor - a pointer to a coordinet to copy
 Return: a void pointer to the copied coordinet that can be casted back to int* form
 */
static void* copy_coor(void* coor) {
	int* cpy_coor;
	cpy_coor = (int*)malloc(sizeof(int));
	if (!cpy_coor)
		return NULL;
	*cpy_coor = *(int*)coor;
	return (void*)cpy_coor;
}

/*
 Function: print_coor
 Abstract: prints the coordinet in the requested format
 Parameters: coor - a pointer to a coordinet to print
 Return: N/A
 */
static void print_coor(void* coor) {
	printf("%d ", *(int*)coor);
}

/*
 Function: del_coor
 Abstract: deletes the coordinet
 Parameters: coor - a pointer to a coordinet to delete
 Return: N/A
 */
static void del_coor(void* coor) {
	free((int*)coor);
}


/*
 iterfacce function implementation
*/
/*
 Function: PointCreate
 Abstract: creates a new point object with an empty coordinets list
 Parameters: dim - the dimension of the new point
 Return: pointer to the new point object
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
	new_point->dimension = dim;
	new_point->size = 0;
	return new_point;
}

/*
 Function: PointDestroy
 Abstract: deletes the point
 Parameters: pPoint - a pointer to a point object to delete
 Return: N/A
 */
void PointDestroy(void* pPoint) {
	PPoint point = (PPoint)pPoint;
	ListDestroy(point->coordinates);
	free(point);
}

/*
 Function: PointAddCoordinate
 Abstract: add a coordinet to the point
 Parameters: pPoint - a pointer to a point object to add a coordinet to
			 n_coodinate - the new coordinet to be added
 Return: SUCCESS if the addition to the coordinet list was successful. FAIL otherwise
 */
Result PointAddCoordinate(PPoint pPoint, int n_coordinate) {
	if (pPoint->size != pPoint->dimension) {
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

/*
 Function: PointGetFirstCoordinate
 Abstract: gets the first coordinate in the point coordinets list
			also initializes the coordinet list iterator
 Parameters: pPoint - a pointer to a point object to get the first coordinate of
 Return: integer with the value of the first coordinet
 */
int PointGetFirstCoordinate(PPoint pPoint) {
	int* coor = (int*)ListGetFirst(pPoint->coordinates);
	return (coor) ? *coor : 0;
}

/*
 Function: PointGetNextCoordinate
 Abstract: gets the next coordinate in the point coordinets list
 Parameters: pPoint - a pointer to a point object to get the next coordinate of
 Return: integer with the value of the next coordinet
 */
int PointGetNextCoordinate(PPoint pPoint) {
	int* coor = (int*)ListGetNext(pPoint->coordinates);
	return (coor) ? *coor : 0;
}

/*
 Function: PointPrint
 Abstract: prints the point information in the requested format
 Parameters: point - a pointer to a point object to print
 Return: N/A
 */
void PointPrint(void* point) {
	PPoint pPoint = (PPoint)point;
	printf("Point Dimension: %d, Size: %d, Coordinates: ", pPoint->dimension, pPoint->size);
	ListPrint(pPoint->coordinates);
	//printf("\n");
}

/*
 Function: PointCompare
 Abstract: compares 2 points by dimention size and coordinates
 Parameters: pPoint1 - a pointer to the first point to compare
			 pPoint2 - a pointer to the second point to compare
 Return: TRUE if all point attributes and coordinates are the same. FALSE otherwise
 */
BOOL PointCompare(void* pPoint1, void* pPoint2) {
	PPoint point1 = (PPoint)pPoint1;
	PPoint point2 = (PPoint)pPoint2;
	return ((point1->dimension == point2->dimension) &&
		(point1->size == point2->size) &&
		(ListCompare(point1->coordinates, point2->coordinates))) ? TRUE : FALSE;
}

/*
 Function: PointCopy
 Abstract: deep copies a point
 Parameters: pPoint - a pointer to a point object to copy
 Return: void* to the copied point that can be casted to a PPoint when needed 
 */
void* PointCopy(void* pPoint) {
	PPoint point = (PPoint)pPoint;
	PPoint New_point = PointCreate(point->dimension);
	int tmp_coor = PointGetFirstCoordinate(point);
	int i;
	for (i = 0; i < point->size; i++, tmp_coor = PointGetNextCoordinate(point)) {
		PointAddCoordinate(New_point, tmp_coor);
	}
	return (void*)New_point;
}

/*
 Function: PointGetAttribute
 Abstract: gets a non list attribute of the point
 Parameters: pPoint - a pointer to a point to get the attribute of
			 attribute - an Attribute value to get
 Return: an integer that is equal to the point's attribute
 */
int PointGetAttribute(PPoint pPoint, Attribute attribute) {
	if (attribute == DIMENSION) {
		return pPoint->dimension;
	}
	else if (attribute == SIZE) {
		return pPoint->size;
	}
	else {
		return -1;
	}
}