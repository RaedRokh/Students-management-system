#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Etudiant.h"
using namespace std;

int Etudiant::getId() const {
    return id;
}

string Etudiant::getNom() const {
    return nom;
}

string Etudiant::getPrenom() const {
    return prenom;
}

double Etudiant::Moyenne() const {
    double moyenne = 0.0;
    double sommeNcc = 0.0;
    double sommeNex = 0.0;
    for (const auto& note : notes) {
        sommeNcc += note.getNoteControle(); // Ajoute la note de contrôle continu à la somme des notes de contrôle continu
        sommeNex += note.getNoteExamen(); // Ajoute la note d'examen à la somme des notes d'examen
    }
    if (notes.size() > 0) {
        moyenne = (sommeNcc / notes.size()) * 0.3 + (sommeNex / notes.size()) * 0.7; // Calcule la moyenne pondérée des notes de contrôle continu et d'examen
        // La pondération est de 30% pour les notes de contrôle continu et de 70% pour les notes d'examen
    }
    return moyenne; // Retourne la moyenne calculée
}

void Etudiant::afficher() {
    Personne::afficher();
    cout << "Moyenne : " << Moyenne() << endl;
}
vector<Note> Etudiant::getNote() const {
    return notes;
}

void Etudiant::ajouterNote(string matiere, double ncc, double nex) {
    // Crée une nouvelle note avec les paramètres fournis et l'ajoute au vecteur de notes de l'étudiant.
    notes.push_back(Note(matiere, ncc, nex));
}
