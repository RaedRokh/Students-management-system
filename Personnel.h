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

class Personnel : public Personne {
private:
    string metier;
public:
    Personnel(int i, string n, string p, string m) : Personne(i, n, p), metier(m) {}
    void afficher() {
        Personne::afficher();
        cout << "Metier : " << metier << endl;
    }
};
