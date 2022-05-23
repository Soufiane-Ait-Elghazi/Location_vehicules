#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Facture.h"
#include "Client.h"
#include "Common_functions.h"


/*********************************************************************************/



Facture *list_Factures = NULL;

/*******************************************************************************************************************/
int Facture_existe_par_id_facture(int id_facture) // existance d'un Facture par ses informations
{
    Facture *All = getFacture("Factures.txt");
    Facture *C;
    C = All;

    while (C != NULL)
    {
        if (C->Id_Facture == id_facture)
        {
            return 1;
        }
        C = C->next;
    }
    return 0;
}
/*******************************************************************************************************************/
int Facture_existe_par_Id_Facture(int Id_Facture) // existance d'un Facture par ses informations
{
    Facture *All = getFacture("Factures.txt");
    Facture *C;
    C = All;

    while (C != NULL)
    {
        if (C->Id_Facture == Id_Facture)
        {
            return 1;
        }
        C = C->next;
    }
    return 0;
}
/***************************************************************************************************************************/
// ajouter un Facture au fichier Factures.txt
int AddFacture(int id_client, char *Type_paiement, float Montant, date date_facturation)
{

    FILE *f = fopen("Factures.txt", "a");
    Facture *New;
    New = (Facture *)malloc(sizeof(Facture));
    New->Id_Facture = getId("Factures.txt") + 1;
    New->next = NULL;
    New->Id_Client = id_client;
    strcpy(New->Type_paiement,Type_paiement);
    New->Montant = Montant;
    New->date_facturation = date_facturation;
    printf(" %d %d %d",date_facturation.j,date_facturation.m,date_facturation.a);

    if (FileEmpty(f) == 1)
    {
        fprintf(f, "%d:%d:%s:%f:%d:%d:%d", New->Id_Facture, id_client, Type_paiement, Montant, New->date_facturation.j, New->date_facturation.m, New->date_facturation.a);
        fclose(f);
        list_Factures = AddFactureToList(New);
        return New->Id_Facture;
    }
    else{

        fprintf(f, "\n%d:%d:%s:%f:%d:%d:%d", New->Id_Facture, id_client, Type_paiement, Montant, date_facturation.j, date_facturation.m, date_facturation.a);
        fclose(f);
        list_Factures = AddFactureToList(New);
        return New->Id_Facture;
    }
}
/******************************************************************************************************************************/
int is_factures_empty(Facture *A) //Verifier si la liste est vide
{
    if (A == NULL)
        return 1;
    return 0;
}


