#include <QtTest>

// add necessary includes here
#include <graph.h>

class BasicGraphTest : public QObject
{
    Q_OBJECT

public:
    BasicGraphTest();
    ~BasicGraphTest();

private:
    Graph<int>* graph;
    int* vertices;
    int nbVertices = 10;

private slots:
    void test_vertex();
    void test_edges();
    void test_weight();
    void test_indegrees();
    void test_outdegrees();

};

BasicGraphTest::BasicGraphTest()
{
    graph = new Graph<int>();
    vertices = new int[nbVertices];
    for(int i = 0; i < nbVertices; i++){
        vertices[i] = i;
    }
}

BasicGraphTest::~BasicGraphTest()
{
    delete vertices;
}
void BasicGraphTest::test_vertex()
{
    QCOMPARE(graph->getNbVertices(), 0);
    for(int i = 0; i < nbVertices; i++){
        graph->addVertex(&vertices[i]);
        QCOMPARE(graph->getNbVertices(), i+1);
    }
}

void BasicGraphTest::test_edges()
{
    for(int i = 0; i < nbVertices;i++){
        int nextIndex = i + 1;
        if(i == nbVertices - 1){
            nextIndex= 0;
        }
        graph->addEdge(&vertices[i], &vertices[nextIndex]);
    }
    QCOMPARE(graph->getNbEdges(), nbVertices);
}

void BasicGraphTest::test_weight()
{
    QVERIFY(!graph->isWeighted());
}


void BasicGraphTest::test_indegrees()
{
    for(int i = 0; i < nbVertices; i++){
        QCOMPARE(graph->getVertexIndegree(&vertices[i]), 1);
    }
}
void BasicGraphTest::test_outdegrees()
{
    for(int i = 0; i < nbVertices; i++){
        QCOMPARE(graph->getVertexOutdegree(&vertices[i]), 1);
    }
}

QTEST_APPLESS_MAIN(BasicGraphTest)

#include "tst_basicgraphtest.moc"
