#include "cluster.h"

struct Cluster_ {
	int dimention;
	PList points;
	int min_dist;
};

PCluster ClusterCreate(int dim) {
	PList new_point_list = ListCreate(PointCopy, PointDestroy, PointCompare, PointPrint);
	if (!new_point_list)
		return NULL;
	PCluster new_cluster;
	new_cluster = (PCluster)malloc(sizeof(struct Cluster_));
	if (!new_cluster) {
		return NULL;
	}
	new_cluster->points = new_point_list;
	new_cluster->dimention = dim;
	new_cluster->min_dist = 0;
	return new_cluster;
}

void ClusterDestroy(PCluster pCluster) {
	ListDestroy(pCluster->points);
	free(pCluster);
}

Result ClusterAddPoint(PCluster pCluster, PPoint pPoint) {
	if ((pPoint->size != pCluster->dimension) || (pPoint->dimension != pCluster->dimension)){
		return FAIL;
	}
	
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	while (point1) {
		if (PointCompare(point1, pPoint)) {
			return FAIL;
		}
		point1 = (PPoint)ListGetNext(pCluster->points);
	}
	if (ListAdd(pCluster->points, pPoint) == SUCCESS) {
		pCluster->min_dist = min(pCluster->min_dist, ClusterGetMinDistance(pCluster, pPoint));
		return SUCCESS;
	}
	return FAIL;
}

int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint) {
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	int min_dist = 10000;
	while (point1) {
		int dist = 0;
		int tmp_coor = PointGetFirstCoordinate(pPoint);
		int tmp_coor1 = PointGetFirstCoordinate(point1);
		int i;
		for (i = 0; i < pPoint->size; i++, tmp_coor = PointGetNextCoordinate(pPoint),
			tmp_coor1 = PointGetNextCoordinate(point1))
		{
			dist += ((tmp_coor1 - tmp_coor) * (tmp_coor1 - tmp_coor));
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
	printf("Cluster's dimension: %d\n", pCluster->dimention);
	ListPrint(pCluster->points);
	printf("Minimum Square Distance: %d\n", pCluster->min_dist);
}