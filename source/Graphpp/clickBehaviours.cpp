#include "qboard.h"
#include "graph.h"
#include "qmultipleinputdialog.h"

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
    // BUILDING MODAL
    // number of vertices
    QLabel* nbVerticesLabel = new QLabel(tr("Choisissez le nombre de sommet (3-360):"),this);
    QSpinBox* nbVerticesSpin = new QSpinBox(this);
    nbVerticesSpin->setRange(3,360);
    nbVerticesSpin->setValue(3);
    nbVerticesSpin->setSingleStep(1);

    // radius
    QLabel* radiusLabel = new QLabel(tr("Choisissez le rayon du graphe (50-1000):"),this);
    QSpinBox* radiusSpin = new QSpinBox(this);
    radiusSpin->setRange(50,1000);
    radiusSpin->setValue(200);
    radiusSpin->setSingleStep(1);

    QList<QPair<QLabel*, QSpinBox*>> fieldList;
    fieldList.push_back(QPair(nbVerticesLabel, nbVerticesSpin));
    fieldList.push_back(QPair(radiusLabel, radiusSpin));

    // first nb = nbVertices
    // second nb = radius
    bool ok;
    QList<int> output = QMultipleInputDialog::getInts(tr("Créer un nouveau graphe cyclique"), fieldList, &ok, this);

    if (ok)
    {
        int nbVertices = output.at(0);
        double radius = output.at(1);

        QVertex* arrayVertices[nbVertices];
        createRoundedVertices(arrayVertices, nbVertices, radius, clickPos);

        // add edges to the graph
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
    // BUILDING MODAL
    // number of vertices
    QLabel* nbVerticesLabel = new QLabel(tr("Choisissez le nombre de sommet (3-100):"),this);
    QSpinBox* nbVerticesSpin = new QSpinBox(this);
    nbVerticesSpin->setRange(3,100);
    nbVerticesSpin->setValue(3);
    nbVerticesSpin->setSingleStep(1);

    // radius
    QLabel* radiusLabel = new QLabel(tr("Choisissez le rayon du graphe (50-1000):"),this);
    QSpinBox* radiusSpin = new QSpinBox(this);
    radiusSpin->setRange(50,1000);
    radiusSpin->setValue(200);
    radiusSpin->setSingleStep(1);

    QList<QPair<QLabel*, QSpinBox*>> fieldList;
    fieldList.push_back(QPair(nbVerticesLabel, nbVerticesSpin));
    fieldList.push_back(QPair(radiusLabel, radiusSpin));

    // first nb = nbVertices
    // second nb = radius
    bool ok;
    QList<int> output = QMultipleInputDialog::getInts(tr("Créer un nouveau graphe complet"), fieldList, &ok, this);

    if (ok)
    {
        int nbVertices = output.at(0);
        double radius = output.at(1);

        QVertex* arrayVertices[nbVertices];
        createRoundedVertices(arrayVertices, nbVertices, radius, clickPos);

        // add edges to the graph
        for (auto * vertexSource: arrayVertices)
        {
            for (auto * vertexTarget: arrayVertices)
            {
                if (vertexSource != vertexTarget)
                {
                    this->graph->addDoubleEdge(vertexSource, vertexTarget);
                }
            }
        }
    }
}

