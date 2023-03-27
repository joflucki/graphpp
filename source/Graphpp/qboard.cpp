#include "qboard.h"
#include <QPainter>
#include <cstdlib>

QBoard::QBoard(QWidget *parent)
    : QWidget(parent)
{
}

QBoard::~QBoard()
{
}

void QBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);

    if (!listVertex.empty())
    {
        /*
        for (const auto edge : listEdge)
        {
            painter.setPen(QPen(edge->getBorderColor(), 2));
            painter.drawLine(edge->source->getPosition().toPoint(), edge->target->getPosition().toPoint());
        }*/
        for (const auto vertex : listVertex)
        {
            painter.setBrush(vertex->getBackgroundColor());
            painter.setPen(vertex->getBorderColor());
            painter.drawEllipse(vertex->getPosition().toPoint(),this->vertexRadius,this->vertexRadius);
        }
    }
}

void QBoard::setSelectedTool(Tool selectedTool)
{
    this->unselectVertices();
    this->selectedTool = selectedTool;
}

bool QBoard::hitVertex(QPointF position, QVertex*& hittedVertex)
{
    hittedVertex = nullptr;
    if (!listVertex.empty())
    {
        for (const auto vertex : listVertex)
        {
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
void QBoard::unselectVertices()
{
    for (const auto vertex : listVertex)
    {
        vertex->setSelected(false);
        vertex->setBackgroundColor(Qt::black); // Debug purpose
    }
    this->update();
}
void QBoard::clickCreateVertex(QMouseEvent *event)
{
    listVertex.append(new QVertex("A", QPointF(event->pos().x(), event->pos().y())));
    //this->update();
}
void QBoard::clickSelector(QMouseEvent *event)
{
    this->unselectVertices();
    QVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        hittedVertex->setBackgroundColor(Qt::red); // Debug purpose
        hittedVertex->setSelected(true);
    }
}
void QBoard::clickCreateEdge(QMouseEvent *event)
{
    QVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        hittedVertex->setSelected(true);
        hittedVertex->setBackgroundColor(Qt::green);
    }
    int selectedVertices = 0;
    QVertex* firstVertex = nullptr;
    QVertex* secondVertex = nullptr;

    for (const auto vertex : listVertex)
    {
        if (vertex->isSelected())
        {
            ++selectedVertices;
            if (firstVertex == nullptr)
            {
                firstVertex = vertex;
            }
            else if (secondVertex == nullptr)
            {
                secondVertex = vertex;
            }
        }
    }
    if (selectedVertices == 2)
    {
        /*
        // create edge
        DisplayableEdge* newEdge = new DisplayableEdge("ouai", firstVertex, secondVertex);
        newEdge->source = firstVertex;
        newEdge->target = secondVertex;
        listEdge.append(newEdge);
        qDebug() << "Creating edge";
        this->unselectVertices();*/
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
void QBoard::moveEraser(QMouseEvent *event)
{
    QVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        /*
        listVertex.remove
        for (const auto vertex : listVertex)
        {
            if (vertex == hittedVertex)
            {

            }
        }
        hittedVertex->setBackgroundColor(Qt::lightGray);
        hittedVertex->setBorderColor(Qt::lightGray);*/
    }
}
