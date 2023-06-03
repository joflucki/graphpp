#include "qboard.h"
#include <QPainter>
#include <cstdlib>
#include "qcaretaker.h"
#include <cmath>

/// @brief Constructor of the QBoard
/// @param QWidget: parent
/// @author Plumey Simon
QBoard::QBoard(VertexDockWidget *vertexDockWidget, QWidget *parent)
    : QWidget(parent)
{
    this->graph = new Graph<QVertex>();
    this->highlightedGraph = new Graph<QVertex>();
    this->vertexDockWidget = vertexDockWidget;
    connect(vertexDockWidget, &VertexDockWidget::vertexUpdated, this, qOverload<>(&QWidget::update));

    qCaretaker = new QCaretaker(this);
    qCaretaker->backup();
}

/// @brief Destructor of the QBoard
/// @author Plumey Simon
QBoard::~QBoard()
{
}

/// @brief Paint event method. Called on every graph update.
/// This method is not supposed to be called. Use this->update() to refresh scene
/// @param QPaintEvent*
/// @author Plumey Simon
void QBoard::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setRenderHint(QPainter::Antialiasing);

    // draw origin (debug purpose)
    {
        painter.setPen(Qt::gray);
        painter.drawLine(QPoint(0, 10), QPoint(0, -10));
        painter.drawLine(QPoint(10, 0), QPoint(-10, 0));
    }

    paint(painter);

    painter.end();
}

/// @brief Paint method. Use to paint on screen or in image
/// @param QPainter
/// @author Plumey Simon & Flückiger Jonas
void QBoard::paint(QPainter &painter)
{
    painter.setTransform(this->transform);

    painter.setBrush(Qt::black);

    if (!graph->adjacencyList.empty())
    {
        // Display edges
        // NOT CONST
        for (auto &mapRow : graph->adjacencyList)
        {
            QPointF sourceVertexPos = mapRow.first->getPosition().toPoint();
            for (auto &edge : mapRow.second)
            {
                painter.setPen(QPen(Qt::black, log(edge->getWeight()) + 1, Qt::SolidLine, Qt::RoundCap));
                QVertex *targetVertex = edge->getTarget();
                QPointF targetVertexPos = targetVertex->getPosition().toPoint();
                painter.drawLine(sourceVertexPos, targetVertexPos);
            }
        }

        // Redraw highlighted edges if needed
        if (this->highlightedGraph != nullptr)
        {
            painter.setBrush(Qt::red);
            for (auto &mapRow : this->highlightedGraph->adjacencyList)
            {
                QPointF sourceVertexPos = mapRow.first->getPosition().toPoint();
                for (auto &edge : mapRow.second)
                {
                    painter.setPen(QPen(Qt::red, log(edge->getWeight()) + 1, Qt::SolidLine, Qt::RoundCap));
                    QVertex *targetVertex = edge->getTarget();
                    QPointF targetVertexPos = targetVertex->getPosition().toPoint();
                    painter.drawLine(sourceVertexPos, targetVertexPos);
                }
            }
        }

        // Display vertices
        for (auto const &mapRow : graph->adjacencyList)
        {
            QVertex *vertex = mapRow.first;
            if (vertex->isSelected())
            {
                painter.setBrush(Qt::lightGray);
                painter.setPen(QPen(Qt::black, 2));
                painter.drawEllipse(vertex->getPosition().toPoint(), this->vertexRadius + 5, this->vertexRadius + 5); // bigger outlined for selected vertices
            }
            painter.setBrush(vertex->getBackgroundColor());
            painter.setPen(vertex->getBorderColor());
            painter.drawEllipse(vertex->getPosition().toPoint(), this->vertexRadius, this->vertexRadius);
        }
    }
}

/***************************************************\
 * USEFUL METHODS                                  *
\***************************************************/
/// @brief Exports the graph of the board in a DOT text file.
/// @author Flückiger Jonas
void QBoard::exportToDOT(QString path)
{
    if (path.isEmpty())
        return;

    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        QTextStream stream(&file);
        stream << QString::fromStdString(this->graph->exportToDOT());
    }
    file.close();
}