void QBoard::createRoundedVertices(QVertex* arrayVertices[], int nbOfVertices, double radius, QPointF center)
{
    double angle = 360./nbOfVertices;
    for (int i=0; i < nbOfVertices; ++i)
    {
        double realAngle = angle*i * M_PI / 180; // convert to radian
        QPointF vertexPos = QPointF(center.x() + (cos(realAngle) * radius), center.y() + (sin(realAngle) * radius));
        QString vertexName = "Vertex " + QString::number(this->graph->adjacencyList.size()+1); //start at 0
        arrayVertices[i] = new QVertex(vertexName, vertexPos);
        // add to graph
        this->graph->addVertex(arrayVertices[i]);
    }
}
void QBoard::clickBipartiteGraph(QPointF clickPos)
{
    // BUILDING MODAL
    // number of vertices first partite
    QLabel* nbVerticesLabel1 = new QLabel(tr("Choisissez le nombre de sommet de la partie supérieure (1-10):"),this);
    QSpinBox* nbVerticesSpin1 = new QSpinBox(this);
    nbVerticesSpin1->setRange(1,10);
    nbVerticesSpin1->setValue(3);
    nbVerticesSpin1->setSingleStep(1);

    // number of vertices second partite
    QLabel* nbVerticesLabel2 = new QLabel(tr("Choisissez le nombre de sommet de la partie inférieure (1-10):"),this);
    QSpinBox* nbVerticesSpin2 = new QSpinBox(this);
    nbVerticesSpin2->setRange(1,10);
    nbVerticesSpin2->setValue(3);
    nbVerticesSpin2->setSingleStep(1);

    // width
    QLabel* widthLabel = new QLabel(tr("Choisissez la largeur du graphe (50-1000):"),this);
    QSpinBox* widthSpin = new QSpinBox(this);
    widthSpin->setRange(50,1000);
    widthSpin->setValue(200);
    widthSpin->setSingleStep(1);

    // height
    QLabel* heightLabel = new QLabel(tr("Choisissez la hauteur du graphe (50-1000):"),this);
    QSpinBox* heightSpin = new QSpinBox(this);
    heightSpin->setRange(50,1000);
    heightSpin->setValue(100);
    heightSpin->setSingleStep(1);

    QList<QPair<QLabel*, QSpinBox*>> fieldList;
    fieldList.push_back(QPair(nbVerticesLabel1, nbVerticesSpin1));
    fieldList.push_back(QPair(nbVerticesLabel2, nbVerticesSpin2));
    fieldList.push_back(QPair(widthLabel, widthSpin));
    fieldList.push_back(QPair(heightLabel, heightSpin));

    // first nb = nbVertices first partite
    // second nb = nbVertices second partite
    // third nb = width
    // quarter nb = height

    bool ok;
    QList<int> output = QMultipleInputDialog::getInts(tr("Créer un nouveau graphe biparti complet"), fieldList, &ok, this);

    if (ok)
    {
        int nbVertices1 = output.at(0);
        int nbVertices2 = output.at(1);
        int width = output.at(2);
        int height = output.at(3);

        QVertex* arrayVertices1[nbVertices1];
        QVertex* arrayVertices2[nbVertices2];

        createLineOfVertices(arrayVertices1, nbVertices1, width, height, true, clickPos);
        createLineOfVertices(arrayVertices2, nbVertices2, width, height, false, clickPos);

        // add edges to the graph
        for (auto * vertexSource: arrayVertices1)
        {
            for (auto * vertexTarget: arrayVertices2)
            {
                if (vertexSource != vertexTarget)
                {
                    this->graph->addDoubleEdge(vertexSource, vertexTarget);
                }
            }
        }
    }
}


void QBoard::createLineOfVertices(QVertex* arrayVertices[], int nbOfVertices, int width, int height, bool upper, QPointF center)
{
    // add vertices to graph
    int spaceBtwPoints;
    int startingPoint;
    if (nbOfVertices <= 1)
    {
        // special case if line has only one vertex.
        // instead of drawing it on corner left, draw it in center
        spaceBtwPoints = width/2;
        startingPoint = 1;
    }
    else
    {
        spaceBtwPoints = width/(nbOfVertices-1);
        startingPoint = 0;
    }

    // define if it's upper line or not
    int lineHeight;
    if (upper)
    {
        lineHeight = -height/2;
    }
    else
    {
        lineHeight = height/2;
    }

    for (int i=startingPoint; i < nbOfVertices+startingPoint; ++i)
    {
        QPointF vertexPos = QPointF(center.x()- width/2 + i*spaceBtwPoints, center.y() + lineHeight);
        QString vertexName = "Vertex " + QString::number(this->graph->adjacencyList.size()+1); //start at 0
        arrayVertices[i-startingPoint] = new QVertex(vertexName, vertexPos);
        // add to graph
        this->graph->addVertex(arrayVertices[i-startingPoint]);
    }
}
