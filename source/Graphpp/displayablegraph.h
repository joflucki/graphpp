#ifndef DISPLAYABLEGRAPH_H
#define DISPLAYABLEGRAPH_H
#include <QString>

class DisplayableGraph
{
public:
    DisplayableGraph();

    //getters
    QString getName();

    //setters
    void setName(QString name);

private:
    QString name = "";
};

#endif // DISPLAYABLEGRAPH_H