/// @brief Function to save current QBoard state and return a new QMemento
/// @author Plumey Simon
QMemento QBoard::save()
{
    return QMemento(this->graph->adjacencyList);
}

/// @brief Function to restore QBoard state from a QMemento
/// @param QMemento used to restore state of QBoard
/// @author Plumey Simon
void QBoard::restore(QMemento memento)
{
    this->graph->adjacencyList = memento.getAdjencyList();
}

/// @brief Return the caretaker
/// @author Plumey Simon
QCaretaker *QBoard::getQCaretaker()
{
    return this->qCaretaker;
}

/// @brief Able to convert QPainter to a PNG image
/// @author Plumey Simon
void QBoard::exportToPng(QString path)
{
    if (path.isEmpty())
        return;

    QImage img(this->size().width(), this->size().height(), QImage::Format_ARGB32);

    QPainter painter;
    painter.begin(&img);
    painter.setRenderHint(QPainter::Antialiasing);
    paint(painter);
    painter.end();

    img.save(path);
}

/// @brief Set the selected Tool
/// @param Tool: Selected
/// @author Plumey Simon
void QBoard::setSelectedTool(Tool selectedTool)
{
    this->unselectVertices();
    this->selectedTool = selectedTool;
}

/// @brief Save current graph to a file.
/// @param path: the path to the file
/// @author Flückiger Jonas
void QBoard::saveToFile(QString path)
{
    if (path.isEmpty())
        return;

    QFile file(path);
    if (file.open(QIODevice::ReadWrite))
    {
        QJsonObject json;
        for (auto pair : this->graph->adjacencyList)
        {
            // Get the vertex address as a string
            std::ostringstream address;
            address << (void const *)pair.first;
            std::string id = address.str();

            QJsonObject vertexJson;
            vertexJson["name"] = pair.first->getName();
            vertexJson["positionX"] = pair.first->getPosition().x();
            vertexJson["positionY"] = pair.first->getPosition().y();
            vertexJson["textColor"] = pair.first->getTextColor().name();
            vertexJson["backgroundColor"] = pair.first->getBackgroundColor().name();
            vertexJson["borderColor"] = pair.first->getBorderColor().name();
            QJsonArray edgesJson = QJsonArray();
            for (auto edge : pair.second)
            {
                // Get the target address as a string
                std::ostringstream address;
                address << (void const *)edge->getTarget();
                std::string id = address.str();

                QJsonObject edgeJson = QJsonObject();
                edgeJson["target"] = QString::fromStdString(id);
                edgeJson["weight"] = edge->getWeight();
                edgesJson.append(edgeJson);
            }
            vertexJson["edges"] = edgesJson;
            json[QString::fromStdString(id)] = vertexJson;
        }
        QTextStream stream(&file);
        stream << QJsonDocument(json).toJson();
    }
    file.close();
}
/// @brief Imports the graph contained in the file.
/// @param path: the path to the file
/// @author Flückiger Jonas
void QBoard::openFile(QString path)
{
    if (path.isEmpty())
        return;

    QFile file(path);
    if (file.open(QIODevice::ReadOnly))
    {
        // Read file
        QString data = file.readAll();
        file.close();

        // Parse JSON data
        QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8());

        std::unordered_map<QString, QVertex *> vertices;
        if (!doc.isNull())
        {
            this->graph = new Graph<QVertex>();
            QJsonObject obj = doc.object();

            QJsonObject::const_iterator it = obj.constBegin();
            QJsonObject::const_iterator end = obj.constEnd();

            // Add all vertices first
            do
            {
                if (it.value().isObject())
                {
                    qDebug() << "isobject";
                    QString id = QString::fromStdString(it.key().toStdString());
                    QJsonObject vertexJson = it.value().toObject();
                    QString name = vertexJson["name"].toString("");
                    QPointF position = QPointF(vertexJson["positionX"].toDouble(0), vertexJson["positionY"].toDouble(0));
                    QColor textColor = QColor(vertexJson["textColor"].toString("#000000"));
                    QColor backgroundColor = QColor(vertexJson["backgroundColor"].toString("#000000"));
                    QColor borderColor = QColor(vertexJson["borderColor"].toString("#000000"));
                    QVertex *vertex = new QVertex(name, position, textColor, backgroundColor, borderColor);
                    vertices.insert(std::make_pair(id, vertex));
                    this->graph->addVertex(vertex);
                }
                it++;
            } while (it != end);

            // Add all edges next
            it = obj.constBegin();
            do
            {
                if (it.value().isObject())
                {
                    QString id = QString::fromStdString(it.key().toStdString());
                    QJsonObject vertexJson = it.value().toObject();
                    QJsonArray edgesJson = vertexJson["edges"].toArray();
                    for (auto edgeRef : edgesJson)
                    {
                        if (edgeRef.isObject())
                        {
                            QJsonObject edgeJson = edgeRef.toObject();
                            QVertex *source = vertices[id];
                            QVertex *target = vertices[edgeJson["target"].toString()];
                            int weight = edgeJson["weight"].toInt(1);
                            this->graph->addEdge(source, target, weight);
                        }
                    }
                }
                it++;
            } while (it != end);
        }
    }
}

