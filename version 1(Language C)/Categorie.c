#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "Functions.h"
#include "Categorie.h"
#include "Common_functions.h"
/**********************************************************************************************************************************************/

/**********************************************************************************************************************************************/

    Categorie *list_Categories=NULL;

    /*
int is_empty(struct Categorie *A) //Verifier si la liste est vide
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
int is_categorie_empty(Categorie *A) //Verifier si la liste est vide
{
    if (A == NULL)
        return 1;
    return 0;
}
int Categorie_existe_par_nom(char* Nom)// existance d'une Agence par ses informations
{
	Categorie *All = getCategorie();
	Categorie *A;
	A = All;
	int occur=0;
	int file_empty = 1;

	while(A != NULL   )
	{
	    file_empty = 0;
	    if( strcmp(A->NomCategorie,Nom) ==0 ) {

        occur++;
        printf("-----------------------------------------------\n");

        printf("id Categorie : %d\n",A->Id_Categorie);
        printf("Nom Categorie : %s\n",A->NomCategorie);

        return 1;
	    }


		A = A->Categorie_suivant;
	}

	if  ( file_empty == 1  )
    {

        printf("-----------------------------------------------\n");
        printf(" aucun Categorie  trouver , liste deja vide \n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");

    }

	else if( occur == 0 )
	{


        printf("-----------------------------------------------\n");
        printf(" aucun Categorie correspond trouver\n");

        printf("-----------------------------------------------\n");

        printf("fin de recherche\n");
    	}


	return 0;
}
/*********************************************************************************/



/*********************************************************************************/
int Categorie_existe_par_id_Categorie(int id_Categorie)// existance d'une Categorie par ses informations
{
	Categorie *All = getCategorie();
	Categorie *A;
	A = All;
	int occur=0;
	int file_empty = 1;

	while(A != NULL   )
	{
	    file_empty = 0;
	    if( A->Id_Categorie == id_Categorie) {

            occur++;
            return 1;


	    }


		A = A->Categorie_suivant;
	}

	if  ( file_empty == 1 || occur == 0  )
    {

     return 0;

    }

    return 0;

}
/*********************************************************************************/


void AddCategorie()
{
	FILE *f = fopen("Categories.txt", "a");
	Categorie *New;
	New = (Categorie*)malloc(sizeof(Categorie));
	New -> Id_Categorie = getId("Categories.txt")+1;
	printf("Donner le nom de Categorie au maximum 19 caractere : ");
	gets(New -> NomCategorie);
	New ->Categorie_suivant = NULL;

	if(FileEmpty(f) == 1)
	{
		fprintf(f,"%d:%s", New -> Id_Categorie, New -> NomCategorie);
		printf("%s est devenu une Categorie",New -> NomCategorie);
		list_Categories = New;
		fclose(f);
	}
	else
	{

			fprintf(f,"\n%d:%s", New -> Id_Categorie, New -> NomCategorie);
			printf("%s est devenu une Categorie",New -> NomCategorie);
            list_Categories=AddCategorieToList(New);
			fclose(f);


    }

    return;

}