Facture *AddFactureToList(Facture *List) // Ajouter un Facture a la list chainee
{
    if (is_factures_empty(list_Factures) == 1)
    {
        list_Factures = List;
        return list_Factures;
    }
    else
    {
        Facture *pt;

        pt = list_Factures;
        while (pt->next != NULL)
        {
            pt = pt->next;
        }
        pt->next = List;
        return list_Factures;
    }
}
/******************************************************************************************************************************/
Facture *getFacture() // Generer une liste chainee dapres le ficher Factures.txt
{
     int id_facture;

    FILE *f = fopen("Factures.txt", "r");
    if (f == NULL)
    {
        printf("could not open the file\n");
        return NULL;
    }
    else
    {
        Facture *current_Facture = NULL, *nouv_Facture = NULL;
        current_Facture = list_Factures;
        Facture *New;
        int file_empty = 1;
        int pos = 1;

        while (!feof(f))
        {
            New = (Facture *)malloc(sizeof(Facture));
            id_facture = atoi(SaisirChaine(f));
            if (id_facture == 0)
            {
                file_empty = id_facture;
                break;
            }
            New->Id_Facture = id_facture;
            New->Id_Client = atoi(SaisirChaine(f));
            strcpy(New->Type_paiement, SaisirChaine(f));
            New->Montant = atof(SaisirChaine(f));
            New->date_facturation.j = atoi(SaisirChaine(f));
            New->date_facturation.m = atoi(SaisirChaine(f));
            New->date_facturation.a = atoi(SaisirChaine(f));
            nouv_Facture = New;
            nouv_Facture->next = NULL;
            if (pos == 1)
            {

                list_Factures = nouv_Facture;
                current_Facture = list_Factures;
                current_Facture->next = NULL;
                pos++;
            }
            else
            {
                current_Facture->next = nouv_Facture;
                current_Facture = current_Facture->next;
                pos++;
            }
        }
        if (file_empty == 0)
        {
            return NULL;
        }
        fclose(f);
        return list_Factures;
    }
}
/************************************************************************************************************************************/
void AfficherTousLesFactures() // Afficher Tous les Factures
{
    printf("L\'affichage de tous les Factures\n");
    Facture *AllFacture = getFacture("Factures.txt");
    Facture *Cl;
    Cl = AllFacture;
    if (Cl == NULL)
    {
        printf("Il n\'y a pas des Factures,list est vide");
        return;
    }
    else
    {
        while (Cl != NULL)
        {
            if (Cl->Id_Facture == 0)
            {
                printf("\nIl n\'y a pas des Factures,fichier Factures est vide");
                return;
            }
            else
            {
                printf("--------------------------------------");
                printf("\nId_facture:\t\t%d\n", Cl->Id_Facture);
                printf("id_client:\t\t%d\n", Cl->Id_Client);
                printf("Type_paiement \t\t%s\n", Cl->Type_paiement);
                printf("Montant:\t%f\n", Cl->Montant);
                printf("date de facturation : %d/", Cl->date_facturation.j);
                printf("%d/", Cl->date_facturation.m);
                printf("%d\n", Cl->date_facturation.a);
            }
            Cl = Cl->next;
        }
    }
}
/********************************************************************************************************************************/

void RefrechFacture(Facture *list, char *file) // mis a jour le ficher Agences
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

            Facture *curent;
            curent = list;
            while (curent != NULL && curent->next != NULL)
            {
                fprintf(f, "%d:%d:%s:%f:%d:%d:%d\n", curent->Id_Facture, curent->Id_Client, curent->Type_paiement, curent->Montant, curent->date_facturation.a, curent->date_facturation.j, curent->date_facturation.m);

                curent = curent->next;
            }

            fprintf(f, "%d:%d:%s:%f:%d:%d:%d", curent->Id_Facture, curent->Id_Client, curent->Type_paiement, curent->Montant, curent->date_facturation.a, curent->date_facturation.j, curent->date_facturation.m);
        }
    }

    fclose(f);
    return;
}
/**********************************************************************************************/

/***************************************************************************************************************************************************/

/*********************************************************************************************************************************************/
void ChercherFacture()
{
    Facture *All;
    Facture *C;
    int id_facture, id_client, choix = 0, occur = 0;

    All = getFacture("Factures.txt");
    C = All;
    if (C == NULL)
    {
        printf("\nLa liste est vide\n");
        return;
    }

    printf("\nRecherche par id_client : 1\n");
    printf("Recherche par id_facture : 2\n");
    do
    {
        printf("Votre choix :");
        scanf("%d", &choix);
        getchar();
    } while (choix != 1 && choix != 2);
    switch (choix)
    {
    case 1:
        printf("\nDonner id_client que vous cherchez :");
        scanf("%d", &id_client);
        while (C != NULL)
        {
            if (C->Id_Client == id_client)
            {
                occur++;
                printf("--------------------------------------");
                printf("\nId_facture\t\t: %d\n", C->Id_Facture);
                printf("id_client\t\t: %d\n", C->Id_Client);
                printf("Type_paiement \t\t: %s\n", C->Type_paiement);
                printf("Montant\t\t\t: %f\n", C->Montant);
                printf("date de facturation \t: %d/", C->date_facturation.j);
                printf("%d/", C->date_facturation.m);
                printf("%d\n", C->date_facturation.a);
            }
            C = C->next;
        }
        if (occur == 0)
            printf("\nCe id_client n\'existe pas\n");
        return;
    case 2:
        printf("\nDonner id_facture que vous cherchez :");
        scanf("%d", &id_facture);
        while (C != NULL)
        {
            if (C->Id_Facture == id_facture)
            {
                occur++;
                printf("--------------------------------------");
                printf("\nId_facture\t\t: %d\n", C->Id_Facture);
                printf("id_client\t\t: %d\n", C->Id_Client);
                printf("Type_paiement \t\t: %s\n", C->Type_paiement);
                printf("Montant\t\t\t: %f\n", C->Montant);
                printf("date de facturation \t: %d/", C->date_facturation.j);
                printf("%d/", C->date_facturation.m);
                printf("%d\n", C->date_facturation.a);
                return;
            }
            C = C->next;
        }
        if (occur == 0)
            printf("\nCette id_facture n\'existe pas\n");
        printf("\nRecherche termine\n");
        return;
    }
}