/// @brief Test if a vertex is hit or not
/// @param QPointF: position of click
/// @param QVertex*&: nullptr by default, if vertex hit, set the the vertex hitted
/// @return bool: if a vertex is hitted or not
/// @author Plumey Simon
bool QBoard::hitVertex(QPointF position, QVertex *&hittedVertex)
{
    hittedVertex = nullptr;
    if (!graph->adjacencyList.empty())
    {
        for (auto const &mapRow : graph->adjacencyList)
        {
            QVertex *vertex = mapRow.first;
            QPoint vertexPos = vertex->getPosition().toPoint();
            if (abs(vertexPos.x() - position.toPoint().x()) < this->vertexRadius + 10 // adding a bit of margin
                && abs(vertexPos.y() - position.toPoint().y()) < this->vertexRadius + 10)
            {
                hittedVertex = vertex;
                return true;
            }
        }
    }
    return false;
}

/// @brief Test if a segment is hit or not
/// @param QPointF: position of click
/// @param QPointF: first coordinate of the segment
/// @param QPointF: second coordinate of the segment
/// @param double: error margin
/// @return bool: if a segment is hitted or not
/// @author Plumey Simon
bool QBoard::hitSegment(QPointF hitPoint, QPointF p1, QPointF p2, double margin)
{
    double xmin = std::min(p1.rx(), p2.rx()) - margin;
    double xmax = std::max(p1.rx(), p2.rx()) + margin;
    double ymin = std::min(p1.ry(), p2.ry()) - margin;
    double ymax = std::max(p1.ry(), p2.ry()) + margin;

    // Check if the point is inside the bounding box (performance)
    if (hitPoint.rx() < xmin || hitPoint.rx() > xmax ||
        hitPoint.ry() < ymin || hitPoint.ry() > ymax)
    {
        return false;
    }

    // Check if the point is on the line segment
    double dist = std::abs((p2.ry() - p1.ry()) * hitPoint.rx() - (p2.rx() - p1.rx()) * hitPoint.ry() + p2.rx() * p1.ry() - p2.ry() * p1.rx()) / std::sqrt(std::pow(p2.ry() - p1.ry(), 2) + std::pow(p2.rx() - p1.rx(), 2));
    if (dist <= margin)
    {
        return true;
    }

    return false;
}

/// @brief Unselected all vertices
/// @author Plumey Simon
void QBoard::unselectVertices()
{
    for (auto const &mapRow : graph->adjacencyList)
    {
        QVertex *vertex = mapRow.first;
        vertex->setSelected(false);
    }
    this->update();
}

/// @brief Zoom
/// @param qreal: zoom factor
/// @param const QPointF& fixed view position
/// @author Plumey Simon
void QBoard::zoom(qreal zoomFactor, const QPointF &fixedViewPos)
{
    QTransform zoomTransform;
    zoomTransform.translate(fixedViewPos.x(), fixedViewPos.y());
    zoomTransform.scale(zoomFactor, zoomFactor);
    zoomTransform.translate(-fixedViewPos.x(), -fixedViewPos.y());

    this->transform = zoomTransform * this->transform;
}

