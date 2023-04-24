
#include <QtTest>

// add necessary includes here
#include <graph.h>

class GraphppTest : public QObject
{
    Q_OBJECT

public:
    GraphppTest();
    ~GraphppTest();

private slots:
    void test_case1();
    void test_graph_initialization();

};

GraphppTest::GraphppTest()
{

}

GraphppTest::~GraphppTest()
{

}

void GraphppTest::test_case1()
{
    QVERIFY(1 == 1);
}

void GraphppTest::test_graph_initialization(){
    Graph<int>* graph = new Graph<int>();
    QVERIFY(graph->getNbVertices() == 0);
    QVERIFY(graph->getNbEdges() == 0);
}


QTEST_APPLESS_MAIN(GraphppTest)

#include "tst_graphpptest.moc"
