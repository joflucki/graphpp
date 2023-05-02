
#include <QtTest>

// add necessary includes here
#include <graph.h>

class CircularGraphTest : public QObject
{
    Q_OBJECT

public:
    CircularGraphTest();
    ~CircularGraphTest();

private:
    Graph<int>* graph;
    int* vertices;
    int nbVertices = 10;

private slots:
    void test_verticesNumber();
    void test_edgesNumber();
};

CircularGraphTest::CircularGraphTest()
{
    graph = new Graph<int>();
    vertices = new int[nbVertices];
    for(int i = 0 ; i < nbVertices ; i++){
        vertices[i] = i+1;
        graph->addVertex(&vertices[i]);
        if(i>0){
            graph->addDoubleEdge(&vertices[i-1],&vertices[i]);
        }
    }
    graph->addDoubleEdge(&vertices[nbVertices-1],&vertices[0]);
}

CircularGraphTest::~CircularGraphTest()
{
    delete vertices;
}

void CircularGraphTest::test_verticesNumber()
{
    QCOMPARE(graph->getNbVertices(), nbVertices);
}

void CircularGraphTest::test_edgesNumber()
{
    QCOMPARE(graph->getNbEdges(), nbVertices);
}

QTEST_APPLESS_MAIN(CircularGraphTest)

#include "tst_circulargraphtest.moc"
