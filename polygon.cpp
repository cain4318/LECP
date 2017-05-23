#include "util.h"
#include "polygon.h"
#include <qdebug.h>
#include <algorithm> 
#include <functional> 
#include <iterator> 
/////////////////////////////////////////////
// red: kernal ��kernal ���ĵ�
// black �� kernal �Ҳ�ĵ�
// yellow��
// green:
////////////////////////////////////////////
Polygon::Polygon() {
	
}


Polygon::Polygon(vector<Vertex*> vertices) {
	vertices_ = vertices;
	if (vertices_.size() > 0)
		kernel_ = vertices_[0];
}

Polygon::Polygon(vector<Vertex*> vertices, PaintWidget* paint_widget) {
	vertices_ = vertices;
	if (vertices_.size() > 0)
		kernel_ = vertices_[0];
	paint_widget_ = paint_widget;
}

Polygon::~Polygon() {

	clear();
}

void Polygon::clear()
{
	vertices_.clear();
	paint_widget_->allQLines2Draw.clear();
	paint_widget_->allQPoints2Draw.clear();
}
void Polygon::setVertices(vector<Vertex*> vertices)
{
	vertices_.clear();
	vertices_ = vertices;
	if (vertices_.size() > 0)
		kernel_ = vertices_[0];
}


void Polygon::setPaintWidget(PaintWidget* paintWidget)
{
	paint_widget_ = paintWidget;
}

PaintWidget* Polygon::getPaintWidget()
{
	return paint_widget_;
}

bool Polygon::comparePolar(Vertex* p, Vertex* q){
	Vertex *s = kernel_;
	double px = p->point().first;
	double py = p->point().second;
	double qx = q->point().first;
	double qy = q->point().second;
	double sx = s->point().first;
	double sy = s->point().second;
	double area = px * qy - py * qx + qx * sy - qy * sx + sx * py - sy * px;
	// TODO: > or <
	return area < 0;
}

//���Ǵ�С�������С���ʱ����
vector<Vertex*> Polygon::getStarPolygon() {
	vector<Vertex*>::iterator it = vertices_.begin();	
	//to left test���м�������
	//sort(vertices_.begin() + 1, vertices_.end(), std::bind(&Polygon::comparePolar, this, std::placeholders::_1, std::placeholders::_2));
	return vertices_;
}

/*process bewteen vertex i&j (counterclockwise order:i->j)
in creating visibility graph*/

void Polygon::proceedNeighborPoints(Vertex* i, Vertex* j,int index_i,int index_j)
{
	

	while ((!(i->Q_.empty())) && toLeft(i->Q_.front(), i, j)){
		//PROCEED
		proceedNeighborPoints(i->Q_.front(), j, i->Q_.front()->index(),j->index());
		//DEQUEUE(Qi)
		int temp_vertex_index = i->Q_.front()->index();
		i->Q_.pop_front();

		//show animation
		paint_widget_->allQPoints2Draw[temp_vertex_index].setColor(Qt::black);
	}
	//ADD(ij)
		//show animation
	paint_widget_->allQPoints2Draw[index_i].setColor(Qt::yellow);
	paint_widget_->allQPoints2Draw[index_j].setColor(Qt::green);

	HalfEdge *e = new HalfEdge(i, j);
	i->outgoing_edges_.push_back(e);
	j->incoming_edges_.push_back(e);
	//ENQUEUE(i,Qj)
	j->Q_.push_back(i);

	//animation
	//MyQPoint vertex_i(QPoint(i->point().first+10, i->point().second+10));
	//MyQPoint vertex_j(QPoint(j->point().first+10, j->point().second+10));
	//vertex_i.setColor(Qt::yellow);
	//vertex_j.setColor(Qt::blue);
	//this->paint_widget_->allQPoints2Draw.push_back(vertex_i);
	//this->paint_widget_->allQPoints2Draw.push_back(vertex_j);
	//this->paint_widget_->update();
	//_sleep(2 * 1000);
	return;
}

