
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Type.h"
#include "Categorie.h"
#include "Type_Categorie.h"
#include "Common_functions.h"

/**********************************************************************************************************************************************/

/**********************************************************************************************************************************************/

Type_Categorie *list_Type_Categories = NULL;

/*
int is_empty(struct Type_Categorie *A) //Verifier si la liste est vide
{
	if(A == NULL)
		return 1;
	return 0;

}
*/
//struct Agence * getAgences();
/*********************************************************************************/
int is_type_categorie_empty(Type_Categorie *A) //Verifier si la liste est vide
{
    if (A == NULL)
        return 1;
    return 0;
}
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
int Type_Categorie_existe_par_id_Type_Categorie(int id) // existance d'une Agence par ses informations
{
    Type_Categorie *All = getType_Categorie();
    Type_Categorie *A;
    A = All;
    int occur = 0;
    int file_empty = 1;

    while (A != NULL)
    {
        file_empty = 0;
        if (A->Id_Type_Categorie == id)
        {
            return 1;
        }

        A = A->Type_Categorie_suivant;
    }
    return 0;
}
/*********************************************************************************/

/*********************************************************************************/
int TC_existe_par_id_TC(int id_type,int id_categorie) // existance d'une Agence par ses informations
{
    Type_Categorie *All = getType_Categorie();
    Type_Categorie *A;
    A = All;

    while (A != NULL)
    {
        if (A->Id_Type == id_type && A->Id_Categorie == id_categorie)
        {
            return 1;
        }

        A = A->Type_Categorie_suivant;
    }

    return 0;
}
/*********************************************************************************/

/*********************************************************************************/

/*********************************************************************************/

void AddType_Categorie(int id_type,int id_categorie)
{
    FILE *f = fopen("Type_Categories.txt", "a");
    Type_Categorie *New;
    int id_TC_existe, id_type_existe, id_categorie_existe;
    id_type_existe = Type_existe_par_id_Type(id_type);
    id_categorie_existe = Categorie_existe_par_id_Categorie(id_categorie);
    id_TC_existe = TC_existe_par_id_TC(id_type,id_categorie);

    if(id_categorie_existe == 1 && id_type_existe == 1 && id_TC_existe == 0)

   {
    New = (Type_Categorie *)malloc(sizeof(Type_Categorie));
    New->Id_Type_Categorie = getId("Type_Categories.txt") + 1;
    New->Id_Type = id_type;
    New->Id_Categorie = id_categorie;
    New->Type_Categorie_suivant = NULL;
    if (FileEmpty(f) == 1)
    {
        fprintf(f, "%d:%d:%d", New->Id_Type_Categorie, New->Id_Type, New->Id_Categorie);
        printf("%d est devenu une Type_Categorie", New->Id_Type_Categorie);
        list_Type_Categories = New;
        fclose(f);
    }
    else
    {

        fprintf(f,"\n%d:%d:%d", New->Id_Type_Categorie, New->Id_Type, New->Id_Categorie);
        printf("%d est devenu une Type_Categorie", New->Id_Type_Categorie);
        list_Type_Categories = AddType_CategorieToList(New);
        fclose(f);
    }

    }

    else {
        printf("id_type et id_categorie deja existe dan type_categorie ou l'un des deux n'existe pas sur fichier type et fichier categorie");
    }


    return;
}

