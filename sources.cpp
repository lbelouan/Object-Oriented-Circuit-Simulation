#include <iostream> // Pour cin et cout
#include <math.h>   // Pour la fonction sinus
#include "sources.h" // Déclaration des classes de sources
#include <cstdlib>   // Pour system("cls") et autres fonctions utilitaires

using namespace std;

///////////////////////////////////
// CLASSE SOURCES               //
///////////////////////////////////

// Constructeur de la classe Sources
Sources::Sources()
{
    // Demander et valider l'amplitude du signal
    do
    {
        cout << " " << endl;
        cout << "Determiner l'amplitude du signal en V: " << endl;
        cin >> V0;  // Amplitude du signal

        if (V0 < 0)   // Vérifier que l'amplitude est positive
        {
            cout << "Erreur : L'amplitude du signal ne peut pas etre negative. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while (V0 < 0);  // Continuer jusqu'à obtenir une amplitude valide

    // Demander et valider le retard du signal
    do
    {
        cout << " " << endl;
        cout << "Determiner le retard du signal en ns: " << endl;
        cin >> Phins;
        Phi = Phins * 1e-9;  // Conversion du retard en secondes

        if (Phi < 0)   // Vérifier que le retard est positif
        {
            cout << "Erreur : Le retard du signal ne peut pas etre negatif. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while (Phi < 0);  // Continuer jusqu'à obtenir un retard valide
}

///////////////////////////////////
// CLASSE PERIODIQUE             //
///////////////////////////////////

// Constructeur de la classe Periodique
Periodique::Periodique()
{
    // Demander et valider la période du signal
    do
    {
        cout << " " << endl;
        cout << "Determiner la periode du signal en ns: " << endl;
        cin >> Periodens;
        Periode = Periodens * 1e-9;  // Conversion de la période en secondes

        if (Periode < 0)    // Vérifier que la période est positive
        {
            cout << "Erreur : La periode du pulse ne peut pas etre negative. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while (Periode < 0);  // Continuer jusqu'à obtenir une période valide
}

///////////////////////////////////
// CLASSE RECTANGULAIRE          //
///////////////////////////////////

// Constructeur de la classe Rectangle
Rectangle::Rectangle()
{
    // Demander et valider le rapport cyclique
    do
    {
        cout << " " << endl;
        cout << "Determiner le rapport cyclique du signal : " << endl;
        cin >> RapportCyclique;

        if ((RapportCyclique < 0) || (RapportCyclique > 1))   // Vérifier que le rapport cyclique est entre 0 et 1
        {
            cout << "Erreur : Le rapport cyclique du signal doit etre compris entre 0 et 1. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while ((RapportCyclique < 0) || (RapportCyclique > 1));  // Continuer jusqu'à obtenir un rapport cyclique valide
}

// Fonction Ve pour un signal rectangulaire, renvoie l'amplitude en fonction du temps
float Rectangle::Ve(float t)
{
    float tmod;

    if (t <= Phi)  // Retourner 0 avant le retard
    {
        return 0;
    }
    else
    {
        tmod = fmod(t - Phi, Periode);  // Calcul du temps modulo la période

        if (tmod <= RapportCyclique * Periode)  // Signal de haute amplitude pendant le rapport cyclique
        {
            return V0;  // Retourner l'amplitude
        }
        else
        {
            return 0;   // Retourner 0 après le rapport cyclique
        }
    }
}

///////////////////////////////////
// CLASSE SINUSOIDALE           //
///////////////////////////////////

// Constructeur de la classe Sinus
Sinus::Sinus()
{
    // Constructeur vide, la classe Sinus n'a pas besoin d'initialisation spécifique
}

// Fonction Ve pour un signal sinusoïdal, renvoie l'amplitude en fonction du temps
float Sinus::Ve(float t)
{
    if (t < Phi)  // Retourner 0 avant le retard
    {
        return 0;
    }
    else
    {
        return (V0 * sin(2 * M_PI * t / Periode));  // Calcul du signal sinusoïdal
    }
}

///////////////////////////////////
// CLASSE TRIANGULAIRE           //
///////////////////////////////////

// Constructeur de la classe Triangle
Triangle::Triangle()
{
    // Constructeur vide, la classe Triangle n'a pas besoin d'initialisation spécifique
}

// Fonction Ve pour un signal triangulaire, renvoie l'amplitude en fonction du temps
float Triangle::Ve(float t)
{
    float tmod;

    if (t < Phi)  // Retourner 0 avant le retard
    {
        return 0;
    }
    else
    {
        tmod = fmod(t - Phi, Periode);  // Calcul du temps modulo la période
    }

    // Signal à pente positive avant la moitié de la période
    if (tmod <= 0.5 * Periode)
    {
        return (2 * V0 * tmod / Periode);  // Pente positive
    }
    else
    {
        return (2 * V0 - 2 * V0 * tmod / Periode);  // Pente négative
    }
}

///////////////////////////////////
// CLASSE IMPULSION              //
///////////////////////////////////

// Constructeur de la classe Impulsion
Impulsion::Impulsion()
{
    // Demander et valider la durée du pulse
    do
    {
        cout << " " << endl;
        cout << "Determiner la duree du pulse en ns : " << endl;
        cin >> dureens;
        duree = dureens * 1e-9;  // Conversion de la durée en secondes

        if (duree < 0)  // Vérifier que la durée est positive
        {
            cout << "Erreur : La duree du pulse ne peut pas etre negative. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while (duree < 0);  // Continuer jusqu'à obtenir une durée valide
}

// Fonction Ve pour un signal impulsionnel, renvoie l'amplitude en fonction du temps
float Impulsion::Ve(float t)
{
    if ((t >= Phi) && (t <= Phi + duree))  // Signal à amplitude V0 pendant la durée du pulse
    {
        return (V0);
    }
    else
    {
        return (0);  // Sinon, retourner 0
    }
}

///////////////////////////////////
// CLASSE STEP                  //
///////////////////////////////////

// Constructeur de la classe Echelon
Echelon::Echelon()
{
    // Constructeur vide, la classe Echelon n'a pas besoin d'initialisation spécifique
}

// Fonction Ve pour un signal échelon, renvoie l'amplitude en fonction du temps
float Echelon::Ve(float t)
{
    if (t >= Phi)  // Signal à amplitude V0 après le retard Phi
    {
        return (V0);
    }
    else
    {
        return (0);  // Avant Phi, retourner 0
    }
}

// Fonction menu pour sélectionner le type de signal
int menu_sources()
{
    int choix;

    // Affichage du menu de sélection des types de signaux
    do
    {
        std::system("cls");
        cout << "Quel type de signal voulez vous creer : " << endl;
        cout << "Tapez sur le clavier : " << endl;
        cout << "1 - Rectangulaire" << endl;
        cout << "2 - Impulsion" << endl;
        cout << "3 - Echelon" << endl;
        cout << "4 - Triangulaire" << endl;
        cout << "5 - Sinusoidale" << endl;
        cout << "0 - quitter" << endl;
        cin >> choix;
    }
    while ((choix > 5) || (choix < 0));  // Continuer jusqu'à ce que le choix soit valide
}
