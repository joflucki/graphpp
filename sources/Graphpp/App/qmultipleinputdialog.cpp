#include "qmultipleinputdialog.h"

/// @brief Constructor of QMultipleInputDialog
/// @param QString: title
/// @param QList<QPair<QLabel*, QSpinBox*>>: list of pair of labels and spinbox
/// @param QWidget: parent
/// @author Plumey Simon, inspired by Bobur
QMultipleInputDialog::QMultipleInputDialog(QString title, QList<QPair<QLabel*, QSpinBox*>> elements, QWidget *parent) : QDialog(parent)
{
    QFormLayout *lytMain = new QFormLayout(this);

    for (QPair<QLabel*, QSpinBox*> element : elements ) {
        lytMain->addRow(element.first, element.second);
        fields << element.second;
    }

    QDialogButtonBox *buttonBox = new QDialogButtonBox
            ( QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
              Qt::Horizontal, this );
    lytMain->addWidget(buttonBox);

    bool conn = connect(buttonBox, &QDialogButtonBox::accepted,
                        this, &QMultipleInputDialog::accept);
    Q_ASSERT(conn);
    conn = connect(buttonBox, &QDialogButtonBox::rejected,
                   this, &QMultipleInputDialog::reject);
    Q_ASSERT(conn);

    this->setWindowTitle(title);
    setLayout(lytMain);
}

/// @brief Get all spinbox values and put in a list
/// @author Plumey Simon, inspired by Bobur
QList<int> QMultipleInputDialog::getInts(QString title, QList<QPair<QLabel*, QSpinBox*>> elements, bool *ok, QWidget *parent)
{
    QMultipleInputDialog *dialog = new QMultipleInputDialog(title, elements, parent);

    QList<int> list;

    const int ret = dialog->exec();
    if (ok)
        *ok = !!ret;

    if (ret) {
        foreach (auto field, dialog->fields) {
            list << field->value();
        }
    }

    dialog->deleteLater();

    return list;
}
