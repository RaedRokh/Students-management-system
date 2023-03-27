#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Gestion.h"
using namespace std;



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
        fichier1.close(); 
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
