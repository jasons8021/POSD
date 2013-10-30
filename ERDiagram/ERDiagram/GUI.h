#ifndef GUI_H_
#define GUI_H_
#include <QtGui/QMainWindow>
#include <QFileDialog>
#include <QMenu>
#include <QtGui>
#include <QLabel>
#include <QFileDialog>
#include "ERDiagramMessageBoxManager.h"
#include "ERDiagramScene.h"
#include "PresentationModel.h"

QT_BEGIN_NAMESPACE
class DiagramScene;
class QGraphicsView;
class QAction;
QT_END_NAMESPACE

class GUI:public QMainWindow
{
	Q_OBJECT
public:
	GUI(PresentationModel*);
	virtual ~GUI();

	private slots:
		void browse();
private:
	void createActions();
	void createMenus();
	void createToolbars();

	QGraphicsView* view;
	ERDiagramScene* scene;

	//bar
	QMenu* fileMenu;
	QToolBar* fileToolBar;

	//QAction
	QAction* exitAction;
	QAction* openAction;

	PresentationModel* _presentationModel;
};
#endif