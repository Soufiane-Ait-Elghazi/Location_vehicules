/**********************************************************************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Common_functions.h"
#include "Type.h"
/**********************************************************************************************************************************************/
 struct Type
{
    int Id_Type;
    char NomType[20];
    struct Type *Type_suivant;
};
/**********************************************************************************************************************************************/

Type *list_Types = NULL;

int is_type_empty(Type *A) //Verifier si la liste est vide
{
    if (A == NULL)
        return 1;
    return 0;
}
/*********************************************************************************/
int Type_existe_par_nom(char *Nom) // existance d'une Agence par ses informations
{
    Type *All = getType();
    Type *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (strcmp(A->NomType, Nom) == 0)
        {

            occur++;
            printf("-----------------------------------------------\n");

            printf("id Type : %d\n", A->Id_Type);
            printf("Nom Type : %s\n", A->NomType);

            return 1;
        }

        A = A->Type_suivant;
    }

    if (file_empty == 1)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun Type  trouver , liste deja vide \n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    else if (occur == 0)
    {

        printf("-----------------------------------------------\n");
        printf(" aucun Type correspond trouver\n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    }

    return 0;
}
/*********************************************************************************/

int Type_existe_par_id_Type(int id_Type) // existance d'une Type par ses informations
{
    Type *All = getType();
    Type *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (A->Id_Type == id_Type)
        {

            occur++;
            return 1;
        }

        A = A->Type_suivant;
    }

    if (file_empty == 1 || occur == 0)
    {

        return 0;
    }

    return 0;
}
/*********************************************************************************/

void AddType()
{
    FILE *f = fopen("Types.txt", "a");
    Type *New;
    New = (Type *)malloc(sizeof(Type));
    New->Id_Type = getId("Types.txt") + 1;
    printf("Donner le nom de Type au maximum 19 caractere : ");
    gets(New->NomType);
    New->Type_suivant = NULL;

    if (FileEmpty(f) == 1)
    {
        fprintf(f, "%d:%s", New->Id_Type, New->NomType);
        printf("%s est devenu une Type", New->NomType);
        list_Types = New;
        fclose(f);
    }
    else
    {
        fprintf(f, "\n%d:%s", New->Id_Type, New->NomType);
        printf("%s est devenu une Type", New->NomType);
        list_Types = AddTypeToList(New);
        fclose(f);
    }

    return;
}

/*********************************************************************************/
Type *AddTypeToList(Type *new_Type) // Ajouter une Agence a la list chainee
{
    if (is_type_empty(list_Types) == 1)
    {
        list_Types = new_Type;
        return list_Types;
    }
    else
    {
        Type *pt;

        pt = list_Types;
        while (pt->Type_suivant != NULL)
        {
            pt = pt->Type_suivant;
        }
        pt->Type_suivant = new_Type;
        return list_Types;
    }
}

/*********************************************************************************/

Type *getType() // Generer une liste chainee dapres le fichier Agences.txt
{
    unsigned int id;
    char *Nom;

    FILE *f = fopen("Types.txt", "r");
    if (f == NULL)
    {
        printf("could not open the file\n");
        return NULL;
    }
    else
    {
        Type *current_Type = NULL, *nouv_Type = NULL;
        current_Type = list_Types;
        Type *X;
        int file_empty = 1;
        int pos = 1;

        while (!feof(f))
        {
            X = (Type *)malloc(sizeof(Type));
            id = atoi(SaisirChaine(f));
            if (id == 0)
            {
                file_empty = id;
                break;
            }
            Nom = SaisirChaine(f);
            X->Id_Type = id;
            strcpy(X->NomType, Nom);
            nouv_Type = X;
            nouv_Type->Type_suivant = NULL;
            if (pos == 1)
            {
                list_Types = nouv_Type;
                current_Type = list_Types;
                current_Type->Type_suivant = NULL;
                pos++;
            }
            else
            {
                current_Type->Type_suivant = nouv_Type;
                current_Type = current_Type->Type_suivant;
                pos++;
            }
        }
        if (file_empty == 0)
        {
            return NULL;
        }
        fclose(f);
        return list_Types;
    }
}
/*********************************************************************************/
void AfficherTousLesTypes() // Afficher Tous les Agences
{
    printf("L'affichage de tous les Types\n");
    Type *AllType = NULL;
    AllType = getType();
    Type *A1;
    A1 = AllType;
    if (AllType == NULL)
    {
        printf("Il n\'y a pas des Types\n");
        return;
    }
    else
    {
        while (A1 != NULL)
        {

            printf("--------------------------------------\n");
            printf("id Type : %d\n", A1->Id_Type);
            printf("Nom: %s\n", A1->NomType);

            A1 = A1->Type_suivant;
        }
        return;
    }
}
/******************************************************************************************/
void RefrechType(Type *list, char *file) // mis a jour le ficher Agences
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

            Type *curent;
            curent = list;
            while (curent != NULL && curent->Type_suivant != NULL)
            {
                fprintf(f, "%d:", curent->Id_Type);
                fprintf(f, "%s\n", curent->NomType);
                curent = curent->Type_suivant;
            }

            fprintf(f, "%d:", curent->Id_Type);
            fprintf(f, "%s", curent->NomType);
        }
    }

    fclose(f);
    return;
}
/**********************************************************************************************/


