#ifndef HALFEDGE_H
#define HALFEDGE_H

class HalfEdge;

//�޶�
class Face
{
public:
	Face();
	~Face();

	HalfEdge* half_edge() { return half_edge_; }//��İ�ߣ�����ඥ���Ӧ��half_edge
	void set_half_edge(HalfEdge *half_edge) { half_edge_ = half_edge; }

private:
	HalfEdge *half_edge_;
};

#endif