# miniprojetcpp
On souhaite mémoriser les étudiants de la faculté ainsi que leurs notes dans un fichier nommé
«fichetu.txt».
Un étudiant est caractérisé par un identifiant, un nom et un prénom. Chaque étudiant
possède un vecteur de notes sachant qu’un étudiant a au total 10 notes. Chaque note est composée d’
une note de contrôle continu Ncc et une note d’examen Nex.
Partie I:
1) Créer les classes Etudiant et Note nécessaires pour élaborer ce système. La classe
Etudiant possède les méthodes publiques suivantes:
 a) un constructeur avec paramètres.
 b) int getId() const qui retourne l’identifiant de l’étudiant.
 c) string getNom() const qui retourne le nom de l’étudiant.
 d) string getPrenom() const qui retourne le prénom de l’étudiant.
 e) double Moyenne() qui retourne la moyenne générale de l’étudiant.
 Notez que la moyenne d’une matière est calculée comme suit:
Moyenne_matière=Ncc*0.3+Nex*0.7
 f) vector<Note> getNote() const qui retourne le vecteur de notes.
 La classe Note possède les méthodes publiques suivantes:
 a) un constructeur avec paramètres
 b) double getNoteControle() const retourne la note de contrôle continu.
 c) double getNoteExamen() const retourne la note d’examen.

2) Créer la classe Gestion qui permet de gérer les étudiants et qui possède comme attribut un
vecteur d’étudiants et les méthodes publiques suivantes:
 a) void saisir_etudiant() qui permet de saisir un ensemble d’étudiants et les mettre
dans le vecteur d’étudiants.
 b) void creer_fichier() permettant de créer un fichier contenant les différents étudiants
avec leurs notes correspondantes.
 c) void étudiants_reussis() qui permet de créer le fichier nommé « res.txt» qui
contiendra les étudiants qui ont réussît, triés dans l’ordre croissant de leur moyenne.
 d) Void Affiche() permet d’afficher à l’écran le contenu du fichier « res.txt».
 3) Ecrire en C++ un programme principal pour tester les différentes classes.
Partie II
 On souhaite modifier la conception de la classe Etudiant. Pour cela on va définir une classe
générale Personne qui admet comme attributs protégés un identifiant, un nom et un prénom ainsi
qu’une méthode publique afficher() qui affiche les caractéristiques générales d’une personne.
1) On vous demande de définir les classes Professseur et Personnel qui héritent de la classe
Dhouha Krichen INDP1 2022-2023
2
Personne d’une manière publique.
Un professeur admet un attribut privé cours indiquant le cours assuré (Français, Maths).
Un personnel admet un attribut privé metier indiquant son métier (directeur, financier, etc).
2) Introduire les modifications nécessaires à la classe Etudiants de telle sorte qu’elle hérite
publiquement de la classe Personne.
3) Redéfinir la méthode afficher() dans chacune des sous classes Etudiants, Professeur et
Personnel.
Partie III
Ajouter à la fonction principale le code qui permet de créer un tableau de pointeurs de type
Personne, le remplir par les adresses d’objets dynamiques de type Etudiants, Professeurs, et
Personnels et invoquer pour chacun la méthode afficher() de telle sorte qu’on ait un
comportement polymorphique des éléments. 
