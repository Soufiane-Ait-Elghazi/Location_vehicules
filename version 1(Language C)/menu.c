#include <stdio.h>
#include <stdlib.h>
#include "Client.h"
#include "Facture.h"
#include "Vehicule.h"
#include "Locations.h"
#include "Agence.h"
#include "Type.h"
#include "Categorie.h"
#include "Type_Categorie.h"

void menu()
{
    unsigned int choix = 20;
    unsigned int choix1 = 0;
    unsigned int choix2 = 0;
    unsigned int choix3 = 0;
    unsigned int choix4 = 20;
    int id, id_client, id_facture, id_vehicule, id_agence;
    char cin[15];

    printf("\n                                     ===================================================================\n");
    printf("\n                                                            Location Des Vehicules\n");
    printf("\n                                     ===================================================================\n");
    printf("\n  Menu1 :\n");
    printf("   _____________________________________________________________________________________________________________________________________________________________\n");
    printf("  | Client                            | Vehicule                       | Location                                   | Agence                                    |\n");
    printf("  |___________________________________|________________________________|____________________________________________|___________________________________________|\n");
    printf("  |                                   |                                |                                            |                                           |\n");
    printf("  | 1) Afficher les Clients           |  7) Afficher Les Vehicules     |  11) Louer un vehicule                     | 14)Afficher les agences                   |\n");
    printf("  |                                   |                                |                                            |                                           |\n");
    printf("  | 2) Ajouter un Client              |  8) Ajouter un Vehicule        |  12) Retourner un Vehicule                 | 15) Ajouter une agence                    |\n");
    printf("  |                                   |                                |                                            |                                           |\n");
    printf("  | 3) Chercher un Client             |  9) Chercher un Vehicule       |  13) Afficher les Locations                | 16) Chercher une agence                   |\n");
    printf("  |                                   |                                |                                            |                                           |\n");
    printf("  | 4) Bloquer un Client              |  10) Supprimer un Vehicule     |                                            | 17) Supprimer une agence                  |\n");
    printf("  |                                   |                                |                                            |                                           |\n");
    printf("  | 5) Aficher chiffre d'affair       |                                |                                            | _______________________________________   |\n");
    printf("  |    par client                     |                                |                                            | 18) Menu(Facture , Type, categorie)       |\n");
    printf("  | 6) debloquer un client            |                                |                                            |                                           |\n");
    printf("  |___________________________________|________________________________|____________________________________________|___________________________________________|\n");

    do
    {
        printf("\nVeuillez choisir le numero de la fonction que vous souhaitez (Inserer \"0\" pour arreter) : ");
        scanf("%d", &choix);
    } while (choix != 0 && choix != 1 && choix != 2 && choix != 3 && choix != 4 && choix != 5 && choix != 6 && choix != 7 && choix != 8 && choix != 9 && choix != 10 && choix != 11 && choix != 12 && choix != 13 && choix != 14 && choix != 15 && choix != 16 && choix != 17 && choix != 18);

    switch (choix)
    {
    case 0:
        printf("\nvous avez choisi le numero 0 L\'operation va arreter, Merci!\n");
        exit(0);
    case 1:
        printf("\nvous avez choisi le numero 1 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            AfficherTousLesClients(); /**Affichage des Clients***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }
    case 2:
        printf("\nvous avez choisi le numero 2 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            AddClient(); /**Ajouter un Client ***/
        }

        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 3:
        printf("\nvous avez choisi le numero 3 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :\n");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {

            ChercherClient(); /**Chercher un Client ***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 4:
        printf("\nvous avez choisi le numero 4 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour bloquer le Client inserer son ID:");
            scanf("%d", &id);
            getchar();
            int check = Bloquer_Client(id);
            if (check == 1)
            {
                printf(" client est devient bloquer");
            }
            else
            {

                printf(" client n'existe pas pour le bloquer");
            }
        }
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                exit(0);

    case 5:
        printf("\nvous avez choisi le numero 5 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);


        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\n--------------------------------------------------\n");
            printf("\n\t\t CHIFFRE D'AFFAIRE par CLIENTS\n");
            afficher_CA_par_Client(); /***Supprimer un Client***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 6:
        printf("\nvous avez choisi le numero 6 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :\n");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

               if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour debloquer le Client inserer son ID:");
            scanf("%d", &id);
            getchar();
            int check = Debloquer_Client(id);
            if (check == 1)
            {
                printf(" client est devient debloquer");
            }
            else
            {

                printf(" client n'existe pas pour le debloquer");
            }
        }
        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
            exit(0);
    case 7:
        printf("\nvous avez choisi le numero 7 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            AfficherTousLesVehicules(); /**Affichage des vehicules***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }
    case 8:
        printf("\nvous avez choisi le numero 8 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :\n");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            AddVehicule(); /**Ajouter un Vehicule ***/
        }
        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 9:
        printf("\nvous avez choisi le numero 9 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :\n");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
        }
        else if (choix1 == 1)
        {
            ChercherVehicule(); /**Chercher un Vehicule ***/
        }

        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 10:
        printf("\nvous avez choisi le numero 10 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour supprimer vehicule inserer sa ID:");
            scanf("%d", &id);
            getchar();
            deleteVehicule(id); /**Supprimer un Vehicule ***/
        }

        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 11:
        printf("\nvous avez choisi le numero 11 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            Louer(); //Louer un Vehicule
        }

        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 12:
        printf("\nvous avez choisi le numero 12 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour retourner vehicule inserer:\n");
            printf("\nid_facture :\n");
            scanf("%d", &id_facture);
            getchar();
            printf("\nid_vehicule :\n");
            scanf("%d", &id_vehicule);
            getchar();

            retour_Vehicule_VIdFacture(id_facture, id_vehicule); //Retourner un Vehicule
        }

        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 13:
        printf("\nvous avez choisi le numero 13 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            // printf("\nPour Bloquer un Client inserer son ID:");
            // scanf("%d", &id);
            // getchar();
            AfficherTousLesLocations();
        }

        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
        {
            exit(0);
        }

    case 14:
        printf("\nvous avez choisi le numero 14 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            AfficherTousLesAgences(); /**Affichage des Agences***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }
    case 15:
        printf("\nvous avez choisi le numero 15 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);
        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            AddAgence(); /**Ajouter une Agence ***/
        }
        do
        {
            printf("\n1) Retour au menu | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
            menu();
        else if (choix2 == 0)
        {
        }
        return;

    case 16:
        printf("\nvous avez choisi le numero 16 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {

            ChercherAgence(); /**Chercher une Agence ***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
                menu();
            else if (choix2 == 0)
            {
            }
            return;
        }
    case 17:
        printf("\nvous avez choisi le numero 17 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour Supprimer l'agence inserer son ID:");
            scanf("%d", &id);
            getchar();
            deleteAgence(id); /**Supprimer une Agence ***/
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu();
                return;
            }
            else if (choix2 == 0)
                return;
        }

    case 18:
        printf("\nvous avez choisi le numero 18 \n");
        menu2();
        return;
    }
}

