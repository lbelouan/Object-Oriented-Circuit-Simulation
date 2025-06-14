#ifndef SOURCE_H_INCLUDED
#define SOURCE_H_INCLUDED

using namespace std;

class Sources
{
protected :
    float V0;  //amplitude
    float Phi;
    float Phins; //phase

public :
    Sources();  // constructeur
    virtual float Ve(float t) = 0;  // méthode virtuelle pure
};

class Periodique : public Sources
{
protected :
    float Periode;  // période
    float Periodens;  // période en nanosecondes

public :
    Periodique();  // constructeur
};

class Aperiodique : public Sources
{
public :
    Aperiodique() {};  // constructeur
};

class Rectangle : public Periodique
{
protected :
    float RapportCyclique;  // rapport cyclique

public :
    Rectangle();  // constructeur
    float Ve(float t);  // méthode Ve
};

class Sinus : public Periodique
{
public :
    Sinus();  // constructeur
    float Ve(float t);  // méthode Ve
};

class Triangle : public Periodique
{
public :
    Triangle();  // constructeur
    float Ve(float t);  // méthode Ve
};

class Impulsion : public Aperiodique
{
protected :
    float duree;  // durée de l'impulsion
    float dureens;  // durée en nanosecondes

public :
    Impulsion();  // constructeur
    float Ve(float t);  // méthode Ve
};

class Echelon : public Aperiodique
{
public :
    Echelon();  // constructeur
    float Ve(float t);  // méthode Ve
};

int menu_sources();  // menu choix sources

#endif // SOURCE_H_INCLUDED
