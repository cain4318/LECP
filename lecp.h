#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include "ui_lecp.h"
#include <QtGui/QPainter>
#include<QtGui/QPen>
#include"Tool.h"
#include"DataStruct.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

private:
	Ui::LECPClass ui;
protected:
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);
	void mouseReleaseEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

public:
	QPoint currentPoint;//��ǰ��
	QPixmap pix;//����滭���

	bool flag;//�����Ƿ���

	LECP_Doc *lecp_doc;
};

#endif // LECP_H
