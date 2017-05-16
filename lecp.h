#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include "ui_lecp.h"
#include <QtGui/QPainter>
#include<QtGui/QPen>
#include"Tool.h"
#include"DataStruct.h"
#include "mesh.h"
#include "Paint.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

private:
	Ui::LECPClass ui;

	PaintWidget *paintWidget;
protected:
	//void paintEvent(QPaintEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);
	//void mousePressEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

	list<LECP_Point> getPolarSort(LECP_Point tmpPoint,vector<LECP_Point> subV);

public:
	QPoint currentPoint;//��ǰ��
	QPixmap pix;//����滭���

	bool flag;//�����Ƿ���

	LECP_Doc *lecp_doc;
	Mesh *mesh;
public slots:
  void polarAngleSortSlot();//����ÿ������㣬�õ��������е㰴�չ��ڸõ���м�������

};

#endif // LECP_H
