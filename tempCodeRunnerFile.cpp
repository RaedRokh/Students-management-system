void Gestion::creer_fichier() {
    ofstream fichier("etudiants.txt", ios::out);

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