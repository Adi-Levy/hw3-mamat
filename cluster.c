#include "cluster.h"
#include "list.h"

struct Cluster_ {
	int dimention, size;
	PList points;
	int min_dist;
};

/*
 static points manipulation methods
*/
static BOOL compare_points(PPoint point1, PPoint point2) {
	return ((point1->dimention == point2->dimention) &&
			(point1->size == point2->size) &&
			(ListCompare(point1->coordinates, point2->coordinates))	? TRUE : FALSE;
}

static PPoint copy_point(PPoint point) {
	PPoint New_point = PointCreate(point->dimension);
	int i = 0;
	
	while (point->coordinates[i])
	{
		New_point->coordinates[i] = point->coordinates[i];
		i++;
	}
	New_point->dimention = point->dimesion;
	New_point->size = point->size;
	return New_point;
}

static void print_point(PPoint point) {
	PointPrint(point);
}

static void del_point(PPoint point) {
	PointDestroy(point);
}

PCluster ClusterCreate(int dim) {
	PList new_point_list = ListCreate(copy_point, del_point, compare_points, print_point);
	if (!new_point_list)
		return NULL;
	PCluster new_cluster;
	new_cluster = (PCluster)malloc(sizeof(struct Cluster_));
	if (!new_cluster) {
		return NULL;
	}
	new_cluster->points = new_point_list;
	new_cluster->dimention = dim;
	new_cluster->size = 0;
	new_cluster->min_dist = 0;
	return new_cluster;
}

void ClusterDestroy(PCluster pCluster) {
	ListDestroy(PList pCluster->points);
	free(pCluster);
}

Result ClusterAddPoint(PCluster pCluster, PPoint pPoint) {
	if (pPoint->size != pCluster->dimension){
		return FAIL;
	}
	
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	while (point1) {
		if (ListCompare(point1->coordinates, pPoint->coordinates)) {
		return FAIL;
		}
	point1 = (PPoint)ListGetNext(pCluster->points);
	}
	return (ListAdd(pCluster->points, pPoint))) ? SUCCESS : FAIL;
}

int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint) {
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	int dist = 0;
	int min_dist = 10000;
	while (point1) {
		int i = 0;
		while (point1->coordinates[i]) {
			dist += ((point1->coordinates[i] - point->coordinates[i]) *
				(point1->coordinates[i] - point->coordinates[i]));
			i++;
		}
		if (dist < min_dist) {
			min_dist = dist;
		}
		point1 = (PPoint)ListGetNext(pCluster->points);
	}
	pCluster->min_dist = min_dist;
	return min_dist;
}

void ClusterPrint(PCluster pCluster) {
	
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	printf("Cluster's dimension: %d\n", pCluster->dimention);
	printf("[");
	while (point1) {
		PointPrint(point1);
		point1 = (PPoint)ListGetNext(pCluster->points);
	}
	printf("]");
	printf("Minimum Square Distance: %d", pCluster->min_dist);
}