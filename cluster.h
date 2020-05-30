#ifndef _CLUSTER_H_
#define _CLUSTER_H_
#include "defs.h"
#include "point.h"

typedef struct Cluster_* PCluster;

/*User functions*/
static BOOL compare_points(PPoint, PPoint);
static PPoint copy_point(PPoint);
static void print_point(PPoint);
static void del_point(PPoint);

/*Interface functions*/
PCluster ClusterCreate(int);
void ClusterDestroy(PCluster);
Result ClusterAddPoint(PCluster, PPoint);
int ClusterGetMinDistance(PCluster, PPoint);
void ClusterPrint(PCluster);

#endif