#include "qboard.h"

/***************************************************\
 * MOVE BEHAVIOURS                                 *
\***************************************************/

void QBoard::moveEraser(QPointF clickPos)
{
    QVertex* hittedVertex = nullptr;
    QPointF hittedPoint = clickPos;
    // check if hit vertex
    if (hitVertex(hittedPoint, hittedVertex))
    {
        graph->removeVertex(hittedVertex);
    }

    // check if hit edge
    if (!graph->adjacencyList.empty())
    {
        std::list<Edge<QVertex>*> edgesToRemove;
        // add edges to the list
        for (auto & mapRow : graph->adjacencyList)
        {
            QPointF sourcePoint = mapRow.first->getPosition().toPoint();
            for (auto * edge : mapRow.second)
            {
                QPointF targetPoint = edge->getTarget()->getPosition().toPoint();
                if (hitSegment(hittedPoint, sourcePoint, targetPoint, 10))
                {
                    edgesToRemove.push_back(edge);
                }
            }
        }
        // remove edges
        for (auto * edge : edgesToRemove)
        {
            graph->removeEdge(edge);
        }
    }
}

void QBoard::moveHand(QPointF clickPos)
{
    if (isDragging) {
        QPointF delta = clickPos - lastMousePos;
        translate(delta);
        lastMousePos = clickPos;
    }
}