/*********************************************************************************/
Type_Categorie *AddType_CategorieToList(Type_Categorie *new_Type_Categorie) // Ajouter une Agence a la list chainee
{
    if (is_type_categorie_empty(list_Type_Categories) == 1)
    {
        list_Type_Categories = new_Type_Categorie;
        return list_Type_Categories;
    }
    else
    {
        Type_Categorie *pt;

        pt = list_Type_Categories;
        while (pt->Type_Categorie_suivant != NULL)
        {
            pt = pt->Type_Categorie_suivant;
        }
        pt->Type_Categorie_suivant = new_Type_Categorie;
        return list_Type_Categories;
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
Type_Categorie *getType_Categorie() // Generer une liste chainee dapres le fichier Agences.txt
{
    unsigned int id_type_categorie;
    unsigned int id_type;
    unsigned int id_categorie;

    FILE *f = fopen("Type_Categories.txt", "r");
    if (f == NULL)
    {
        printf("could not open the file\n");
        return NULL;
    }
    else
    {
        Type_Categorie *current_Type_Categorie = NULL, *nouv_Type_Categorie = NULL;
        current_Type_Categorie = list_Type_Categories;
        Type_Categorie *X;
        int file_empty = 1;
        int pos = 1;

        while (!feof(f))
        {
            X = (Type_Categorie *)malloc(sizeof(Type_Categorie));
            id_type_categorie = atoi(SaisirChaine(f));
            id_type = atoi(SaisirChaine(f));
            id_categorie = atoi(SaisirChaine(f));
            if (id_type_categorie == 0)
            {
                file_empty = id_type_categorie;
                break;
            }
            X->Id_Type_Categorie = id_type_categorie;
            X->Id_Type = id_type;
            X->Id_Categorie = id_categorie;

            /*
                printf("%d\n",X->Id_Agence);
                printf("%s\n",X->NomAgence);
                printf("%s\n",X->VilleAgence);
                */
            //X->Agence_suivant=NULL;
            nouv_Type_Categorie = X;
            nouv_Type_Categorie->Type_Categorie_suivant = NULL;
            if (pos == 1)
            {

                list_Type_Categories = nouv_Type_Categorie;
                current_Type_Categorie = list_Type_Categories;
                current_Type_Categorie->Type_Categorie_suivant = NULL;
                pos++;
            }
            else
            {
                current_Type_Categorie->Type_Categorie_suivant = nouv_Type_Categorie;
                current_Type_Categorie = current_Type_Categorie->Type_Categorie_suivant;
                pos++;
            }
        }
        if (file_empty == 0)
        {
            return NULL;
        }
        fclose(f);
        return list_Type_Categories;
    }
}
/*********************************************************************************/
void AfficherTousLesType_Categories() // Afficher Tous les Agences
{
    printf("L'affichage de tous les Type_Categories\n");
    Type_Categorie *AllType_Categorie = NULL;
    AllType_Categorie = getType_Categorie();
    Type_Categorie *A1;
    A1 = AllType_Categorie;
    if (AllType_Categorie == NULL)
    {
        printf("Il n\'y a pas des Type_Categories\n");
        return;
    }
    else
    {
        while (A1 != NULL)
        {

            printf("--------------------------------------\n");
            printf("id Type_Categorie : %d\n", A1->Id_Type_Categorie);
            printf("Nom: %d\n", A1->Id_Categorie);

            A1 = A1->Type_Categorie_suivant;
        }
        return;
    }
}
/******************************************************************************************/
void RefrechType_Categorie(Type_Categorie *list, char *file) // mis a jour le ficher Agences
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

            Type_Categorie *curent;
            curent = list;
            while (curent != NULL && curent->Type_Categorie_suivant != NULL)
            {
                fprintf(f, "%d:%d:%d\n", curent->Id_Type_Categorie,curent->Id_Type,curent->Id_Categorie);
                curent = curent->Type_Categorie_suivant;
            }

                fprintf(f, "%d:%d:%d", curent->Id_Type_Categorie, curent->Id_Type, curent->Id_Categorie);
        }
    }

    fclose(f);
    return;
}
/**********************************************************************************************/


