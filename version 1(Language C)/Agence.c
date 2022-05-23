#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Agence.h"
#include "Common_functions.h"

/*********************************************************************************/

Agence *list_agence = NULL;

/*********************************************************************************
int is_agences_empty(struct Agences *A) //Verifier si la liste est vide
{
	if(A == NULL)
		return 1;
	return 0;

}

//struct Agence * getAgences();
/*********************************************************************************
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
*********************************************************************************/

int Agence_existe(char *Nom, char *Ville) // existance d'une Agence par ses informations
{
    Agence *All = getAgences();
    Agence *A;
    A = All;

    while (A != NULL && (strcmp(A->NomAgence, Nom) != 0 || strcmp(A->VilleAgence, Ville) != 0))
    {
        A = A->Agence_suivant;
    }

    if (A == NULL)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun agence correspond trouver\n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }
    else
    {
        printf("-----------------------------------------------\n");
        printf("ville est trouvé \n");
        printf("-----------------------------------------------\n");

        printf("id agence : %d\n", A->Id_Agence);
        printf("Nom agence : %s\n", A->NomAgence);
        printf("Nom ville : %s\n", A->VilleAgence);

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    return 0;
}
/*********************************************************************************/

/*********************************************************************************/
int Agences_existe_par_nom(char *Nom) // existance d'une Agence par ses informations
{
    Agence *All = getAgences();
    Agence *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (strcmp(A->NomAgence, Nom) == 0)
        {

            occur++;
            printf("-----------------------------------------------\n");

            printf("id agence : %d\n", A->Id_Agence);
            printf("Nom agence : %s\n", A->NomAgence);
            printf("Nom ville : %s\n", A->VilleAgence);
        }

        A = A->Agence_suivant;
    }

    if (file_empty == 1)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun agence  trouver , liste deja vide \n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    else if (occur == 0)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun agence correspond trouver\n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    return 0;
}
/*********************************************************************************/

/*********************************************************************************/
int Agences_existe_par_ville(char *Ville) // existance d'une Agence par ses informations
{
    Agence *All = getAgences();
    Agence *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (strcmp(A->VilleAgence, Ville) == 0)
        {

            occur++;
            printf("-----------------------------------------------\n");

            printf("id agence : %d\n", A->Id_Agence);
            printf("Nom agence : %s\n", A->NomAgence);
            printf("Nom ville : %s\n", A->VilleAgence);
        }

        A = A->Agence_suivant;
    }

    if (file_empty == 1)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun agence  trouver , liste deja vide \n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    else if (occur == 0)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun agence correspond trouver\n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    return 0;
}
/*********************************************************************************/

/*********************************************************************************/
int Agences_existe_par_id_agence(int id_agence) // existance d'une Agence par ses informations
{
    Agence *All = getAgences();
    Agence *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (A->Id_Agence == id_agence)
        {

            occur++;
            return 1;
        }

        A = A->Agence_suivant;
    }

    if (file_empty == 1 || occur == 0)
    {

        return 0;
    }
}
/*********************************************************************************/

void AddAgence()
{
    FILE *f = fopen("Agences.txt", "a");
    Agence *New;
    New = (Agence *)malloc(sizeof(Agence));
    New->Id_Agence = getId("Agences.txt") + 1;
    printf("Donner le nom de l'agence : ");
    scanf("%s", New->NomAgence);
    printf("Donner la ville de l'agence : ");
    scanf("%s", New->VilleAgence);
    New->Agence_suivant = NULL;

    if (FileEmpty(f) == 1)
    {
        fprintf(f, "%d:%s:%s", New->Id_Agence, New->NomAgence, New->VilleAgence);
        printf("%s est devenu une Agence", New->NomAgence);
        list_agence = New;
        fclose(f);
    }
    else
    {

        fprintf(f, "\n%d:%s:%s", New->Id_Agence, New->NomAgence, New->VilleAgence);
        printf("%s est devenu une Agence", New->NomAgence);
        list_agence = AddAgenceToList(New);
        fclose(f);
    }

    return;
}

/*********************************************************************************/
Agence *AddAgenceToList(Agence *new_Agence) // Ajouter une Agence a la list chainee
{
    if (is_agences_empty(list_agence) == 1)
    {
        list_agence = new_Agence;
        return list_agence;
    }
    else
    {
        Agence *pt;

        pt = list_agence;
        while (pt->Agence_suivant != NULL)
        {
            pt = pt->Agence_suivant;
        }
        pt->Agence_suivant = new_Agence;
        return list_agence;
    }
}
/*********************************************************************************/
char *SaisirChaine(FILE *fp)
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


