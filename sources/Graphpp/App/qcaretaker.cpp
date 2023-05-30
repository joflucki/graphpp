#include "qcaretaker.h"

QCaretaker::QCaretaker(QBoard* qboard)
{
    this->qboard = qboard;
    this->undoStack = QStack<QMemento>();
    this->redoStack = QStack<QMemento>();
}

void QCaretaker::backup()
{
    this->redoStack.clear();
    // remove object in redo stack
    this->undoStack.push(this->qboard->save());
}
void QCaretaker::undo()
{
    if (this->undoStack.length() > 0) {
        QMemento currentMemento = this->undoStack.pop();
        // save current state of app in redo stack
        this->redoStack.push(this->qboard->save());
        this->qboard->restore(currentMemento);
        this->qboard->update();
    }
}
void QCaretaker::redo()
{
    if (this->redoStack.length() > 0) {
        QMemento currentMemento = this->redoStack.pop();

        this->undoStack.push(this->qboard->save());
        this->qboard->restore(currentMemento);
        this->qboard->update();
    }
}
