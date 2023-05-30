#ifndef QCARETAKER_H
#define QCARETAKER_H
#include <QStack>
#include "qmemento.h"
#include "qboard.h"

class QCaretaker
{
private:
    QBoard* qboard;
    QStack<QMemento> undoStack;
    QStack<QMemento> redoStack;

public:
    QCaretaker(QBoard* qboard);
    void backup();
    void undo();
    void redo();
};

#endif // QCARETAKER_H
