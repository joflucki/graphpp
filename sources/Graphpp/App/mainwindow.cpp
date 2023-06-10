#include <QtWidgets>
#include "mainwindow.h"
#include "qboard.h"
#include "qcaretaker.h"
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

    saveGraphAct = new QAction(tr("&Enregistrer"), this);
    saveGraphAct->setShortcut(QKeySequence(QKeySequence::Save));
    saveGraphAct->setStatusTip(tr("Enregistrer le document courant"));
    connect(saveGraphAct, &QAction::triggered, this, &MainWindow::saveGraph);

    exportToDotAct = new QAction(tr("Export en &DOT"), this);
    exportToDotAct->setStatusTip(tr("Exporter le graph en .dot"));
    connect(exportToDotAct, &QAction::triggered, this, &MainWindow::exportToDot);

    exportToPngAct = new QAction(tr("Export en &PNG"), this);
    exportToPngAct->setStatusTip(tr("Exporter le graph en une image PNG"));
    connect(exportToPngAct, &QAction::triggered, this, &MainWindow::exportToPng);

    openGraphAct = new QAction(tr("&Ouvrir"), this);
    openGraphAct->setShortcut(QKeySequence(QKeySequence::Open));
    openGraphAct->setStatusTip(tr("Ouvir un fichier contant un graph créé à l'aide de graph++"));
    connect(openGraphAct, &QAction::triggered, this, &MainWindow::openGraph);

    exitAct = new QAction(tr("&Quitter"), this);
    exitAct->setShortcut(QKeySequence(QKeySequence::Quit));
    exitAct->setStatusTip(tr("Quitter l'application"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::close);

    undoAct = new QAction(QIcon(":/img/undo.png"), tr("&Annuler"), this);
    undoAct->setShortcut(QKeySequence(QKeySequence::Undo));
    undoAct->setStatusTip(tr("Annuler la dernière action"));
    undoAct->setEnabled(false);
    connect(undoAct, &QAction::triggered, this, &MainWindow::undo);

    redoAct = new QAction(QIcon(":/img/redo.png"), tr("&Rétablir"), this);
    redoAct->setShortcut(QKeySequence(QKeySequence::Redo));
    redoAct->setStatusTip(tr("Rétablir la dernière modification"));
    redoAct->setEnabled(false);
    connect(redoAct, &QAction::triggered, this, &MainWindow::redo);

    aboutAct = new QAction(tr("A &Propos..."), this);
    aboutAct->setStatusTip(tr("Affiche des informations sur le programme"));
    connect(aboutAct, &QAction::triggered, this, &MainWindow::about);

    highlightMDGAct = new QAction(tr("Afficher le graphe des chemins les plus courts"), this);
    highlightMDGAct->setStatusTip(tr("Indique l'un des graphes des chemins les plus courts"));
    connect(highlightMDGAct, &QAction::triggered, this, &MainWindow::highlightMinimumDistanceGraph);

    highlightMSTAct = new QAction(tr("Afficher l'arbre recouvrant minimal"), this);
    highlightMSTAct->setStatusTip(tr("Indique l'un des arbres recouvrants minimaux"));
    connect(highlightMSTAct, &QAction::triggered, this, &MainWindow::highlightMinimumSpanningTree);

    highlightHamPathAct = new QAction(tr("Afficher un chemin hamiltonien"), this);
    highlightHamPathAct->setStatusTip(tr("Indique l'un des chemins hamiltoniens possibles"));
    connect(highlightHamPathAct, &QAction::triggered, this, &MainWindow::highlightHamiltonianPath);

    // TOOLS actions
    selectToolAct = new QAction(QIcon(":/img/selector.png"), tr("&Outil de sélection"), this);
    selectToolAct->setShortcut(tr("Ctrl+1"));
    selectToolAct->setCheckable(true);
    selectToolAct->setChecked(true);
    selectToolAct->setStatusTip(tr("Outil de sélection/édition"));

    newVertexAct = new QAction(QIcon(":/img/vertex.png"), tr("&Nouveau sommet"), this);
    newVertexAct->setShortcut(tr("Ctrl+2"));
    newVertexAct->setCheckable(true);
    newVertexAct->setStatusTip(tr("Créer un sommet"));

    linkVertexAct = new QAction(QIcon(":/img/link.png"), tr("&Lier deux sommets"), this);
    linkVertexAct->setShortcut(tr("Ctrl+3"));
    linkVertexAct->setCheckable(true);
    linkVertexAct->setStatusTip(tr("Lier deux sommets entres-eux"));

    eraserAct = new QAction(QIcon(":/img/eraser.png"), tr("&Gomme"), this);
    eraserAct->setShortcut(tr("Ctrl+4"));
    eraserAct->setCheckable(true);
    eraserAct->setStatusTip(tr("Outil de gomme"));

    moveToolAct = new QAction(QIcon(":/img/hand.png"), tr("&Main"), this);
    moveToolAct->setShortcut(tr("Ctrl+5"));
    moveToolAct->setCheckable(true);
    moveToolAct->setStatusTip(tr("Outil de main"));

    cycleGrapheAct = new QAction(QIcon(":/img/cycle.png"), tr("&Graphe cyclique"), this);
    cycleGrapheAct->setShortcut(tr("Ctrl+6"));
    cycleGrapheAct->setCheckable(true);
    cycleGrapheAct->setStatusTip(tr("Outil de création de graphe cyclique"));

    completeGrapheAct = new QAction(QIcon(":/img/complete.png"), tr("&Graphe complet"), this);
    completeGrapheAct->setShortcut(tr("Ctrl+7"));
    completeGrapheAct->setCheckable(true);
    completeGrapheAct->setStatusTip(tr("Outil de création de graphe complet"));

    bipartiteGrapheAct = new QAction(QIcon(":/img/bipartite.png"), tr("&Graphe bi parties"), this);
    bipartiteGrapheAct->setShortcut(tr("Ctrl+8"));
    bipartiteGrapheAct->setCheckable(true);
    bipartiteGrapheAct->setStatusTip(tr("Outil de création de graphe bi parties"));

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

    closeCurrentGrapheAct = new QAction(tr("Fermer &le graphe actif"), this);
    closeCurrentGrapheAct->setShortcut(QKeySequence(QKeySequence::Close));
    closeCurrentGrapheAct->setStatusTip(tr("Ferme le graphe qui est actuellement ouvert et visible"));
    connect(closeCurrentGrapheAct, &QAction::triggered, this, &MainWindow::closeCurrentGraphe);

    closeAllGrapheAct = new QAction(tr("Fermer &tous les graphes"), this);
    closeAllGrapheAct->setStatusTip(tr("Ferme tous les graphes qui sont actuellement ouverts SANS les enregistrer"));
    connect(closeAllGrapheAct, &QAction::triggered, this, &MainWindow::closeAllGraphe);

    nextAct = new QAction(tr("&Graphe suivant"), this);
    nextAct->setShortcut(QKeySequence(QKeySequence::NextChild));
    connect(nextAct, &QAction::triggered, this, &MainWindow::next);

    prevAct = new QAction(tr("&Graphe précédent"), this);
    prevAct->setShortcut(QKeySequence(QKeySequence::PreviousChild));
    connect(prevAct, &QAction::triggered, this, &MainWindow::prev);

    toggleGraphDockAct = graphDock->toggleViewAction();
    toggleGraphDockAct->setText(tr("&Afficher les propriétés du graphe"));

    toggleVertexDockAct = vertexDock->toggleViewAction();
    toggleVertexDockAct->setText(tr("&Afficher les propriétés du sommet"));

    // update graph settings when changing tabs
    connect(mdi, &QMdiArea::subWindowActivated, this, &MainWindow::initialiseGraphSettings);
}

