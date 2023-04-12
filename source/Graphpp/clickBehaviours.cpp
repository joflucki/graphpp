#include "qboard.h"
#include "graph.h"

/***************************************************\
 * CLICK BEHAVIOURS                                *
\***************************************************/

void QBoard::clickCreateVertex(QMouseEvent *event)
{
    // TODO change vertex name
    this->graph->addVertex(new QVertex("A", QPointF(event->pos().x(), event->pos().y())));
}
void QBoard::clickSelector(QMouseEvent *event)
{
    this->unselectVertices();
    QVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        hittedVertex->setBackgroundColor(Qt::red); // Debug purpose
        this->vertexDockWidget->setSelectedVertex(hittedVertex);
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

    for (auto const& mapRow : graph->adjacencyList)
    {
        QVertex* vertex = mapRow.first;
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
        this->graph->addDoubleEdge(firstVertex, secondVertex);
        qDebug() << "Creating edge";
        this->unselectVertices();
    }
}

void QBoard::clickCycleGraph(QMouseEvent *event)
{

}
void QBoard::clickCompleteGraph(QMouseEvent *event)
{

}
void QBoard::clickBipartiteGraph(QMouseEvent *event)
{

}
