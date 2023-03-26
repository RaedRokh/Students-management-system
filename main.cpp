#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
using namespace std;
class Personne {
protected:
    int id;
    string nom;
    string prenom;
public:
    Personne(int i, string n, string p) : id(i), nom(n), prenom(p) { }
    void afficher() {
        cout << "Identifiant : " << id << endl;
        cout << "Nom : " << nom << endl;
        cout << "Prenom : " << prenom << endl;
    }
    
};

class Note {
public:
    Note(string matiere,double ncc, double nex);
    string getMatiereNom() const;
    double getNoteControle() const;
    double getNoteExamen() const;

private:
    string matiere; //nom de la matiere
    double ncc;  // note de contrôle continu
    double nex;  // note d'examen
};

Note::Note(string matiere,double ncc, double nex) :matiere(matiere), ncc(ncc), nex(nex) {}

string Note::getMatiereNom() const {
    return matiere;
}
double Note::getNoteControle() const {
    return ncc;
}

double Note::getNoteExamen() const {
    return nex;
}

class Etudiant : public Personne {
public:
    Etudiant(int i, string n, string p): Personne(i, n, p) {
        
    };
    int getId() const;
    string getNom() const;
    string getPrenom() const;
    vector<Note> getNote() const;
    void ajouterNote(string matiere,double ncc, double nex);
    double Moyenne() const;
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

void Etudiant::ajouterNote(string matiere,double ncc, double nex) {
   
    notes.push_back(Note(matiere, ncc, nex));
}

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
void Gestion::charger_fichier() {
    ifstream fichier("etudiants.txt");

    if (fichier) {
        // On vide le vecteur d'étudiants pour éviter d'avoir des doublons
        etudiants.clear();

        // Lecture du fichier ligne par ligne
        string ligne;
        while (getline(fichier, ligne)) {
            stringstream ss(ligne);
            int id;
            string nom, prenom;
            ss >> id >> nom >> prenom;
            Etudiant etudiant(id, nom, prenom);

            // Lecture des notes de l'étudiant
            string matiere;
            double note_controle, note_examen;
            while (ss >> matiere >> note_controle >> note_examen) {
                etudiant.ajouterNote(matiere, note_controle, note_examen);
            }

            // Ajout de l'étudiant au vecteur d'étudiants
            etudiants.push_back(etudiant);
        }

        fichier.close();
        cout << "Le fichier a ete charge avec succes." << endl;
    } else {
        cerr << "Erreur : impossible de charger le fichier." << endl;
    }
}
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
        
        // Ajouter l'objet à la liste des personnes
       
        cout << "Nom : ";
        cin >> nom;
        cout << "Prenom : ";
        cin >> prenom;
        Etudiant etudiant(id, nom, prenom);
        for (int i = 0; i < 10; i++){
            string matiere;
            double ncc, nex;
            string rep;
            cout << "Le nom de la matiere:";
            cin >> matiere;
            cout << "La note de contrôle continu:";
            cin >> ncc;
            cout << "La note d’examen:";
            cin >> nex;
            etudiant.ajouterNote(matiere, ncc , nex);
            
            cout << "Voulez vous ajouter d'autres matieres? (o/n)";
            cin >> rep;
            if (rep == "n") {
                break;
            }
        }
        etudiants.push_back(etudiant);
    }
}

void Gestion::creer_fichier() {
    ofstream fichier("etudiants.txt", ios::app);

    if (fichier) {
        for (Etudiant& etudiant : etudiants) {
            cout << etudiant.getId() << endl;
            fichier << etudiant.getId() << " " << etudiant.getNom() << " " << etudiant.getPrenom() << " ";
            for (Note& note : etudiant.getNote()) {
                fichier <<note.getMatiereNom()<< " " << note.getNoteControle() << " " << note.getNoteExamen() << " " <<etudiant.Moyenne() << " ";
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

int main() {
  

    Gestion supcom;
    supcom.charger_fichier();
    supcom.etudiants_reussis();
    supcom.Affiche();


    return 0;
}


