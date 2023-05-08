#include <QtWidgets>
#include "mainwindow.h"
#include "qboard.h"
#include "graphdockwidget.h"
#include "vertexdockwidget.h"

/// @brief Constructor main window
/// @author Plumey Simon
MainWindow::MainWindow() : QMainWindow()
{
    mdi = new QMdiArea(this);
    mdi->setViewMode(QMdiArea::TabbedView);
    mdi->setTabsClosable(true);
    setCentralWidget(mdi);

    createDockWindows();
    createActions();
    createMenus();
    createToolBars();
    addToolBar(Qt::LeftToolBarArea, this->toolsToolBar);
    statusBar()->showMessage(tr("Menu contextuel avec un clic droit"));
    setStyleSheet("QStatusBar{border-top: 1px outset grey;}");

    setWindowTitle(tr("Graph++ Outil de visualisation et analyse de graphes"));
    setMinimumSize(200, 100);
    resize(1280, 720);
}

/// @brief Create all application's actions
/// @author Plumey Simon
void MainWindow::createActions()
{
    newGraphAct = new QAction(tr("&Nouveau"), this);
    newGraphAct->setShortcut(QKeySequence(QKeySequence::New));
    newGraphAct->setStatusTip(tr("Créer un nouveau graphe..."));
    connect(newGraphAct, &QAction::triggered, this, &MainWindow::newGraph);

    openGraphAct = new QAction(tr("&Ouvrir..."), this);
    openGraphAct->setShortcut(QKeySequence(QKeySequence::Open));
    openGraphAct->setStatusTip(tr("Ouvir un fichier graphe++"));
    connect(openGraphAct, &QAction::triggered, this, &MainWindow::openGraph);

    saveGraphAct = new QAction(tr("&Enregistrer"), this);
    saveGraphAct->setShortcut(QKeySequence(QKeySequence::Save));
    saveGraphAct->setStatusTip(tr("Enregistrer le travail"));
    connect(saveGraphAct, &QAction::triggered, this, &MainWindow::saveGraph);

    exitAct = new QAction(tr("&Quitter"), this);
    exitAct->setShortcut(QKeySequence(QKeySequence::Quit));
    exitAct->setStatusTip(tr("Quitter l'application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    undoAct = new QAction(QIcon(":/img/undo.png"), tr("&Annuler"), this);
    undoAct->setShortcut(QKeySequence(QKeySequence::Undo));
    undoAct->setStatusTip(tr("Annuler la dernière action"));
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(QIcon(":/img/redo.png"), tr("&Rétablir"), this);
    redoAct->setShortcut(QKeySequence(QKeySequence::Redo));
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
    //connect(selectToolAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    newVertexAct = new QAction(QIcon(":/img/vertex.png"), tr("&Nouveau sommet"), this);
    newVertexAct->setShortcut(tr("Ctrl+2"));
    newVertexAct->setCheckable(true);
    newVertexAct->setStatusTip(tr("Créer un sommet"));
    //connect(newVertexAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    linkVertexAct = new QAction(QIcon(":/img/link.png"), tr("&Lier deux sommets"), this);
    linkVertexAct->setShortcut(tr("Ctrl+3"));
    linkVertexAct->setCheckable(true);
    linkVertexAct->setStatusTip(tr("Lier deux sommets entres-eux"));
    //connect(linkVertexAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    eraserAct = new QAction(QIcon(":/img/eraser.png"), tr("&Gomme"), this);
    eraserAct->setShortcut(tr("Ctrl+4"));
    eraserAct->setCheckable(true);
    eraserAct->setStatusTip(tr("Outil de gomme"));
    //connect(eraserAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    moveToolAct = new QAction(QIcon(":/img/hand.png"), tr("&Main"), this);
    moveToolAct->setShortcut(tr("Ctrl+5"));
    moveToolAct->setCheckable(true);
    moveToolAct->setStatusTip(tr("Outil de main"));
    //connect(moveToolAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    cycleGrapheAct = new QAction(QIcon(":/img/cycle.png"), tr("&Graphe cyclique"), this);
    cycleGrapheAct->setShortcut(tr("Ctrl+6"));
    cycleGrapheAct->setCheckable(true);
    cycleGrapheAct->setStatusTip(tr("Outil de création de graphe cyclique"));
    //connect(cycleGrapheAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    completeGrapheAct = new QAction(QIcon(":/img/complete.png"), tr("&Graphe complet"), this);
    completeGrapheAct->setShortcut(tr("Ctrl+7"));
    completeGrapheAct->setCheckable(true);
    completeGrapheAct->setStatusTip(tr("Outil de création de graphe complet"));
    //connect(completeGrapheAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

    bipartiteGrapheAct = new QAction(QIcon(":/img/bipartite.png"), tr("&Graphe bi parties"), this);
    bipartiteGrapheAct->setShortcut(tr("Ctrl+8"));
    bipartiteGrapheAct->setCheckable(true);
    bipartiteGrapheAct->setStatusTip(tr("Outil de création de graphe bi parties"));
    //connect(bipartiteGrapheAct, &QAction::triggered, this, &MainWindow::updateSelectedTool);

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
    connect(toolsActGroup, &QActionGroup::triggered, this, &MainWindow::updateSelectedTool);

    closeCurrentGrapheAct = new QAction(tr("&Fermer le graphe actif"), this);
    closeCurrentGrapheAct->setShortcut(QKeySequence(QKeySequence::Close));
    closeCurrentGrapheAct->setStatusTip(tr("Ferme le graphe qui est actuellement ouvert et visible"));
    connect(closeCurrentGrapheAct, &QAction::triggered, this, &MainWindow::closeCurrentGraphe);

    closeAllGrapheAct = new QAction(tr("&Fermer tous les graphes"), this);
    closeAllGrapheAct->setStatusTip(tr("Ferme tous les graphes qui sont actuellement ouverts SANS les enregistrer"));
    connect(closeAllGrapheAct, &QAction::triggered, this, &MainWindow::closeAllGraphe);

    nextAct = new QAction(tr("&Graphe suivant"), this);
    nextAct->setShortcut(QKeySequence(QKeySequence::NextChild));
    connect(nextAct, &QAction::triggered, this, &MainWindow::next);

    prevAct = new QAction(tr("&Graphe suivant"), this);
    prevAct->setShortcut(QKeySequence(QKeySequence::PreviousChild));
    connect(prevAct, &QAction::triggered, this, &MainWindow::prev);

    toggleGraphDockAct = graphDock->toggleViewAction();
    toggleGraphDockAct->setText(tr("&Afficher les propriétés du graphe"));

    toggleVertexDockAct = vertexDock->toggleViewAction();
    toggleVertexDockAct->setText(tr("&Afficher les propriétés du sommet"));

    // update graph in graphdockwidget
    connect(mdi, &QMdiArea::subWindowActivated, this, &MainWindow::updateGraphDockWidget);
}

/// @brief Create all application's menus
/// @author Plumey Simon
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(newGraphAct);
    fileMenu->addAction(openGraphAct);
    fileMenu->addAction(saveGraphAct);
    fileMenu->addSeparator();
    fileMenu->addAction(closeCurrentGrapheAct);
    fileMenu->addAction(closeAllGrapheAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    editMenu = menuBar()->addMenu(tr("&Edition"));
    editMenu->addAction(undoAct);
    editMenu->addAction(redoAct);

    optionMenu = menuBar()->addMenu(tr("&Options"));
    optionMenu->addAction(toggleGraphDockAct);
    optionMenu->addAction(toggleVertexDockAct);

    aboutMenu = menuBar()->addMenu(tr("&A propos"));
    aboutMenu->addAction(aboutAct);
}

/// @brief Create the tool bars
/// @author Plumey Simon
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

/// @brief Create the dock widgets like an overlay
/// @author Plumey Simon
void MainWindow::createDockWindows()
{
    graphDock = new QDockWidget(tr("Propriétés du graphe"), this);
    graphDock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

    graphDockWidget = new GraphDockWidget(this);
    graphDock->setWidget(graphDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, graphDock);

    vertexDock = new QDockWidget(tr("Propriétés du sommet"), this);
    vertexDockWidget = new VertexDockWidget(this);
    vertexDock->setWidget(vertexDockWidget);
    addDockWidget(Qt::RightDockWidgetArea, vertexDock);
}

/// @brief Create a graph
/// @author Plumey Simon
void MainWindow::newGraph()
{
    QBoard *qBoard= new QBoard(vertexDockWidget);
    mdi->addSubWindow(qBoard);
    qBoard->setWindowTitle("Graphe");
    qBoard->show();
    // set right tool
    updateSelectedTool(toolsActGroup->checkedAction());
}

/// @brief Open a graph
/// @author Plumey Simon
void MainWindow::openGraph()
{

}

/// @brief Save a graph
/// @author Plumey Simon
void MainWindow::saveGraph()
{

}

/// @brief Undo
/// @author Plumey Simon
void MainWindow::undo()
{

}

/// @brief Redo
/// @author Plumey Simon
void MainWindow::redo()
{

}

/// @brief About message box
/// @author Plumey Simon
void MainWindow::about()
{
    QMessageBox::about(this, tr("A Propos"),
                       tr("Graph++, Banger international"));
}

/// @brief update the selected graph of the GraphDockWidget depending of the selected tab
/// @author Plumey Simon
void MainWindow::updateGraphDockWidget()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        graphDockWidget->setSelectedGraph(qBoard->graph);
    }
}