/************************************************************************************************/
void deleteType_Categorie(int id) // Supprimer une Agence dapres son ID
{
    int choix = 3;
    Type_Categorie *AllType_Categories = getType_Categorie();
    Type_Categorie *CType_Categories;        // Curent Client
    Type_Categorie *PType_Categories = NULL; // Previous Client
    int pos = 0;
    if (AllType_Categories == NULL)
    {
        printf("impossible de supprimer car liste est vide\n");
        return;
    }
    else
    {
        CType_Categories = AllType_Categories;
        while (CType_Categories != NULL)
        {
            pos++;
            if (CType_Categories->Id_Type_Categorie == id)
            {
                if (PType_Categories == NULL && CType_Categories->Type_Categorie_suivant == NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));
                    if (choix == 1)
                    {
                        AllType_Categories = NULL;
                        RefrechType_Categorie(AllType_Categories, "Type_Categories.txt");
                        printf("\nvous avez sauvgarder.\n");
                        return;
                    }
                    else if (choix == 0)
                    {
                        printf("\nvous n'avez pas sauvgarder.\n");
                        return;
                    }
                }
                else if (PType_Categories == NULL && CType_Categories->Type_Categorie_suivant != NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));

                    if (choix == 1)
                    {
                        AllType_Categories = CType_Categories->Type_Categorie_suivant;
                        RefrechType_Categorie(AllType_Categories, "Type_Categories.txt");
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
                    if (CType_Categories->Type_Categorie_suivant == NULL)
                    {

                        do
                        {
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d", &choix);
                        } while ((choix != 0) && (choix != 1));
                        if (choix == 1)
                        {
                            PType_Categories->Type_Categorie_suivant = NULL;
                            RefrechType_Categorie(AllType_Categories, "Type_Categories.txt");
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
                            PType_Categories->Type_Categorie_suivant = CType_Categories->Type_Categorie_suivant;
                            RefrechType_Categorie(AllType_Categories, "Type_Categories.txt");
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
            PType_Categories = CType_Categories;
            CType_Categories = CType_Categories->Type_Categorie_suivant;
        }
        if (pos != 0)
        {
            printf("Cette Type_Categorie n\'existe pas");
        }
        else
        {
            printf("impossible de supprimer car liste Type_Categorie est vide");
        }
        return;
    }
}

/****************************************************************************************************************************/
void ChercherType_Categorie()
{
    Type_Categorie *All;
    Type_Categorie *A;
    int id, choix = 0, occur = 0;


    All = getType_Categorie();
    A = All;
    if (A == NULL)
    {
        printf("\nLa liste est vide\n");
        return;
    }

    printf("-----------recherche de Type_Categorie---------------------\n");
    printf("\nRecherche par id_type_categorie : 1\n");
    printf("Recherche par id_type : 2\n");
    printf("Recherche par id_categorie : 3\n");

    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2 && choix != 3);
    switch (choix)
    {
    case 1:
        printf("\nDonner id de  Type_Categorie que vous cherchez :");
        scanf("%d", &id);
        getchar();
        while (A != NULL)
        {
            if (A->Id_Type_Categorie == id)
            {
                printf("\n--------------------------------\n");
                printf("Id:\t\t%d\n", A->Id_Type_Categorie);
                printf("Nom:\t\t%d\n", A->Id_Type);
                printf("Nom:\t\t%d\n", A->Id_Categorie);
                printf("--------------------------------\n");
                return;
            }
            A = A->Type_Categorie_suivant;
        }
        printf("\nCette id n\'existe pas\n");
        return;
    case 2:
        printf("\nDonner id de Type que vous cherchez :");
        scanf("%d", &id);
        while (A != NULL)
        {
            if (A->Id_Type == id)
            {
                occur++;
                printf("\n--------------------------------\n");
                printf("Id:\t\t%d\n", A->Id_Type_Categorie);
                printf("Nom:\t\t%d\n", A->Id_Type);
                printf("Nom:\t\t%d\n", A->Id_Categorie);
                printf("--------------------------------\n");
                break;
            }
            A = A->Type_Categorie_suivant;
        }
        if (occur == 0)
        {
            printf("aucune Type_Categorie associe a cet id type");
        }
        printf("\nRecherche termine\n");
        return;
    case 3:
        printf("\nDonner id de Categorie que vous cherchez :");
        scanf("%d", &id);
        while (A != NULL)
        {
            if (A->Id_Categorie == id)
            {
                occur++;
                printf("\n--------------------------------\n");
                printf("Id:\t\t%d\n", A->Id_Type_Categorie);
                printf("Nom:\t\t%d\n", A->Id_Type);
                printf("Nom:\t\t%d\n", A->Id_Categorie);
                printf("--------------------------------\n");
                break;
            }
            A = A->Type_Categorie_suivant;
        }
        if (occur == 0)
        {
            printf("aucune Type_Categorie associe a cet id categorie");
        }
        printf("\nRecherche termine\n");
        return;
    }
}

/**********************************************************************************************************************/
