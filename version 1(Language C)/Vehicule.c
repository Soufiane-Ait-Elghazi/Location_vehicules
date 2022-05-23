#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Agence.h"
#include "Type_Categorie.h"
#include "Vehicule.h"
#include "Common_functions.h"

/**********************************************************************************************************************************************/

/**********************************************************************************************************************************************/

Vehicule *list_Vehicules = NULL;

/*
int is_vehicule_empty(struct Vehicule *A) //Verifier si la liste est vide
{
	if(A == NULL)
		return 1;
	return 0;

}
*/
//struct Agence * getAgences();
/*********************************************************************************/
/*
int FileEmpty(FILE *file) // Verifier si le ficher Agences est vide
{
    long savedOffset = ftell(file);
    fseek(file, 0, SEEK_END);

    if (ftell(file) == 0){
        return 1;
    }
    fseek(file, savedOffset, SEEK_SET);
    return 0;
}

*/
/*********************************************************************************/
int is_vehicules_empty(Vehicule *A) //Verifier si la liste est vide
{
    if (A == NULL)
        return 1;
    return 0;
}
/*********************************************************************************/
int Vehicule_existe_par_id_Vehicule(int id_Vehicule) // existance d'une Vehicule par ses informations
{
    Vehicule *All = getVehicule();
    Vehicule *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (A->Id_Vehicule == id_Vehicule)
        {

            occur++;
            return 1;
        }

        A = A->Vehicule_suivant;
    }

    if (file_empty == 1 || occur == 0)
    {

        return 0;
    }

    return 0;
}
/*********************************************************************************/
/*********************************************************************************/
int Vehicule_existe_par_Matricule(char *mat) // existance d'une Vehicule par ses informations
{
    Vehicule *All = getVehicule();
    Vehicule *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (strcmp(A->Immatricule, mat) == 0)
        {

            occur++;
            return 1;
        }

        A = A->Vehicule_suivant;
    }

    if (file_empty == 1 || occur == 0)
    {

        return 0;
    }

    return 0;
}
/*********************************************************************************/

/*********************************************************************************/
int Vehicule_disponible(int id_vehicule) // existance d'une Vehicule par ses informations
{
    Vehicule *All = getVehicule();
    Vehicule *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (A->Id_Vehicule == id_vehicule && A->Disponibilite == 1)
        {
            occur++;
            return 1;
        }

        A = A->Vehicule_suivant;
    }

    if (file_empty == 1)
    {

        return -1;
    }

    return 0;
}
/*********************************************************************************/

void AddVehicule()
{
    FILE *f = fopen("Vehicules.txt", "a");
    Vehicule *New;
    New = (Vehicule *)malloc(sizeof(Vehicule));
    New->Id_Vehicule = getId("Vehicules.txt") + 1;
    printf("Donner id_agence : ");
    scanf("%d", &(New->Id_Agence));
    getchar();
    printf("Donner id_Type_Categorie : ");
    scanf("%d", &(New->Id_Type_Categorie));
    getchar();
    printf("donner immatricule : ");
    gets(New->Immatricule);
    New->Vehicule_suivant = NULL;
    if ((Type_Categorie_existe_par_id_Type_Categorie(New->Id_Type_Categorie) == 1) && (Agences_existe_par_id_agence(New->Id_Agence) == 1) && (Vehicule_existe_par_Matricule(New->Immatricule) == 0))
    {

        printf("donner nombre des places :");
        scanf("%d", &(New->Nbr_Places));
        getchar();
        printf("donner Puissance_Fiscale : ");
        gets(New->Puissance_Fiscale);
        printf("donner Modele : ");
        gets(New->Modele);
        printf("donner Marque : ");
        gets(New->Marque);
        printf("donner prix_par_jour du vehicule :");
        scanf("%f", &(New->Prix_Par_Jour));
        getchar();
        printf("donner Type_carburant : ");
        gets(New->Type_carburant);
        New->Disponibilite = 1;
        printf("donner taux_tarif du vehicule : ");
        scanf("%f", &(New->Taux_Tarf));
        getchar();

        if (FileEmpty(f) == 1)
        {
            fprintf(f, "%d:%d:%d:%s:%d:%s:%s:%s:%s:%f:%d:%f", New->Id_Vehicule, New->Id_Type_Categorie, New->Id_Agence, New->Immatricule, New->Nbr_Places, New->Puissance_Fiscale, New->Modele, New->Marque, New->Type_carburant, New->Prix_Par_Jour, New->Disponibilite, New->Taux_Tarf);
            printf("%d est devenu une Vehicule", New->Id_Vehicule);
            list_Vehicules = New;
            fclose(f);
        }
        else
        {

            fprintf(f, "\n%d:%d:%d:%s:%d:%s:%s:%s:%s:%f:%d:%f", New->Id_Vehicule, New->Id_Type_Categorie, New->Id_Agence, New->Immatricule, New->Nbr_Places, New->Puissance_Fiscale, New->Modele, New->Marque, New->Type_carburant, New->Prix_Par_Jour, New->Disponibilite, New->Taux_Tarf);
            printf("%d est devenu une Vehicule", New->Id_Vehicule);
            list_Vehicules = AddVehiculeToList(New);
            fclose(f);
        }
    }

    else
    {

        printf("l'une des id est deja ou n'existe pas dans les fichiers vehicule,agence,type_categorie");
    }

    return;
}

