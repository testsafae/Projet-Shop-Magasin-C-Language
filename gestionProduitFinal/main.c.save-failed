#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Produit {
int code;
char *designation;
double prix;
} Produit;

typedef struct ProduitElement {
Produit *produit;
struct ProduitElement *next;
} ProduitElement;

char *allouerEspace() {
char text[100];
char *String;
scanf("%s", text);
String = (char *)malloc(sizeof(char) * strlen(text));
strcpy(String, text);
return String;
}

Produit *createProduit(int, char *, double);
ProduitElement *createProduitElement(Produit *);
void addProduitToList(ProduitElement **, Produit *);
void afficherDetailProduit(Produit *);
ProduitElement *supprimerElement(ProduitElement **, int);
Produit *chercherProduit(ProduitElement *, int);
void modifierProduit(Produit *, int, char *, float);
void afficherAll(ProduitElement *);

void export(ProduitElement *clients);
void import(ProduitElement **clients);

void menuProduit(ProduitElement **L) {
//FILE *pf_out=fopen("gestionProduit.txt","a");

ProduitElement *ptr;
int choix, i, code, nvCode, c;
float nvPrix;
char *nvDesignation;
printf("\n\n-------------------------- Gestion des produits ------------------------------\n\n");

do {
printf("******************* Menu ***********************\n");
printf(" 1. Ajouter un produit \n");
printf(" 2. Afficher la liste de produits \n");
printf(" 3. Supprimer un produit \n");
printf(" 4. Modifier un produit \n");
printf(" 5. Chercher un produit \n");
printf(" 6. export \n");
printf(" 7. import \n");
printf(" 8. Quitter \n");
printf("*************************************************\n\n");
printf(" Tapez votre choix SVP : ");
scanf("%d", &choix);
switch (choix) {
case 1: {
system("cls");
printf("\n****************** Ajouter ************************\n");
int code;
double prix;
char *designation;
// getchar();
printf(" Code : ");
scanf("%d", &code);
printf(" Designation : ");
designation = allouerEspace();
printf(" Prix : ");
scanf("%lf", &prix);
addProduitToList(L, createProduit(code, designation, prix));

break;
}
case 2: {
system("cls");
afficherAll(*L);
break;
}
case 3: {
system("cls");
printf("\n****************** Suppression ******************\n");
printf(" Tapez le code de produit que vous voulez supprimer : ");
scanf("%d", &c);
supprimerElement(L, c);
break;
}
case 4: {
system("cls");
printf("\n****************** Modification ********************\n");
printf(" Tapez le code de produit que vous voulez modifier : ");
scanf("%d", &code);
nvDesignation = (char *)malloc(sizeof(char) * 10);
printf("nvDesignation: ");
scanf("%s", nvDesignation);
printf("nvPrix: ");
scanf("%f", &nvPrix);
ptr = *L;
while (ptr != NULL) {
if (ptr->produit->code == code)
break;
ptr = ptr->next;
}
modifierProduit(ptr->produit, code, nvDesignation, nvPrix);
break;
}
case 5: {
system("cls");
printf("\n****************** la Recherche ********************\n");
printf(" Donner le code de produit a chercher : ");
scanf("%d", &c);
Produit *p;
if ((p = chercherProduit(*L, c)) != NULL) {
printf("Oui, il existe c'est:\ncode: %d\ndesigniation: %s\nprix: %2.lf\n", p->code, p->designation, p->prix);
} else
printf(" maleureusement il n'existe pas");
printf("\n**************************************************\n");
break;
}

case 6:
export(*L);
break;

case 7:
import(L);
break;

case 8: {
system("cls");
printf(" ***** Fin de traitement ******\n");
break;
}
default:
printf(" Votre choix n'est pas compatible avec les choix disponibles\n");
break;
}
} while (choix != 8);

printf("\n l'enregisetrement est etrain de s'effectue \n");
// enregister(*L, pf_out);
// fclose(pf_out);
}

