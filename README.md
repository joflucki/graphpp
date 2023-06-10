# Graph++
Vous pouvez trouver toutes les informations liées à la réalisation de ce projet dans le Wiki GitLab. Ceci n'est qu'une simple introduction au projet :

## Introduction
Graph++ est un projet en C++ qui offre une boîte à outils complète pour l'analyse et l'exploration de graphes.
Le projet se compose de trois composants principaux : une bibliothèque, une application d'interface utilisateur graphique (GUI) et un projet de tests unitaires.
Son objectif principal est de faciliter les tâches liées aux graphes, telles que le calcul des degrés des sommets, des nombres chromatiques, des chemins hamiltoniens et eulériens, et d'autres propriétés.
Graph++ offre une plateforme précieuse pour les chercheurs, les étudiants et les passionnés de graphes afin d'analyser et d'explorer efficacement des graphes.
Sa bibliothèque, son application GUI et son projet de tests unitaires travaillent ensemble pour fournir un instrument d'analyse de graphes, en en faisant une ressource utile pour diverses tâches liées aux graphes.

## Bibliothèque Graph++
La bibliothèque Graph++ sert de base au projet, offrant des implémentations efficaces de diverses structures de données et algorithmes de graphes.
Elle fournit aux développeurs une API simple pour créer et modifier des graphes.
De plus, la bibliothèque comprend des algorithmes d'analyse de graphes, permettant aux utilisateurs d'obtenir des informations sur la structure de leurs graphes.

## Application GUI Graph++
L'application GUI complète la bibliothèque en fournissant une interface conviviale pour interagir avec les graphes.
Elle permet aux utilisateurs de créer, modifier et visualiser des graphes, d'appliquer des algorithmes et d'obtenir un retour visuel sur les propriétés des graphes.
L'application comprend des fonctionnalités telles que des outils d'édition de graphes, des mises en page personnalisables et des affichages interactifs des propriétés des graphes.
Utilisation

## Installation
Vous pouvez [télécharger](https://gitlab-etu.ing.he-arc.ch/isc/2022-23/niveau-2/2282.1-projet-p2-sp-il/graphpp/-/raw/1add954272f4948a5ff8517b2eed55b8791593ec/bin/graphpp-win64.zip) une version compilée exécutable de l'application graphique pour Windows 64 bits.

## Utilisation

```c++
#include <graph.h>

///.......
// Create some vertices
int vertices[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

// Create a graph for those vertices
Graph<int>* graph = new Graph<int>();

// Add the vertices to the graph
for(int i : vertices){
    graph->addVertex(&i);
}

// Add some edges to the graph (Circular graph)
for(int i : vertices){
    int nextIndex = i + 1;
    if(nextIndex >= nbVertices){
        nextIndex = 0;
    }
    graph->addDoubleEdge(&vertices[i], &vertices[nextIndex]);
}
```