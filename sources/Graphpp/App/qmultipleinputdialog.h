#ifndef QMULTIPLEINPUTDIALOG_H
#define QMULTIPLEINPUTDIALOG_H

#include <QDialog>
#include <QtWidgets>

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
