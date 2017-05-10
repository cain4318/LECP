#ifndef LECP_H
#define LECP_H

#include <QtWidgets/QMainWindow>
#include "ui_lecp.h"
#include <QtGui/QPainter>
#include<QtGui/QPen>
#include <qsignalmapper.h>
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

	/*deal with signals mapping*/
	QSignalMapper *signalMapper;

	bool flag;//�����Ƿ���

	LECP_Doc *lecp_doc;

private slots:
	void doClicked(const QString & btnname);
	void showVGSlot();

signals:
	void showVGSignal();
};

#endif // LECP_H
