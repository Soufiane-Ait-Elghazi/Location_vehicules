typedef struct Date
{
    int j;
    int m;
    int a;
}date;

#include "Common_functions.h"

typedef struct Facture
{
    int Id_Facture, Id_Client;
    float Montant;
    char Type_paiement[20];
    date date_facturation;

    struct Facture *next;
}Facture;

int Facture_existe_par_id_facture(int id_facture); // tester l'existance d'une Facture par ses informations
int Facture_existe_par_Id_Facture(int Id_Facture); // tester l'existance d'une Facture par ses informations
int AddFacture(int id_client, char *Type_paiement, float Montant, date date_facturation); // stocker une facture dans le fichier
Facture *AddFactureToList(Facture *List) ;// Ajouter une Facture a la list chainee
Facture *getFacture(); // Generer une liste chainee d'apres le ficher Factures.txt
void AfficherTousLesFactures(); // Afficher Toutes les Factures
void RefrechFacture(Facture *list, char *file); // mis a jour du ficher Factures.txt
void ChercherFacture();
Facture *Factures_par_client(char *CIN); // retourne une liste chainee contient toutes les factures d'un client donne
void afficher_CA_par_Client(); // calculer le chiffre d'affaire par client
