#include <iostream>
#include <cstdio>
#include "sources.h"
#include "circuits_jacqueselouan.h"
#include <vector>

using namespace std;


int main() {
    // Variables principales
    int choixCircuit, choixMethod;
    circuit* myCircuit = NULL; // Pointeur pour créer l'objet circuit
    FILE* fich = NULL; // Pointeur pour gérer le fichier de sortie

    // Sélection du type de circuit
    do {
        cout << "=================================================" << endl;
        cout << "=== Bienvenue dans le simulateur de circuits ===" << endl;
        cout << "=================================================" << endl;
        cout << "Quel type de circuit voulez-vous creer ?" << endl;
        cout << "1 - Circuit A (R et C)" << endl;
        cout << "2 - Circuit B (R1, R2, C et V_be)" << endl;
        cout << "3 - Circuit C (R, C, et L)" << endl;
        cout << "4 - Circuit D (R, C, L avec Ve_prime)" << endl;
        cout << "0 - Quitter" << endl;
        cin >> choixCircuit;

        if (choixCircuit < 0 || choixCircuit > 4) {
            cout << "Choix invalide, veuillez reessayer." << endl;
        }
    } while (choixCircuit < 0 || choixCircuit > 4);

    if (choixCircuit == 0) {
        cout << "Au revoir !" << endl;
        return 0;
    }

    // Création du circuit correspondant
    switch (choixCircuit) {
        case 1:
            myCircuit = new Circuit_A();
            cout << "Circuit A cree avec succès." << endl;
            break;
        case 2:
            myCircuit = new Circuit_B();
            cout << "Circuit B cree avec succès." << endl;
            break;
        case 3:
            myCircuit = new Circuit_C();
            cout << "Circuit C cree avec succès." << endl;
            break;
        case 4:
            myCircuit = new Circuit_D();
            cout << "Circuit D cree avec succès." << endl;
            break;
    }

    // Sélection de la méthode d'analyse
    do {
        cout << "=================================================" << endl;
        cout << "Choisissez la méthode d'analyse numérique :" << endl;
        cout << "1 - Methode d'Euler" << endl;
        cout << "2 - Methode de Heun" << endl;
        cout << "3 - Methode de Runge-Kutta 4" << endl;
        cout << "4 - Executer toutes les methodes" << endl;
        cout << "0 - Quitter" << endl;
        cin >> choixMethod;

        if (choixMethod < 0 || choixMethod > 4) {
            cout << "Choix invalide, veuillez reessayer." << endl;
        }
    } while (choixMethod < 0 || choixMethod > 4);

    if (choixMethod == 0) {
        cout << "Simulation annulee. Au revoir !" << endl;
        delete myCircuit;
        return 0;
    }

    // Ouvrir un fichier pour enregistrer les résultats
    fich = fopen("ve.dat", "wt");
    if (fich == NULL) {
        cerr << "Erreur : Impossible d'ouvrir le fichier pour ecriture." << endl;
        delete myCircuit;
        return 1;
    }

    // Exécution de la méthode choisie et enregistrement des résultats
    switch (choixMethod) {
        case 1:
            fprintf(fich, "Resultats de la méthode d'Euler :\n");
            myCircuit->euler(); // Exécution de la méthode
            cout << "Methode d'Euler executee avec succes." << endl;
            break;
        case 2:
            fprintf(fich, "Résultats de la méthode de Heun :\n");
            myCircuit->Heun();
            cout << "Methode de Heun executee avec succes." << endl;
            break;
        case 3:
            fprintf(fich, "Resultats de la methode de Runge-Kutta 4 :\n");
            myCircuit->RungeKutta4();
            cout << "Methode de Runge-Kutta 4 exécutee avec succes." << endl;
            break;
        case 4:
            fprintf(fich, "Resultats de la methode de Runge-Kutta 4 :\n");
            myCircuit->RungeKutta4();
            cout << "Methode de Runge-Kutta 4 exécutee avec succes." << endl;

            fprintf(fich, "Résultats de la méthode de Heun :\n");
            myCircuit->Heun();
            cout << "Methode de Heun executee avec succes." << endl;

            fprintf(fich, "Resultats de la méthode d'Euler :\n");
            myCircuit->euler(); // Exécution de la méthode
            cout << "Methode d'Euler executee avec succes." << endl;

            break;
    }

    // Fermer le fichier
    fclose(fich);

    // Libérer la mémoire allouée pour le circuit
    delete myCircuit;

    cout << "Les resultats ont ete enregistres dans 've.dat'." << endl;
    cout << "Au revoir !" << endl;

    return 0;
}
