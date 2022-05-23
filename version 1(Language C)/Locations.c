#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "Client.h"
#include "Facture.h"
#include "Vehicule.h"
#include "Locations.h"
#include "Common_functions.h"
#include "LocalDate.h"

/*********************************************************************************/
/*
typedef struct Date
{
    unsigned int j;
    unsigned int m;
    unsigned int a;
} date;
*/
/*********************************************************************************/
struct Location
{
    int Id_Facture;
    int Id_Vehicule;
    date dateDebut;
    date dateFin;
    date dateRetour;
    float Tarif;
    struct Location *Location_suivant;
};
typedef struct Location Location;

Location *list_Location = NULL;

/*********************************************************************************/
int is_location_empty(struct Location *L) //Verifier si la liste est vide
{
    if (L == NULL)
        return 1;
    return 0;
}

//struct Location * getLocations();
/*********************************************************************************
int FileEmpty(FILE *file) // Verifier si le ficher Locations.txt est vide
{
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0)
    {
        return 1;
    }
    fseek(file, savedOffset, SEEK_SET);
    return 0;
}

*********************************************************************************/
Location *getLocations() // G�n�re une liste chain�e du fichier Locations.txt
{
    int idf;
    int idv;
    date d_debut;
    date d_fin;
    date d_retour;
    float tarif;

    FILE *f = fopen("Locations.txt", "r");

    if (f == NULL)
    {
        printf("could not open the file.\n");
        return NULL;
    }
    else
    {
        Location *current_Location = NULL, *nouv_Location = NULL;
        current_Location = list_Location;
        Location *X;
        int file_empty = 1;
        int pos = 1;
        while (!feof(f))
        {
            X = (Location *)malloc(sizeof(Location));
            file_empty = 0;
            idf = atoi(LireChaine(f));
            idv = atoi(LireChaine(f));
            if (idf == 0)
            {
                printf("aucune location trouver :\n");
                return NULL;
            }
            else
            {
                d_debut.j = atoi(LireChaine(f));
                d_debut.m = atoi(LireChaine(f));
                d_debut.a = atoi(LireChaine(f));
                d_fin.j = atoi(LireChaine(f));
                d_fin.m = atoi(LireChaine(f));
                d_fin.a = atoi(LireChaine(f));
                d_retour.j = atoi(LireChaine(f));
                d_retour.m = atoi(LireChaine(f));
                d_retour.a = atoi(LireChaine(f));
                tarif = atof(LireChaine(f));
                X->Id_Facture = idf;
                X->Id_Vehicule = idv;
                X->dateDebut = d_debut;
                X->dateFin = d_fin;
                X->dateRetour = d_retour;
                X->Tarif = tarif;

                nouv_Location = X;
                nouv_Location->Location_suivant = NULL;
                if (pos == 1)
                {
                    list_Location = nouv_Location;
                    current_Location = list_Location;
                    current_Location->Location_suivant = NULL;
                    pos++;
                }
                else
                {
                    current_Location->Location_suivant = nouv_Location;
                    current_Location = current_Location->Location_suivant;
                    pos++;
                }
            }
        }
        if (file_empty == 1)
        {
            return NULL;
        }
        fclose(f);
        return list_Location;
    }
}

/*********************************************************************************/