/************************************************************************************************/
void deleteType(int id) // Supprimer une Agence dapres son ID
{
    int choix = 3;
    Type *AllTypes = getType();
    Type *CTypes;        // Curent Client
    Type *PTypes = NULL; // Previous Client
    int pos = 0;
    if (AllTypes == NULL)
    {
        printf("impossible de supprimer car liste est vide\n");
        return;
    }
    else
    {
        CTypes = AllTypes;
        while (CTypes != NULL)
        {
            pos++;
            if (CTypes->Id_Type == id)
            {
                if (PTypes == NULL && CTypes->Type_suivant == NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));
                    if (choix == 1)
                    {
                        AllTypes = NULL;
                        RefrechType(AllTypes, "Types.txt");
                        printf("\nvous avez sauvgarder.\n");
                        return;
                    }
                    else if (choix == 0)
                    {
                        printf("\nvous n'avez pas sauvgarder.\n");
                        return;
                    }
                }
                else if (PTypes == NULL && CTypes->Type_suivant != NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));

                    if (choix == 1)
                    {
                        AllTypes = CTypes->Type_suivant;
                        RefrechType(AllTypes, "Types.txt");
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
                    if (CTypes->Type_suivant == NULL)
                    {

                        do
                        {
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d", &choix);
                        } while ((choix != 0) && (choix != 1));
                        if (choix == 1)
                        {
                            PTypes->Type_suivant = NULL;
                            RefrechType(AllTypes, "Types.txt");
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
                            PTypes->Type_suivant = CTypes->Type_suivant;
                            RefrechType(AllTypes, "Types.txt");
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
            PTypes = CTypes;
            CTypes = CTypes->Type_suivant;
        }
        if (pos != 0)
        {
            printf("Cette Type n\'existe pas");
        }
        else
        {
            printf("impossible de supprimer car liste Type est vide");
        }
        return;
    }
}

/****************************************************************************************************************************/
void ChercherType()
{
    Type *All;
    Type *A;
    int id, choix = 0, occur = 0;
    char Nom[20];

    All = getType();
    A = All;
    if (A == NULL)
    {
        printf("\nLa liste est vide\n");
        return;
    }

    printf("-----------rechercher de Type---------------------\n");
    printf("\nRecherche par id : 1\n");
    printf("Recherche par Nom : 2\n");
    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2);
    switch (choix)
    {
    case 1:
        printf("\nDonner id de  Type que vous cherchez :");
        scanf("%d", &id);
        getchar();
        while (A != NULL)
        {
            if (A->Id_Type == id)
            {
                printf("\n--------------------------------\n");
                printf("Id:\t\t%i\n", A->Id_Type);
                printf("Nom:\t\t%s\n", A->NomType);
                printf("--------------------------------\n");
                return;
            }
            A = A->Type_suivant;
        }
        printf("\nCette id n\'existe pas\n");
        return;
    case 2:
        printf("\nDonner le nom de Type que vous cherchez au maximum 20 caractere :");
        gets(Nom);
        while (A != NULL)
        {
            if (strcmp(A->NomType, Nom) == 0)
            {
                occur++;
                printf("\n--------------------------------\n");
                printf("Id:\t\t%i\n", A->Id_Type);
                printf("Nom:\t\t%s\n", A->NomType);
                printf("--------------------------------\n");
                break;
            }
            A = A->Type_suivant;
        }
        if (occur == 0)
        {
            printf("aucune Type associe a cet nom");
        }
        printf("\nRecherche termine\n");
        return;
    }
}

/**********************************************************************************************************************/
