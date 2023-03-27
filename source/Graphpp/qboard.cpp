#include "qboard.h"
#include <QPainter>
#include <cstdlib>

QBoard::QBoard(QWidget *parent)
    : QWidget(parent)
{
    this->graph = new Graph<QVertex>();

}

QBoard::~QBoard()
{
}

void QBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(Qt::black);
    painter.setPen(QPen(Qt::black, 2));

    if (!graph->adjacencyList.empty())
    {
        // NOT CONST
        for (auto & mapRow : graph->adjacencyList)
        {
            QPointF sourceVertexPos = mapRow.first->getPosition().toPoint();
            for (auto & edge : mapRow.second)
            {
                QVertex* targetVertex = edge.getTarget();
                QPointF targetVertexPos = targetVertex->getPosition().toPoint();
                painter.drawLine(sourceVertexPos, targetVertexPos);
            }
        }
        for (auto const& mapRow : graph->adjacencyList)
        {
            QVertex* vertex = mapRow.first;
            painter.setBrush(vertex->getBackgroundColor());
            painter.setPen(vertex->getBorderColor());
            painter.drawEllipse(vertex->getPosition().toPoint(),this->vertexRadius,this->vertexRadius);
        }
    }
}

/***************************************************\
 * USEFUL METHODS                                  *
\***************************************************/

void QBoard::setSelectedTool(Tool selectedTool)
{
    this->unselectVertices();
    this->selectedTool = selectedTool;
}

bool QBoard::hitVertex(QPointF position, QVertex*& hittedVertex)
{
    hittedVertex = nullptr;
    if (!graph->adjacencyList.empty())
    {
        for (auto const& mapRow : graph->adjacencyList)
        {
            QVertex* vertex = mapRow.first;
            QPoint vertexPos = vertex->getPosition().toPoint();
            if (abs(vertexPos.x()-position.toPoint().x()) < this->vertexRadius + 10 // adding a bit of margin
                    && abs(vertexPos.y()-position.toPoint().y()) < this->vertexRadius + 10)
            {
                hittedVertex = vertex;
                return true;
            }
        }
    }
    return false;
}

void QBoard::unselectVertices()
{
    for (auto const& mapRow : graph->adjacencyList)
    {
        QVertex* vertex = mapRow.first;
        vertex->setSelected(false);
        vertex->setBackgroundColor(Qt::black); // Debug purpose
    }
    this->update();
}

/***************************************************\
 * MOUSE EVENTS                                    *
\***************************************************/

void QBoard::mousePressEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
        case CREATE_VERTEX: clickCreateVertex(event);
        break;
        case SELECTOR: clickSelector(event);
        break;
        case CREATE_EDGE: clickCreateEdge(event);
        break;
        default: qDebug() << "click: Not implemented" << Qt::endl;
    }
}

void QBoard::mouseReleaseEvent(QMouseEvent *event)
{
    this->update();
}

void QBoard::mouseMoveEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
        case ERASER: moveEraser(event);
        break;
        default: qDebug() << "move: Not implemented" << Qt::endl;
    }
    this->update();
}
