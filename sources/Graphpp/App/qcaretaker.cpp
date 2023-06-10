#include "qcaretaker.h"

/// @brief Constructor of QCaretaker
/// @author Plumey Simon
QCaretaker::QCaretaker(QBoard* qboard)
{
    this->qboard = qboard;
    this->undoStack = QStack<QMemento>();
    this->redoStack = QStack<QMemento>();
}

/// @brief Save current stat of graph in a QMemento object
/// @author Plumey Simon
void QCaretaker::backup()
{
    QMemento graphMemento = this->qboard->save();

    // remove all objects in redostack
    this->redoStack.clear();
    for (QMemento memento: this->redoStack)
    {
        deleteDifferences(memento.getAdjencyList(), graphMemento.getAdjencyList());
    }

    // remove object in redo stack
    this->undoStack.push(graphMemento);
    emit backupAction();
}

/// @brief Restore the current state from the previous memento
/// @author Plumey Simon
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

/// @brief Redo the last operation undid
/// @author Plumey Simon
void QCaretaker::redo()
{
    if (this->redoStack.length() > 0) {
        QMemento currentMemento = this->redoStack.pop();

        this->undoStack.push(this->qboard->save());
        this->qboard->restore(currentMemento);
        this->qboard->update();
    }
}

/// @brief Delete in memory all objects present in mapToRemove and not in currentMap
/// @param std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> mapToRemove map with all object more will be deleted (often memento map)
/// @param std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> currentMap the reference map to compare the mapToRemove (often current graph map)
/// @author Plumey Simon
void QCaretaker::deleteDifferences(std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> mapToRemove,
                                   std::unordered_map<QVertex*, std::list<Edge<QVertex>*>> currentMap)
{
    // Parcours de la map du graph
    for (auto it = mapToRemove.begin(); it != mapToRemove.end();) {
        QVertex* key = it->first;
        std::list<Edge<QVertex>*>& list1 = it->second;

        // Vérification de la présence de la clé dans la map du memento
        auto it2 = currentMap.find(key);
        if (it2 == currentMap.end()) {
            // La clé n'existe pas dans la memento map, suppression de l'élément de la graph map
            for (Edge<QVertex>* edge : list1) {
                delete edge;
            }
            delete key;
        } else {
            // La clé existe dans la memento, comparaison des listes
            std::list<Edge<QVertex>*>& list2 = it2->second;

            // Comparaison des éléments des listes
            auto itList1 = list1.begin();
            auto itList2 = list2.begin();
            while (itList1 != list1.end()) {
                if (*itList1 != *itList2) {
                    delete *itList1;
                } else {
                    ++itList1;
                    ++itList2;
                }
            }

            if (list1.empty()) {
                delete key;
            } else {
                ++it;
            }
        }
    }
}

/// @return true if the caretaker can undo something. Otherwise, return false
/// @author Plumey Simon
bool QCaretaker::canUndo()
{
    return this->undoStack.length() > 1;
}

/// @return true if the caretaker can redo something. Otherwise, return false
/// @author Plumey Simon
bool QCaretaker::canRedo()
{
    return this->redoStack.length() > 0;
}
