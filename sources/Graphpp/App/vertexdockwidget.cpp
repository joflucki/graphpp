#include "vertexdockwidget.h"
#include <QtWidgets>

/// @brief Constructor of the dock widget about vertex properties
/// @param QWidget: parent
/// @author Plumey Simon
VertexDockWidget::VertexDockWidget(QWidget *parent) : QWidget(parent)
{
    QWidget *propertyPanel = new QWidget(this);

    // instanciate labels
    labelName = new QLabel(tr("Nom:"), propertyPanel);
    labelPositionX = new QLabel(tr("Position X:"), propertyPanel);
    labelPositionY = new QLabel(tr("Position Y:"), propertyPanel);
    labelTextColor = new QLabel(tr("Couleur du texte:"), propertyPanel);
    labelBackgroundColor = new QLabel(tr("Couleur de fond:"), propertyPanel);
    labelBorderColor = new QLabel(tr("Couleur de bordure:"), propertyPanel);

    // instanciate fields
    name = new QLineEdit(propertyPanel);
    positionX = new QSpinBox(propertyPanel);
    positionX->setRange(-9999, 9999);
    positionY = new QSpinBox(propertyPanel);
    positionY->setRange(-9999, 9999);

    // create color picker buttons
    textColorBtn = new SelectColorButton(propertyPanel);
    backgroundColorBtn = new SelectColorButton(propertyPanel);
    borderColorBtn = new SelectColorButton(propertyPanel);
    QPushButton *applyBtn = new QPushButton("&Appliquer");
    connect(applyBtn, &QPushButton::clicked, this, &VertexDockWidget::updateVertex);

    QFormLayout *layout = new QFormLayout();
    layout->addRow(labelName, name);
    layout->addRow(labelPositionX, positionX);
    layout->addRow(labelPositionY, positionY);
    layout->addRow(labelTextColor, textColorBtn);
    layout->addRow(labelBackgroundColor, backgroundColorBtn);
    layout->addRow(labelBorderColor, borderColorBtn);
    layout->addRow(new QLabel(), applyBtn);

    this->setLayout(layout);
}

/// @brief Update the selected vertex with values from user
/// @author Plumey Simon
void VertexDockWidget::updateVertex()
{
    if (this->selectedVertex != nullptr)
    {
        this->selectedVertex->setName(this->name->text());
        this->selectedVertex->setPosition(QPointF(this->positionX->value(), this->positionY->value()));
        this->selectedVertex->setTextColor(this->textColorBtn->getColor());
        this->selectedVertex->setBackgroundColor(this->backgroundColorBtn->getColor());
        this->selectedVertex->setBorderColor(this->borderColorBtn->getColor());
        emit vertexUpdated();
    }
}

/// @brief Update field when a new vertex is selected
/// @author Plumey Simon
void VertexDockWidget::updateFields()
{
    if (this->selectedVertex != nullptr)
    {
        this->name->setText(this->selectedVertex->getName());
        this->positionX->setValue(this->selectedVertex->getPosition().x());
        this->positionY->setValue(this->selectedVertex->getPosition().y());
        this->textColorBtn->setColor(this->selectedVertex->getTextColor());
        this->backgroundColorBtn->setColor(this->selectedVertex->getBackgroundColor());
        this->borderColorBtn->setColor(this->selectedVertex->getBorderColor());
    }
    else
    {
        this->name->setText("");
        this->positionX->setValue(0);
        this->positionY->setValue(0);
        this->textColorBtn->setColor(Qt::lightGray);
        this->backgroundColorBtn->setColor(Qt::lightGray);
        this->borderColorBtn->setColor(Qt::lightGray);
    }
}

/// @brief Set the selected vertex
/// @param QVertex*: vertex
/// @author Plumey Simon
void VertexDockWidget::setSelectedVertex(QVertex* vertex)
{
    this->selectedVertex = vertex;
    this->updateFields();
}