/*********************************************************************************/
Categorie* AddCategorieToList(Categorie * new_Categorie) // Ajouter une Agence a la list chainee
{
	if(is_categorie_empty(list_Categories) == 1)
    {
		list_Categories = new_Categorie;
		return list_Categories;
	}
	else
	{
		Categorie * pt;

		pt = list_Categories;
		while(pt->Categorie_suivant != NULL)
		{
			pt = pt -> Categorie_suivant;
		}
		pt -> Categorie_suivant = new_Categorie;
		return list_Categories;
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
Categorie * getCategorie() // Generer une liste chainee dapres le fichier Agences.txt
{
	unsigned int id;
	char *Nom;

	FILE *f = fopen("Categories.txt", "r");
	if(f == NULL){
        printf("could not open the file\n");
        return NULL;
	}
	else
        {
            Categorie *current_Categorie=NULL,*nouv_Categorie=NULL;
            current_Categorie=list_Categories;
            Categorie *X;
             int file_empty = 1;
            int pos = 1;

            while(!feof(f))
            {
                X=(Categorie*)malloc(sizeof(Categorie));
                id = atoi(SaisirChaine(f));
                if(id==0){
                        file_empty=id;
                    break;
                }
                Nom = SaisirChaine(f);
                X->Id_Categorie=id;
                strcpy(X->NomCategorie,Nom);
                /*
                printf("%d\n",X->Id_Agence);
                printf("%s\n",X->NomAgence);
                printf("%s\n",X->VilleAgence);
                */
                //X->Agence_suivant=NULL;
                nouv_Categorie=X;
                nouv_Categorie->Categorie_suivant=NULL;
                if(pos == 1){

                    list_Categories = nouv_Categorie;
                    current_Categorie=list_Categories;
                    current_Categorie->Categorie_suivant=NULL;
                    pos++;
                }
                else{
                    current_Categorie->Categorie_suivant=nouv_Categorie;
                    current_Categorie=current_Categorie->Categorie_suivant;
                    pos++;
                }

            }
            if(file_empty==0){
               return  NULL;
            }
            	fclose(f);
                return list_Categories;
	}



}
/*********************************************************************************/
void AfficherTousLesCategories() // Afficher Tous les Agences
{
	printf("L'affichage de tous les Categories\n");
	Categorie *AllCategorie=NULL ;
	AllCategorie= getCategorie();
	Categorie *A1;
	A1 = AllCategorie;
	if(AllCategorie == NULL){
		printf("Il n\'y a pas des Categories\n");
		return;
	}
	else{
		while(A1!= NULL)
		{

			printf("--------------------------------------\n");
			printf("id categorie : %d\n", A1 -> Id_Categorie);
			printf("Nom: %s\n", A1 -> NomCategorie);

			A1 = A1->Categorie_suivant;

		}
		return;
	}

}
/******************************************************************************************/
void RefrechCategorie(Categorie * list,char * file) // mis a jour le ficher Agences
{



	FILE * f = fopen(file , "w");
	if(f == NULL)
	{
		printf("Can\'t open the file");
		return;
	}
	 else{

        if(list == NULL){

            fprintf(f, "");

        }

       else {

        Categorie *curent;
        curent = list;
        while(curent != NULL && curent->Categorie_suivant != NULL)
         {
            fprintf(f, "%d:", curent ->Id_Categorie);
            fprintf(f, "%s\n",  curent -> NomCategorie);
            curent = curent ->Categorie_suivant;

          }

            fprintf(f, "%d:", curent ->Id_Categorie);
            fprintf(f, "%s",  curent -> NomCategorie);

        }

	 }

	fclose(f);
	return;
}
/**********************************************************************************************/

void changerInfoCategorie(int id) // modifier les info une Agence dapres son ID
{
	Categorie *AllCategories = getCategorie();
	int choix;
	Categorie *A1;
	A1 = AllCategories;
		if(A1 == NULL){
		printf("Il n\'y a pas des Categories");
		return  ;
	}
	else{
		while(A1 != NULL)
		{
			if(A1 -> Id_Categorie == id)
			{
				printf("\nChoisissez ce que vous voulez changer:\n1 - Le nom\n2 - exit\n");
				scanf("%i", &choix);
				getchar();
				switch(choix)
				{
					case 1 ://si jamais on fait des erreure au niveau de la saisir du nom
						printf("Inserer le nouveau nom: ");
						gets(A1 -> NomCategorie);

						break;
					case 2 ://si jamais on fait des erreure au niveau de la saisir du Ville
						exit(-1);
						break;
				}
				printf("\nLe nouveau profil est : \n");
				printf("\nId:\t\t%i\n", A1 -> Id_Categorie);
				printf("\nNom:\t\t%s\n", A1 -> NomCategorie);
				do{
				printf("voulez vous sauvgarder les changements ? \n");
				printf("entez 1 pour valider ou 0 sinon : ");
				scanf("%d",&choix);
			    }while((choix != 0) && (choix != 1));
				if(choix == 1){
			    	RefrechCategorie(AllCategories,"Categories.txt");
			    	printf("vous avez sauvgarder.\n");
			    	return ;
		        }
		        else if (choix == 0){
		         printf("changement annuler,  vous n'avez pas sauvgarder.\n");
		         return ;
		        }
			}
			A1 = A1 ->Categorie_suivant;
		}
		printf("Cette Categorie n'existe pas n\'existe pas");
		return ;
	}
}
/************************************************************************************************/
void deleteCategorie(int id) // Supprimer une Agence dapres son ID
{
	int choix = 3;
	Categorie *AllCategories = getCategorie();
	Categorie *CCategories; // Curent Client
	Categorie *PCategories = NULL; // Previous Client
    int pos = 0;
	if(AllCategories == NULL){
	printf("impossible de supprimer car liste est vide\n");
	return  ;
	}
	else{
		CCategories = AllCategories;
		while(CCategories != NULL)
		{
		    pos++;
			if(CCategories->Id_Categorie == id)
			{
				if(PCategories == NULL && CCategories->Categorie_suivant == NULL)
				{
					do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1)
                        {
                            AllCategories = NULL;
					    	RefrechCategorie(AllCategories,"Categories.txt");
					    	printf("\nvous avez sauvgarder.\n");
							return;
						}
						else if (choix == 0)
						{
							printf("\nvous n'avez pas sauvgarder.\n");
							return;
						}
				}
				else if(PCategories == NULL && CCategories->Categorie_suivant != NULL)
				{
						do{
                                printf("voulez vous sauvgarder les changements ? \n");
                                printf("entez 1 pour valider ou 0 sinon : ");
                                scanf("%d",&choix);
					      }while((choix != 0) && (choix != 1));

						if(choix == 1){
                            AllCategories = CCategories->Categorie_suivant;
					    	RefrechCategorie(AllCategories,"Categories.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return;
				        }
				        else if (choix == 0){
				           printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }
				}
				else
				{
					if(CCategories->Categorie_suivant == NULL)
					  {

						do{
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
                            PCategories->Categorie_suivant = NULL;
					    	RefrechCategorie(AllCategories,"Categories.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return ;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }
					}
					else
					{

						do{
						printf("voulez vous sauvgarder les changements ? \n");
						printf("entez 1 pour valider ou 0 sinon : ");
						scanf("%d",&choix);
					    }while((choix != 0) && (choix != 1));
						if(choix == 1){
                            PCategories->Categorie_suivant = CCategories->Categorie_suivant;
					    	RefrechCategorie(AllCategories,"Categories.txt");
					    	printf("vous avez sauvgarder.\n");
					    	return ;
				        }
				        else if (choix == 0){
				         printf("vous n'avez pas sauvgarder.\n");
				         return ;
				        }

					}
				}
			}
			PCategories = CCategories;
			CCategories = CCategories->Categorie_suivant;
		}
        if(pos !=0){
            		printf("Cette Categorie n\'existe pas");

        }
        else{
            		printf("impossible de supprimer car liste categorie est vide");

        }
		return ;
	}
}

/****************************************************************************************************************************/
void ChercherCategorie()
{
	Categorie *All;
	Categorie *A;
	int id, choix = 0,occur=0;
	char Nom[20];


	All = getCategorie();
	A = All;
	if(A == NULL)
	{
		printf("\nLa liste est vide\n");
		return;
	}

	printf("-----------rechercher de categorie---------------------\n");
	printf("\nRecherche par id : 1\n");
	printf("Recherche par Nom : 2\n");
	do{
	printf("Votre choix :");
	scanf("%d",&choix);
	getchar();
	}while(choix != 1 && choix != 2 );
	switch(choix){
		case 1:
			printf("\nDonner id de  Categorie que vous cherchez :");
			scanf("%d",&id);
			getchar();
			while(A != NULL)
			{
				if(A->Id_Categorie== id)
				{
					printf("\n--------------------------------\n");
					printf("Id:\t\t%i\n", A -> Id_Categorie);
					printf("Nom:\t\t%s\n", A -> NomCategorie);
					printf("--------------------------------\n");
					return;
				}
				A = A->Categorie_suivant;
			}
			printf("\nCette id n\'existe pas\n");
			return;
		case 2:
			printf("\nDonner le nom de Categorie que vous cherchez au maximum 20 caractere :");
            gets(Nom);
			while(A != NULL)
			{
				if(strcmp(A->NomCategorie, Nom) == 0)
				{
				    occur++;
					printf("\n--------------------------------\n");
                    printf("Id:\t\t%i\n", A ->Id_Categorie);
					printf("Nom:\t\t%s\n", A ->NomCategorie);
					printf("--------------------------------\n");
                    break;
				}
				A = A->Categorie_suivant;
			}
			if(occur == 0){
            printf("aucune categorie associe a cet nom");
			}
			printf("\nRecherche termine\n");
			return;

	}
}

/**********************************************************************************************************************/


