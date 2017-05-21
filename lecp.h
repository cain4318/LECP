#ifndef LECP_H
#define LECP_H
#define showSpeedMax 20
#define showSpeedMin 1

#include <QtWidgets/QMainWindow>
#include <QtGui/QPainter>
#include <QtGui/QPen>

#include <qspinbox.h>
#include <qmessagebox.h>
#include <qlabel.h>
#include <qcheckbox.h>
#include <qpushbutton.h>
#include <qdebug.h>
#include <qfiledialog.h>
#include <qslider.h>

#include "ui_lecp.h"
#include"Paint.h"
#include"lecp_doc.h"

class LECP : public QMainWindow
{
	Q_OBJECT

public:
	LECP(QWidget *parent = 0);
	~LECP();

	
private:
	Ui::LECPClass ui;

	PaintWidget *paintWidget;

	//toolbar content:
	QCheckBox* sortComboBox;
	QCheckBox* vgComboBox;
	QCheckBox* chainComboBox;
	QPushButton* startButton;
	QPushButton* stopButton;
	QSlider* speedSlider;
	QSpinBox* pSpinBox;

public:
	void createToolBar();
public slots:
	void polarAngleSortSlot();//����ÿ������㣬�õ��������е㰴�չ��ڸõ���м�������
	void showVisibilityGraphSlot();
	void saveFileSlot();
	void openFileSlot();
	void polarAngleSortDCELSlot();

	//������ʾ
	void sortMenuSlot();
	void vgMenuSlot();
	void chainMenuSlot();
	void onSortSelected(int flag);
	void onVGSelected(int flag);
	void onChainSelected(int flag);
	void changeSpeedSlot(int newSpeed);
	void startShowSlot();
	void stopShowSlot();
public:
	Mesh *mesh;
	LECP_Doc* lecp_doc;

	//show variable
	enum showMode { finalRes, allPoints, simplePoint };
	bool showSort = false;
	bool showVG = false;
	bool showChain = false;
	bool isStart = false;
	bool isStop = false;
	int showspeed = 1;
	
};

#endif // LECP_H
