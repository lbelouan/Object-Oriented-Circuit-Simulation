# POO_sortie_circuit_elec

# Simulation de Circuits Électroniques – BE Programmation Orientée Objet

## Objectif

Ce projet de Bureau d'Études (BE) a pour objectif de développer, en **programmation orientée objet (POO)**, un simulateur capable de modéliser des **circuits électroniques** soumis à différents types de **sources** (imposées dans le sujet).

L'ensemble des circuits considérés conduit à la résolution d’**équations différentielles ordinaires (EDO)** avec des **conditions initiales**.  
L’approche adoptée repose sur l’**implémentation de méthodes numériques** permettant de simuler le comportement dynamique des circuits dans le temps.

##  Méthodes Numériques

Le simulateur intègre plusieurs **méthodes de résolution numérique** :

-  **Méthode d'Euler**
-  **Méthode de Heun**
-  **Méthode de Runge-Kutta**

## Fonctionnalités

- Représentation modulaire orientée objet des composants électroniques.
- Simulation dynamique avec choix de la méthode numérique.
- Circuits et sources définis selon le sujet imposé.
- Code structuré pour clarté, réutilisabilité et extensibilité.

##  Structure du Projet

```
jacqueselouanpoo3/
├── Sources/
│ ├── main.cpp # Programme principal : point d'entrée
│ ├── sources.cpp # Méthodes numériques (Euler, Heun, Runge-Kutta)
│ └── circuits_jacqueselouan.cpp # Définition des circuits
│
└── Headers/
├── sources.h # Déclarations des solveurs
└── circuits_jacqueselouan.h # Déclarations des circuits

```

##  Compilation & Exécution

Utiliser un compilateur C++ compatible C++11 ou plus :

```bash
g++ -std=c++11 Sources/main.cpp Sources/sources.cpp Sources/circuits_jacqueselouan.cpp -o simulateur./simulateur
