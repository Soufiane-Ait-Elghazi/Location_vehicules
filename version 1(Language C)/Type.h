typedef struct Type Type;

struct Type *getType(); // lire les informations du fichier et les mettres dans une liste
int Type_existe_par_nom(char *Nom); // comme son nom l'indique, tester l'existance d'un type avec son nom
int Type_existe_par_id_Type(int id_id_Type);
void AddType(); // stocker un nouveau type dans le fichier
Type *AddTypeToList(Type *new_Type); // ajouter un nouveau type dans la liste
char *SaisirChaine(FILE *fp); // lire les attributs du fichier un part un 
int getId(char *File); // genere un id auto-incrementable du fichier passe en parametre
void AfficherTousLesTypes(); //comme son nom l'indique
void RefrechType(struct Type *list, char *file); // actualiser les donnees stocker dans le fichier *file de la part de la liste *list
void deleteType(int id); // supprimer un type par son id
void ChercherType(); // chercher un type selon des critere demander dans la fonction