/// @brief Create all application's menus
/// @author Plumey Simon
void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&Fichier"));
    fileMenu->addAction(newGraphAct);
    fileMenu->addAction(saveGraphAct);
    fileMenu->addAction(openGraphAct);
    fileMenu->addSeparator();

    QMenu* subMenuExport = fileMenu->addMenu(tr("Exporter"));
    subMenuExport->addAction(exportToDotAct);
    subMenuExport->addAction(exportToPngAct);

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

    algorithmMenu = menuBar()->addMenu(tr("Algorithmes"));
    algorithmMenu->addAction(highlightMDGAct);
    algorithmMenu->addAction(highlightMSTAct);
    algorithmMenu->addAction(highlightHamPathAct);
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
    ++graphCounter;
    qBoard->setWindowTitle(tr("Nouveau graphe ") + QString::number(graphCounter));
    qBoard->show();
    initialiseGraphSettings();
}

/// @brief Save a graph
/// @author Flückiger Jonas
void MainWindow::saveGraph()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());

        QString path = QFileDialog::getSaveFileName(this, tr("Sauvegarder"), "", tr("Fichier Graph++ (*.gpp)"));
        QFileInfo fileInfo(path);

        qBoard->saveToFile(fileInfo.absoluteFilePath());
        qBoard->setWindowTitle(fileInfo.fileName());
    }
}