/*********************************************************************************/
Vehicule *AddVehiculeToList(Vehicule *new_Vehicule) // Ajouter une Agence a la list chainee
{
    if (is_vehicules_empty(list_Vehicules) == 1)
    {
        list_Vehicules = new_Vehicule;
        return list_Vehicules;
    }
    else
    {
        Vehicule *pt;

        pt = list_Vehicules;
        while (pt->Vehicule_suivant != NULL)
        {
            pt = pt->Vehicule_suivant;
        }
        pt->Vehicule_suivant = new_Vehicule;
        return list_Vehicules;
    }
}
/*********************************************************************************/

/*
char * SaisirChaine(FILE * fp)
{
	char * str = NULL ;
	unsigned int c, nbc = 0 ;

	while(((c = fgetc(fp)) != ':') && (c != EOF) && (c != '\n'))
	{
		str = realloc(str, (nbc+1)*sizeof(char)) ;
		str[nbc++] = c ;
	}
	str = realloc(str, (nbc+1)*sizeof(char)) ;
	str[nbc] = '\0' ;
	return str ;
}
*/
/*********************************************************/
/*
int getId( char * File) // Genere l'id de nouveau Client
{
	char Number[100];
	char * pch;
	FILE *f = fopen(File, "r");
	if(f == NULL){
		printf("Can\'t open the file");
		return -1;
	}
	while(!feof(f))
	{
		fgets(Number, 100, f);
		pch = strtok(Number, ":");
	}
	char * N = pch;
	fclose(f);
	return atoi(N);
}

*/
/*********************************************************************************/
Vehicule *getVehicule() // Generer une liste chainee dapres le fichier Agences.txt
{
    unsigned int id;
    char *Nom;

    FILE *f = fopen("Vehicules.txt", "r");
    if (f == NULL)
    {
        printf("could not open the file\n");
        return NULL;
    }
    else
    {
        Vehicule *current_Vehicule = NULL, *nouv_Vehicule = NULL;
        current_Vehicule = list_Vehicules;
        Vehicule *New;
        int file_empty = 1;
        int pos = 1;

        while (!feof(f))
        {
            New = (Vehicule *)malloc(sizeof(Vehicule));
            id = atoi(SaisirChaine(f));
            if (id == 0)
            {
                file_empty = id;
                break;
            }
            New->Id_Vehicule = id;
            New->Id_Type_Categorie = atoi(SaisirChaine(f));
            New->Id_Agence = atoi(SaisirChaine(f));
            strcpy(New->Immatricule, SaisirChaine(f));
            New->Nbr_Places = atoi(SaisirChaine(f));
            strcpy(New->Puissance_Fiscale, SaisirChaine(f));
            strcpy(New->Modele, SaisirChaine(f));
            strcpy(New->Marque, SaisirChaine(f));
            strcpy(New->Type_carburant, SaisirChaine(f));
            New->Prix_Par_Jour = atof(SaisirChaine(f));
            New->Disponibilite = atoi(SaisirChaine(f));
            New->Taux_Tarf = atof(SaisirChaine(f));

            /*
                printf("%d\n",X->Id_Agence);
                printf("%s\n",X->NomAgence);
                printf("%s\n",X->VilleAgence);
                */
            //X->Agence_suivant=NULL;
            nouv_Vehicule = New;
            nouv_Vehicule->Vehicule_suivant = NULL;
            if (pos == 1)
            {

                list_Vehicules = nouv_Vehicule;
                current_Vehicule = list_Vehicules;
                current_Vehicule->Vehicule_suivant = NULL;
                pos++;
            }
            else
            {
                current_Vehicule->Vehicule_suivant = nouv_Vehicule;
                current_Vehicule = current_Vehicule->Vehicule_suivant;
                pos++;
            }
        }
        if (file_empty == 0)
        {
            return NULL;
        }
        fclose(f);
        return list_Vehicules;
    }
}
/*********************************************************************************/
void AfficherTousLesVehicules() // Afficher Tous les Agences
{
    printf("L'affichage de tous les Vehicules\n");
    Vehicule *AllVehicule = NULL;
    AllVehicule = getVehicule();
    Vehicule *New;
    New = AllVehicule;
    if (AllVehicule == NULL)
    {
        printf("Il n\'y a pas des Vehicules\n");
        return;
    }
    else
    {
        while (New != NULL)
        {

            printf("---------------------------------------\n");
            printf("\tId_Vehicule : %d\n", New->Id_Vehicule);
            printf("\tId_Type_Categorie :%d\n", New->Id_Type_Categorie);
            printf("\tId_Agence : %d\n", New->Id_Agence);
            printf("\tImmatricule : %s\n", New->Immatricule);
            printf("\tNbr_Places : %d\n", New->Nbr_Places);
            printf("\tPuissance_Fiscale : %s\n", New->Puissance_Fiscale);
            printf("\tModele : %s\n", New->Modele);
            printf("\tMarque : %s\n", New->Marque);
            printf("\tType de carburant : %s\n", New->Type_carburant);
            printf("\tPrix_Par_Jour : %f\n", New->Prix_Par_Jour);
            printf("\tDisponibilite : %d\n", New->Disponibilite);
            printf("\tTaux_Tarf : %f\n", New->Taux_Tarf);
            printf("---------------------------------------\n");

            New = New->Vehicule_suivant;
        }
        return;
    }
}
/******************************************************************************************/
void RefrechVehicule(Vehicule *list, char *file) // mis a jour le ficher Agences
{

    FILE *f = fopen(file, "w");
    if (f == NULL)
    {
        printf("Can\'t open the file");
        return;
    }
    else
    {

        if (list == NULL)
        {

            fprintf(f, "");
        }

        else
        {

            Vehicule *curent;
            curent = list;
            while (curent != NULL && curent->Vehicule_suivant != NULL)
            {
                fprintf(f, "%d:%d:%d:%s:%d:%s:%s:%s:%s:%f:%d:%f\n", curent->Id_Vehicule, curent->Id_Type_Categorie, curent->Id_Agence, curent->Immatricule, curent->Nbr_Places, curent->Puissance_Fiscale, curent->Modele, curent->Marque, curent->Type_carburant, curent->Prix_Par_Jour, curent->Disponibilite, curent->Taux_Tarf);

                curent = curent->Vehicule_suivant;
            }

            fprintf(f, "%d:%d:%d:%s:%d:%s:%s:%s:%s:%f:%d:%f", curent->Id_Vehicule, curent->Id_Type_Categorie, curent->Id_Agence, curent->Immatricule, curent->Nbr_Places, curent->Puissance_Fiscale, curent->Modele, curent->Marque, curent->Type_carburant, curent->Prix_Par_Jour, curent->Disponibilite, curent->Taux_Tarf);
        }
    }

    fclose(f);
    return;
}
/**********************************************************************************************/