/// @brief update the selected tool
/// @param QAction: action selected
/// @author Plumey Simon
void MainWindow::updateSelectedTool(QAction* action)
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (action != nullptr && qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());

        if (action == selectToolAct)
        {
            qBoard->setSelectedTool(Tool::SELECTOR);
            qBoard->setCursor(QCursor(Qt::ArrowCursor));
            qDebug() << "updateSelectedTool: SELECTOR";
        }
        else if (action == newVertexAct)
        {
            qBoard->setSelectedTool(Tool::CREATE_VERTEX);
            qBoard->setCursor(QCursor(Qt::CrossCursor));
            qDebug() << "updateSelectedTool: CREATE_VERTEX";
        }
        else if (action == linkVertexAct)
        {
            qBoard->setSelectedTool(Tool::CREATE_EDGE);
            qBoard->setCursor(QCursor(Qt::CrossCursor));
            qDebug() << "updateSelectedTool: CREATE_EDGE";
        }
        else if (action == eraserAct)
        {
            qBoard->setSelectedTool(Tool::ERASER);
            qBoard->setCursor(QCursor(QPixmap(":/img/eraser.png")));
            qDebug() << "updateSelectedTool: ERASER";
        }
        else if (action == moveToolAct)
        {
            qBoard->setSelectedTool(Tool::HAND);
            qBoard->setCursor(QCursor(Qt::OpenHandCursor));
            qDebug() << "updateSelectedTool: HAND";
        }
        else if (action == cycleGrapheAct)
        {
            qBoard->setSelectedTool(Tool::CYCLE_GRAPH);
            qBoard->setCursor(QCursor(Qt::CrossCursor));
            qDebug() << "updateSelectedTool: CYCLE_GRAPH";
        }
        else if (action == completeGrapheAct)
        {
            qBoard->setSelectedTool(Tool::COMPLETE_GRAPH);
            qBoard->setCursor(QCursor(Qt::CrossCursor));
            qDebug() << "updateSelectedTool: COMPLETE_GRAPH";
        }
        else if (action == bipartiteGrapheAct)
        {
            qBoard->setSelectedTool(Tool::BIPARTITE_GRAPH);
            qBoard->setCursor(QCursor(Qt::CrossCursor));
            qDebug() << "updateSelectedTool: BIPARTITE_GRAPH";
        }
    }
}

/// @brief close current graph
/// @author Plumey Simon
void MainWindow::closeCurrentGraphe()
{
    mdi->closeActiveSubWindow();
}

/// @brief close all graphs
/// @author Plumey Simon
void MainWindow::closeAllGraphe()
{
    mdi->closeAllSubWindows();
}

/// @brief select next graph
/// @author Plumey Simon
void MainWindow::next()
{
    mdi->activateNextSubWindow();
}

/// @brief select previous graph
/// @author Plumey Simon
void MainWindow::prev()
{
    mdi->activatePreviousSubWindow();
}