int Location_existe(int id_client, int id_vehicule) // existance d'une Location par ses identifants
{
    int id_facture = 0; /******** = getLastFacture(id_client) ********/
    Location *All = getLocations();
    Location *L;
    L = All;

    while (L != NULL && (L->Id_Facture != id_facture) && (L->Id_Vehicule != id_vehicule))
    {
        L = L->Location_suivant;
    }

    if (L == NULL)
    {
        printf("-----------------------------------------------\n");
        printf(" Aucun location correspondante trouvee! \n");
        printf("-----------------------------------------------\n");
        printf("Fin de recherche\n");
        return 0;
    }
    else
    {
        printf("-----------------------------------------------\n");
        printf("Location trouvee \n");
        printf("-----------------------------------------------\n");
        printf("Id_Facture\t\t : %d\n", L->Id_Facture);
        printf("Id_Vehicule\t\t : %d\n", L->Id_Vehicule);
        printf("La date de debut\t : %02u/%02u/%04u \n", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
        printf("La date de fin\t : %02u/%02u/%04u \n", L->dateFin.j, L->dateFin.m, L->dateFin.a);
        if (L->dateRetour.j == 0 && L->dateRetour.m == 0 && L->dateRetour.a == 0)
            printf("La date de retour\t : (null) \n");
        else
            printf("La date de retour\t : %02u/%02u/%04u \n", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);

        printf("Tarif\t\t : %f\n", L->Tarif);
        printf("-----------------------------------------------\n");
        printf("fin de recherche\n");
        return 1;
    }
}
/*********************************************************************************/

Location *Louer()
{
    int Id_Vehicule, Id_Client, a, j, m, check;
    date  date_fin;
    char type_Payement[20], CIN[10];

    printf("Entrer CIN du client :  ");
    gets(CIN);

    printf("Entrer Id du vehicule :  ");
    scanf("%d", &Id_Vehicule);
    getchar();

    if (Client_existe_par_CIN(CIN) && Vehicule_existe_par_id_Vehicule(Id_Vehicule))
    {
        if (Client_etat_blocage(CIN) == 0)
        {
            if (Vehicule_disponible(Id_Vehicule) == 1)
            {
                Location *L = (Location *)malloc(sizeof(Location));

                L->dateDebut.a = LocalDate().a;
                L->dateDebut.m = LocalDate().m;
                L->dateDebut.j = LocalDate().j;

                printf("Entrer La date de fin :  \n");
                
                do
                {
                    printf("Entrer le jour : ");
                    check = scanf("%d", &j);
                    getchar();
                    if(check != 1)
                    {
                        printf("\n jour entre est incorrect\n");
                    }

                } while (check != 1 || j < 1 || j > 31);

                
                do
                {
                    printf("Entrer le mois : ");
                    check = scanf("%d", &m);
                    getchar();
                    if(check != 1)
                    {
                        printf("\n mois entre est incorrect\n");
                    }

                } while (check != 1 || m < 1 || m > 12);
                
                do
                {
                    printf("Entrer l'annee : ");
                    check = scanf("%d", &a);
                    getchar();
                    if(check != 1)
                    {
                        printf("\n annee entree est incorrecte\n");
                    }

                } while (check != 1 || a < LocalDate().a || a > 9999);
                date_fin.j = j;
                date_fin.m = m;
                date_fin.a = a;
                L->dateFin = date_fin;
                Id_Client = get_id_client_par_CIN(CIN);
                printf("Entrer le type du payement (espece,carte bancaire,cheque)  : ");
                gets(type_Payement);
                
                L->Id_Facture = AddFacture(Id_Client, type_Payement, calculerMontant(Id_Vehicule, L->dateDebut, L->dateFin), L->dateDebut);
                L->Id_Vehicule = Id_Vehicule;
                L->Tarif = 0;
                L->dateRetour.a = 0;
                L->dateRetour.m = 0;
                L->dateRetour.j = 0;
                L->Location_suivant = NULL;

                Modifier_Disponibiliter_Vehicule(Id_Vehicule, 0);
                AddLocation(L);
                printf("\nVehicule louee avec succes:\nVotre facture est de numero %d.\n", L->Id_Facture);
                return L;
            }
            else
            {
                printf("Vehicule non disonible ! \n");
                return NULL;
            }
        }
        else
        {
            printf("Client bloque ! Il ne peut pas louer. \n");
            return NULL;
        }
    }
    else
    {
        printf("Client ou vehicule inexistant !! \n");
        return NULL;
    }
}

/*********************************************************************************/

void AddLocation(Location *L)
{
    FILE *f = fopen("Locations.txt", "a");
    if (FileEmpty(f) == 1)
    {
        fprintf(f, "%d:", L->Id_Facture);
        fprintf(f, "%d:", L->Id_Vehicule);
        fprintf(f, "%02u:%02u:%04u:", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
        fprintf(f, "%02u:%02u:%04u:", L->dateFin.j, L->dateFin.m, L->dateFin.a);
        fprintf(f, "%02u:%02u:%04u:", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);
        fprintf(f, "%f", L->Tarif);

        printf("Location ajoutee \n");
        list_Location = L;
    }
    else
    {
        fprintf(f, "\n%d:", L->Id_Facture);
        fprintf(f, "%d:", L->Id_Vehicule);
        fprintf(f, "%02u:%02u:%04u:", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
        fprintf(f, "%02u:%02u:%04u:", L->dateFin.j, L->dateFin.m, L->dateFin.a);
        fprintf(f, "%02u:%02u:%04u:", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);
        fprintf(f, "%f", L->Tarif);

        printf("Location ajoutee \n");
        list_Location = AddLocationToList(L);
    }
    fclose(f);
}

/*********************************************************************************/
Location *AddLocationToList(Location *new_Location) // Ajouter une Location a la list chainee
{
    if (is_location_empty(list_Location) == 1)
    {
        list_Location = new_Location;
        return list_Location;
    }
    else
    {
        Location *pt;
        pt = list_Location;
        while (pt->Location_suivant != NULL)
        {
            pt = pt->Location_suivant;
        }
        pt->Location_suivant = new_Location;
        return list_Location;
    }
}

/*********************************************************************************/

char *LireChaine(FILE *fp)
{
    char *str = NULL;
    unsigned int c, nbc = 0;

    while (((c = fgetc(fp)) != ':') && (c != EOF) && (c != '\n'))
    {
        str = realloc(str, (nbc + 1) * sizeof(char));
        str[nbc++] = c;
    }
    str = realloc(str, (nbc + 1) * sizeof(char));
    str[nbc] = '\0';
    return str;
}

/*********************************************************/
/*
int getId(char *File) // G�n�re l'id du nouveau Client
{
    char Number[100];
    char *pch;
    FILE *f = fopen(File, "r");
    if (f == NULL)
    {
        printf("Can\'t open the file");
        return -1;
    }
    while (!feof(f))
    {
        fgets(Number, 100, f);
        pch = strtok(Number, ":");
    }
    char *N = pch;
    fclose(f);
    return atoi(N);
}
*/
/*********************************************************************************/

date stringToDate(char *str)
{
    //str = "jj/mm/aaaa"
    date d;
    d.j = (str[1] - '0') + ((str[0] - '0') * 10);
    d.m = (str[4] - '0') + ((str[3] - '0') * 10);
    d.a = (str[9] - '0') + ((str[8] - '0') * 10) + ((str[7] - '0') * 100) + ((str[6] - '0') * 1000);
    return d;
}

/*********************************************************************************/

void AfficherTousLesLocations()
{ // Afficher Tous les Locations
    printf("L'affichage de toutes les Locations \n");
    Location *AllLocation = getLocations("Locations.txt");
    Location *L;
    L = AllLocation;
    if (AllLocation == NULL)
    {
        printf("Il n\'y a pas de Locations .\n");
        return;
    }
    else
    {
        while (L != NULL)
        {
            printf("-----------------------------------------------\n");
            printf("Location trouvee \n");
            printf("-----------------------------------------------\n");
            printf("Id_Facture\t\t : %d\n", L->Id_Facture);
            printf("Id_Vehicule\t\t : %d\n", L->Id_Vehicule);
            printf("La date de debut\t : %02u/%02u/%04u \n", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
            printf("La date de fin\t\t : %02u/%02u/%04u \n", L->dateFin.j, L->dateFin.m, L->dateFin.a);
            if (L->dateRetour.j == 0 && L->dateRetour.m == 0 && L->dateRetour.a == 0)
                printf("La date de retour\t : (null) \n");
            else
                printf("La date de retour\t : %02u/%02u/%04u \n", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);

            printf("Tarif\t\t\t : %f\n", L->Tarif);

            L = L->Location_suivant;
        }
    }
}

/******************************************************************************************/

void RefrechLocation(Location *list, char *file)
{ //Mise a jour du fichier Locations.txt
    if (list == NULL)
    {
        printf("la list est vide .\n");
        return;
    }
    else
    {
        FILE *f = fopen(file, "w");
        if (f == NULL)
        {
            printf("Can\'t open the file");
            return;
        }
        else
        {
            Location *curent;
            curent = list;
            while (curent != NULL && curent->Location_suivant != NULL)
            {

                fprintf(f, "%d:", curent->Id_Facture);
                fprintf(f, "%d:", curent->Id_Vehicule);
                fprintf(f, "%02u:%02u:%04u:", curent->dateDebut.j, curent->dateDebut.m, curent->dateDebut.a);
                fprintf(f, "%02u:%02u:%04u:", curent->dateFin.j, curent->dateFin.m, curent->dateFin.a);
                fprintf(f, "%02u:%02u:%04u:", curent->dateRetour.j, curent->dateRetour.m, curent->dateRetour.a);
                fprintf(f, "%f\n", curent->Tarif);
                curent = curent->Location_suivant;
            }

            fprintf(f, "%d:", curent->Id_Facture);
            fprintf(f, "%d:", curent->Id_Vehicule);
            fprintf(f, "%02u:%02u:%04u:", curent->dateDebut.j, curent->dateDebut.m, curent->dateDebut.a);
            fprintf(f, "%02u:%02u:%04u:", curent->dateFin.j, curent->dateFin.m, curent->dateFin.a);
            fprintf(f, "%02u:%02u:%04u:", curent->dateRetour.j, curent->dateRetour.m, curent->dateRetour.a);
            fprintf(f, "%f", curent->Tarif);
        }
        fclose(f);
    }
}

/**********************************************************************************************/

// int diffdate(date datefin, date date_retour)
// {
//     int nbr_jours = 0, jours_a_retrancher = 0;
//     nbr_jours = (date_retour.a - datefin.a) * 365 + (date_retour.m - datefin.m) * 31 + (date_retour.j - datefin.j);

//     for (int i = datefin.m; i < date_retour.m; i++)
//     {
//         if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
//         {
//             jours_a_retrancher += 0;
//         }
//         else if (i == 4 || i == 6 || i == 9 || i == 11)
//         {
//             jours_a_retrancher += 1;
//         }
//         else
//         {
//             jours_a_retrancher += 3;
//         }
//     }
//     nbr_jours = nbr_jours - jours_a_retrancher;
//     return nbr_jours;
// }

/**********************************************************************************************/

int diffdate(date datefin, date date_retour)
{

    int nbr_jours = 0, jours_a_retrancher = 0, i = 0;
    int n_years = 0, n_months = 0, n_days = 0;

    //nbr_jours = (date_retour.a - datefin.a) * 365 - mdiffmonth* 31 + (date_retour.j - datefin.j)+2;

    if (datefin.m > date_retour.m)
    {

        n_years = date_retour.a - datefin.a;
        n_months = (12 - (datefin.m - date_retour.m));
        n_days = date_retour.j - datefin.j;

        nbr_jours = n_months * 31 + n_days;

        i = date_retour.m;
        while (n_months != 0)
        {

            if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
            {

                jours_a_retrancher += 0;
            }
            else if (i == 4 || i == 6 || i == 9 || i == 11)
            {

                jours_a_retrancher += 1;
            }
            else
            {
                jours_a_retrancher += 3;
            }

            i--;
            if (i == 0)
            {

                i = 12;
            }

            n_months--;
        }

        nbr_jours = nbr_jours - jours_a_retrancher;

        if (n_years > 1)
        {
            nbr_jours = nbr_jours + (n_years - 1) * 365;
            return nbr_jours;
        }
        else
        {
            return nbr_jours;
        }
    }

    else
    {
        nbr_jours = (date_retour.a - datefin.a) * 365 + (date_retour.m - datefin.m) * 31 + (date_retour.j - datefin.j);

        for (int i = datefin.m; i < date_retour.m; i++)
        {

            if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12)
            {

                jours_a_retrancher += 0;
            }
            else if (i == 4 || i == 6 || i == 9 || i == 11)
            {

                jours_a_retrancher += 1;
            }
            else
            {
                jours_a_retrancher += 3;
            }
        }

        nbr_jours = nbr_jours - jours_a_retrancher;

        return nbr_jours;
    }
}

/****************************************************************************************************************************/

void retour_Vehicule_VIdFacture(int id_facture, int id_vehicule)
{ // modifier les info une Location dapres son ID
    Location *AllLocations = getLocations("Locations.txt");
    Location *L;
    L = AllLocations;
    if (L == NULL)
    {
        printf("Il n'y a pas de Locations .\n");
        return;
    }
    else
    {
        char CIN[10];
        printf("\nEntrer CIN : ");
        gets(CIN);
        if (Client_existe_par_CIN(CIN) == 1)
        {
            //int idcl = get_id_client_par_CIN(CIN);
            int pos = 0;
            while (L != NULL)
            {
                if (L->Id_Facture == id_facture && L->Id_Vehicule == id_vehicule)
                {
                    pos++;
                    if (L->dateRetour.j == 0 && L->dateRetour.m == 0 && L->dateRetour.a == 0)
                    {
                        L->dateRetour.a = LocalDate().a;
                        L->dateRetour.m = LocalDate().m;
                        L->dateRetour.j = LocalDate().j;
                        Modifier_Disponibiliter_Vehicule(id_vehicule, 1);

                        if (L->dateRetour.a > L->dateFin.a || ((L->dateRetour.a == L->dateFin.a) && (L->dateRetour.m > L->dateFin.m)) || ((L->dateRetour.a == L->dateFin.a) && (L->dateRetour.m == L->dateFin.m) &&(L->dateRetour.j > L->dateFin.j)))
                        {

                            int diff = diffdate(L->dateFin, L->dateRetour);

                            Vehicule *V = get_vehicule_par_id(id_vehicule);
                            float t = V->Prix_Par_Jour * (1 + V->Taux_Tarf) * diff;
                            L->Tarif = t;
                            printf("\nLe client est penalise avec un tarif de %f DHS", t);
                            RefrechLocation(AllLocations, "Locations.txt");
                        }
                        else{
                            RefrechLocation(AllLocations, "Locations.txt");
                        }
                        return;
                    }
                    else
                    {
                        printf("\nCe vehicule déja de retour !! ");
                        return;
                    }
                }
                L = L->Location_suivant;
            }
            if (pos == 0)
            {
                printf("\nVous ne pouvez pas retourner ce vehicule car ce n'est pas le notre ! \n");
            }
        }
        else
        {
            printf("\nLe client n'existe pas.");
        }
    }
}

/****************************************************************************************************************************/

void ChercherLocation()
{
    Location *All;
    Location *L;
    int id_vehicule, id_facture, choix = 0;

    char CIN[10];

    All = getLocations("Locations.txt");
    L = All;
    if (L == NULL)
    {
        printf("\nLa liste est vide.\n");
        return;
    }
    printf("\nRecherche par vehicule : 1\n");
    printf("Recherche par client : 2\n");
    printf("Recherche par facture : 3\n");
    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2 && choix != 3);

    switch (choix)
    {
    case 1:
        printf("\nDonner l'id du vehicule que vous cherchez :");
        scanf("%d", &id_vehicule);
        getchar();
        while (L != NULL)
        {
            if (L->Id_Vehicule == id_vehicule)
            {
                printf("-----------------------------------------------\n");
                printf("Id_Facture\t\t : %d\n", L->Id_Facture);
                printf("Id_Vehicule\t\t : %d\n", L->Id_Vehicule);
                printf("La date de debut\t : %02u/%02u/%04u \n", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
                printf("La date de fin\t : %02u/%02u/%04u \n", L->dateFin.j, L->dateFin.m, L->dateFin.a);
                if (L->dateRetour.j == 0 && L->dateRetour.m == 0 && L->dateRetour.a == 0)
                    printf("La date de retour\t : (null) \n");
                else
                    printf("La date de retour\t : %02u/%02u/%04u \n", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);

                printf("Tarif : %f\n", L->Tarif);
                printf("-----------------------------------------------\n");
            }
            L = L->Location_suivant;
        }
        printf("\n------Recherche termine------\n");
        return;
    case 2:
        printf("\nDonner CIN du client :");
        gets(CIN);
        ///stocker les factures du client qui a cette cin dans une liste de facture
        Facture *F = Factures_par_client(CIN);
        if (F == NULL)
        {
            printf("\nCe client n'a jammais loue un vehicule. ");
            return;
        }
        ///parcourir la liste des locations et tester chaque fois si le id_facture est dans la liste des factures
        while (L != NULL)
        {
            while (F != NULL)
            {
                if (L->Id_Facture == F->Id_Facture)
                {
                    printf("-----------------------------------------------\n");
                    printf("Id_Facture\t\t : %d\n", L->Id_Facture);
                    printf("Id_Vehicule\t\t : %d\n", L->Id_Vehicule);
                    printf("La date de debut\t : %02u/%02u/%04u \n", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
                    printf("La date de fin\t : %02u/%02u/%04u \n", L->dateFin.j, L->dateFin.m, L->dateFin.a);
                    if (L->dateRetour.j == 0 && L->dateRetour.m == 0 && L->dateRetour.a == 0)
                        printf("La date de retour\t : (null) \n");
                    else
                        printf("La date de retour\t : %02u/%02u/%04u \n", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);

                    printf("Tarif : %f\n", L->Tarif);
                    printf("-----------------------------------------------\n");
                    //break;
                }
                F = F->next;
            }
            L = L->Location_suivant;
        }
        printf("\n------Recherche termine------\n");
        return;
    case 3:
        printf("\nDonner l'id de la facture : ");
        scanf("%d", &id_facture);
        getchar();
        while (L != NULL)
        {
            if (L->Id_Facture == id_facture)
            {
                printf("-----------------------------------------------\n");
                printf("Id_Facture\t\t : %d\n", L->Id_Facture);
                printf("Id_Vehicule\t\t : %d\n", L->Id_Vehicule);
                printf("La date de debut\t : %02u/%02u/%04u \n", L->dateDebut.j, L->dateDebut.m, L->dateDebut.a);
                printf("La date de fin\t : %02u/%02u/%04u \n", L->dateFin.j, L->dateFin.m, L->dateFin.a);
                if (L->dateRetour.j == 0 && L->dateRetour.m == 0 && L->dateRetour.a == 0)
                    printf("La date de retour\t : (null) \n");
                else
                    printf("La date de retour\t : %02u/%02u/%04u \n", L->dateRetour.j, L->dateRetour.m, L->dateRetour.a);

                printf("Tarif : %f\n", L->Tarif);
                printf("-----------------------------------------------\n");
            }
            L = L->Location_suivant;
        }
        printf("\n------Recherche termine------\n");
        return;
    }
}

float calculerMontant(int idvehicule, date deb, date fin)
{
    Vehicule *V = get_vehicule_par_id(idvehicule);
    float PPJ = V->Prix_Par_Jour;
    int nbJours = diffdate(deb, fin);
    return (nbJours * PPJ);
}
