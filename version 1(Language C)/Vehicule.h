typedef struct Vehicule
{
    int Id_Vehicule;
    int Id_Type_Categorie;
    int Id_Agence;
    int Nbr_Places, Disponibilite;
    float Prix_Par_Jour, Taux_Tarf;
    char Immatricule[20], Puissance_Fiscale[20], Modele[20], Marque[20], Type_carburant[20];
    struct Vehicule *Vehicule_suivant;
} Vehicule;

int Vehicule_existe_par_id_Vehicule(int id_Vehicule); // tester existance d'un Vehicule par son id
int Vehicule_existe_par_Matricule(char * mat); // tester existance d'un Vehicule par son matricule
void AddVehicule(); // ajouter un vehicule dans le fichier
Vehicule *AddVehiculeToList(Vehicule *new_Vehicule); // Ajouter un vehicule dans la list chainee
Vehicule *getVehicule(); // Generer une liste chainee d'apres le fichier Agences.txt
void AfficherTousLesVehicules(); // Afficher Tous les vehicules
void RefrechVehicule(Vehicule *list, char *file); // mis a jour du ficher
void deleteVehicule(int id); // Supprimer un vehicule d'apres son ID
void ChercherVehicule();
int Vehicule_disponible(int id_vehicule); //tester la disponibilite d'un vehicule (return 1 si oui et 0 sinon)
int Modifier_Disponibiliter_Vehicule(int id_vehicule, int dispo); // modifier la disponibilite d'un vehicule
Vehicule *get_vehicule_par_id(int id_Vehicule); // cette fonction prend l'id d'un vehicule et retourne toutes ses informations