/************************************************************************************************/
void deleteVehicule(int id) // Supprimer une Agence dapres son ID
{
    int choix = 3;
    Vehicule *AllVehicules = getVehicule();
    Vehicule *CVehicules;        // Curent Client
    Vehicule *PVehicules = NULL; // Previous Client
    int pos = 0;
    if (AllVehicules == NULL)
    {
        printf("impossible de supprimer car liste est vide\n");
        return;
    }
    else
    {
        CVehicules = AllVehicules;
        while (CVehicules != NULL)
        {
            pos++;
            if (CVehicules->Id_Vehicule == id)
            {
                if (PVehicules == NULL && CVehicules->Vehicule_suivant == NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));
                    if (choix == 1)
                    {
                        AllVehicules = NULL;
                        RefrechVehicule(AllVehicules, "Vehicules.txt");
                        printf("\nvous avez sauvgarder.\n");
                        return;
                    }
                    else if (choix == 0)
                    {
                        printf("\nvous n'avez pas sauvgarder.\n");
                        return;
                    }
                }
                else if (PVehicules == NULL && CVehicules->Vehicule_suivant != NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));

                    if (choix == 1)
                    {
                        AllVehicules = CVehicules->Vehicule_suivant;
                        RefrechVehicule(AllVehicules, "Vehicules.txt");
                        printf("vous avez sauvgarder.\n");
                        return;
                    }
                    else if (choix == 0)
                    {
                        printf("vous n'avez pas sauvgarder.\n");
                        return;
                    }
                }
                else
                {
                    if (CVehicules->Vehicule_suivant == NULL)
                    {

                        do
                        {
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d", &choix);
                        } while ((choix != 0) && (choix != 1));
                        if (choix == 1)
                        {
                            PVehicules->Vehicule_suivant = NULL;
                            RefrechVehicule(AllVehicules, "Vehicules.txt");
                            printf("vous avez sauvgarder.\n");
                            return;
                        }
                        else if (choix == 0)
                        {
                            printf("vous n'avez pas sauvgarder.\n");
                            return;
                        }
                    }
                    else
                    {

                        do
                        {
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d", &choix);
                        } while ((choix != 0) && (choix != 1));
                        if (choix == 1)
                        {
                            PVehicules->Vehicule_suivant = CVehicules->Vehicule_suivant;
                            RefrechVehicule(AllVehicules, "Vehicules.txt");
                            printf("vous avez sauvgarder.\n");
                            return;
                        }
                        else if (choix == 0)
                        {
                            printf("vous n'avez pas sauvgarder.\n");
                            return;
                        }
                    }
                }
            }
            PVehicules = CVehicules;
            CVehicules = CVehicules->Vehicule_suivant;
        }
        if (pos != 0)
        {
            printf("Cette Vehicule n\'existe pas");
        }
        else
        {
            printf("impossible de supprimer car liste Vehicule est vide");
        }
        return;
    }
}

