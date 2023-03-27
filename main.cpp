#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;
class Personne {
protected:
    int id;
    string nom;
    string prenom;
public:
    Personne(int i, string n, string p) : id(i), nom(n), prenom(p) { }
    virtual void afficher() {
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
            double note_controle, note_examen,moyenne;
            while (ss >> matiere >> note_controle >> note_examen >> moyenne) {
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
    etudiants.clear();
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
        if (etudiants.empty()) {
        cout << "Aucun etudiant a ecrire dans le fichier etudiants.txt." << endl;
        return;
       
    }
    ofstream fichier("etudiants.txt",ios::app);

    if (fichier) {
        for (Etudiant& etudiant : etudiants) {
            cout << "test" << endl;
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
    if (etudiants.empty()) {
        cout << "Aucun etudiant a ecrire dans le fichier res.txt." << endl;
        return;
       
    }
    ifstream fichier1("res.txt");

    if (fichier1) {
        // Lecture du fichier ligne par ligne
        string ligne;
        while (getline(fichier1, ligne)) {
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
        fichier1.close(); // closing the file inside the if block
    } 
    else {
        cerr << "Erreur : impossible de lire le fichier." << endl;}

    ofstream fichier("res.txt");
    
    if (fichier) {
       
        sort(etudiants.begin(), etudiants.end(), [](const Etudiant& a, const Etudiant& b) {
            return a.Moyenne() < b.Moyenne();
        });

        // Écrire les étudiants réussis dans le fichier
        for (Etudiant& etudiant : etudiants) {
            if (etudiant.Moyenne() >= 10.0) {
                fichier << etudiant.getId() << " " << etudiant.getNom() << " " << etudiant.getPrenom() << " ";
                for (Note& note : etudiant.getNote()) {
                    fichier << note.getMatiereNom() << " " << note.getNoteControle() << " " << note.getNoteExamen() << " ";
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
    // Personne* personnes[4];

    // personnes[1] = new Professeur(2, "Martin", "Jean", "Mathematiques");
    // personnes[1]->afficher();
    // personnes[2] = new Personnel(3, "Lefevre", "Marie", "Ressources Humaines");
    // personnes[2]->afficher();
    // personnes[3] = new Etudiant(1, "Jhon", "batiste");
    // Etudiant* etudiant_ptr = dynamic_cast<Etudiant*>(personnes[3]);
    // etudiant_ptr->ajouterNote("maths",14,12);
    // etudiant_ptr->ajouterNote("francais",18,12);
    // personnes[3]->afficher();

  Gestion gestion;
    int choix = 0;

    do {
        // clear the console screenX


        // print the ASCII interface
        cout << "+-------------------------------------------+" << endl;
        cout << "|          GESTION DES ETUDIANTS            |" << endl;
        cout << "+-------------------------------------------+" << endl;
        cout << "| Que voulez-vous faire ?                   |" << endl;
        cout << "|                                           |" << endl;
        cout << "| 1. Saisir un etudiant                     |" << endl;
        cout << "| 2. Creer le fichier des etudiants          |" << endl;
        cout << "| 3. Creer le fichier des etudiants reussis  |" << endl;
        cout << "| 4. Afficher les etudiants reussis          |" << endl;
        cout << "| 5. Quitter                                |" << endl;
        cout << "+-------------------------------------------+" << endl;
        cout << endl;

        // read the user's choice
        cout << "Votre choix : ";
       if (!(cin >> choix)) {
    // input failed to read as an integer, handle error
    cin.clear(); // clear the input stream's error state
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // discard remaining characters in the input buffer
    cerr << "Erreur : choix invalide" << endl;
    continue; // go back to the top of the loop
    }

        switch (choix) {
            case 1:
                
                gestion.charger_fichier();
                gestion.saisir_etudiant();
                break;
            case 2:
                
                gestion.creer_fichier();
                break;
            case 3:
                
                gestion.etudiants_reussis();
                break;
            case 4:
                
                gestion.Affiche();
                break;
            case 5:
                cout << endl << "Au revoir !" << endl;
                break;
            default:
                cerr << "Erreur : choix invalide" << endl;
                break;
        }

        // pause the program to let the user read the output
        cout << endl << "Appuyez sur une touche pour continuer...";
        cin.get();
        cin.ignore();

    } while (choix != 5);

    return 0;

}