/// @brief Translation method
/// @param const QPointF &: delta between current position and the next
/// @author Plumey Simon
void QBoard::translate(const QPointF &delta)
{
    QTransform translateTransform;
    translateTransform.translate(delta.x(), delta.y());

    this->transform = this->transform * translateTransform;
    update();
}

/// @brief Convert relativ to Transform
/// @param QPointF: global position
/// @author Plumey Simon
QPointF QBoard::convertRelativToTransform(QPointF globalPosition)
{
    QPointF clickPos = mapFromGlobal(globalPosition); // convert it relativ to QBoard
    return transform.inverted().map(clickPos);        // apply transformation with transform matrix
}

/***************************************************\
 * MOUSE EVENTS                                    *
\***************************************************/

/// @brief Method to handle the right behaviour on click depending on which tool is selected
/// @param QMouseEvent: Mouse event
/// @author Plumey Simon
void QBoard::mousePressEvent(QMouseEvent *event)
{
    QPointF clickPos = convertRelativToTransform(event->globalPosition());

    switch (this->selectedTool)
    {
    case CREATE_VERTEX:
        clickCreateVertex(clickPos);
        break;
    case SELECTOR:
        clickSelector(clickPos);
        break;
    case CREATE_EDGE:
        clickCreateEdge(clickPos);
        break;
    case ERASER:
        moveEraser(clickPos);
        break;
    case HAND:
        isDragging = true;
        lastMousePos = clickPos;
        setCursor(QCursor(Qt::ClosedHandCursor));
        break;

    case CYCLE_GRAPH:
        clickCycleGraph(clickPos);
        break;
    case COMPLETE_GRAPH:
        clickCompleteGraph(clickPos);
        break;
    case BIPARTITE_GRAPH:
        clickBipartiteGraph(clickPos);
        break;
    default:
        qDebug() << "click: Not implemented" << Qt::endl;
    }
}

/// @brief Method to handle the right behaviour on release click depending on which tool is selected
/// @param QMouseEvent: Mouse event
/// @author Plumey Simon
void QBoard::mouseReleaseEvent(QMouseEvent *event)
{
    switch (this->selectedTool)
    {
    case HAND:
        setCursor(QCursor(Qt::OpenHandCursor));
        isDragging = false;
        break;
    default:
        break;
    }
    this->update();
}

/// @brief Method to handle the right behaviour on mouse moving depending on which tool is selected
/// @param QMouseEvent: Mouse event
/// @author Plumey Simon
void QBoard::mouseMoveEvent(QMouseEvent *event)
{
    QPointF clickPos = convertRelativToTransform(event->globalPosition());

    switch (this->selectedTool)
    {
    case ERASER:
        moveEraser(clickPos);
        break;
    case HAND:
        setCursor(QCursor(Qt::ClosedHandCursor));
        moveHand(clickPos);
        break;
    default:
        qDebug() << "move: Not implemented" << Qt::endl;
    }
    this->update();
}

/// @brief Zoom when mouse wheel is used
/// @param QWheelEvent: Mouse event
/// @author Plumey Simon
void QBoard::wheelEvent(QWheelEvent *event)
{
    for (auto const &mapRow : graph->adjacencyList)
    {
        if (mapRow.first->isSelected())
        {
            highlightedGraph = graph->getMinimumDistanceGraph(mapRow.first);
        }
    }

    // ATTENTION
    // Pas totalement fonctionnel, désactivé pour l'instant
    /*
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
    */
}

/// @brief Highlights the current graph's minimum distance graph.
/// @author Flückiger Jonas
void QBoard::highlightMinimumDistanceGraph()
{
    for (auto const &mapRow : graph->adjacencyList)
    {
        if (mapRow.first->isSelected())
        {
            this->highlightedGraph = graph->getMinimumDistanceGraph(mapRow.first);
            this->update();
            return;
        }
    }
    QMessageBox msgBox;
    msgBox.setText(tr("Veuillez sélectionner un sommet de départ"));
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.exec();
}

/// @brief Highlights the current graph's minimum spanning tree.
/// @author Flückiger Jonas
void QBoard::highlightMinimumSpanningTree()
{
    this->highlightedGraph = graph->getMinimumSpanningTree();
    this->update();
}
