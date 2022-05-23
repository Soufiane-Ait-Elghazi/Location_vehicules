typedef struct Client
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
}Client;


int Client_existe_par_CIN(char * CIN); // tester l'existance d'un client par CIN
int Client_existe_par_Id_Client(int Id_Client); // tester l'existance d'un client par son id
void AddClient(); //// stocker un client dans le fichier
int get_id_client_par_CIN(char * CIN); //elle retourne l'id du client qui a la CIN donnee
Client *AddClientToList(Client *List); // Ajouter un Client a la list chainee
Client *getClient(); // Generer une liste chainee dapres le ficher Clients.txt
void AfficherTousLesClients(); // Afficher Tous les clients
void RefrechClient(Client *list, char *file); // mis a jour le fichier
void deleteClient(); // Supprimer un client dapres son ID
void ChercherClient();
int Modifier_blocage_Client(char *CIN, int etat); // modifier le bloquage du client apres la fin de la periode de penalisation
int Client_etat_blocage(char * CIN); // tester si un client est bloque ou pas
int Bloquer_Client(int id); //bloquer un cleint
int Debloquer_Client(int id);
