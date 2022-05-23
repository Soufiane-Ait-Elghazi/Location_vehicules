typedef struct Location Location;
int Location_existe(int id_client, int id_vehicule); // tester l'existance d'une location d'apres le client qui l'a fait et le vehicule louee

Location * Louer(); // un client loue un vehicule dans une periode
void AddLocation(Location * L); //ajoute  dans le fichier
Location* AddLocationToList(Location * new_Location);
void AfficherTousLesLocations();
void RefrechLocation(Location * list, char * file); // m a j du fichier
void retour_Vehicule_VIdFacture(int id_facture, int id_vehicule); //entrer la date de retoure du vehicule, changer sa disponibilite, et calculer le tarif du retard s'il extiste
void ChercherLocation();
char *LireChaine(FILE *fp); // lire les champ du fichier un par un
date stringToDate(char *str); // convertir une chaine de caractere en une date
int diffdate(date datefin, date date_retour); // calculer la difference, en jour, entre deux dates
float calculerMontant(int idvehicule, date deb, date fin); // calculer le montant de la location
