#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
private:
    QMenu *fileMenu, *editMenu, *optionMenu, *aboutMenu;
    QToolBar *toolsToolBar;
    QAction *newGraphAct, *openGraphAct, *saveGraphAct,
    *exitAct, *undoAct, *redoAct, *aboutAct, *selectToolAct,
    *newVertexAct, *linkVertexAct, *eraserAct, *moveToolAct,
    *cycleGrapheAct, *completeGrapheAct, *bipartiteGrapheAct,
    *closeCurrentGrapheAct, *closeAllGrapheAct, *nextAct, *prevAct;
    QMdiArea *mdi;
    QActionGroup *toolsActGroup;

public:
    MainWindow();

private slots:
    void newGraph();
    void openGraph();
    void saveGraph();
    void undo();
    void redo();
    void about();

    void updateSelectedTool(QAction* action);
    /*
    void selectTool();
    void newVertex();
    void linkVertex();
    void eraser();
    void moveTool();
    void cycleGraphe();
    void completeGraphe();
    void bipartiteGraphe();*/

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
