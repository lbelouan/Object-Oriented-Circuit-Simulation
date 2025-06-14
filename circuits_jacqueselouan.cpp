#include <iostream>
#include <math.h>
#include "circuits_jacqueselouan.h"
#include "sources.h" // Inclure les sources
#include <cstdlib>
#include <vector>
#include <cstdio>

using namespace std;



//////////////////////////////////////////
/////// CLASSE CIRCUIT ///////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

circuit::circuit()
{



    switch(menu_sources())
    {
    case 1 :
        std::system("cls");
        Vin = new Rectangle; // Utilisation du polymorphisme pour créer un signal rectangle
        cout<<"Utilisation d'un signal rectangle en entree"<<endl;
        break;

    case 2 :
        std::system("cls");
        Vin = new Impulsion; // Utilisation du polymorphisme pour créer un signal impulsion
        cout<<"Utilisation d'un signal impulsion en entree"<<endl;
        break;

    case 3 :
        std::system("cls");
        Vin = new Echelon; // Utilisation du polymorphisme pour créer un signal echelon
        cout<<"Utilisation d'un signal echelon en entree"<<endl;
        break;

    case 4 :
        std::system("cls");
        Vin = new Triangle; // Utilisation du polymorphisme pour créer un signal triangle
        cout<<"Utilisation d'un signal triangulaire en entree"<<endl;
        break;

    case 5 :
        std::system("cls");
        Vin = new Sinus;  // Utilisation du polymorphisme pour créer un signal sinus
        cout<<"Utilisation d'un signal sinusoidale en entree"<<endl;
        break;

    default:
        std::system("cls");
        cout<<"Pas de signal"<<endl;

    }

    // Définir la valeur de la capacité en nanofarads (nF)
        do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la  capa en nF : " << endl;
        cin >> CnF;
        C = CnF * 1e-9 ;

        if (C < 0)    //verifier capa positive
        {
            cout << "Erreur : La valeur de la capa ne peut pas etre negative. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while (C < 0);
}


//////////////////////////////////////////
/////// CLASSE CIRCUIT 1er ORDRE ///////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

circuit_premier_ordre::circuit_premier_ordre()
{

}



/////// EULER ///////

void circuit_premier_ordre::euler()
{
    FILE * fich;
    float un=0;
    float dun=0;
    std::vector<float> temps;
    fich=fopen("ve_euler","wt");

    float tempsDebut = 0.0;
    float tempsFin = 500e-9;
    float pasDeTemps =1e-9;


    for (float t = tempsDebut; t <= tempsFin; t += pasDeTemps)
    {
        temps.push_back(t); //creation vecteur temps
    }

    for (size_t i = 0; i < temps.size(); ++i) {
            float t = temps[i];
            dun=f1(t,un);//calcule dun
            un = un + (dun) * pasDeTemps;//calcul un
            fprintf(fich,"%0.10f %0.10f %f \n",t,un,Vin->Ve(t)); //ecriture fichier
        }
    fclose(fich);
}

/////// HEUN ///////

void circuit_premier_ordre::Heun()
{
    FILE * fich;
    float un=0;
    float un1,un2;
    std::vector<float> temps;
    fich=fopen("ve_heun","wt");

    float tempsDebut = 0.0;
    float tempsFin = 500e-9;
    float dt =1e-9;

    for (float t = tempsDebut; t <= tempsFin; t += dt)
    {
        temps.push_back(t);//creation vecteur temps
    }

    for (size_t i = 0; i < temps.size(); ++i) {
        float t = temps[i];
        un1=f1(t,un);//calcul un1
        un2=f1((t+dt),(un+dt*un1));//calcul un2
        un = un +(dt/2)*(un1+un2);//calcul un
        fprintf(fich,"%0.10f %0.10f %f \n",t,un,Vin->Ve(t));//ecriture fichier
    }
    fclose(fich);
}

/////// RungeKutta4 ///////

void circuit_premier_ordre::RungeKutta4()
{
    FILE * fich;
    float un=0;
    float un1, un2, un3, un4;
    std::vector<float> temps;
    fich = fopen("ve_rungekutta","wt");

    float tempsDebut = 0.0;
    float tempsFin = 500e-9;
    float dt = 1e-9;

    for (float t = tempsDebut; t <= tempsFin; t += dt)
    {
        temps.push_back(t);//creation vecteur temps
    }

    for (size_t i = 0; i < temps.size(); ++i) {
        float t = temps[i];
        un1 = f1(t,un);//calcul un1
        un2 = f1(t + dt/2, un + (dt/2) * un1);//calcul un2
        un3 = f1(t + dt/2, un + (dt/2) * un2);//calcul un3
        un4 = f1(t + dt, un + dt * un3);//calcul un

        un = un + (dt/6) * (un1 + 2*un2 + 2*un3 + un4); //calcul un
        fprintf(fich,"%0.10f %0.10f %f \n",t,un,Vin->Ve(t)); //ecriture fichier
    }
    fclose(fich);
}


//////////////////////////////////////////
/////// CLASSE CIRCUIT 1er ORDRE ///////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

circuit_deuxieme_ordre::circuit_deuxieme_ordre()
{
    do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la  bobine du circuit du deuxième ordre en uH: " << endl;
        cin >> LuH;
        L = LuH*1e-6;

        if ((L < 0)||(L>1)) // verifier valeur L
        {
            cout << "Erreur : La valeur de la bobine doit etre comprise entre 0 et 1uH. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }

    }
    while (L < 0);
}



/////////// EULER /////////

void circuit_deuxieme_ordre::euler()
{
    FILE * fich;
    float un=0;
    float dun=0;
    float ddun;
    std::vector<float> temps;
    fich=fopen("ve_euler","wt");

    float tempsDebut = 0.0;
    float tempsFin = 500e-9;
    float dt =1e-9;


    for (float t = tempsDebut; t <= tempsFin; t += dt)
    {
        temps.push_back(t);//creation vecteur temps
    }

    for (size_t i = 0; i < temps.size(); ++i) {
        float t = temps[i];
        ddun=f2(t,un,dun);//calcul dunp
        dun = dun + ddun * dt;//calcul dun
        un = un + dun * dt;//calcul un
        fprintf(fich,"%0.10f %0.10f %f \n",t,un,Vin->Ve(t));   //ecriture fichier
    }
    fclose(fich);
}

//////// HEUN /////////

void circuit_deuxieme_ordre::Heun()
{
    FILE * fich;
    float un=0;
    float dun=0;
    float un1,un2;
    std::vector<float> temps;
    fich=fopen("ve_heun","wt");

    float tempsDebut = 0.0;
    float tempsFin = 500e-9;
    float dt =1e-9;

    for (float t = tempsDebut; t <= tempsFin; t += dt)
    {
        temps.push_back(t); //creation vecteur temps
    }

    for (size_t i = 0; i < temps.size(); ++i) {
        float t = temps[i];
        un1=f2(t,un,dun); //calcul un1
        un2=f2((t+dt),un,(dun+dt*un1)); //calcul un2
        dun = dun +(dt/2)*(un1+un2); // calcul dun
        un =un+dt*dun; //calcul un
        fprintf(fich,"%0.10f %0.10f %f \n",t,un,Vin->Ve(t)); //ecriture fichier
    }
    fclose(fich);
}

////// RUNGE KUTTA ///////

void circuit_deuxieme_ordre::RungeKutta4()
{
    FILE * fich;
    float un=0;
    float dun=0;
    float un1, un2, un3, un4 ;
    std::vector<float> temps;
    fich = fopen("ve_rungekutta","wt");

    float tempsDebut = 0.0;
    float tempsFin = 500e-9;
    float dt = 1e-9;

    for (float t = tempsDebut; t <= tempsFin; t += dt)
    {
        temps.push_back(t);//creation vecteur temps
    }

    for (size_t i = 0; i < temps.size(); ++i) {
        float t = temps[i];
        un1 = f2(t, un, dun); //calcul un1
        un2 = f2(t + dt/2, un, dun + (dt/2) * un1);//calcul un2
        un3 = f2(t + dt/2, un, dun + (dt/2) * un2);//calcul un3
        un4 = f2(t + dt, un, dun + dt * un3);//calcul un4

        dun = dun + (dt/6) * (un1 + 2*un2 + 2*un3 + un4); //calcul dun

        un =un+dt*dun; //calcul un

        fprintf(fich,"%0.10f %0.10f %f \n",t,un,Vin->Ve(t)); //ecriture fichier
    }
    fclose(fich);
}





//////////////////////////////////////////
//////////// CLASSE CIRCUIT A ////////////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

Circuit_A::Circuit_A()
{
    do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la resistance en ohm: " << endl;
        cin >> R;

        if ((R < 0)||(R>1e6)) // verifier valeur R
        {
            cout << "Erreur : La valeur de la resistance doit etre comprise entre 0 et 1MOhm. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while ((R < 0)||(R>1e6));


}

//////// F1 ///////

float Circuit_A::f1(float tn, float un)
{
    float dun;
    float dt=1e-9;

    if (tn==0)
    {
        dun=0;// Conditions initiales
    }
    else
    {
        dun=(((Vin->Ve(tn))-un)/(R*C)); // calcul dun
    }

    return dun;
}




//////////////////////////////////////////
//////////// CLASSE CIRCUIT B ////////////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

Circuit_B::Circuit_B()
{
    V_be=0.6;

    do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la resistance R1 en ohm: " << endl;
        cin >> R1;

        if ((R1 < 0)||(R1>1e6)) // verifier valeur R1
        {
            std::system("cls");
            cout << "Erreur : La valeur de la resistance doit etre comprise entre 0 et 1MOhm. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while ((R1 < 0)||(R1>1e6));

    do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la resistance R2 en ohm: " << endl;
        cin >> R2;

        if ((R2 < 0)||(R2>1e6)) // verifier valeur R2
        {
            cout << "Erreur : La valeur de la resistance doit etre comprise entre 0 et 1MOhm. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while ((R2 < 0)||(R2>1e6));
}

/////// F1 //////

float Circuit_B::f1(float tn, float un)
{
    V_be=0.6;
    float dun;

    if (tn==0)
    {
        dun=0;// Conditions initiales
    }

    else if (Vin->Ve(tn)>V_be)
    {
        dun= (-((1/(R1*C))+(1/(R2*C)))*un+(Vin->Ve(tn)-V_be)/(R1*C)); //calcul dun
    }
    else
    {
        dun=-un/(R2*C); //calcul dun
    }
    return dun;
}



//////////////////////////////////////////
//////////// CLASSE CIRCUIT C ////////////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

Circuit_C::Circuit_C()
{
    do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la resistance en ohm: " << endl;
        cin >> R;

        if ((R < 0)||(R>1e6)) // verifier valeur R
        {
            cout << "Erreur : La valeur de la resistance doit etre comprise entre 0 et 1MOhm. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while ((R < 0)||(R>1e6));

}

//////// F2//////////
float Circuit_C::f2(float tn, float un, float dun)
{
    float dunp;
    // Intervalle de temps
    float dt = 1e-9;

    if (tn == 0)
    {
        // Conditions initiales
        un = 0;   // vs(0) = 0
        dun = 0;  // vs'(0) = 0
    }
    // Calculer la seconde dérivée de vs en fonction du temps
    dunp = (-R / L) * dun + (Vin->Ve(tn) - un) / (L * C);
    return dunp;
}



//////////////////////////////////////////
//////////// CLASSE CIRCUIT D ////////////
//////////////////////////////////////////

/////// CONSTRUCTEUR ///////

Circuit_D::Circuit_D()
{
    do
    {
        cout << " " << endl;
        cout << "Determiner la valeur de la resistance en ohm : " << endl;
        cin >> R;

        if ((R < 0)||(R>1e6)) // Verifier valeur R
        {
            cout << "Erreur : La valeur de la resistance doit etre comprise entre 0 et 1MOhm. Veuillez saisir une nouvelle valeur." << endl;
            cout << " " << endl;
        }
    }
    while ((R < 0)||(R>1e6));

}

float Circuit_D::Ve_prime(float t)
{
    float dt = 1e-9;
    float Ve_t = Vin->Ve(t);
    float Ve_t_plus_delta = Vin->Ve(t + dt);

    return (Ve_t_plus_delta - Ve_t) / dt;  // Approximation de la dérivée
}

float Circuit_D::f2(float tn, float un, float dun)
{
    float dunp;
    float dt = 1e-9;

    if (tn == 0)
    {
        // Conditions initiales
        un = 0;
        dun = 0;
    }
    // Calculer la seconde dérivée de vs en fonction du temps
    dunp = ((Ve_prime(tn) - dun) / (R * C) - un / (L * C));

    return dunp; // Retourne la valeur mise à jour de dun (vs')
}
