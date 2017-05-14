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

	void AddVertex(Vertex *v);
	void ConnectVertices(Vertex *v1, Vertex *v2);

	void AddLine(double a, double b);

	void init();//��ʼ����bounding box, one face,4 half_edge,4 vertex
	HalfEdge*  getIntersectHalfEdge(double a,double b);


	Vertex* intersectWithBoundingBox(HalfEdge* tmp,double a,double b);

private:
	list<Face*> faces_;
	list<Vertex*> vertices_;
	list<HalfEdge*> half_edges_;

	LECP_Doc *lecp_doc;

	list<HalfEdge*> boundingBox;//����߽��HalfEdge,����ȷ���²����ֱ�����ȴ����ĸ�face

	//����Ļ�ϵĵ㰴�պ������������ÿ������Ҳ����е�����ڵ�ǰ��ļ������򣬴洢Ϊlist,���еĵ㰴������洢Ϊvector
public:
	vector<list<LECP_Point>> polarAngleSortedVector;
};