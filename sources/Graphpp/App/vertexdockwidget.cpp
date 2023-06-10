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
    labelInDegree = new QLabel(tr("Degré entrant:"), propertyPanel);
    labelOutDegree = new QLabel(tr("Degré sortant:"), propertyPanel);

    inDegree = new QLabel("0", propertyPanel);
    outDegree = new QLabel("0", propertyPanel);

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
    QPushButton *applyBtn = new QPushButton("&Appliquer", propertyPanel);
    connect(applyBtn, &QPushButton::clicked, this, &VertexDockWidget::updateVertex);

    QFormLayout *layout = new QFormLayout(this);
    layout->addRow(labelName, name);
    layout->addRow(labelInDegree, inDegree);
    layout->addRow(labelOutDegree, outDegree);
    layout->addRow(labelPositionX, positionX);
    layout->addRow(labelPositionY, positionY);
    layout->addRow(labelTextColor, textColorBtn);
    layout->addRow(labelBackgroundColor, backgroundColorBtn);
    layout->addRow(labelBorderColor, borderColorBtn);
    layout->addRow(new QLabel(this), applyBtn);

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
        this->inDegree->setText(QString::number(this->selectedGraph->getVertexIndegree(this->selectedVertex)));
        this->outDegree->setText(QString::number(this->selectedGraph->getVertexOutdegree(this->selectedVertex)));
    }
    else
    {
        this->name->setText("");
        this->positionX->setValue(0);
        this->positionY->setValue(0);
        this->textColorBtn->setColor(Qt::lightGray);
        this->backgroundColorBtn->setColor(Qt::lightGray);
        this->borderColorBtn->setColor(Qt::lightGray);
        this->inDegree->setText("0");
        this->outDegree->setText("0");
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


/// @brief Set the selected graph (graph is used to know the degree of the selected vertex)
/// @param Graph<QVertex>*: graph of QVertex
/// @author Plumey Simon
void VertexDockWidget::setSelectedGraph(Graph<QVertex>* graph)
{
    this->selectedGraph = graph;
}
