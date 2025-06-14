#ifndef CIRCUITS_JACQUESELOUAN_H
#define CIRCUITS_JACQUESELOUAN_H

#include "sources.h" // Inclure les sources pour utiliser les classes de signaux

#include <iostream>
#include <math.h>

using namespace std;

// Classe de base pour les circuits
class circuit
{
protected :
    Sources *Vin; // Tension d'entrée, de type Sources (classe parent des sources de signal)
    float C; // Capacité du circuit
    float CnF; // Capacité en nanofarads

public :
    circuit();  // Constructeur de la classe circuit
    virtual void euler() = 0;  // Méthode virtuelle pure pour l'intégration d'Euler
    virtual void Heun() = 0;  // Méthode virtuelle pure pour l'intégration de Heun
    virtual void RungeKutta4() = 0;  // Méthode virtuelle pure pour l'intégration de Runge-Kutta d'ordre 4
};

// Classe dérivée pour les circuits du premier ordre
class circuit_premier_ordre : public circuit
{
public :
    circuit_premier_ordre();  // Constructeur
    void euler();  // Implémentation de l'intégration d'Euler
    void Heun();  // Implémentation de l'intégration de Heun
    void RungeKutta4();  // Implémentation de l'intégration de Runge-Kutta d'ordre 4
    virtual float f1(float, float) = 0;  // Fonction virtuelle pure pour calculer f1 en fonction des paramètres
};

// Classe dérivée pour les circuits du deuxième ordre
class circuit_deuxieme_ordre : public circuit
{
protected :
    float L;    // Inductance (bobine)
    float LuH;  // Inductance en henrys

public :
    circuit_deuxieme_ordre();  // Constructeur
    void euler();  // Implémentation de l'intégration d'Euler
    void Heun();  // Implémentation de l'intégration de Heun
    void RungeKutta4();  // Implémentation de l'intégration de Runge-Kutta d'ordre 4
    virtual float f2(float, float, float) = 0;  // Fonction virtuelle pure pour calculer f2
};

// Circuit spécifique de type A, héritant de circuit_premier_ordre
class Circuit_A : public circuit_premier_ordre
{
protected :
    float R;    // Résistance du circuit

public :
    Circuit_A();  // Constructeur
    float f1(float, float);  // Implémentation de la fonction f1 pour ce circuit
};

// Circuit spécifique de type B, héritant de circuit_premier_ordre
class Circuit_B : public circuit_premier_ordre
{
protected :
    float R1;   // Résistance 1
    float R2;   // Résistance 2
    float V_be; // Tension de base-émetteur (utilisée dans les circuits à transistors)

public :
    Circuit_B();  // Constructeur
    float f1(float, float);  // Implémentation de la fonction f1 pour ce circuit
};

// Circuit spécifique de type C, héritant de circuit_deuxieme_ordre
class Circuit_C : public circuit_deuxieme_ordre
{
protected :
    float R;  // Résistance du circuit

public :
    Circuit_C();  // Constructeur
    float f2(float, float, float);  // Implémentation de la fonction f2 pour ce circuit
};

// Circuit spécifique de type D, héritant de circuit_deuxieme_ordre
class Circuit_D : public circuit_deuxieme_ordre
{
protected :
    float R;  // Résistance du circuit

public :
    Circuit_D();  // Constructeur
    float f2(float, float, float);  // Implémentation de la fonction f2 pour ce circuit
    float Ve_prime(float t);  // Calcul de la dérivée du signal de sortie
};

// Fonction pour choisir la méthode d'intégration
void chooseMethod();

#endif // CIRCUIT_PREMIER_ORDRE_H_INCLUDED
