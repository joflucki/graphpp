#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Forward declarations
class GraphDockWidget;
class VertexDockWidget;

/// @brief MainWindow of the application. It contains a MDI, menu, tools,...
/// @author Plumey Simon & Jonas Flückiger
/// @date spring 2023
class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu *fileMenu, *editMenu, *optionMenu, *aboutMenu, *algorithmMenu;
    QToolBar *toolsToolBar;
    QAction *newGraphAct, *saveGraphAct, *openGraphAct,
    *exportToDotAct, *exportToPngAct,
    *exitAct, *undoAct, *redoAct, *aboutAct, *selectToolAct,
    *newVertexAct, *linkVertexAct, *eraserAct, *moveToolAct,
    *cycleGrapheAct, *completeGrapheAct, *bipartiteGrapheAct,
    *closeCurrentGrapheAct, *closeAllGrapheAct, *nextAct, *prevAct,
    *toggleGraphDockAct, *toggleVertexDockAct, *highlightMDGAct, *highlightMSTAct, *highlightHamPathAct;
    QDockWidget *vertexDock, *graphDock;
    QMdiArea *mdi;
    QActionGroup *toolsActGroup;
    GraphDockWidget *graphDockWidget;
    VertexDockWidget *vertexDockWidget;
    int graphCounter = 0;
public:
    MainWindow();

private slots:
    void newGraph();
    void saveGraph();
    void openGraph();
    void exportToDot();
    void exportToPng();
    void undo();
    void redo();
    void about();
    void highlightMinimumDistanceGraph();
    void highlightMinimumSpanningTree();
    void highlightHamiltonianPath();

    void initialiseGraphSettings();
    void updateSelectedTool(QAction* action);

    void closeCurrentGraphe();
    void closeAllGraphe();
    virtual void closeEvent(QCloseEvent* event) override;
    void next();
    void prev();

private:
    void createActions();
    void createMenus();
    void createToolBars();
    void createDockWindows();
    QListWidget *customerList;
    QListWidget *paragraphsList;

    QMenu *viewMenu;
};
#endif // MAINWINDOW_H
