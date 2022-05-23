typedef struct Type_Categorie
{
    int Id_Type_Categorie;
    int Id_Type;
    int Id_Categorie;
    struct Type_Categorie *Type_Categorie_suivant;
} Type_Categorie; // c'est une table nee lors de la modelisation entre l'entite categorie et l'entite type  

int Type_Categorie_existe_par_id_Type_Categorie(int id); // tester l'existance d'une type_categorie d'apres son id
void AddType_Categorie( int id_type, int id_categorie); //ajouter une ligne dans le fichier
Type_Categorie *AddType_CategorieToList(Type_Categorie *new_Type_Categorie);
Type_Categorie *getType_Categorie(); // lire toutes les "type_categories" du fichier puis les mettre dans une liste
int TC_existe_par_id_TC(int id_type, int id_categorie); // tester l'existance d'apres les id des deux entites categories et types
void AfficherTousLesType_Categories(); // comme son nom l'indique
void RefrechType_Categorie(Type_Categorie *list, char *file); // m a j du fichier
void deleteType_Categorie(int id);
void ChercherType_Categorie();

