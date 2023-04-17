#include "qboard.h"
#include "graph.h"

/***************************************************\
 * CLICK BEHAVIOURS                                *
\***************************************************/

void QBoard::clickCreateVertex(QPointF clickPos)
{
    QString vertexName = "Vertex " + QString::number(this->graph->adjacencyList.size()+1); //start at 0
    this->graph->addVertex(new QVertex(vertexName, clickPos));
}
void QBoard::clickSelector(QPointF clickPos)
{
    this->unselectVertices();
    QVertex* hittedVertex = nullptr;
    if (hitVertex(clickPos, hittedVertex))
    {
        hittedVertex->setBackgroundColor(Qt::red); // Debug purpose
        hittedVertex->setSelected(true);
    }
    this->vertexDockWidget->setSelectedVertex(hittedVertex);
}
void QBoard::clickCreateEdge(QPointF clickPos)
{
    QVertex* hittedVertex = nullptr;
    if (hitVertex(clickPos, hittedVertex))
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

void QBoard::clickCycleGraph(QPointF clickPos)
{

}
void QBoard::clickCompleteGraph(QPointF clickPos)
{

}
void QBoard::clickBipartiteGraph(QPointF clickPos)
{

}
