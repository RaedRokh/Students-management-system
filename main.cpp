#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;
// Déclaration de la classe Personne
class Personne {
protected:
    int id; // identifiant
    string nom; // nom
    string prenom; // prénom
public:
    // Constructeur avec initialisation de la classe
    Personne(int i, string n, string p) : id(i), nom(n), prenom(p) { }
    
    // Méthode pour afficher les informations de la personne
    virtual void afficher() {
        cout << "Identifiant : " << id << endl;
        cout << "Nom : " << nom << endl;
        cout << "Prenom : " << prenom << endl;
    }
}; // fin de la classe Personne


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


// Constructeur de la classe Note avec initialisation des variables membres
Note::Note(string matiere, double ncc, double nex) : matiere(matiere), ncc(ncc), nex(nex) {}


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
    // Ouvre le fichier "etudiants.txt"
    ifstream fichier("etudiants.txt");

    // Si le fichier a été ouvert avec succès
    if (fichier) {
        // On vide le vecteur d'étudiants pour éviter d'avoir des doublons
        etudiants.clear();

        // Lecture du fichier ligne par ligne
        string ligne;
        while (getline(fichier, ligne)) {
            // Utilise un stringstream pour lire les informations de l'étudiant depuis la ligne lue
            stringstream ss(ligne);

            // Lecture de l'identifiant, du nom et du prénom de l'étudiant
            int id;
            string nom, prenom;
            ss >> id >> nom >> prenom;

            // Création d'un objet Etudiant avec les informations lues
            Etudiant etudiant(id, nom, prenom);

            // Lecture des notes de l'étudiant
            string matiere;
            double note_controle, note_examen,moyenne;
            while (ss >> matiere >> note_controle >> note_examen >> moyenne) {
                // Ajoute les notes à l'étudiant
                etudiant.ajouterNote(matiere, note_controle, note_examen);
            }

            // Ajout de l'étudiant au vecteur d'étudiants
            etudiants.push_back(etudiant);
        }

        // Ferme le fichier
        fichier.close();
        cout << "Le fichier a ete charge avec succes." << endl;
    } else {
        // Si le fichier n'a pas pu être ouvert, affiche un message d'erreur
        cerr << "Erreur : impossible de charger le fichier." << endl;
    }

    // Vide le vecteur d'étudiants pour éviter d'avoir des doublons
    etudiants.clear();
}

void Gestion::saisir_etudiant() {
    int nb_etudiants;
    cout << "Combien d\'etudiants voulez-vous ajouter ? ";
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
        // Boucle pour ajouter des notes à l'étudiant
        for (int i = 0; i < 10; i++){
            string matiere;
            double ncc, nex;
            string rep;
            cout << "Le nom de la matiere:";
            cin >> matiere;
            cout << "La note de contrôle continu:";
            cin >> ncc;
            cout << "La note d\'examen:";
            cin >> nex;
            etudiant.ajouterNote(matiere, ncc , nex);
             // Demander à l'utilisateur s'il veut ajouter d'autres matières
            cout << "Voulez vous ajouter d\'autres matieres? (o/n)";
            cin >> rep;
            if (rep == "n") {
                break;// Sortir de la boucle si l'utilisateur ne veut plus ajouter de matières
            }
        }
        // Ajouter l'objet à la liste des personnes
        etudiants.push_back(etudiant);
    }
}

void Gestion::creer_fichier() {
    // Vérifie si le vecteur d'étudiants est vide
    if (etudiants.empty()) {
        cout << "Aucun etudiant a ecrire dans le fichier etudiants.txt." << endl;
        return;
    }

    // Ouvre le fichier en mode ajout
    ofstream fichier("etudiants.txt",ios::app);

    // Vérifie si l'ouverture du fichier a réussi
    if (fichier) {
        // Parcourt tous les étudiants stockés dans le vecteur
        for (Etudiant& etudiant : etudiants) {
            // Écrit l'ID, le nom et le prénom de l'étudiant dans le fichier
            fichier << etudiant.getId() << " " << etudiant.getNom() << " " << etudiant.getPrenom() << " ";

            // Parcourt toutes les notes de l'étudiant
            for (Note& note : etudiant.getNote()) {
                // Écrit le nom de la matière, la note de contrôle continu, la note d'examen et la moyenne dans le fichier
                fichier <<note.getMatiereNom()<< " " << note.getNoteControle() << " " << note.getNoteExamen() << " " <<etudiant.Moyenne() << " ";
            }
            fichier << endl; // Passe à la ligne suivante pour le prochain étudiant
        }

        fichier.close(); // Ferme le fichier
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
    etudiants.clear();
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