/****************************************************************************************************************************/
void ChercherVehicule()
{
    Vehicule *All;
    Vehicule *New;
    int id, choix = 0, occur = 0;
    char Nom[20];

    All = getVehicule();
    New = All;
    if (New == NULL)
    {
        printf("\nLa liste est vide\n");
        return;
    }

    printf("-----------recherche de Vehicule---------------------\n");
    printf("\nRecherche par id_vehicule : 1\n");
    printf("Recherche par id_Type_Categorie : 2\n");
    printf("Recherche par id_Agence : 3\n");
    printf("recherche par immatricule : 4\n");

    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2 && choix != 3 && choix != 4);
    switch (choix)
    {
    case 1:
        printf("\nDonner id de  Vehicule que vous cherchez :");
        scanf("%d", &id);
        getchar();
        while (New != NULL)
        {
            if (New->Id_Vehicule == id)
            {
                printf("---------------------------------------\n");
                printf("\tId_Vehicule : %d\n", New->Id_Vehicule);
                printf("\tId_Type_Categorie :%d\n", New->Id_Type_Categorie);
                printf("\tId_Agence : %d\n", New->Id_Agence);
                printf("\tImmatricule : %s\n", New->Immatricule);
                printf("\tNbr_Places : %d\n", New->Nbr_Places);
                printf("\tPuissance_Fiscale : %s\n", New->Puissance_Fiscale);
                printf("\tModele : %s\n", New->Modele);
                printf("\tMarque : %s\n", New->Marque);
                printf("\tType de carburant : %s\n", New->Type_carburant);
                printf("\tPrix_Par_Jour : %f\n", New->Prix_Par_Jour);
                printf("\tDisponibilite : %d\n", New->Disponibilite);
                printf("\tTaux_Tarf : %f\n", New->Taux_Tarf);
                printf("---------------------------------------\n");
                return;
            }
            New = New->Vehicule_suivant;
        }
        printf("\nCette id_vehicule n\'existe pas\n");
        return;
    case 2:
        printf("\nDonner le id_type_categorie que vous cherchez  :");
        scanf("%d", &id);
        while (New != NULL)
        {
            if (New->Id_Type_Categorie == id)
            {
                occur++;
                printf("---------------------------------------\n");
                printf("\tId_Vehicule : %d\n", New->Id_Vehicule);
                printf("\tId_Type_Categorie :%d\n", New->Id_Type_Categorie);
                printf("\tId_Agence : %d\n", New->Id_Agence);
                printf("\tImmatricule : %s\n", New->Immatricule);
                printf("\tNbr_Places : %d\n", New->Nbr_Places);
                printf("\tPuissance_Fiscale : %s\n", New->Puissance_Fiscale);
                printf("\tModele : %s\n", New->Modele);
                printf("\tMarque : %s\n", New->Marque);
                printf("\tType de carburant : %s\n", New->Type_carburant);
                printf("\tPrix_Par_Jour : %f\n", New->Prix_Par_Jour);
                printf("\tDisponibilite : %d\n", New->Disponibilite);
                printf("\tTaux_Tarf : %f\n", New->Taux_Tarf);
                printf("---------------------------------------\n");
            }
            New = New->Vehicule_suivant;
        }
        if (occur == 0)
        {
            printf("aucune Vehicule associe a cet id_type_categorie");
        }
        printf("\nRecherche termine\n");
        return;

    case 3:
        printf("\nDonner le id_agence que vous cherchez  :");
        scanf("%d", &id);
        while (New != NULL)
        {
            if (New->Id_Agence == id)
            {
                occur++;
                printf("---------------------------------------\n");
                printf("\tId_Vehicule : %d\n", New->Id_Vehicule);
                printf("\tId_Type_Categorie :%d\n", New->Id_Type_Categorie);
                printf("\tId_Agence : %d\n", New->Id_Agence);
                printf("\tImmatricule : %s\n", New->Immatricule);
                printf("\tNbr_Places : %d\n", New->Nbr_Places);
                printf("\tPuissance_Fiscale : %s\n", New->Puissance_Fiscale);
                printf("\tModele : %s\n", New->Modele);
                printf("\tMarque : %s\n", New->Marque);
                printf("\tType de carburant : %s\n", New->Type_carburant);
                printf("\tPrix_Par_Jour : %f\n", New->Prix_Par_Jour);
                printf("\tDisponibilite : %d\n", New->Disponibilite);
                printf("\tTaux_Tarf : %f\n", New->Taux_Tarf);
                printf("---------------------------------------\n");
            }
            New = New->Vehicule_suivant;
        }
        if (occur == 0)
        {
            printf("aucune Vehicule associe a cet id_agence");
        }
        printf("\nRecherche termine\n");
        return;
    case 4:
        printf("\nDonner id immatricule de  Vehicule que vous cherchez :");
        gets(Nom);
        getchar();
        while (New != NULL)
        {
            if (strcmp(New->Immatricule, Nom) == 0)
            {
                printf("---------------------------------------\n");
                printf("\tId_Vehicule : %d\n", New->Id_Vehicule);
                printf("\tId_Type_Categorie :%d\n", New->Id_Type_Categorie);
                printf("\tId_Agence : %d\n", New->Id_Agence);
                printf("\tImmatricule : %s\n", New->Immatricule);
                printf("\tNbr_Places : %d\n", New->Nbr_Places);
                printf("\tPuissance_Fiscale : %s\n", New->Puissance_Fiscale);
                printf("\tModele : %s\n", New->Modele);
                printf("\tMarque : %s\n", New->Marque);
                printf("\tType de carburant : %s\n", New->Type_carburant);
                printf("\tPrix_Par_Jour : %f\n", New->Prix_Par_Jour);
                printf("\tDisponibilite : %d\n", New->Disponibilite);
                printf("\tTaux_Tarf : %f\n", New->Taux_Tarf);
                printf("---------------------------------------\n");
                return;
            }
            New = New->Vehicule_suivant;
        }
        printf("\nCette id_vehicule n\'existe pas\n");
        return;
    }
}

