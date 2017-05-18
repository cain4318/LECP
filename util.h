#include "vertex.h"
#include "half_edge.h"
//���պ����������������
bool comparePoint(Vertex* a, Vertex* b);

/*toLeft test
direct line i->j, test point k*/
bool toLeft(Vertex* i, Vertex* j, Vertex* k);
bool toLeft(pair<double, double> i, pair<double, double> j, pair<double, double> k);
bool isConvexTurn(HalfEdge *i, HalfEdge *o);