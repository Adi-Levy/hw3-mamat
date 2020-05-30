#ifndef _CLUSTER_H_
#define _CLUSTER_H_

#include "defs.h"
#include "point.h"

typedef struct Cluster_* PCluster;

/*Interface functions*/
PCluster ClusterCreate(int);
void ClusterDestroy(PCluster);
Result ClusterAddPoint(PCluster, PPoint);
int ClusterGetMinDistance(PCluster, PPoint);
void ClusterPrint(PCluster);

#endif