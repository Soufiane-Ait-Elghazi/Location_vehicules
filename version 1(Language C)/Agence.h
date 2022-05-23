struct Agences
{
	int Id_Agence ;
	char  NomAgence[20];
	char  VilleAgence[20];
	struct Agences * Agence_suivant;

};
typedef struct Agences Agence;


struct Agences * getAgences(); // lire les informations du fichier et les mettres dans une liste
int FileEmpty(FILE *file); // tester si le fichier est vide
int Agence_existe(char* Nom, char * Ville);
int Agences_existe_par_nom(char* Nom);
int Agences_existe_par_ville(char* Ville);
int Agences_existe_par_id_agence(int id_agence);
void AddAgence(); // ajouter une agence dans le fichier
struct Agences * AddAgenceToList(struct Agences * new_Agence);
char * SaisirChaine(FILE * fp); // lire les attributs du fichier un part un
int getId(char * File) ;
void AfficherTousLesAgences();
void RefrechAgence(struct Agences * list, char * file); // actualiser les donnees stocker dans le fichier *file de la part de la liste *list
void changerInfoAgence(int id);
void deleteAgence(int id); // supprimer une agence par son id
void ChercherAgence();
