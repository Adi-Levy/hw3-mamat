#include "cluster.h"
#include "point.h"

struct Cluster_ {
	int dimension;
	PList points;
	int min_dist;
};

/*
 Function: ClusterCreate
 Abstract: creates a new cluster of points
 Parameters: dim - int, the dimension of all points in the cluster
 Return: pointer to the new cluster with no points in it
 */
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
	new_cluster->dimension = dim;
	new_cluster->min_dist = 0;
	return new_cluster;
}

/*
 Function: ClusterDestroy
 Abstract: deletes a cluster and all it's points
 Parameters: pCluster - a pointer to the cluster to delete
 Return: N/A
 */
void ClusterDestroy(PCluster pCluster) {
	ListDestroy(pCluster->points);
	free(pCluster);
}

/*
 Function: ClusterAddPoint
 Abstract: adds a pooint to the cluster
 Parameters: pCluster - a pointer to the cluster to add to
			 pPoint - a pointer to the point to add to the cluster
 Return: SUCCESS if the point was added correctly. FAIL otherwise
 */
Result ClusterAddPoint(PCluster pCluster, PPoint pPoint) {
	if ((PointGetAttribute(pPoint,SIZE) != pCluster->dimension) || 
		(PointGetAttribute(pPoint, DIMENSION) != pCluster->dimension)){
		return FAIL;
	}
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	while (point1) {
		if (PointCompare(point1, pPoint)) {
			return FAIL;
		}
		point1 = (PPoint)ListGetNext(pCluster->points);
	}
	int n_min_d = ClusterGetMinDistance(pCluster, pPoint);
	n_min_d = (pCluster->min_dist < n_min_d) ? pCluster->min_dist : n_min_d;
	if (ListAdd(pCluster->points, pPoint) == SUCCESS) {
		pCluster->min_dist = n_min_d;
		return SUCCESS;
	}
	return FAIL;
}

/*
 Function: ClusterGetMinDistance
 Abstract: claculates the min square distance between a point and a cluster
 Parameters: pCluster - a pointer to the cluster to get the min square distance to
			 pPoint - a pointer to the point to get the min square distance from
 Return: int holding the min square distance between the point and the cluster
 */
int ClusterGetMinDistance(PCluster pCluster, PPoint pPoint) {
	PPoint point1 = (PPoint)ListGetFirst(pCluster->points);
	int min_dist = (pCluster->min_dist < 10000 && pCluster->min_dist) ? pCluster->min_dist : 10000;
	while (point1) {
		int dist = 0;
		int tmp_coor = PointGetFirstCoordinate(pPoint);
		int tmp_coor1 = PointGetFirstCoordinate(point1);
		int i;
		for (i = 0; i < PointGetAttribute(pPoint, SIZE); i++, tmp_coor = PointGetNextCoordinate(pPoint),
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

/*
 Function: ClusterPrint
 Abstract: prints a givven cluster in the requested format
 Parameters: pCluster - a pointer to the cluster to be printed
 Return: N/A
 */
void ClusterPrint(PCluster pCluster) {
	printf("Cluster's dimension: %d\n", pCluster->dimension);
	ListPrint(pCluster->points);
	printf("Minimum Square Distance: %d\n", pCluster->min_dist);
}