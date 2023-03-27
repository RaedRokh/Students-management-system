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


// Constructeur de la classe Note avec initialisation des variables membres
Note::Note(string matiere, double ncc, double nex) : matiere(matiere), ncc(ncc), nex(nex) {
      if (ncc < 0 || ncc > 20) {
        throw std::invalid_argument("La note doit etre entre 0 et 20");
    }
    if (nex < 0 || nex > 20) {
        throw std::invalid_argument("La note doit etre entre 0 et 20");
    }
}


// Méthode pour obtenir le nom de la matière
string Note::getMatiereNom() const {
    return matiere; // renvoie le nom de la matière
}

// Méthode pour obtenir la note de contrôle continu
double Note::getNoteControle() const {
    return ncc; // renvoie la note de contrôle continu
}

// Méthode pour obtenir la note d'examen
double Note::getNoteExamen() const {
    return nex; // renvoie la note d'examen
}
