#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Client.h"
#include "Common_functions.h"


/*********************************************************************************/

 /*
 struct Client
{
    int Id_Client;
    char NomClient[20];
    char PrenomClient[20];
    char CIN[20];
    char NumPermis[20];
    char Adresse[40];
    char Telephone[20];
    char Ville[20];
    int Bloquer;
    struct Client *next;
};
*/
//typedef struct Client Client;


Client *list_Clients=NULL;

/*******************************************************************************************************************/
int Client_existe_par_CIN(char * CIN) // existance d'un client par ses informations
{
    Client *All = getClient("Clients.txt");
    Client *C;
    C = All;

    while (C != NULL)
    {
        if ( strcmp(C->CIN,CIN) == 0 )
        {
            return 1;
        }
        C = C->next;
    }
    return 0;
}
/***************************************************************************************************************************/
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
/*******************************************************************************************************************/
int Client_existe_par_Id_Client(int Id_Client) // existance d'un client par ses informations
{
    Client *All = getClient("Clients.txt");
    Client *C;
    C = All;

    while (C != NULL)
    {
        if (C->Id_Client == Id_Client)
        {
            return 1;
        }
        C = C->next;
    }
    return 0;
}
/***************************************************************************************************************************/
// ajouter un Client au fichier Clients.txt
void AddClient()
{

    FILE *f = fopen("Clients.txt", "a");
    Client *New;
    New = (Client*)malloc(sizeof(Client));
    New->Id_Client = getId("Clients.txt") + 1;
    New->next = NULL;

    printf("donner NomClient : ");
    gets(New->NomClient);
    printf("donner PrenomClient :");
    gets(New->PrenomClient);
    printf("donner CIN : ");
    gets(New->CIN);
    printf("donner NumPermis : ");
    gets(New->NumPermis);
    printf("donner Adresse : ");
    gets(New->Adresse);
    printf("donner Telephone : ");
    gets(New->Telephone);
    New->Bloquer = 0;
    printf("donner Ville : ");
    gets(New->Ville);


    if (FileEmpty(f) == 1)
    {
        fprintf(f, "%d:%s:%s:%s:%s:%s:%s:%s:%d", New->Id_Client, New->NomClient, New->PrenomClient, New->CIN, New->NumPermis, New->Adresse, New->Telephone, New->Ville, New->Bloquer);
        printf("%s %s est devenu un client", New->NomClient, New->PrenomClient);
        fclose(f);
        list_Clients = AddClientToList(New);
         return;
    }
    else
    {
        if (Client_existe_par_CIN(New->CIN) == 0)
        {
            fprintf(f, "\n%d:%s:%s:%s:%s:%s:%s:%s:%d", New->Id_Client, New->NomClient, New->PrenomClient, New->CIN, New->NumPermis, New->Adresse, New->Telephone, New->Ville, New->Bloquer);
            printf("%s %s est devenu un client", New->NomClient, New->PrenomClient);
            fclose(f);
            list_Clients = AddClientToList(New);
            return;
        }
        else
        {
            printf("\nCe Client deja existe.\n");
            return;
        }
    }
}
/******************************************************************************************************************************/
int is_clients_empty(Client *A)
{
    if (A == NULL)
        return 1;
    return 0;
}
Client *AddClientToList(Client *List) // Ajouter un Client a la list chainee
{
    if (is_clients_empty(list_Clients) == 1)
    {
        list_Clients = List;
        return list_Clients;
    }
    else
    {
        Client *pt;

        pt = list_Clients;
        while (pt->next != NULL)
        {
            pt = pt->next;
        }
        pt->next = List;
        return list_Clients;
    }
}
/******************************************************************************************************************************/
Client *getClient() // Generer une liste chainee dapres le ficher Clients.txt
{
     int id;
    FILE *f = fopen("Clients.txt", "r");
    if (f == NULL)
    {
        printf("could not open the file\n");
        return NULL;
    }
    else
    {
        Client *current_Client = NULL, *nouv_Client = NULL;
        current_Client = list_Clients;
        Client *New;
        int file_empty = 1;
        int pos = 1;

        while (!feof(f))
        {
            New = (Client *)malloc(sizeof(Client));
            id = atoi(SaisirChaine(f));
            if (id == 0)
            {
                file_empty = id;
                break;
            }
            New->Id_Client = id;
            strcpy(New->NomClient, SaisirChaine(f));
            strcpy(New->PrenomClient, SaisirChaine(f));
            strcpy(New->CIN, SaisirChaine(f));
            strcpy(New->NumPermis, SaisirChaine(f));
            strcpy(New->Adresse, SaisirChaine(f));
            strcpy(New->Telephone, SaisirChaine(f));
            strcpy(New->Ville, SaisirChaine(f));
            New->Bloquer=atoi(SaisirChaine(f));

            /*
                printf("%d\n",X->Id_Agence);
                printf("%s\n",X->NomAgence);
                printf("%s\n",X->VilleAgence);
                */
            //X->Agence_suivant=NULL;
            nouv_Client = New;
            nouv_Client->next = NULL;
            if (pos == 1)
            {

                list_Clients = nouv_Client;
                current_Client = list_Clients;
                current_Client->next = NULL;
                pos++;
            }
            else
            {
                current_Client->next = nouv_Client;
                current_Client = current_Client->next;
                pos++;
            }
        }
        if (file_empty == 0)
        {
            return NULL;
        }
        fclose(f);
        return list_Clients;
    }
}
/************************************************************************************************************************************/
void AfficherTousLesClients() // Afficher Tous les clients
{
    printf("L\'affichage de tous les clients\n");
    Client *AllClient = getClient("Clients.txt");
    Client *Cl;
    Cl = AllClient;
    if (Cl == NULL)
    {
        printf("Il n\'y a pas des clients,list est vide");
        return;
    }
    else
    {
        while (Cl != NULL)
        {
            if (Cl->Id_Client == 0)
            {
                printf("\nIl n\'y a pas des clients,fichier Clients est vide");
                return;
            }
            else
            {
                printf("--------------------------------------");
                printf("\nId:\t\t%d\n", Cl->Id_Client);
                printf("Nom:\t\t%s\n", Cl->NomClient);
                printf("Prenom \t\t%s\n", Cl->PrenomClient);
                printf("Telephone:\t%s\n", Cl->CIN);
                printf("Adresse:\t%s\n", Cl->Adresse);
                printf("Telephone:\t%s\n", Cl->Telephone);
                printf("Ville:\t%s\n", Cl->Ville);
                printf(" l'etat de client :\t");
                if (Cl->Bloquer == 0)
                printf("n'est pas bloquer\n");
                else
                printf("bloquer\n");
            }
            Cl = Cl->next;
        }
    }
}
/********************************************************************************************************************************/

