#include <QTest>

// add necessary includes here
#include <graph.h>

/// This class tests the different properties of a circular graph of size 10
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
    void test_vertices();
    void test_edges();
    void test_weight();
    void test_indegrees();
    void test_outdegrees();
    void test_connectivity();
    void test_strongConnectivity();
    void test_orientation();
    void test_eulerian();
    void test_hamiltonian();
    void test_chromaticNumber();

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
    delete graph;
}
void BasicGraphTest::test_vertices()
{
    QCOMPARE(graph->getNbVertices(), 0);
    for(int i = 0; i < nbVertices; i++){
        graph->addVertex(&vertices[i]);
        QCOMPARE(graph->getNbVertices(), i+1);
    }
}

void BasicGraphTest::test_edges()
{
    //Build graph edges (graph is actually the circular graph C10)
    for(int i = 0; i < nbVertices;i++){
        int nextIndex = i + 1;
        if(nextIndex >= nbVertices){
            nextIndex = 0;
        }
        graph->addDoubleEdge(&vertices[i], &vertices[nextIndex]);
    }
    QCOMPARE(graph->getNbEdges(), nbVertices);
}

void BasicGraphTest::test_weight()
{
    QVERIFY(!graph->isWeighted());
}


void BasicGraphTest::test_indegrees()
{
    //TODO uncomment with working Indegree method
    for(int i = 0; i < nbVertices; i++){
        //QCOMPARE(graph->getVertexIndegree(&vertices[i]), 1);
    }
    QVERIFY(false);
}
void BasicGraphTest::test_outdegrees(){
    //TODO uncomment with working Outdegree method
    for(int i = 0; i < nbVertices; i++){
        //QCOMPARE(graph->getVertexOutdegree(&vertices[i]), 1);
    }
    QVERIFY(false);
}

void BasicGraphTest::test_connectivity()
{
    QVERIFY(graph->isConnected());
}

void BasicGraphTest::test_strongConnectivity()
{
    QVERIFY(!graph->isStronglyConnected());
}

void BasicGraphTest::test_orientation()
{
    QVERIFY(!graph->isOriented());
}

void BasicGraphTest::test_eulerian()
{
    QVERIFY(graph->isEulerian());
}

void BasicGraphTest::test_chromaticNumber()
{
    QCOMPARE(graph->getChromaticNumber(), 2);
}

void BasicGraphTest::test_hamiltonian()
{
    QVERIFY(graph->isHamiltonian());
}

QTEST_APPLESS_MAIN(BasicGraphTest)

#include "tst_basicgraphtest.moc"
