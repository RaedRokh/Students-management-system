#include <iostream>
#include <string>
#include <vector>
#include <limits>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include "Personne.h"
#include "Professeur.h"
#include "Personnel.h"
#include "Note.cpp"
#include "Etudiant.cpp"
#include "Gestion.cpp"

using namespace std;


int main() {

    // Question 6: 
    Personne* personnes[4];
    personnes[1] = new Professeur(2, "Will", "Smith", "Mathematiques");
    personnes[1]->afficher();
    personnes[2] = new Personnel(3, "Lefevre", "Marie", "Ressources Humaines");
    personnes[2]->afficher();
    personnes[3] = new Etudiant(1, "Jhon", "batiste");
    Etudiant* etudiant_ptr = dynamic_cast<Etudiant*>(personnes[3]);
    etudiant_ptr->ajouterNote("Mathematiques",14,12);
    etudiant_ptr->ajouterNote("Francais",18,12);
    personnes[3]->afficher();

  Gestion gestion;
    int choix = 0;

    do {
        // Ecrire l'interface en code ASCII
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

        // Lire le choix de l'utilisateur
        cout << "Votre choix : ";
       if (!(cin >> choix)) {
    // Gestion d'erreur si l'entree de l'utilisateur n'est pas un entier de 1 à 5
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
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

        //Pauser le programmer pour que l'utilisateur puisse lire le résultat de l'output
        cout << endl << "Appuyez sur une touche pour continuer...";
        cin.get();
        cin.ignore();

    } while (choix != 5);

    return 0;

}



