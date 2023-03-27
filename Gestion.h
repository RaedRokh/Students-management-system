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

class Gestion {
public:
    void saisir_etudiant();
    void creer_fichier();
    void etudiants_reussis();
    void Affiche();
    void charger_fichier();

private:
    vector<Etudiant> etudiants;
};