int is_agences_empty(Agence *A) //Verifier si la liste est vide
{
    if (A == NULL)
        return 1;
    return 0;
}
int getId(char *File) // Genere l'id de nouveau Client
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

/*********************************************************************************/
Agence *getAgences() // Generer une liste chainee dapres le fichier Agences.txt
{
    unsigned int id;
    char *Nom;
    char *Ville;

    FILE *f = fopen("Agences.txt", "r");
    if (f == NULL)
    {
        printf("could not open the file\n");
    }
    else
    {
        Agence *current_agence = NULL, *nouv_agence = NULL;
        current_agence = list_agence;
        Agence *X;
        int file_empty = 1;
        int pos = 1;

        while (!feof(f))
        {
            X = (Agence *)malloc(sizeof(Agence));
            file_empty = 0;
            id = atoi(SaisirChaine(f));
            Nom = SaisirChaine(f);
            Ville = SaisirChaine(f);
            X->Id_Agence = id;
            strcpy(X->NomAgence, Nom);
            strcpy(X->VilleAgence, Ville);
            /*
                printf("%d\n",X->Id_Agence);
                printf("%s\n",X->NomAgence);
                printf("%s\n",X->VilleAgence);
                */
            //X->Agence_suivant=NULL;
            nouv_agence = X;
            nouv_agence->Agence_suivant = NULL;
            if (pos == 1)
            {

                list_agence = nouv_agence;
                current_agence = list_agence;
                current_agence->Agence_suivant = NULL;
                pos++;
            }
            else
            {
                current_agence->Agence_suivant = nouv_agence;
                current_agence = current_agence->Agence_suivant;
                pos++;
            }

            //list_agence = AddAgenceToList(X);
            //X=(Agence*)malloc(sizeof(Agence));
        }
        if (file_empty == 1)
        {
            return NULL;
        }
        fclose(f);

        return list_agence;
    }
}
/*********************************************************************************/
void AfficherTousLesAgences() // Afficher Tous les Agences
{
    printf("L'affichage de tous les Agences\n");
    Agence *AllAgence = getAgences("Agences.txt");
    Agence *A1;
    A1 = AllAgence;
    if (AllAgence == NULL)
    {
        printf("Il n\'y a pas des Agences");
        return;
    }
    else
    {
        while (A1 != NULL)
        {

            printf("--------------------------------------");
            printf("\nId:\t\t%i\n", A1->Id_Agence);
            printf("Nom:\t\t%s\n", A1->NomAgence);
            printf("Nom:\t\t%s\n", A1->VilleAgence);

            A1 = A1->Agence_suivant;
        }
        return;
    }
}
/******************************************************************************************/
void RefrechAgence(Agence *list, char *file) // mis a jour le ficher Agences
{
    if (list == NULL)
    {
        printf("la list est vide");
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

            Agence *curent;
            curent = list;
            while (curent != NULL && curent->Agence_suivant != NULL)
            {
                fprintf(f, "%d:", curent->Id_Agence);
                fprintf(f, "%s:", curent->NomAgence);
                fprintf(f, "%s\n", curent->VilleAgence);
                curent = curent->Agence_suivant;
            }

            fprintf(f, "%d:", curent->Id_Agence);
            fprintf(f, "%s:", curent->NomAgence);
            fprintf(f, "%s", curent->VilleAgence);
        }

        fclose(f);
    }
}
/**********************************************************************************************/

