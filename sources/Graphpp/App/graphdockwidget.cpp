#include "graphdockwidget.h"
#include <QtWidgets>

/// @brief Constructor of the dock widget about graph analysis
/// @param QWidget: parent
/// @author Plumey Simon
GraphDockWidget::GraphDockWidget(QWidget *parent) : QWidget(parent)
{
    QWidget *propertyPanel = new QWidget(this);

    eulerian = new QLabel(tr("Eulérien: "), propertyPanel);
    hamiltonian = new QLabel(tr("Hamiltonien: "), propertyPanel);
    connected = new QLabel(tr("Connexe: "), propertyPanel);
    stronglyConnected = new QLabel(tr("Fortement connexe: "), propertyPanel);
    oriented = new QLabel(tr("Orienté: "), propertyPanel);
    weighted = new QLabel(tr("Pondéré: "), propertyPanel);
    chromaticNumber = new QLabel(tr("Estimation du nombre chromatique: "), propertyPanel);
    chromaticNumber->setToolTip(tr("La méthode utilisée nous permet approcher la solution avec une complexité de O(n). Pour une solution exacte, il faudrait utiliser un 'brut force'"));
    nbEdges = new QLabel(tr("Nombre d'arrêtes: "), propertyPanel);
    nbVertices = new QLabel(tr("Nombre sommets: "), propertyPanel);

    QVBoxLayout *layout = new QVBoxLayout(propertyPanel);
    layout->setAlignment(Qt::AlignTop);
    layout->addWidget(eulerian);
    layout->addWidget(hamiltonian);
    layout->addWidget(connected);
    layout->addWidget(stronglyConnected);
    layout->addWidget(oriented);
    layout->addWidget(weighted);
    layout->addWidget(chromaticNumber);
    layout->addWidget(nbEdges);
    layout->addWidget(nbVertices);
    layout->addStretch(1);

    QPushButton *analyseBtn = new QPushButton(tr("Analyser"), propertyPanel);
    connect(analyseBtn, &QPushButton::clicked, this, &GraphDockWidget::updateLabels);

    QHBoxLayout *btnLayout = new QHBoxLayout(propertyPanel);
    btnLayout->setAlignment(Qt::AlignRight);
    btnLayout->addWidget(analyseBtn);

    layout->addLayout(btnLayout);
    this->setLayout(layout);
}

/// @brief updateLabels depending of the selected graph
/// @author Plumey Simon
void GraphDockWidget::updateLabels()
{
    if (this->selectedGraph != nullptr)
    {
        eulerian->setText(tr("Eulérien: ") + (selectedGraph->isEulerian() ? tr("Oui") : tr("Non")));
        qDebug() << "Eulerian done" << Qt::endl;
        hamiltonian->setText(tr("Hamiltonien: ") + (selectedGraph->isHamiltonian() ? tr("Oui") : tr("Non")));
        qDebug() << "Hamiltonien done" << Qt::endl;
        connected->setText(tr("Connexe: ") + (selectedGraph->isConnected() ? tr("Oui") : tr("Non")));
        qDebug() << "Connexe done" << Qt::endl;
        stronglyConnected->setText(tr("Fortement connexe: ") + (selectedGraph->isStronglyConnected() ? tr("Oui") : tr("Non")));
        qDebug() << "Fortement connexe done" << Qt::endl;
        oriented->setText(tr("Orienté: ") + (selectedGraph->isOriented() ? tr("Oui") : tr("Non")));
        qDebug() << "Orienté done" << Qt::endl;
        weighted->setText(tr("Pondéré: ") + (selectedGraph->isWeighted() ? tr("Oui") : tr("Non")));
        qDebug() << "Pondéré done" << Qt::endl;
        chromaticNumber->setText(tr("Estimation du nombre chromatique: ") + QString::number(selectedGraph->getChromaticNumber()));
        qDebug() << "Estimation du nombre chromatique done" << Qt::endl;
        nbEdges->setText(tr("Nombre d'arrêtes: ") + QString::number(selectedGraph->getNbEdges()));
        qDebug() << "Nombre d'arrêtes done" << Qt::endl;
        nbVertices->setText(tr("Nombre de sommets: ") + QString::number(selectedGraph->getNbVertices()));
        qDebug() << "Nombre de sommets done" << Qt::endl;

    }
}

/// @brief Set the selected graph
/// @param Graph<QVertex>*: graph of QVertex
/// @author Plumey Simon
void GraphDockWidget::setSelectedGraph(Graph<QVertex>* graph)
{
    this->selectedGraph = graph;
    qDebug() << graph;
}
