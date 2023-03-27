#include "qboard.h"

/***************************************************\
 * MOVE BEHAVIOURS                                 *
\***************************************************/

void QBoard::moveEraser(QMouseEvent *event)
{
    QVertex* hittedVertex = nullptr;
    if (hitVertex(QPointF(event->pos().x(), event->pos().y()), hittedVertex))
    {
        graph->removeVertex(hittedVertex);
    }
}