void RefrechClient(Client *list, char *file) // mis a jour le ficher Agences
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

            Client *curent;
            curent = list;
            while (curent != NULL && curent->next != NULL)
            {
                fprintf(f, "%d:%s:%s:%s:%s:%s:%s:%s:%d\n", curent->Id_Client, curent->NomClient, curent->PrenomClient, curent->CIN, curent->NumPermis, curent->Adresse, curent->Telephone, curent->Ville, curent->Bloquer);

                curent = curent->next;
            }

            fprintf(f, "%d:%s:%s:%s:%s:%s:%s:%s:%d", curent->Id_Client, curent->NomClient, curent->PrenomClient, curent->CIN, curent->NumPermis, curent->Adresse, curent->Telephone, curent->Ville, curent->Bloquer);

                }
    }

    fclose(f);
    return;
}
/**********************************************************************************************/

/***************************************************************************************************************************************************/
void deleteClient() // Supprimer une Agence dapres son ID
{
    int choix = 3;
    char CIN[20];
    printf("donner CIN de client a supprimer : ");
    gets(CIN);
    Client *AllClients = getClient();
    Client *CClients;        // Curent Client
    Client *PClients = NULL; // Previous Client
    int pos = 0;
    if (AllClients == NULL)
    {
        printf("impossible de supprimer car liste est vide\n");
        return;
    }
    else
    {
        CClients = AllClients;
        while (CClients != NULL)
        {
            pos++;
            if (strcmp(CClients->CIN,CIN) == 0)
            {
                if (PClients == NULL && CClients->next == NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));
                    if (choix == 1)
                    {
                        AllClients = NULL;
                        RefrechClient(AllClients, "Clients.txt");
                        printf("\nvous avez sauvgarder.\n");
                        return;
                    }
                    else if (choix == 0)
                    {
                        printf("\nvous n'avez pas sauvgarder.\n");
                        return;
                    }
                }
                else if (PClients == NULL && CClients->next != NULL)
                {
                    do
                    {
                        printf("voulez vous sauvgarder les changements ? \n");
                        printf("entez 1 pour valider ou 0 sinon : ");
                        scanf("%d", &choix);
                    } while ((choix != 0) && (choix != 1));

                    if (choix == 1)
                    {
                        AllClients = CClients->next;
                        RefrechClient(AllClients, "Clients.txt");
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
                    if (CClients->next == NULL)
                    {

                        do
                        {
                            printf("voulez vous sauvgarder les changements ? \n");
                            printf("entez 1 pour valider ou 0 sinon : ");
                            scanf("%d", &choix);
                        } while ((choix != 0) && (choix != 1));
                        if (choix == 1)
                        {
                            PClients->next = NULL;
                            RefrechClient(AllClients, "Clients.txt");
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
                            PClients->next = CClients->next;
                            RefrechClient(AllClients, "Clients.txt");
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
            PClients = CClients;
            CClients = CClients->next;
        }
        if (pos != 0)
        {
            printf(" Client n'est pas supprimer car il n\'existe pas");
        }
        else
        {
            printf("impossible de supprimer car liste Client est vide");
        }
        return;
    }
}

/*********************************************************************************************************************************************/
void ChercherClient()
{
    Client *All;
    Client *C;
    int choix = 0;
    char nom[20], prenom[20], cin[20], NumPermis[20];

    All = getClient("clients.txt");
    C = All;
    if (C == NULL)
    {
        printf("\nLa liste est vide\n");
        return;
    }

    printf("\nRecherche par nom et prenom : 1\n");
    printf("Recherche par CIN : 2\n");
    printf("Recherche par NumPermis : 3\n");
    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2 && choix != 3);
    switch (choix)
    {
    case 1:
        printf("\nDonner nom de Client que vous cherchez :");
        gets(nom);
        printf("\nDonner prenom de Client que vous cherchez :");
        gets(prenom);
        while (C != NULL)
        {
            if (strcmp(C->NomClient, nom) == 0 && strcmp(C->PrenomClient, prenom) == 0)
            {
                printf("--------------------------------------");
                printf("\nId:\t\t%d\n", C->Id_Client);
                printf("Nom:\t\t%s\n", C->NomClient);
                printf("Prenom \t\t%s\n", C->PrenomClient);
                printf("Telephone:\t%s\n", C->CIN);
                printf("Adresse:\t%s\n", C->Adresse);
                printf("Telephone:\t%s\n", C->Telephone);
                printf("Ville:\t%s\n", C->Ville);
                printf(" l'etat de client :\t");
                if (C->Bloquer == 0)
                    printf("n'est pas bloquer\n");
                else
                    printf("bloquer\n");
                printf("--------------------------------\n");
                return;
            }
            C = C->next;
        }
        printf("\nCette id n\'existe pas\n");
        return;
    case 2:
        printf("\nDonner CIN du Client que vous cherchez :");
        gets(cin);
        while (C != NULL)
        {
            if (strcmp(C->CIN, cin) == 0)
            {
                printf("--------------------------------------");
                printf("\nId:\t\t%d\n", C->Id_Client);
                printf("Nom:\t\t%s\n", C->NomClient);
                printf("Prenom \t\t%s\n", C->PrenomClient);
                printf("Telephone:\t%s\n", C->CIN);
                printf("Adresse:\t%s\n", C->Adresse);
                printf("Telephone:\t%s\n", C->Telephone);
                printf("Ville:\t%s\n", C->Ville);
                printf(" l'etat de client :\t");
                if (C->Bloquer == 0){
                    printf("n'est pas bloquer\n");
                }
                else{
                    printf("bloquer\n");
                }
                printf("--------------------------------\n");
                printf("\nRecherche termine\n");

                return;
            }
            C = C->next;
        }
        printf("aucun client trouver associe a cet CIN\n");
        printf("\nRecherche termine\n");
        return;
    case 3:
        printf("\nDonner NumPermis du Client que vous cherchez :");
        gets(NumPermis);
        while (C != NULL)
        {
            if (strcmp(C->NumPermis, NumPermis) == 0)
            {
                printf("--------------------------------------");
                printf("\nId:\t\t%d\n", C->Id_Client);
                printf("Nom:\t\t%s\n", C->NomClient);
                printf("Prenom \t\t%s\n", C->PrenomClient);
                printf("Telephone:\t%s\n", C->CIN);
                printf("Adresse:\t%s\n", C->Adresse);
                printf("Telephone:\t%s\n", C->Telephone);
                printf("Ville:\t%s\n", C->Ville);
                printf(" l'etat de client :\t");
                if (C->Bloquer == 0)
                    printf("n'est pas bloquer\n");
                else
                    printf("bloquer\n");
                printf("--------------------------------\n");
                printf("\nRecherche termine\n");

                return;
            }
            C = C->next;
        }
        printf("aucun client trouver associe a cet NumPermis\n");
        printf("\nRecherche termine\n");
        return;
    }
}

/*******************************************************************************************************************************/
int Modifier_blocage_Client(char *CIN, int etat) // Supprimer une Agence dapres son ID
{
    Client *AllClients = getClient();
    Client *CClients;                // Curent Client
    Client *PClients = AllClients; // Previous Client
    int pos = 0;
    if (AllClients == NULL)
    {
        printf("impossible de modifier car liste est vide\n");
        return 0;
    }
    else
    {
        CClients = AllClients;
        while (CClients != NULL)
        {
            pos++;
            if (strcmp(CClients->CIN,CIN)==0)
            {
                CClients->Bloquer = etat;

                RefrechClient(PClients, "Clients.txt");
                return 1;
                break;
            }

            CClients = CClients->next;
        }
            return 0;

    }

}

/*******************************************************************************************************************************/
int  Bloquer_Client(int id)// Supprimer une Agence dapres son ID
{
    Client *AllClients = getClient();
    Client *CClients;                // Curent Client
    Client *PClients = AllClients; // Previous Client
    int pos = 0;
    if (AllClients == NULL)
    {
        return 0;
    }
    else
    {
        CClients = AllClients;
        while (CClients != NULL)
        {
            pos++;
            if (CClients->Id_Client   == id   )
            {
                CClients->Bloquer = 1;

                RefrechClient(PClients, "Clients.txt");
                return 1;
                break;
            }

            CClients = CClients->next;
        }
            return 0;

    }

}
/*******************************************************************************************************************************/

/*******************************************************************************************************************************/
int  Debloquer_Client(int id)// Supprimer une Agence dapres son ID
{
    Client *AllClients = getClient();
    Client *CClients;                // Curent Client
    Client *PClients = AllClients; // Previous Client
    int pos = 0;
    if (AllClients == NULL)
    {
        return 0;
    }
    else
    {
        CClients = AllClients;
        while (CClients != NULL)
        {
            pos++;
            if (CClients->Id_Client   == id   )
            {
                CClients->Bloquer = 0;

                RefrechClient(PClients, "Clients.txt");
                return 1;
                break;
            }

            CClients = CClients->next;
        }
            return 0;

    }

}
/*******************************************************************************************************************************/


int Client_etat_blocage(char * CIN) // existance d'une Client par ses informations
{
    Client *All = getClient();
    Client *A;
    A = All;

    while (A != NULL)
    {
        if (strcmp(A->CIN,CIN) == 0)
        {

            return A->Bloquer;
        }

        A = A->next;
    }


    return -1;
}


/************************************************************************************/
int get_id_client_par_CIN(char * CIN){


    Client *All = getClient("Clients.txt");
    Client *C;
    C = All;

    while (C != NULL)
    {
        if (strcmp(C->CIN,CIN)==0)
        {
            return C->Id_Client;
        }
        C = C->next;
    }
    return 0;


}
