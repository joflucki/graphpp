#include "board.h"
#include <QPainter>
#include <cstdlib>

Board::Board(QWidget *parent)
    : QWidget(parent)
{
}

Board::~Board()
{
}

void Board::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setBrush(Qt::black);
    painter.setPen(Qt::black);

    if (!listVertex.empty())
    {
        for (const auto edge : listEdge)
        {
            painter.setPen(QPen(edge->getBorderColor(), 2));
            painter.drawLine(edge->source->getPosition().toPoint(), edge->target->getPosition().toPoint());
        }
        for (const auto vertex : listVertex)
        {
            painter.setBrush(vertex->getBackgroundColor());
            painter.setPen(vertex->getBorderColor());
            painter.drawEllipse(vertex->getPosition().toPoint(),this->vertexRadius,this->vertexRadius);
        }
    }
}

void Board::setSelectedTool(Tool selectedTool)
{
    this->unselectVertices();
    this->selectedTool = selectedTool;
}
void Board::mousePressEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
        case CREATE_VERTEX: clickCreateVertex(event);
        break;
        case SELECTOR: clickSelector(event);
        break;
        case CREATE_EDGE: clickCreateEdge(event);
        break;
        default: qDebug() << "Not implemented" << Qt::endl;
    }
}
void Board::unselectVertices()
{
    for (const auto vertex : listVertex)
    {
        vertex->setSelected(false);
        vertex->setBackgroundColor(Qt::black); // Debug purpose
    }
    this->update();
}
void Board::clickCreateVertex(QMouseEvent *event)
{
    listVertex.append(new DisplayableVertex("A", QPointF(event->pos().x(), event->pos().y())));
    //this->update();
}
void Board::clickSelector(QMouseEvent *event)
{
    this->unselectVertices();
    DisplayableVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        hittedVertex->setBackgroundColor(Qt::red); // Debug purpose
        hittedVertex->setSelected(true);
    }
}
void Board::clickCreateEdge(QMouseEvent *event)
{
    DisplayableVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        hittedVertex->setSelected(true);
        hittedVertex->setBackgroundColor(Qt::green);
    }
    int selectedVertices = 0;
    DisplayableVertex* firstVertex = nullptr;
    DisplayableVertex* secondVertex = nullptr;

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
        // create edge
        DisplayableEdge* newEdge = new DisplayableEdge("ouai", firstVertex, secondVertex);
        newEdge->source = firstVertex;
        newEdge->target = secondVertex;
        listEdge.append(newEdge);
        qDebug() << "Creating edge";
        this->unselectVertices();
    }
}

void Board::mouseReleaseEvent(QMouseEvent *event)
{
    this->update();
}

void Board::mouseMoveEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
        case CREATE_VERTEX:
        listVertex.last()->getPosition().setX(event->pos().x());
        listVertex.last()->getPosition().setY(event->pos().y());
        this->update();
        break;
        default: qDebug() << "Not implemented" << Qt::endl;
    }

}
bool Board::hitVertex(QPointF position, DisplayableVertex*& hittedVertex)
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
