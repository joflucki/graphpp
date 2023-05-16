#include <QTest>

// add necessary includes here
#include <graph.h>

/// This class will test the different properties of a complete graph of size 10
class ComplexGraphTest : public QObject
{
    Q_OBJECT

public:
    ComplexGraphTest();
    ~ComplexGraphTest();

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

ComplexGraphTest::ComplexGraphTest()
{
    graph = new Graph<int>();
    vertices = new int[nbVertices];
    for(int i = 0; i < nbVertices; i++){
        vertices[i] = i+1;
    }
}

ComplexGraphTest::~ComplexGraphTest()
{
    delete vertices;
    delete graph;
}
void ComplexGraphTest::test_vertices()
{
    QCOMPARE(graph->getNbVertices(), 0);
    for(int i = 0; i < nbVertices; i++){
        graph->addVertex(&vertices[i]);
        QCOMPARE(graph->getNbVertices(), i+1);
    }
}

void ComplexGraphTest::test_edges()
{
    //Build graph edges (graph is actually the complete graph K10)
    for(int i = 0; i < nbVertices;i++){
        for(int j = 0; j < nbVertices; j++){
            if(i != j){
                graph->addEdge(&vertices[i], &vertices[j], vertices[i]*vertices[j]);
            }
        }
    }
    QCOMPARE(graph->getNbEdges(), ((nbVertices-1)*nbVertices)/2);
}

void ComplexGraphTest::test_weight()
{
    QVERIFY(graph->isWeighted());
}


void ComplexGraphTest::test_indegrees()
{
    //TODO uncomment with working Indegree method
    for(int i = 0; i < nbVertices; i++){
        //QCOMPARE(graph->getVertexIndegree(&vertices[i]), 1);
    }
    QVERIFY(false);
}
void ComplexGraphTest::test_outdegrees(){
    //TODO uncomment with working Outdegree method
    for(int i = 0; i < nbVertices; i++){
        //QCOMPARE(graph->getVertexOutdegree(&vertices[i]), 1);
    }
    QVERIFY(false);
}

void ComplexGraphTest::test_connectivity()
{
    QVERIFY(graph->isConnected());
}

void ComplexGraphTest::test_strongConnectivity()
{
    QVERIFY(graph->isStronglyConnected());
}

void ComplexGraphTest::test_orientation()
{
    QVERIFY(!graph->isOriented());
}

void ComplexGraphTest::test_eulerian()
{
    QVERIFY(!graph->isEulerian());
}
void ComplexGraphTest::test_chromaticNumber()
{
    QCOMPARE(graph->getChromaticNumber(), nbVertices);
}

void ComplexGraphTest::test_hamiltonian()
{
    QVERIFY(graph->isHamiltonian());
}


QTEST_APPLESS_MAIN(ComplexGraphTest)

#include "tst_complexgraphtest.moc"
