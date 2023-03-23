#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
class Personne {
protected:
    int id;
    string nom;
    string prenom;
public:
    Personne(int i, string n, string p) : id(i), nom(n), prenom(p) {}
    void afficher() {
        cout << "Identifiant : " << id << endl;
        cout << "Nom : " << nom << endl;
        cout << "Prenom : " << prenom << endl;
    }
};
class Note {
public:
    Note(double ncc, double nex);
    double getNoteControle() const;
    double getNoteExamen() const;

private:
    double ncc;  // note de contrôle continu
    double nex;  // note d'examen
};

Note::Note(double ncc, double nex) : ncc(ncc), nex(nex) {}

double Note::getNoteControle() const {
    return ncc;
}

double Note::getNoteExamen() const {
    return nex;
}

class Etudiant : public Personne {
public:
    Etudiant(int i, string n, string p): Personne(i, n, p) {};
    int getId() const;
    string getNom() const;
    string getPrenom() const;
    double Moyenne() const;
    vector<Note> getNote() const;
    void ajouterNote(double ncc, double nex);
    double Moyenne();
    void afficher();

private:
    vector<Note> notes;
};


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
        sommeNcc += note.getNoteControle();
        sommeNex += note.getNoteExamen();
    }
    if (notes.size() > 0) {
        moyenne = (sommeNcc / notes.size()) * 0.3 + (sommeNex / notes.size()) * 0.7;
    }
    return moyenne;
}
void Etudiant::afficher() {
    Personne::afficher();
    cout << "Moyenne : " << Moyenne() << endl;
}
vector<Note> Etudiant::getNote() const {
    return notes;
}

void Etudiant::ajouterNote(double ncc, double nex) {
    notes.push_back(Note(ncc, nex));
}

class Gestion {
public:
    void saisir_etudiant();
    void creer_fichier();
    void etudiants_reussis();
    void Affiche();

private:
    vector<Etudiant> etudiants;
};

void Gestion::saisir_etudiant() {
    int nb_etudiants;
    cout << "Combien d'etudiants voulez-vous ajouter ? ";
    cin >> nb_etudiants;

    for (int i = 0; i < nb_etudiants; i++) {
        int id;
        string nom, prenom;
        cout << "Etudiant " << i+1 << endl;
        cout << "ID : ";
        cin >> id;
        cout << "Nom : ";
        cin >> nom;
        cout << "Prenom : ";
        cin >> prenom;
        Etudiant etudiant(id, nom, prenom);
        etudiants.push_back(etudiant);
    }
}

void Gestion::creer_fichier() {
    ofstream fichier("etudiants.txt");

    if (fichier) {
        for (Etudiant& etudiant : etudiants) {
            fichier << etudiant.getId() << " " << etudiant.getNom() << " " << etudiant.getPrenom() << " ";
            for (Note& note : etudiant.getNote()) {
                fichier << note.getNoteControle() << " " << note.getNoteExamen() << " ";
            }
            fichier << endl;
        }

        fichier.close();
        cout << "Le fichier a ete cree avec succes." << endl;
    } else {
        cerr << "Erreur : impossible de creer le fichier." << endl;
    }
}

void Gestion::etudiants_reussis() {
    ofstream fichier("res.txt");

    if (fichier) {
        // Trier les étudiants par moyenne croissante
        sort(etudiants.begin(), etudiants.end(), [](const Etudiant& a, const Etudiant& b) {
            return a.Moyenne() < b.Moyenne();
        });

        // Écrire les étudiants réussis dans le fichier
        for (Etudiant& etudiant : etudiants) {
            if (etudiant.Moyenne() >= 10.0) {
                fichier << etudiant.getId() << " " << etudiant.getNom() << " " << etudiant.getPrenom() << " ";
                for (Note& note : etudiant.getNote()) {
                    fichier << note.getNoteControle() << " " << note.getNoteExamen() << " ";
                }
                fichier << endl;
            }
        }

        fichier.close();
        cout << "Le fichier des etudiants reussis a ete cree avec succes." << endl;
    } else {
        cerr << "Erreur : impossible de creer le fichier." << endl;
    }
}

void Gestion::Affiche() {
    ifstream fichier("res.txt");
    string ligne;

    if (fichier) {
        while (getline(fichier, ligne)) {
            cout << ligne << endl;
        }

        fichier.close();
    } else {
        cerr << "Erreur : impossible de lire le fichier." << endl;
    }
}

int main() {
    Gestion gestion;
    
    // Saisie des étudiants
    gestion.saisir_etudiant();
    
    // Création du fichier des étudiants
    gestion.creer_fichier();
    
    // Affichage des étudiants réussis
    gestion.etudiants_reussis();
    
    // Affichage du contenu du fichier res.txt
    gestion.Affiche();
    
    return 0;
}