/// @brief Open a graph
/// @author Flückiger Jonas
void MainWindow::openGraph()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Ouvrir"), "", tr("Fichier Graph++ (*.gpp)"));
    if(path != nullptr){
        QFileInfo fileInfo(path);
        QBoard *qBoard= new QBoard(vertexDockWidget);
        mdi->addSubWindow(qBoard);
        qBoard->setWindowTitle(fileInfo.fileName());
        qBoard->openFile(fileInfo.absoluteFilePath());
        qBoard->show();

        ++graphCounter;
        initialiseGraphSettings();
    }
}

/// @brief Export to dot
/// @author Flückiger Jonas
void MainWindow::exportToDot()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());

        QString path = QFileDialog::getSaveFileName(this, tr("Sauvegarder en tant que fichier DOT"), "", tr("Fichier DOT (*.dot)"));
        qBoard->exportToDOT(path);
    }
}

/// @brief Export to Png
/// @author Plumey Simon
void MainWindow::exportToPng()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());

        QString path = QFileDialog::getSaveFileName(this, tr("Sauvegarder en tant qu'image"), "", tr("Fichier PNG (*.png)"));
        qBoard->exportToPng(path);
    }
}

/// @brief Undo
/// @author Plumey Simon
void MainWindow::undo()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        qBoard->getQCaretaker()->undo();
        redoAct->setEnabled(true);
        if (!qBoard->getQCaretaker()->canUndo())
        {
            qDebug() << "gris undo" << Qt::endl;
            undoAct->setEnabled(false);
        }
    }
}

/// @brief Redo
/// @author Plumey Simon
void MainWindow::redo()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        qBoard->getQCaretaker()->redo();
        undoAct->setEnabled(true);
        if (!qBoard->getQCaretaker()->canRedo())
        {
            qDebug() << "gris redo" << Qt::endl;
            redoAct->setEnabled(false);
        }
    }
}

/// @brief About message box
/// @author Plumey Simon
void MainWindow::about()
{
    QMessageBox::about(this, tr("A Propos"),
                       tr("Graph++, Banger international"));
}

/// @brief Computes the minimum distance tree and highlights it.
/// @author Flückiger Jonas
void MainWindow::highlightMinimumDistanceGraph()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        qBoard->highlightMinimumDistanceGraph();
    }
}

/// @brief Computes the minimum spanning tree and highlights it.
/// @author Flückiger Jonas
void MainWindow::highlightMinimumSpanningTree()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        qBoard->highlightMinimumSpanningTree();
    }
}

/// @brief Computes a hamiltonian path and highlights it.
/// @author Tschan Damien
void MainWindow::highlightHamiltonianPath()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        qBoard->highlightHamiltonianPath();
    }
}

/// @brief Used to change settings depending of the current active sub window and
/// changing graph settings like selected tool, current graph dock widget,
/// vertex dock widget,...
/// This function is call when changing tab, new graph, open graph...
/// @author Plumey Simon
void MainWindow::initialiseGraphSettings()
{
    QMdiSubWindow* qMDISubWindow = this->mdi->activeSubWindow();
    if (qMDISubWindow != nullptr)
    {
        // change graph and vertex docks widget
        QBoard* qBoard = (QBoard*)(qMDISubWindow->widget());
        graphDockWidget->setSelectedGraph(qBoard->graph);
        vertexDockWidget->setSelectedGraph(qBoard->graph);

        // for undo-redo buttons
        connect(qBoard->getQCaretaker(), &QCaretaker::backupAction, this, [=]
        {
            undoAct->setEnabled(true);
        });

        if (qBoard->getQCaretaker()->canRedo())
        {
            redoAct->setEnabled(true);
        }
        else
        {
            redoAct->setEnabled(false);
        }

        if (qBoard->getQCaretaker()->canUndo())
        {
            undoAct->setEnabled(true);
        }
        else
        {
            undoAct->setEnabled(false);
        }
        // set right tool
        updateSelectedTool(toolsActGroup->checkedAction());
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
    initialiseGraphSettings();
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
    initialiseGraphSettings();
}

/// @brief select previous graph
/// @author Plumey Simon
void MainWindow::prev()
{
    mdi->activatePreviousSubWindow();
    initialiseGraphSettings();
}
