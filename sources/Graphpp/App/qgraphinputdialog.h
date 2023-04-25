#ifndef QGRAPHINPUTDIALOG_H
#define QGRAPHINPUTDIALOG_H

#include <QDialog>

class QGraphInputDialog : public QDialog
{
    Q_OBJECT
public:
    QGraphInputDialog(QWidget *parent = nullptr);
    static int getVertexNb(QWidget *parent, bool *ok = nullptr);
    static int getRadiusNb(QWidget *parent, bool *ok = nullptr);

private:
    int vertexNb;
    int radius;
};

#endif // QGRAPHINPUTDIALOG_H
