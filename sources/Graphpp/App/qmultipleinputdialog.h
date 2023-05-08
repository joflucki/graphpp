#ifndef QMULTIPLEINPUTDIALOG_H
#define QMULTIPLEINPUTDIALOG_H

#include <QDialog>
#include <QtWidgets>

/**
 * @brief This class create a multiple input dialog. It can manage inputs from a list of spinBox
 * @author Simon Plumey, inspired by Bobur (https://stackoverflow.com/a/53332748)
 */
class QMultipleInputDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QMultipleInputDialog(QString title, QList<QPair<QLabel*, QSpinBox*>> elements, QWidget *parent = nullptr);
    static QList<int> getInts(QString title, QList<QPair<QLabel*, QSpinBox*>> elements, bool *ok, QWidget *parent = nullptr);

private:
    QList<QSpinBox*> fields;
};

#endif // QMULTIPLEINPUTDIALOG_H
