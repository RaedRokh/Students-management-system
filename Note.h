#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;
#ifndef NOTE_H
#define NOTE_H
// Déclaration de la classe Note
class Note {
public:
    // Constructeur de la classe Note
    Note(string matiere, double ncc, double nex);
    
    // Méthode pour obtenir le nom de la matière
    string getMatiereNom() const;
    
    // Méthode pour obtenir la note de contrôle continu
    double getNoteControle() const;
    
    // Méthode pour obtenir la note d'examen
    double getNoteExamen() const;

private:
    string matiere; // Nom de la matière
    double ncc;     // Note de contrôle continu
    double nex;     // Note d'examen
}; // fin de la classe Note
#endif

