#ifndef QCARETAKER_H
#define QCARETAKER_H
#include <QStack>
#include "qmemento.h"
#include "qboard.h"

/// @brief Caretaker of qboard state. It's part of the memento design pattern
/// @author Plumey Simon
/// @date spring 2023
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
    void deleteDifferences(std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> graphMap,
                           std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> mementoMap);
};

#endif // QCARETAKER_H
