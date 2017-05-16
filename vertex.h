#ifndef VERTEX_H
#define VERTEX_H

#include <utility>
#include <deque>
using namespace std;

class HalfEdge;

class Vertex
{
public:
	Vertex();
	~Vertex();

	HalfEdge* half_edge() { return half_edge_; }//�ö����Ӧ�İ��
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }
	pair<double, double> point() { return point_; }//��������
	void set_point(pair<double, double> point) { point_ = point; }

	deque<Vertex*>* queue2store() { return &queue2store_; }
	void set_queue2store(deque<Vertex*>* queue2store) { queue2store_ = *queue2store; }

	int index() { return index_; }
	void set_index(int index) { index_ = index; }

private:
	HalfEdge *half_edge_;//ÿ��Vertex��Ӧ���half_edge,ѡ��һ����Ϊorigin
	pair<double, double> point_;

	/*to store the starting points of the incoming edges of this vertex */
	deque<Vertex*> queue2store_;

	/*only for test&debug ,can be used in animation*/
	int index_;
};

#endif
