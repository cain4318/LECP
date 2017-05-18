#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QPen>
#include "ui_lecp.h"
#include "paint.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

	LECP_Doc* lecp_doc;
private:
	Ui::LECPClass ui;

	PaintWidget *paintWidget;	
protected:
	//void paintEvent(QPaintEvent *event);
	//void mouseReleaseEvent(QMouseEvent *event);
	void resizeEvent(QResizeEvent *event);
	//void mousePressEvent(QMouseEvent *event);
	//void mouseMoveEvent(QMouseEvent *event);

public:
	//QPoint currentPoint; //��ǰ��
	//QPixmap pix; //����滭���

	///*deal with signals mapping*/
	//QSignalMapper *signalMapper;

public slots:
	void polarAngleSortSlot();//����ÿ������㣬�õ��������е㰴�չ��ڸõ���м�������
	void showVisibilityGraphSlot();
	void saveFileSlot();
	void openFileSlot();
};

#endif // LECP_H
