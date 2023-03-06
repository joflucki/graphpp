#include <QtWidgets>
#include "mainwindow.h"

MainWindow::MainWindow() : QMainWindow()
{
    mdi = new QMdiArea(this);
    mdi->setViewMode(QMdiArea::TabbedView);
    mdi->setTabsClosable(true);
    setCentralWidget(mdi);

    createActions();
    createMenus();
    createToolBars();
    addToolBar(Qt::LeftToolBarArea, this->toolsToolBar);
    statusBar()->showMessage(tr("Menu contextuel avec un clic droit"));

    setWindowTitle(tr("Graph++ Outil de visualisation et analyse de graphes"));
    setMinimumSize(200, 100);
    resize(1280, 720);
}

void MainWindow::createActions()
{
    newGraphAct = new QAction(tr("&Nouveau"), this);
    newGraphAct->setShortcut(tr("Ctrl+Shift+N"));
    newGraphAct->setStatusTip(tr("Créer un nouveau graphe..."));
    connect(newGraphAct, &QAction::triggered, this, &MainWindow::newGraph);

    openGraphAct = new QAction(tr("&Ouvrir..."), this);
    openGraphAct->setShortcut(tr("Ctrl+O"));
    openGraphAct->setStatusTip(tr("Ouvir un fichier graphe++"));
    connect(openGraphAct, &QAction::triggered, this, &MainWindow::openGraph);

    saveGraphAct = new QAction(tr("&Enregistrer"), this);
    saveGraphAct->setShortcut(tr("Ctrl+S"));
    saveGraphAct->setStatusTip(tr("Enregistrer le travail"));
    connect(saveGraphAct, &QAction::triggered, this, &MainWindow::saveGraph);

    exitAct = new QAction(tr("&Quitter"), this);
    exitAct->setShortcut(tr("Ctrl+Q"));
    exitAct->setStatusTip(tr("Quitter l'application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    undoAct = new QAction(QIcon(":/img/undo.png"), tr("&Annuler"), this);
    undoAct->setShortcut(tr("Ctrl+Z"));
    undoAct->setStatusTip(tr("Annuler la dernière action"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(QIcon(":/img/redo.png"), tr("&Rétablir"), this);
    redoAct->setShortcut(tr("Ctrl+Y"));
    redoAct->setStatusTip(tr("Rétablir la dernière modification"));
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    aboutAct = new QAction(tr("A &Propos..."), this);
    aboutAct->setStatusTip(tr("Affiche des informations sur le programme"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    selectToolAct = new QAction(QIcon(":/img/selector.png"), tr("&Outil de sélection"), this);
    selectToolAct->setShortcut(tr("Ctrl+1"));
    selectToolAct->setCheckable(true);
    selectToolAct->setChecked(true);
    selectToolAct->setStatusTip(tr("Outil de sélection/édition"));
    connect(selectToolAct, &QAction::triggered, this, &MainWindow::selectTool);

    newVertexAct = new QAction(QIcon(":/img/vertex.png"), tr("&Nouveau sommet"), this);
    newVertexAct->setShortcut(tr("Ctrl+2"));
    newVertexAct->setCheckable(true);
    newVertexAct->setStatusTip(tr("Créer un sommet"));
    connect(newVertexAct, &QAction::triggered, this, &MainWindow::newVertex);

    linkVertexAct = new QAction(QIcon(":/img/link.png"), tr("&Lier deux sommets"), this);
    linkVertexAct->setShortcut(tr("Ctrl+3"));
    linkVertexAct->setCheckable(true);
    linkVertexAct->setStatusTip(tr("Lier deux sommets entres-eux"));
    connect(linkVertexAct, &QAction::triggered, this, &MainWindow::linkVertex);

    eraserAct = new QAction(QIcon(":/img/eraser.png"), tr("&Gomme"), this);
    eraserAct->setShortcut(tr("Ctrl+4"));
    eraserAct->setCheckable(true);
    eraserAct->setStatusTip(tr("Outil de gomme"));
    connect(eraserAct, &QAction::triggered, this, &MainWindow::eraser);

    moveToolAct = new QAction(QIcon(":/img/hand.png"), tr("&Main"), this);
    moveToolAct->setShortcut(tr("Ctrl+5"));
    moveToolAct->setCheckable(true);
    moveToolAct->setStatusTip(tr("Outil de main"));
    connect(moveToolAct, &QAction::triggered, this, &MainWindow::moveTool);

    cycleGrapheAct = new QAction(QIcon(":/img/cycle.png"), tr("&Graphe cyclique"), this);
    cycleGrapheAct->setShortcut(tr("Ctrl+6"));
    cycleGrapheAct->setCheckable(true);
    cycleGrapheAct->setStatusTip(tr("Outil de création de graphe cyclique"));
    connect(cycleGrapheAct, &QAction::triggered, this, &MainWindow::cycleGraphe);

    completeGrapheAct = new QAction(QIcon(":/img/complete.png"), tr("&Graphe complet"), this);
    completeGrapheAct->setShortcut(tr("Ctrl+7"));
    completeGrapheAct->setCheckable(true);
    completeGrapheAct->setStatusTip(tr("Outil de création de graphe complet"));
    connect(completeGrapheAct, &QAction::triggered, this, &MainWindow::completeGraphe);

    bipartiteGrapheAct = new QAction(QIcon(":/img/bipartite.png"), tr("&Graphe bi parties"), this);
    bipartiteGrapheAct->setShortcut(tr("Ctrl+8"));
    bipartiteGrapheAct->setCheckable(true);
    bipartiteGrapheAct->setStatusTip(tr("Outil de création de graphe bi parties"));
    connect(bipartiteGrapheAct, &QAction::triggered, this, &MainWindow::bipartiteGraphe);

    // groupe with tools. exclusiv each other
    toolsActGroup = new QActionGroup(this);
    toolsActGroup->addAction(selectToolAct);
    toolsActGroup->addAction(newVertexAct);
    toolsActGroup->addAction(linkVertexAct);
    toolsActGroup->addAction(eraserAct);
    toolsActGroup->addAction(moveToolAct);
    toolsActGroup->addAction(cycleGrapheAct);
    toolsActGroup->addAction(completeGrapheAct);
    toolsActGroup->addAction(bipartiteGrapheAct);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(newGraphAct);
    fileMenu->addAction(openGraphAct);
    fileMenu->addAction(saveGraphAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edition"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    optionMenu = menuBar()->addMenu(tr("&Options"));

    aboutMenu = menuBar()->addMenu(tr("&A propos"));
    aboutMenu->addAction(aboutAct);
}

void MainWindow::createToolBars()
{
    toolsToolBar = addToolBar(tr(""));
    toolsToolBar->setMovable(false);

    toolsToolBar->addAction(undoAct);
    toolsToolBar->addAction(redoAct);
    toolsToolBar->addSeparator();
    toolsToolBar->addAction(selectToolAct);
    toolsToolBar->addAction(newVertexAct);
    toolsToolBar->addAction(linkVertexAct);
    toolsToolBar->addAction(eraserAct);
    toolsToolBar->addAction(moveToolAct);
    toolsToolBar->addSeparator();
    toolsToolBar->addAction(cycleGrapheAct);
    toolsToolBar->addAction(completeGrapheAct);
    toolsToolBar->addAction(bipartiteGrapheAct);
}

void MainWindow::newGraph()
{

}

void MainWindow::openGraph()
{

}

void MainWindow::saveGraph()
{

}

void MainWindow::undo()
{

}

void MainWindow::redo()
{

}

void MainWindow::about()
{
    QMessageBox::about(this, tr("A Propos"),
                       tr("Graph++, Banger international"));
}

void MainWindow::selectTool()
{

}

void MainWindow::newVertex()
{

}

void MainWindow::linkVertex()
{

}

void MainWindow::eraser()
{

}

void MainWindow::moveTool()
{

}

void MainWindow::cycleGraphe()
{

}
void MainWindow::completeGraphe()
{

}
void MainWindow::bipartiteGraphe()
{

}