/*******************************************************************************************************************************/

Facture  *Factures_par_client(char *CIN)
{

    int id_client, existence_de_client;
    existence_de_client = Client_existe_par_CIN(CIN);
    int pos = 0;

    if (existence_de_client)
    {
        Facture *AllFacture = getFacture("Factures.txt"), *current_facture = NULL, *Client_factures = NULL, *Client_factures_suiv = NULL, *New = NULL;
        id_client = get_id_client_par_CIN(CIN);
        current_facture = AllFacture;
        while (current_facture != NULL)
        {

            if (current_facture->Id_Client == id_client)
            {
                New = (Facture *)malloc(sizeof(Facture));
                if (pos == 0)
                {

                    New->Id_Facture = current_facture->Id_Facture;
                    New->Id_Client = current_facture->Id_Client;
                    strcpy(New->Type_paiement ,current_facture->Type_paiement);
                    New->Montant = current_facture->Montant;
                    New->date_facturation.j = current_facture->date_facturation.j;
                    New->date_facturation.m = current_facture->date_facturation.m;
                    New->date_facturation.a = current_facture->date_facturation.a;
                    New->next = NULL;
                    Client_factures = New;
                    Client_factures_suiv=Client_factures;
                    pos++;
                }

                else
                {

                    New->Id_Facture = current_facture->Id_Facture;
                    New->Id_Client = current_facture->Id_Client;
                    strcpy(New->Type_paiement ,current_facture->Type_paiement);
                    New->Montant = current_facture->Montant;
                    New->date_facturation.j = current_facture->date_facturation.j;
                    New->date_facturation.m = current_facture->date_facturation.m;
                    New->date_facturation.a = current_facture->date_facturation.a;
                    New->next = NULL;
                    Client_factures_suiv->next = New;
                    Client_factures_suiv = Client_factures_suiv->next;
                    pos++;
                }
            }
            current_facture=current_facture->next;
        }

        if (pos == 0)
        {
            return NULL;
        }
        else
        {
            return Client_factures;
        }
    }
    else
    {

        return NULL;
    }
}

/*******************************************************************************************************************************/

void afficher_CA_par_Client()
{

    Client *AllClient = getClient("Clients.txt"), *current_Client;
    Facture *Facture_lie=NULL,*current_facture ;
    float Montant;
    char CIN[20];
    current_Client = AllClient;
    while (current_Client != NULL)
    {
        strcpy(CIN,current_Client->CIN);
        Montant = 0;
        Facture_lie = Factures_par_client(CIN);
        while (Facture_lie != NULL)
        {
            Montant = Montant + Facture_lie->Montant;
            Facture_lie=Facture_lie->next;

        }

        
        printf("\n--------------------------------------------------\n");
        printf(" id_client : %d\n", current_Client->Id_Client);
        printf(" NomClient : %s\n", current_Client->NomClient);
        printf(" PrenomClient : %s\n", current_Client->PrenomClient);
        printf(" chiffre d'affaires : %f", Montant);

        current_Client = current_Client->next;
    }
}
