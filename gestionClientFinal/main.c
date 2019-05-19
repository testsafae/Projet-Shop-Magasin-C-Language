#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Client {
int code;
char *nom;
char *prenom;
char *Tel;
struct Client *Next;
} Client;

typedef struct ClientElement {
Client *client;
struct ClientElement *next;
} ClientElement;

Client *createClient(int, char *, char *, char *);
ClientElement *createClientElm(Client *);
void ajouterClient(ClientElement **, Client *);
Client *chercherClient(ClientElement *, int);
void supprimerClient(ClientElement **, int);
void modifierClient(ClientElement *, int, char *nom, char *, char *);
void afficherListClient(ClientElement *);
void enregister(ClientElement *, FILE *);

void export(ClientElement *);
void import(ClientElement **);

//----------------------------------- MENU ------------------------------------//

char *allouerEspace() {
char text[100];
char *String;
scanf("%s", text);
String = (char *)malloc(sizeof(char) * strlen(text));
strcpy(String, text);
return String;
}

void menuClient(ClientElement **C) {
//Declaration de notre liste C
ClientElement *ptr;

// Declaration du fichier pour enregistrer les clients
//FILE *pf_out=fopen("gestionClient.txt","a");

int choix, Taille, c, code, nvCode;
char *Nom, *Prenom, *Tel;

// Le Menu pour tester toutes les fonctions qui permettant la gestion des clients
printf("\n\n************************ Gestion des clients **********************\n\n");

// La boucle qui va donner la main a l'utilisateur pour choisir la fonction qu'elle veut
do {
printf("\n\n\n******************* Menu **********************\n");
printf("* 1. Ajouter un client *\n");
printf("* 2. Afficher la liste des clients *\n");
printf("* 3. Supprimer un client *\n");
printf("* 4. Modifier un client *\n");
printf("* 5. Chercher un client *\n");
printf("* 6. export *\n");
printf("* 7. import *\n");
printf("* 8. Quitter *\n");
printf("*************************************************\n\n\n");
printf(" Taper votre choix SVP : ");
scanf("%d", &choix);
switch (choix) {
case 1: {
system("cls");
int code;
char *Nom, *Prenom, *Tel;
printf("***************** Le client qui a effectue la vente ******************\n");
printf(" Code : ");
scanf("%d", &code);
printf(" Nom : ");

Nom = allouerEspace();
printf(" Prenom : ");

Prenom = allouerEspace();
printf(" Tel : ");

Tel = allouerEspace();
Client *client = createClient(code, Nom, Prenom, Tel);
ajouterClient(C, client);
break;
}
case 2: {
system("cls");
afficherListClient(*C);
break;
}
case 3: {
system("cls");
printf("\n****************** Suppression ******************\n");
printf(" Donner le code de client a supprimer : ");
scanf("%d", &c);
supprimerClient(C, c);
break;
}
case 4: {
system("cls");
printf("\n****************** Modification ********************\n");
printf("code: ");
scanf("%d", &code);
printf("Nouveau Nom: ");
Nom = allouerEspace();
printf("Nouveau Prenom: ");
Prenom = allouerEspace();
printf("Nouveau Tel: ");
Tel = allouerEspace();

ptr = *C;
while (ptr != NULL) {
if (ptr->client->code == code) break;
ptr = ptr->next;
}
modifierClient(*C, code, Nom, Prenom, Tel);
break;
printf("\n**************************************************\n");
}
case 5: {
system("cls");
printf("\n****************** Recherche ********************\n");
printf(" Donner le code de client a chercher : ");
scanf("%d", &c);
Client *cc;
if ((cc = chercherClient(*C, c)) != NULL) {
printf(" il existe c'est:\ncode: %d\nnom: %s\nprenom: %s\nTel: %s\n", cc->code, cc->nom, cc->prenom, cc->Tel);
} else
printf(" il n'existe pas");
printf("\n**************************************************\n");
break;
}
case 6:
system("cls");
export(*C);
break;
case 7:
system("cls");
import(C);
break;
case 8: {
printf(" Fin de traitement \n");
break;
}
default: {
printf(" Votre choix n'est pas compatible avec les choix disponibles \n");
break;
}
}
} while (choix != 8);
//L'enregistrement des donnees
// enregister(*C, pf_out);
printf("\n l'enregistrement est entrain de s'effectue \n");

// la fermeture du fichier
// fclose(pf_out);
}

//----------------------------------- MENU ------------------------------------//

// nous devons savoir si notre liste est vide ou non
int estVide(ClientElement *listClient) {
if (listClient == NULL)
return 1;
return 0;
}

