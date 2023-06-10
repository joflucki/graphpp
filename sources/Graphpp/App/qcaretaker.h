#ifndef QCARETAKER_H
#define QCARETAKER_H
#include <QStack>
#include <QObject>
#include "qmemento.h"
#include "qboard.h"

/// @brief Caretaker of qboard state. It's part of the memento design pattern
/// @author Plumey Simon
/// @date spring 2023
class QCaretaker : public QObject
{
    Q_OBJECT
private:
    QBoard* qboard;
    QStack<QMemento> undoStack;
    QStack<QMemento> redoStack;
    void boardActionCallback();

public:
    QCaretaker(QBoard* qboard);
    void backup();
    void undo();
    void redo();
    bool canUndo();
    bool canRedo();
    void deleteDifferences(std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> graphMap,
                           std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> mementoMap);

signals:
    void backupAction();
};

#endif // QCARETAKER_H
