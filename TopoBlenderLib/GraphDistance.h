#pragma once
#include "StructureGraph.h"
#include "Dijkstra.h"

typedef std::map< int, std::pair<int,double> > CloseMap;

struct GraphDistanceNode{
	Vector3 pos;
	Structure::Node * n;
	int idx, gid;
	GraphDistanceNode(Vector3 & position, Structure::Node * node, int index, int globalID):
		pos(position),n(node),idx(index),gid(globalID){}
};

typedef QPair<QString, Vec4d> PathPoint;

class GraphDistance
{
public:
    GraphDistance(Structure::Graph * graph, QVector<QString> exclude_nodes = QVector<QString>());
	GraphDistance(Structure::Node * n);

	int globalID;

	void prepareNodes( Scalar resolution, const std::vector<Vector3> & startingPoints, 
		CloseMap & closestStart, QVector<Structure::Node *> nodes );

	void computeDistances( Vector3 startingPoint, double resolution = -1 );
	void computeDistances( std::vector<Vector3> startingPoints, double resolution = -1 );

	double distance( Vector3 point );
    double pathTo( Vector3 point, std::vector<Vector3> & path );
	double pathCoordTo( Vector3 point, QVector< PathPoint > & path );
	Structure::Node * closestNeighbourNode( Vector3 to, double resolution = 0.25 );
	void clear();

	Structure::Graph * g;
	double used_resolution;

	adjacency_list_t adjacency_list;
	std::vector<weight_t> min_distance;
	std::vector<vertex_t> previous;

	std::map< Structure::Node *, std::vector<GraphDistanceNode> > nodesMap;
	std::map< Structure::Node *, std::vector<Vector3> > samplePoints;
	std::map< Structure::Node *, std::pair<int,int> > nodeCount;

	std::vector<Vector3> allPoints;
	QVector< QPair<QString,Vec4d> > allCoords;
	std::vector<double> dists;
	std::vector<Structure::Node *> correspond;
	std::set< std::pair<int,int> > jumpPoints;
	QVector<QString> excludeNodes;

	bool isReady;

	// Jump free paths
	struct PathPointPair{
		PathPoint a,b;
		double wA,wB;
		PathPointPair(PathPoint A = PathPoint("",Vec4d(0))){
			a = b = A;
			wA = 1.0; wB = 0.0;
		}
		PathPointPair(PathPoint A, PathPoint B, double alpha){
			a = A;
			b = B;
			alpha = qMax(0.0,qMin(alpha,1.0));
			wA = 1 - alpha; wB = alpha;
		}
		Vector3 position(Structure::Graph * graph){
			Vector3 posA = graph->position(a.first, a.second);
			Vector3 posB = graph->position(b.first, b.second);
			return (posA * wA) + (posB * wB);
		}
	};
	double smoothPathCoordTo( Vector3 point, QVector< PathPointPair > & smooth_path );

	// DEBUG:
	void draw();
};

static inline QVector<QString> SingleNode(const QString & nodeID){
	return QVector<QString>(1, nodeID);
}