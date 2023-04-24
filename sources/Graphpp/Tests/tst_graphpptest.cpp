
#include <QtTest>

// add necessary includes here
#include <graphpplib.h>

class GraphppTest : public QObject
{
    Q_OBJECT

public:
    GraphppTest();
    ~GraphppTest();

private slots:
    void test_case1();
    void test_case2();
    void test_case3();
    void test_case4();

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
void GraphppTest::test_case2()
{
    QVERIFY(1 != 12);
}

void GraphppTest::test_case3()
{
    QVERIFY(1 > -1);
}

void GraphppTest::test_case4()
{
    QVERIFY(0 == 0);
}


QTEST_APPLESS_MAIN(GraphppTest)

#include "tst_graphpptest.moc"
