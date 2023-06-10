
#include <QtTest>

// add necessary includes here
#include <graph.h>

using namespace std;

/// @brief This class tests the minimum distance graph algorithm.
/// The tested graph is the complete graph K10, where each edge's weight is equal to the
/// index of the source vertex multiplied by the index of the target vertex (indices range from 1 to 10).
/// Meaning that the minimum distance graph of this graph, starting from any vertex, is composed only of the edges connected to the '1' vertex.
class MinimumDistanceGraphTest : public QObject
{
    Q_OBJECT

public:
    MinimumDistanceGraphTest();
    ~MinimumDistanceGraphTest();

private:
    Graph<int>* initial;
    Graph<int>* expected;
    Graph<int>* actual;
    int* vertices;
    int nbVertices = 10;

private slots:
    void test_vertices_nb();
    void test_edges_nb();
    void test_vertices();
    void test_edges();
    void test_graph_weight();

};

MinimumDistanceGraphTest::MinimumDistanceGraphTest()
{
    initial = new Graph<int>();
    expected = new Graph<int>();
    vertices = new int[nbVertices];
    for(int i = 0; i < nbVertices; i++){
        vertices[i] = i+1;
        initial->addVertex(&vertices[i]);
        expected->addVertex(&vertices[i]);
    }
    for(int i = 0; i < nbVertices;i++){
        for(int j = 0; j < nbVertices; j++){
            if(i != j){
                initial->addEdge(&vertices[i], &vertices[j], vertices[i]*vertices[j]);
                if(i == 0 || j == 0){
                    auto hasTarget = [this, j](Edge<int> edge){
                        return &vertices[j] == edge.getTarget();
                    };
                    Edge<int>* edge = std::find_if(initial->adjacencyList[&vertices[i]].front(), initial->adjacencyList[&vertices[i]].back(), hasTarget);
                    if(edge != nullptr){
                        expected->addPrebuiltEdge(&vertices[i], edge);
                    }

                }
            }
        }
    }

    actual = initial->getMinimumDistanceGraph(&vertices[0]);
}

MinimumDistanceGraphTest::~MinimumDistanceGraphTest()
{
    delete vertices;
    delete initial;
    delete expected;
    delete actual;
}

void MinimumDistanceGraphTest::test_vertices_nb()
{
    QCOMPARE(actual->getNbVertices(), expected->getNbVertices());
}

void MinimumDistanceGraphTest::test_edges_nb()
{
    QCOMPARE(actual->getNbEdges(), expected->getNbEdges());
}

void MinimumDistanceGraphTest::test_graph_weight(){
    int expectedSum = 0;
    int actualSum = 0;
    for (auto const &pair : expected->adjacencyList)
    {
        for (auto const &edge : pair.second)
        {
            expectedSum += edge->getWeight();
        }
    }
    for (auto const &pair : actual->adjacencyList)
    {
        for (auto const &edge : pair.second)
        {
            actualSum += edge->getWeight();
        }
    }
    QCOMPARE(actualSum, expectedSum);
}

void MinimumDistanceGraphTest::test_vertices(){
    for (auto const &pair : actual->adjacencyList){
        QVERIFY(expected->adjacencyList.find(pair.first) != expected->adjacencyList.end());
    }
}

void MinimumDistanceGraphTest::test_edges(){
    for (auto const &pair : actual->adjacencyList){
        QCOMPARE(pair.second.size(), expected->adjacencyList[pair.first].size());
        for(auto const &edge : pair.second){
            QVERIFY(
                std::find(
                    expected->adjacencyList[pair.first].begin(),
                    expected->adjacencyList[pair.first].end(),
                    edge) !=
                expected->adjacencyList[pair.first].end());
        }
    }
}

QTEST_APPLESS_MAIN(MinimumDistanceGraphTest)

#include "tst_minimumdistancegraphtest.moc"
