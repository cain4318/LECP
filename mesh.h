#ifndef MESH_H
#define MESH_H
#include "face.h"
#include "vertex.h"
#include "half_edge.h"
#include <list>
#include <Tool.h>

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	list<Face*> faces() { return faces_; }
	list<Vertex*> vertices() { return vertices_; }
	list<HalfEdge*> edges() { return half_edges_; }
	/*store all directed edges from low_index to high_index in vg*/
	//list<pair<Vertex*, Vertex*>>* all_edges(){ return &all_edges_; }
	vector<list<pair<Vertex*, Vertex*>>>* all_edges(){ return &all_edges_; }

	void AddVertex(Vertex *v);
	void ConnectVertices(Vertex *v1, Vertex *v2);
	void AddLine(double a, double b);
	void init();//��ʼ����bounding box, one face,4 half_edge,4 vertex
	void clear();
	HalfEdge*  getIntersectHalfEdge(double a,double b);
	Vertex* intersectWithBoundingBox(HalfEdge* tmp,double a,double b);

private:
	list<Face*> faces_;
	list<Vertex*> vertices_;
	list<HalfEdge*> half_edges_;
	/*store all directed edges from low_index to high_index in vg*/
	//list<pair<Vertex*, Vertex*>> all_edges_;
	vector<list<pair<Vertex*, Vertex*>>> all_edges_;
	LECP_Doc *lecp_doc;

	list<HalfEdge*> boundingBox;//����߽��HalfEdge,����ȷ���²����ֱ�����ȴ����ĸ�face

	//����Ļ�ϵĵ㰴�պ������������ÿ������Ҳ����е�����ڵ�ǰ��ļ������򣬴洢Ϊlist,���еĵ㰴������洢Ϊvector
public:
	vector<list<LECP_Point>> polarAngleSortedVector;
	vector<list<Vertex*>> sortedVector;
};

#endif

