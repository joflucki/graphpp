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
    bool ok;
    int nbVertices = QInputDialog::getInt(this, tr("Graphe cyclique"), tr("Choisissez le nombre de sommet (3-360):"),3, 3,360,1,&ok);

    if (ok)
    {
        QVertex* arrayVertices[nbVertices];
        double angle = 360./nbVertices;
        double radius = 200;
        QPointF center = clickPos;

        for (int i=0; i < nbVertices; ++i)
        {
            double realAngle = angle*i * M_PI / 180; // convert to radian
            QPointF vertexPos = QPointF(center.x() + (cos(realAngle) * radius), center.y() + (sin(realAngle) * radius));
            QString vertexName = "Vertex cycle " + QString::number(this->graph->adjacencyList.size()+1); //start at 0
            arrayVertices[i] = new QVertex(vertexName, vertexPos);
            this->graph->addVertex(arrayVertices[i]);
        }
        for (int i=0; i < nbVertices-1; ++i)
        {
            this->graph->addDoubleEdge(arrayVertices[i], arrayVertices[i+1]);
        }
        // add last connexion between the last and the first
        this->graph->addDoubleEdge(arrayVertices[nbVertices-1], arrayVertices[0]);

    }
}
void QBoard::clickCompleteGraph(QPointF clickPos)
{
    bool ok;
    int nbVertices = QInputDialog::getInt(this, tr("Graphe complet"), tr("Choisissez le nombre de sommet (3-360):"),3, 3,360,1,&ok);

    if (ok)
    {
    }

}
void QBoard::clickBipartiteGraph(QPointF clickPos)
{

}
