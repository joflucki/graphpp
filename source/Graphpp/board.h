#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QtWidgets>

enum Tool
{
    SELECTOR,
    CREATE_VERTEX,
    CREATE_EDGE,
    ERASER,
    HAND,
    CYCLE_GRAPH,
    COMPLETE_GRAPH,
    BIPARTITE_GRAPH
};

class Board : public QWidget
{
public:
    Board(QWidget *parent = nullptr);
    virtual ~Board();
    void setSelectedTool(Tool selectedTool);

private:
    QList<QPointF> listVertex;
    Tool selectedTool = Tool::SELECTOR;

protected:
    void paintEvent(QPaintEvent *);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // BOARD_H
