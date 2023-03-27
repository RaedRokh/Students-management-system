#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;
#ifndef PERSONNE_H
#define PERSONNE_H
// Déclaration de la classe Personne
class Personne {
protected:
    int id; // identifiant
    string nom; // nom
    string prenom; // prénom
public:
    // Constructeur avec initialisation de la classe
    Personne(int i, string n, string p) : id(i), nom(n), prenom(p) { }
    
    // Méthode pour afficher les informations de la personne
    virtual void afficher() {
        cout << "Identifiant : " << id << endl;
        cout << "Nom : " << nom << endl;
        cout << "Prenom : " << prenom << endl;
    }
}; // fin de la classe Personne
#endif
