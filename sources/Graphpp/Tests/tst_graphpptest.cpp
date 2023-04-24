
#include <QtTest>

// add necessary includes here

class GraphppTest : public QObject
{
    Q_OBJECT

public:
    GraphppTest();
    ~GraphppTest();

private slots:
    void test_case1();

};

GraphppTest::GraphppTest()
{

}

GraphppTest::~GraphppTest()
{

}

void GraphppTest::test_case1()
{

}

QTEST_APPLESS_MAIN(GraphppTest)

#include "tst_graphpptest.moc"