void changerInfoAgence(int id) // modifier les info une Agence dapres son ID
{
    Agence *AllAgences = getAgences("Agences.txt");
    int choix;
    Agence *A1;
    A1 = AllAgences;
    if (A1 == NULL)
    {
        printf("Il n\'y a pas des Agences");
        return;
    }
    else
    {
        while (A1 != NULL)
        {
            if (A1->Id_Agence == id)
            {
                printf("\nChoisissez ce que vous voulez changer:\n1 - Le nom\n2 - La ville\n3");
                scanf("%i", &choix);
                getchar();
                switch (choix)
                {
                case 1: //si jamais on fait des erreure au niveau de la saisir du nom
                    printf("Inserer le nouveau nom: ");
                    gets(A1->NomAgence);

                    break;
                case 2: //si jamais on fait des erreure au niveau de la saisir du Ville
                    printf("Inserer la nouvelle Ville: ");
                    gets(A1->VilleAgence);
                    break;
                }
                printf("\nLe nouveau profil est : \n");
                printf("\nId:\t\t%i\n", A1->Id_Agence);
                printf("\nNom:\t\t%s\n", A1->NomAgence);
                printf("\nVille \t\t%s\n", A1->VilleAgence);
                do
                {
                    printf("voulez vous sauvgarder les changements ? \n");
                    printf("entez 1 pour valider ou 0 sinon : ");
                    scanf("%d", &choix);
                } while ((choix != 0) && (choix != 1));
                if (choix == 1)
                {
                    RefrechAgence(AllAgences, "Agences.txt");
                    printf("vous avez sauvgarder.\n");
                    return;
                }
                else if (choix == 0)
                {
                    printf("vous n'avez pas sauvgarder.\n");
                    return;
                }
            }
            A1 = A1->Agence_suivant;
        }
        printf("Cette Agence n'existe pas n\'existe pas");
        return;
    }
}
/************************************************************************************************/
void deleteAgence(int id) // Supprimer une Agence dapres son ID
{
    int choix = 3;
    Agence *AllAgences = getAgences("Agences.txt");
    Agence *CAgences;        // Curent Client
    Agence *PAgences = NULL; // Previous Client

    if (AllAgences == NULL)
    {
        printf("Il n\'y a pas des Agences");
        return;
    }
    else
    {
        CAgences = AllAgences;
        while (CAgences != NULL)
        {
            if (CAgences->Id_Agence == id)
            {
                if (PAgences == NULL && CAgences->Agence_suivant == NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));
                    if (choix == 1)
                    {
                        AllAgences = NULL;
                        RefrechAgence(AllAgences, "Agences.txt");
                        printf("\nvous avez sauvgarder.\n");
                        return;
                    }
                    else if (choix == 0)
                    {
                        printf("\nvous n'avez pas sauvgarder.\n");
                        return;
                    }
                }
                else if (PAgences == NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));

                    if (choix == 1)
                    {
                        AllAgences = CAgences->Agence_suivant;
                        RefrechAgence(AllAgences, "Agences.txt");
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
                    if (CAgences->Agence_suivant == NULL)
                    {

                        do
                        {
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d", &choix);
                        } while ((choix != 0) && (choix != 1));
                        if (choix == 1)
                        {
                            PAgences->Agence_suivant = NULL;
                            RefrechAgence(AllAgences, "Agences.txt");
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
                            PAgences->Agence_suivant = CAgences->Agence_suivant;
                            RefrechAgence(AllAgences, "Agences.txt");
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
            PAgences = CAgences;
            CAgences = CAgences->Agence_suivant;
        }
        printf("Cette Agence n\'existe pas");
        return;
    }
}

/****************************************************************************************************************************/
void ChercherAgence()
{
    Agence *All;
    Agence *A;
    int id, choix = 0;
    char *Nom;
    char *Ville;

    All = getAgences("Agences.txt");
    A = All;
    if (A == NULL)
    {
        printf("\nLa liste est vide\n");
        return;
    }

    printf("\nRecherche par id : 1\n");
    printf("Recherche par Nom : 2\n");
    printf("Recherche par Ville : 3\n");
    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2 && choix != 3);
    switch (choix)
    {
    case 1:
        printf("\nDonner id d'agece que vous cherchez :");
        scanf("%d", &id);
        getchar();
        while (A != NULL)
        {
            if (A->Id_Agence == id)
            {
                printf("\n--------------------------------\n");
                printf("Id:\t\t%i\n", A->Id_Agence);
                printf("Nom:\t\t%s\n", A->NomAgence);
                printf("Ville \t\t%s\n", A->VilleAgence);
                printf("--------------------------------\n");
                return;
            }
            A = A->Agence_suivant;
        }
        printf("\nCette id n\'existe pas\n");
        return;
    case 2:
        printf("\nDonner le nom d'agence que vous cherchez :");
        Nom = SaisirChaine(stdin);
        while (A != NULL)
        {
            if (strcmp(A->NomAgence, Nom) == 0)
            {
                printf("\n--------------------------------\n");
                printf("Id:\t\t%i\n", A->Id_Agence);
                printf("Nom:\t\t%s\n", A->NomAgence);
                printf("Ville \t\t%s\n", A->VilleAgence);
                printf("--------------------------------\n");
            }
            A = A->Agence_suivant;
        }
        printf("\nRecherche termine\n");
        return;
    case 3:
        printf("\nDonner la ville d'agence que vous cherchez :");
        Ville = SaisirChaine(stdin);
        while (A != NULL)
        {
            if (strcmp(A->VilleAgence, Ville) == 0)
            {
                printf("\n--------------------------------\n");
                printf("Id:\t\t%i\n", A->Id_Agence);
                printf("Nom:\t\t%s\n", A->NomAgence);
                printf("Ville \t\t%s\n", A->VilleAgence);
                printf("--------------------------------\n");
            }
            A = A->Agence_suivant;
        }
        printf("\nRecherche termine\n");
        return;
    }
}

/**********************************************************************************************************************/
