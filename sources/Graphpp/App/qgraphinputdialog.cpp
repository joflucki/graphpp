#include "qgraphinputdialog.h"

#include <QtWidgets>

/**
 * @brief QGraphInputDialog::QGraphInputDialog
 * @param parent
 * @author Bobur & Plumey Simon
 * Inspired from https://stackoverflow.com/questions/17512542/getting-multiple-inputs-from-qinputdialog-in-qt
 */
QGraphInputDialog::QGraphInputDialog(QWidget *parent) : QDialog(parent)
{
    QFormLayout *layout = new QFormLayout(this);

    layout->addRow(new QLabel(tr("Choisissez le nombre de sommet (3-360):")), new QSpinBox());
    layout->addRow(new QLabel(tr("Choisissez le rayon (>0):")), new QSpinBox());

    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    layout->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted, this, &InputDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected, this, &InputDialog::reject);
    Q_ASSERT(conn);

    setLayout(layout);
}

int QGraphInputDialog::getRadiusNb(QWidget *parent, bool *ok)
{
    QGraphInputDialog *dialog = new QGraphInputDialog(parent);

    int returnValue;
    const int ret = dialog->exec();
    if (ok)
    {
        *ok = !!ret;
    }

    if (ret) {
        returnValue = dialog->radius;
    }

    dialog->deleteLater();

    return returnValue;
}
