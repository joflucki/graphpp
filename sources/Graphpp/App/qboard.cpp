#include "qboard.h"
#include <QPainter>
#include <cstdlib>

QBoard::QBoard(VertexDockWidget *vertexDockWidget, QWidget *parent)
    : QWidget(parent)
{
    this->graph = new Graph<QVertex>();
    this->vertexDockWidget = vertexDockWidget;
    connect(vertexDockWidget, &VertexDockWidget::vertexUpdated, this, qOverload<>(&QWidget::update));
}

QBoard::~QBoard()
{
}

void QBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setTransform(this->transform);

    // draw origin (debug purpose)
    {
        painter.setPen(Qt::gray);
        painter.drawLine(QPoint(0,10), QPoint(0,-10));
        painter.drawLine(QPoint(10,0), QPoint(-10,0));
    }

    painter.setBrush(Qt::black);
    painter.setPen(QPen(Qt::black, 2));

    //    QPoint cursorPos = this->mapFromGlobal(QCursor::pos());

    if (!graph->adjacencyList.empty())
    {
        // Display edges
        // NOT CONST
        for (auto & mapRow : graph->adjacencyList)
        {
            QPointF sourceVertexPos = mapRow.first->getPosition().toPoint();
            for (auto & edge : mapRow.second)
            {
                QVertex* targetVertex = edge->getTarget();
                QPointF targetVertexPos = targetVertex->getPosition().toPoint();
                painter.drawLine(sourceVertexPos, targetVertexPos);
            }
        }
        // Display vertices
        for (auto const& mapRow : graph->adjacencyList)
        {
            QVertex* vertex = mapRow.first;
            if (vertex->isSelected())
            {
                painter.setBrush(Qt::lightGray);
                painter.setPen(QPen(Qt::black, 2));
                painter.drawEllipse(vertex->getPosition().toPoint(),this->vertexRadius+5,this->vertexRadius+5); // bigger outlined for selected vertices
            }
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

bool QBoard::hitSegment(QPointF hitPoint, QPointF p1, QPointF p2, double margin)
{
    double xmin = std::min(p1.rx(), p2.rx()) - margin;
    double xmax = std::max(p1.rx(), p2.rx()) + margin;
    double ymin = std::min(p1.ry(), p2.ry()) - margin;
    double ymax = std::max(p1.ry(), p2.ry()) + margin;

    // Check if the point is inside the bounding box (performance)
    if (hitPoint.rx() < xmin || hitPoint.rx() > xmax ||
            hitPoint.ry() < ymin || hitPoint.ry() > ymax) {
        return false;
    }

    // Check if the point is on the line segment
    double dist = std::abs((p2.ry() - p1.ry())*hitPoint.rx() - (p2.rx() - p1.rx())*hitPoint.ry() + p2.rx()*p1.ry() - p2.ry()*p1.rx()) / std::sqrt(std::pow(p2.ry() - p1.ry(), 2) + std::pow(p2.rx() - p1.rx(), 2));
    if (dist <= margin) {
        return true;
    }

    return false;
}

void QBoard::unselectVertices()
{
    for (auto const& mapRow : graph->adjacencyList)
    {
        QVertex* vertex = mapRow.first;
        vertex->setSelected(false);
    }
    this->update();
}

void QBoard::zoom(qreal zoomFactor, const QPointF &fixedViewPos)
{
    QTransform zoomTransform;
    zoomTransform.translate(fixedViewPos.x(), fixedViewPos.y());
    zoomTransform.scale(zoomFactor, zoomFactor);
    zoomTransform.translate(-fixedViewPos.x(), -fixedViewPos.y());

    this->transform = zoomTransform * this->transform;
}

void QBoard::translate(const QPointF &delta)
{
    QTransform translateTransform;
    translateTransform.translate(delta.x(), delta.y());

    this->transform = this->transform * translateTransform;
    update();
}

QPointF QBoard::convertRelativToTransform(QPointF globalPosition)
{
    QPointF clickPos = mapFromGlobal(globalPosition); // convert it relativ to QBoard
    return transform.inverted().map(clickPos); // apply transformation with transform matrix
}

/***************************************************\
 * MOUSE EVENTS                                    *
\***************************************************/

void QBoard::mousePressEvent(QMouseEvent *event)
{
    QPointF clickPos = convertRelativToTransform(event->globalPosition());

    switch (this->selectedTool)
    {
    case CREATE_VERTEX: clickCreateVertex(clickPos);
        break;
    case SELECTOR: clickSelector(clickPos);
        break;
    case CREATE_EDGE: clickCreateEdge(clickPos);
        break;
    case ERASER: moveEraser(clickPos);
        break;
    case HAND:
        isDragging = true;
        lastMousePos = clickPos;
        setCursor(QCursor(Qt::ClosedHandCursor));
        break;

    case CYCLE_GRAPH: clickCycleGraph(clickPos);
        break;
    case COMPLETE_GRAPH: clickCompleteGraph(clickPos);
        break;
    case BIPARTITE_GRAPH: clickBipartiteGraph(clickPos);
        break;
    default: qDebug() << "click: Not implemented" << Qt::endl;
    }
}

void QBoard::mouseReleaseEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
    case HAND:
        setCursor(QCursor(Qt::OpenHandCursor));
        isDragging = false;
        break;
    default: break;
    }
    this->update();
}

void QBoard::mouseMoveEvent(QMouseEvent *event)
{
    QPointF clickPos = convertRelativToTransform(event->globalPosition());

    switch (this->selectedTool)
    {
    case ERASER: moveEraser(clickPos);
        break;
    case HAND:
        setCursor(QCursor(Qt::ClosedHandCursor));
        moveHand(clickPos);
        break;
    default: qDebug() << "move: Not implemented" << Qt::endl;
    }
    this->update();
}

void QBoard::wheelEvent(QWheelEvent *event)
{
    // calcule la position de la souris dans la vue
    QPoint mousePos = event->position().toPoint();

    // calcule le facteur de zoom en fonction de l'événement de la roulette
    qreal scaleFactor = 1;
    if (event->angleDelta().y() > 0)
    {
        scaleFactor = 1.1;
    }
    else
    {
        scaleFactor = 0.9;
    }

    // effectue le zoom en utilisant la position de la souris comme point fixe
    zoom(scaleFactor, event->globalPosition());

    // force le widget à se redessiner
    update();
}