/**********************************************************************************************************************/
int Modifier_Disponibiliter_Vehicule(int id_vehicule, int dispo) // Supprimer une Agence dapres son ID
{
    Vehicule *AllVehicules = getVehicule();
    Vehicule *CVehicules;                // Curent Client
    Vehicule *PVehicules = AllVehicules; // Previous Client
    int pos = 0;
    if (AllVehicules == NULL)
    {
        printf("impossible de modifier car liste est vide\n");
        return 0;
    }
    else
    {
        CVehicules = AllVehicules;
        while (CVehicules != NULL)
        {
            pos++;
            if (CVehicules->Id_Vehicule == id_vehicule)
            {
                CVehicules->Disponibilite = dispo;

                RefrechVehicule(PVehicules, "Vehicules.txt");
                return 1;
                break;
            }

            CVehicules = CVehicules->Vehicule_suivant;
        }
    }

    return 0;
}

Vehicule *get_vehicule_par_id(int id_Vehicule)
{

    Vehicule *All = getVehicule();
    Vehicule *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (A->Id_Vehicule == id_Vehicule)
        {

            occur++;
            return A;
        }

        A = A->Vehicule_suivant;
    }

    if (file_empty == 1 || occur == 0)
    {

        return NULL;
    }

    return NULL;
}