vector<Vertex*> Polygon::getVisibilityGraph()
{
	//kernal �� starpolygon�Ķ���
	for (size_t i = 0; i < vertices_.size(); ++i) {
		MyQPoint vertex_i(QPoint(vertices_[i]->point().first, (vertices_[i]->point().second*-1)));
		if (i == 0)
			vertex_i.setColor(Qt::red);
		else
			vertex_i.setColor(Qt::black);
		vertex_i.setIndex(vertices_[i]->index());
		this->paint_widget_->allQPoints2Draw.push_back(vertex_i);

		MyQline edge_i;
		if (i == vertices_.size() - 1)
			edge_i.setLine(vertices_[i]->point().first, vertices_[i]->point().second*-1, vertices_[0]->point().first, vertices_[0]->point().second*-1);
		else
			edge_i.setLine(vertices_[i]->point().first, vertices_[i]->point().second*-1, vertices_[i + 1]->point().first, vertices_[i + 1]->point().second*-1);
		this->paint_widget_->allQLines2Draw.push_back(edge_i);
		this->paint_widget_->repaint();
		this->paint_widget_->update();
		_sleep(2 * 1000);
	}

	vector<Vertex*>::iterator it = vertices_.begin();
	for (; it != vertices_.end(); ++it) {
		(*it)->Q_.clear();
	}

	for (size_t i = 1; i + 1 < vertices_.size(); ++i) {
		proceedNeighborPoints(vertices_[i], vertices_[i + 1], vertices_[i]->index(), vertices_[i+1]->index());
	}
	return vertices_;
}

/* For each vertex in the VG, we have a list of incoming edges
* Also, the incoming edges have been sorted counterclock wise
*/

HalfEdge* ConvexChainPoint(Vertex * p, int &len) {
	vector<HalfEdge*> in_edges = p->incoming_edges_;
	vector<HalfEdge*> out_edges = p->outgoing_edges_;
	qDebug() << p->index() << "# in edges:" << in_edges.size() << "," << "# out edges:" << out_edges.size();
	vector<HalfEdge*>::reverse_iterator it_i;
	vector<HalfEdge*>::iterator it_o = out_edges.begin();

	HalfEdge *longest_edge;
	int m = 0;
	for (it_i = in_edges.rbegin(); it_i != in_edges.rend(); it_i++) {
		// we compute the L for incoming edge i.
		qDebug() << "in edge:" << (*it_i)->target()->index() << "<-" << (*it_i)->origin()->index();
		if (it_o != out_edges.end()) {
			qDebug() << "out edge:" << (*it_o)->origin()->index() << "->" << (*it_o)->target()->index();
			qDebug() << "convex turn:" << isConvexTurn(*it_i, *it_o);
		}
		while (it_o != out_edges.end() && isConvexTurn(*it_i, *it_o)) {
			if ((*it_o)->L() > m) {
				m = (*it_o)->L();
				longest_edge = *it_i;
				(*it_i)->prev_chain_ = *it_o;
			}
			it_o++;
		}
		qDebug() << (*it_i)->target()->index() << "<-" << (*it_i)->origin()->index() << " L:" << m + 1;
		(*it_i)->set_L(m + 1);
	}
	len = m + 1;
	return longest_edge;
}

vector<Vertex*> Polygon::getConvexChain() {
	int max_len = 0;
	HalfEdge *longest_edge;
	for (size_t i = vertices_.size() - 1; i > 0; --i) {
		Vertex *p = vertices_[i];
		int len = 0;
		HalfEdge *temp_edge = ConvexChainPoint(p, len);
		if (len > max_len) {
			max_len = len;
			longest_edge = temp_edge;
		}
		qDebug() << "max_len for point" << p->index() << ":" << max_len << endl;
	}
	qDebug() << "max_len for all points:" << max_len << endl;
	// TODO
	vector<Vertex*> convex_chain_;
	/*convex_chain_.push_back(longest_edge->origin());
	while (longest_edge) {
		convex_chain_.push_back(longest_edge->target());
	}*/
	return convex_chain_;
}