/*******************************************************************************************************************************************************/
void menu2()
{
    unsigned int choix1 = 3;
    unsigned int choix2 = 3;
    unsigned int choix3 = 3;
    unsigned int choix4 = 20;
    int id;

    printf("\n              ===================================================================\n");
    printf("\n                                    Location Des Vehicules\n");
    printf("\n              ===================================================================\n");
    printf("\n  Menu 2:\n");
    printf("   _________________________________________________________________________________________________________\n");
    printf("  | Facture                     | Categorie(Vehicule)                |                Type(Vehicule)        |\n");
    printf("  |_____________________________|____________________________________|______________________________________|\n");
    printf("  |                             |                                    |                                      |\n");
    printf("  |  1) Afficher les Factures   |  3) Afficher Les Categories        |  7) Afficher Les Types               |\n");
    printf("  |                             |                                    |                                      |\n");
    printf("  |  2) Chercher une Facture    |  4) Ajouter une Categories         |  8) Ajouter un Type                  |\n");
    printf("  |                             |                                    |                                      |\n");
    printf("  |                             |  5) Chercher une Categorie         |  9) Chercher un Type                 |\n");
    printf("  |                             |                                    |                                      |\n");
    printf("  |                             |  6) Supprimer une Categorie        |  10) Supprimer un Type               |\n");
    printf("  |                             |                                    |                                      |\n");
    printf("  |_____________________________|____________________________________|______________________________________|\n");

    do
    {
        printf("\nVeuillez choisir le numero de la fonction que vous souhaitez (Inserer \"0\" pour arreter) : ");
        scanf("%d", &choix4);
    } while (choix4 != 0 && choix4 != 1 && choix4 != 2 && choix4 != 3 && choix4 != 4 && choix4 != 5 && choix4 != 6 && choix4 != 7 && choix4 != 8 && choix4 != 9 && choix4 != 10 && choix4 != 11 && choix4 != 12 && choix4 != 13);

    switch (choix4)
    {

    case 0:
        do
        {
            printf("\n1) Retour au menu  1 | 0) Arreter le programme ");
            scanf("%d", &choix2);
            getchar();
        } while (choix2 != 0 && choix2 != 1);
        if (choix2 == 1)
        {
            menu();
            return;
        }
        else if (choix2 == 0)
            exit(0);

    case 1:
        printf("\nvous avez choisi le numero 1 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            AfficherTousLesFactures(); //Affichage de tous les factures
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    

    case 2:
        printf("\nvous avez choisi le numero 2 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            ChercherFacture(); //chercher Facture
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                {
                    menu2();
                    return;
                }
            }
            else if (choix2 == 0)
                exit(0);
        }

   

    case 3:
        printf("\nvous avez choisi le numero 3 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            AfficherTousLesCategories(); //Afficher Les Categories
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 4:
        printf("\nvous avez choisi le numero 4 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            AddCategorie(); //Ajouter une Categories
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 5:
        printf("\nvous avez choisi le numero 5 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            ChercherCategorie(); //Chercher une Categorie
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    
    case 6:
        printf("\nvous avez choisi le numero 6 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour supprimer une  Categorie inserer son ID:");
            scanf("%d", &id);
            getchar();
            deleteCategorie(id); //supprimer une  Categorie
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 7:
        printf("\nvous avez choisi le numero 7 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
            menu2();
        else if (choix1 == 1)
        {

            AfficherTousLesTypes(); //Afficher Les Types
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 8:
        printf("\nvous avez choisi le numero 8 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            AddType(); //Ajouter une Type
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    case 9:
        printf("\nvous avez choisi le numero 9 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            ChercherType(); //Chercher un Type
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }

    

    case 10:
        printf("\nvous avez choisi le numero 10 \n");
        do
        {
            printf("Veuillez confirmer votre choix (1: oui | 0: Non) :");
            scanf("%d", &choix1);
            getchar();
        } while (choix1 != 0 && choix1 != 1);

        if (choix1 == 0)
        {
            menu2();
            return;
        }
        else if (choix1 == 1)
        {
            printf("\nPour supprimer un Type inserer son ID:");
            scanf("%d", &id);
            getchar();
            deleteType(id); //supprimer un  Type
            do
            {
                printf("\n1) Retour au menu | 0) Arreter le programme ");
                scanf("%d", &choix2);
                getchar();
            } while (choix2 != 0 && choix2 != 1);
            if (choix2 == 1)
            {
                menu2();
                return;
            }
            else if (choix2 == 0)
                exit(0);
        }
    }
}
