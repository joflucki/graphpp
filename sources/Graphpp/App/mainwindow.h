#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

// Forward declarations
class GraphDockWidget;
class VertexDockWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu *fileMenu, *editMenu, *optionMenu, *aboutMenu, *algorithmMenu;
    QToolBar *toolsToolBar;
    QAction *newGraphAct, *saveGraphAct, *importFromJsonAct,
    *exportToDotAct, *exportToPngAct, *exportToJsonAct,
    *exitAct, *undoAct, *redoAct, *aboutAct, *selectToolAct,
    *newVertexAct, *linkVertexAct, *eraserAct, *moveToolAct,
    *cycleGrapheAct, *completeGrapheAct, *bipartiteGrapheAct,
    *closeCurrentGrapheAct, *closeAllGrapheAct, *nextAct, *prevAct,
    *toggleGraphDockAct, *toggleVertexDockAct, *highlightMDGAct, *highlightMSTAct;
    QDockWidget *vertexDock, *graphDock;
    QMdiArea *mdi;
    QActionGroup *toolsActGroup;
    GraphDockWidget *graphDockWidget;
    VertexDockWidget *vertexDockWidget;

public:
    MainWindow();

private slots:
    void newGraph();
    void saveGraph();
    void exportToDot();
    void exportToPng();
    void exportToJson();
    void importFromJson();
    void undo();
    void redo();
    void about();
    void highlightMinimumDistanceGraph();
    void highlightMinimumSpanningTree();

    void updateGraphDockWidget();
    void updateSelectedTool(QAction* action);

    void closeCurrentGraphe();
    void closeAllGraphe();
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
