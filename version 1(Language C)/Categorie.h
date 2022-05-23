typedef struct Categorie
{
	int Id_Categorie ;
	char  NomCategorie [20] ;
	struct Categorie * Categorie_suivant;
}Categorie;

struct Categorie * getCategorie(); // lire toutes les categories du fichier pour les mettre dans une liste chainee
int FileEmpty(FILE *file); // tester si le fichier est vide
int Categorie_existe_par_nom(char* Nom); //tester l'existance d'apres le nom
int Categorie_existe_par_id_Categorie(int id_id_Categorie);
void AddCategorie(); //ajouter une categorie et la stocker dans le fichier
Categorie* AddCategorieToList(Categorie * new_Categorie);
char * SaisirChaine(FILE * fp); // !!! lire les champs du fichier un par un
int getId(char * File) ; // genere l'id suiva,t automatiquement pour avoir un id auto-incrementable
void AfficherTousLesCategories();
void RefrechCategorie(struct Categorie * list,char * file); // m a j du fichier d'apres la liste
void changerInfoCategorie(int id);
void deleteCategorie(int id); // supprimer une categorie par son id
void ChercherCategorie();