//Creation de Produit
Produit *createProduit(int code, char *designation, double prix) {
Produit *newProduit;
newProduit = (Produit *)malloc(sizeof(Produit));
newProduit->code = code;
printf("%d", code);
newProduit->designation = (char *)malloc(sizeof(char) * strlen(designation));
newProduit->designation = designation;

newProduit->prix = prix;
return newProduit;
}

//create new element
ProduitElement *createProduitElement(Produit *produit) {
ProduitElement *newElement;
newElement = (ProduitElement *)malloc(sizeof(ProduitElement));
newElement->produit = produit;

newElement->next = NULL;
return newElement;
}

//Add an element to the list

void addProduitToList(ProduitElement **listProduit, Produit *produit) {
ProduitElement *newElement;
//creation de l'element
newElement = createProduitElement(produit);
//if empty
if (*listProduit == NULL) {
*listProduit = newElement;
return;
}

ProduitElement *last;
last = *listProduit;
while (last->next != NULL) {
last = last->next;
}
last->next = newElement;
}

//afficher detail d'un produit
void afficherDetailProduit(Produit *produit) {
printf("code : %d \n", produit->code);
printf("Designation: %s \n", produit->designation);
printf("prix : %.2lf\n", produit->prix);
}

//delete element
ProduitElement *supprimerElement(ProduitElement **listProduit, int code) {
ProduitElement *ptr;
ptr = *listProduit;
if ((*listProduit)->produit->code == code) {
(*listProduit) = (*listProduit)->next;
printf("La supression est bien faite \n");
free(ptr);
ptr = NULL;
} else {
ProduitElement *tmp;
while (ptr != NULL) {
tmp = ptr;
ptr = ptr->next;
if (ptr->produit->code == code) {
tmp->next = ptr->next;
free(ptr);
break;
}
}
if (ptr != NULL)
printf("la suppression est bien faite \n");
else {
printf("le code que vous avez entrez n'existe pas dans la list \n");
}
}
}

//recherche d'un element
Produit *chercherProduit(ProduitElement *listProduit, int code) {
ProduitElement *ptr;
ptr = listProduit;
while (listProduit != NULL) {
if (ptr->produit->code == code) {
return ptr->produit;
}
listProduit = listProduit->next;
}
return NULL;

printf("votre list est Vide");
}

//Modification de produit
void modifierProduit(Produit *produit, int nvCode, char *nvDesignation, float nvPrix) {
strcpy(produit->designation, nvDesignation);
produit->prix = nvPrix;
}

//display all elementList
void afficherAll(ProduitElement *listProduit) {
ProduitElement *ptr;
ptr = listProduit;
for (ptr = listProduit; ptr != NULL; ptr = ptr->next) {
afficherDetailProduit(ptr->produit);
}
}

//Enregister les donnees
/*void enregister(ProduitElement*listProduit,FILE*pf_out){
    ProduitElement*ptr;
    ptr=listProduit;
    while(ptr!=NULL){
        fprintf(pf_out,"%d\t%s\t%lf\n",ptr->produit->code,ptr->produit->designation,ptr->produit->prix);
        ptr=ptr->next;
    }
}*/

int main(int argc, char const *argv[]) {
ProduitElement *produits = NULL;
menuProduit(&produits);
return 0;
}

void export(ProduitElement *produits) {
FILE *file = fopen("produits.txt", "w");
if (!file) {
printf("file is nulll!!!\n");
return;
}
while (produits) {
fprintf(file, "%d %s %.2lf\n", produits->produit->code, produits->produit->designation, produits->produit->prix);
produits = produits->next;
}
fclose(file);
}

void import(ProduitElement **produits) {
FILE *file = fopen("produits.txt", "r");
if (!file) {
printf("file is null!!!\n");
return;
}
*produits = NULL;
ProduitElement *tmp = *produits;
int code;
char designation[100];
double prix;
char *d;
while (fscanf(file, "%d %s %lf", &code, designation, &prix) != EOF) {
d = (char *)malloc(strlen(designation));
strcpy(d, designation);
if (*produits == NULL) {
*produits = createProduitElement(createProduit(code, d, prix));
tmp = *produits;
} else {
tmp->next = createProduitElement(createProduit(code, d, prix));
tmp = tmp->next;
}
}
}
