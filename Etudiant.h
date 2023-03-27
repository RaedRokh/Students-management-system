#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>

#include "Note.h"
using namespace std;
#ifndef ETUDIANT_H
#define ETUDIANT_H
#include "Personne.h"
// Classe pour représenter un étudiant, héritant de la classe Personne
class Etudiant : public Personne {
public:
    // Constructeur prenant en paramètre l'identifiant, le nom et le prénom de l'étudiant
    Etudiant(int i, string n, string p): Personne(i, n, p) {
        
    };
    // Méthode pour obtenir l'identifiant de l'étudiant
    int getId() const;
    // Méthode pour obtenir le nom de l'étudiant
    string getNom() const;
    // Méthode pour obtenir le prénom de l'étudiant
    string getPrenom() const;
    // Méthode pour obtenir la liste des notes de l'étudiant
    vector<Note> getNote() const;
    // Méthode pour ajouter une note à la liste des notes de l'étudiant
    void ajouterNote(string matiere,double ncc, double nex);
    // Méthode pour calculer la moyenne de l'étudiant
    double Moyenne() const;
    // Méthode pour afficher les informations de l'étudiant
    void afficher();

private:
    // Vecteur contenant les notes de l'étudiant
    vector<Note> notes;
};
#endif