//la creation d"un Client
Client *createClient(int code, char *nom, char *prenom, char *Tel) {
Client *newClient;
newClient = (Client *)malloc(sizeof(Client));
newClient->code = code;
newClient->nom = nom;
newClient->prenom = prenom;
newClient->Tel = Tel;

return newClient;
}

ClientElement *createClientElm(Client *c) {
ClientElement *elm = (ClientElement *)malloc(sizeof(ClientElement));
elm->client = c;
elm->next = NULL;
return elm;
}

//l"ajout d'un client

// void ajouterClient(ClientElement, Client);
void ajouterClient(ClientElement **listClient, Client *client) {
if (*listClient == NULL) {
*listClient = (ClientElement *)malloc(sizeof(ClientElement));
(*listClient)->client = client;
(*listClient)->next = NULL;
return;
}
ClientElement *tmp = *listClient;
while (tmp->next) tmp = tmp->next;
tmp->next = createClientElm(client);
}

//chercher un Client
// ClientElement *chercherClient(ClientElement* , int);
Client *chercherClient(ClientElement *listClient, int code) {
ClientElement *ptr;
ptr = listClient;
if (!estVide(listClient)) {
while (ptr != NULL) {
if (ptr->client->code == code) {
return ptr->client;
}
ptr = ptr->next;
}
}
return NULL;
}
// supprimer un Client
// void supprimerClient(ClientElement** , int);
void supprimerClient(ClientElement **listClient, int code) {
if (*listClient == NULL) {
printf("la liste est deja vide \n");
return;
}

ClientElement *ptr, *tmp;
ptr = *listClient;

if (ptr->client->code == code) {
tmp = ptr->next;
free(ptr->client);
free(ptr);
*listClient = tmp;
return;
}
tmp = ptr;
ptr = ptr->next;
while (ptr != NULL) {
if (ptr->client->code == code) {
tmp->next = ptr->next;
free(ptr->client);
free(ptr);
break;
}
tmp = ptr;
ptr = ptr->next;
}
}

//modifier un client
// void modifierClient(ClientElement *, int , char *nom, char *, char *);
void modifierClient(ClientElement *C, int code, char *nom, char *prenom, char *tel) {
while (C != NULL) {
if (C->client->code == code) {
C->client->nom = nom;
C->client->prenom = prenom;
C->client->Tel = tel;
break;
}
C = C->next;
}
}

//afficher la liste des clients
// void afficherListClient(ClientElement **);
void afficherListClient(ClientElement *listClient) {
printf("\n************ affichage des Clients************\n");
int i = 0;

while (listClient != NULL) {
i++;
printf("Client %d : \n", i);
printf("code : %d \n", listClient->client->code);
printf("nom : %s \n", listClient->client->nom);
printf("prenom : %s \n", listClient->client->prenom);
printf("Tel : %s \n", listClient->client->Tel);
listClient = listClient->next;
}
}

//Pour enregistrer les clients saisie par l'utilisateur dans une fichier texte "gestion"
// void enregister(ClientElement *, FILE *);
void enregister(ClientElement *L, FILE *fp_out) {
ClientElement *ptr = L;
for (ptr = L; ptr != NULL; ptr = ptr->next) {
fprintf(fp_out, "%d\t%s\t%s\t%s\n", ptr->client->code, ptr->client->nom, ptr->client->prenom, ptr->client->Tel);
}
fflush(fp_out);
}

int main(int argc, char const *argv[]) {
ClientElement *clients = NULL;
menuClient(&clients);

return 0;
}

void export(ClientElement *clients) {
FILE *file = fopen("clients.txt", "w");
if (!file) {
printf("file is nulll!!!\n");
return;
}
while (clients) {
fprintf(file, "%d %s %s %s\n", clients->client->code, clients->client->nom, clients->client->prenom, clients->client->Tel);
clients = clients->next;
}
fclose(file);
}

void import(ClientElement **clients) {
FILE *file = fopen("clients.txt", "r");
if (!file) {
printf("file is null!!!\n");
return;
}
*clients = NULL;
ClientElement *tmp = *clients;
int code;
char nom[100];
char prenom[100];
char tel[100];
char *n, *p, *t;
while (fscanf(file, "%d %s %s %s\n", &code, nom, prenom, tel) != EOF) {
n = (char *)malloc(strlen(nom));
p = (char *)malloc(strlen(prenom));
t = (char *)malloc(strlen(tel));
strcpy(n, nom);
strcpy(p, prenom);
strcpy(t, tel);
if (*clients == NULL) {
*clients = createClientElm(createClient(code, n, p, t));
tmp = *clients;
} else {
tmp->next = createClientElm(createClient(code, n, p, t));
tmp = tmp->next;
}
}
}
