#include "board.h"
#include <QPainter>

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
        for (int i = 0; i < listVertex.size(); ++i)
        {
            painter.drawEllipse(listVertex[i].toPoint(),5,5);
        }
    }
}

void Board::setSelectedTool(Tool selectedTool)
{
    this->selectedTool = selectedTool;
}
void Board::mousePressEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
        case CREATE_VERTEX:
        listVertex.append(QPointF(event->pos().x(), event->pos().y()));
        this->update();
        break;
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
        listVertex.last().setX(event->pos().x());
        listVertex.last().setY(event->pos().y());
        this->update();
        break;
    }

}
