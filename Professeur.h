#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Personne.h"
using namespace std;



class Professeur : public Personne {
private:
    string cours;
public:
    Professeur(int i, string n, string p, string c) : Personne(i, n, p), cours(c) {}
    void afficher() {
        Personne::afficher();
        cout << "Cours : " << cours << endl;
    }
};
