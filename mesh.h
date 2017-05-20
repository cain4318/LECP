#ifndef MESH_H
#define MESH_H
#include "vertex.h"
#include "half_edge.h"
#include "lecp_doc.h"
#include <list>

using namespace std;

class Mesh
{
public:
	Mesh();
	~Mesh();

	list<Vertex*> vertices() { return vertices_; }
	list<HalfEdge*> edges() { return half_edges_; }

	/*store all directed edges from low_index to high_index in vg*/
	vector<list<pair<Vertex*, Vertex*>>>* all_edges(){ return &all_edges_; }

	void AddVertex(Vertex *v);
	void ConnectVertices(Vertex *v1, Vertex *v2);
	void AddLine(LECP_Point *point);
	void init();//��ʼ����bounding box, one face,4 half_edge,4 vertex
	void clear();
	HalfEdge*  getIntersectHalfEdge(double a,double b);
	Vertex* intersectWithBoundingBox(HalfEdge* tmp,double a,double b);

	//�õ��²����ֱ�ߺ͵�ǰ��Ľ���.
	//��newHalfEdge��next��ʼ�ж��Ƿ��н���
	//���ص�newIntersection�б��潻��Vertex
	//���ص�intersectHalfEdge���浱ǰface������half_edge��ֱ��y=ax-b�ཻ
	HalfEdge* getIntersection(double a, double b, HalfEdge newHalf, Vertex &newIntersection, HalfEdge &intersectHalfEdgeRight);
	bool onBoundingBox(Vertex* newIntersection);

	HalfEdge* getIntersectBundingBox(double a, double b, Vertex &vertex);

	//poH��neH����һ���������±߶�Ӧ������half_edge,����һ����Ҫ����ĳЩ�ֶ�
	//newPoH��new neH�Ǹò��²����ı߶�Ӧ������half_edge
	void dealWithNormalIntersection(Vertex* newIntersection, HalfEdge* intersectHalfEdgeLeft, HalfEdge* intersectHalfEdgeRight, HalfEdge* newPoH, HalfEdge* newNeH);//�����м�Ľ���

	void  postCalcPolarAngle();

private:
	list<Vertex*> vertices_;
	list<HalfEdge*> half_edges_;

	/*store all directed edges from low_index to high_index in vg*/
	vector<list<pair<Vertex*, Vertex*>>> all_edges_;

	list<HalfEdge*> boundingBox;//����߽��HalfEdge,����ȷ���²����ֱ�����ȴ����ĸ�face

public:
	vector<list<Vertex*>> sortedVector;
	vector<list<LECP_Point*>> sortedPoint;
	vector<LECP_Point*> points;
};

#endif

