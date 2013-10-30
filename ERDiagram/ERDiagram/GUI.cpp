#include "GUI.h"

GUI::GUI(PresentationModel* presentationModel)
{
	_presentationModel = presentationModel;
	createActions();
	createMenus();
	createToolbars();
	scene = new ERDiagramScene(this);
	scene->setSceneRect(QRectF(0, 0, 4000, 3000));

	QHBoxLayout *layout = new QHBoxLayout;
	view = new QGraphicsView(scene);
	layout->addWidget(view);

	QWidget *widget = new QWidget;
	widget->setLayout(layout);

	setCentralWidget(widget);
}


GUI::~GUI(void)
{
}

void GUI::createActions()
{
	openAction = new QAction(QIcon("images/folder.png"), tr("O&pen..."), this);
	openAction->setShortcut(tr("Ctrl+O"));
	connect(openAction, SIGNAL(triggered()), this, SLOT(browse()));

	exitAction = new QAction(QIcon("images/exit.png"), tr("E&xit"), this);
	exitAction->setShortcut(tr("Ctrl+X"));
	connect(exitAction, SIGNAL(triggered()), this, SLOT(close()));
}

void GUI::createMenus()
{
	fileMenu = menuBar()->addMenu(tr("&File"));
	fileMenu->addAction(openAction);
	fileMenu->addSeparator();
	fileMenu->addAction(exitAction);
}

void GUI::createToolbars()
{
	fileToolBar = addToolBar(tr("File"));
	fileToolBar->addAction(openAction);
	fileToolBar->addAction(exitAction);
}

void GUI::browse()
{
	QString directory = QFileDialog::getOpenFileName(this, tr("Find File"), "C://", tr("ERD File (*.erd)"));
	if (directory != "")
	{
		string inputFileText;
		inputFileText = _presentationModel->loadERDiagram_TextUI(directory.toStdString());
		ERDiagramMessageBoxManager::showMessageBox(inputFileText);
	}
}