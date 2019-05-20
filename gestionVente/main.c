
#include <stdio.h>
#include <stdlib.h>

#include "client.h"
#include "produits.h"
#include "vente.h"

// ------------------------ MENU -----------------------------------//

void menuVente(VenteElement **L, ClientElement *ListClient, ProduitElement *ListProduit) {
    // Declaration de fichier pour enregistrer les donnees
    FILE *pf_out = fopen("gestionVente.txt", "a");

    int choix, i;
    // Menu pour la meilleur utilisation des fonctions de gestion des ventes
    printf("\n\n****************  Gestion des Ventes  **************\n\n");

    // Pour gerer les besoins de l'utilisateur
    do {
        printf("*******************  Menu  ***********************\n");
        printf(" 1. Ajouter une vente                          \n");
        printf(" 2. Afficher la liste des ventes               \n");
        printf(" 3. Supprimer une vente                        \n");
        //printf(" 4. Modifier une vente                         \n");
        printf(" 4. Chercher une vente                         \n");
        printf(" 5. Quitter                                    \n");
        printf("*************************************************\n\n\n");
        printf("  Taper votre choix SVP : ");
        scanf("%d", &choix);
        switch (choix) {
            case 1: {
                system("cls");
                printf("\n********************* Ajouter ****************************\n");
                ajouterVente(L, ListProduit, ListClient);

                break;
            }
            case 2: {
                system("cls");
                printf("\n********************* Affichage **************************\n");

                afficherVentes(*L);
                break;
            }
            case 3: {
                system("cls");
                printf("\n********************* Suppression ************************\n");
                int CV;
                printf("  Saisie le code de vente a supprimer : ");
                scanf("%d", &CV);
                supprimerVente(L, CV);

                break;
            }
            /*case 4: {
                system("cls");
                printf("\n********************* Modification ***********************\n");
                // modifierVente(L);

                break;
            }*/
            case 4: {
                system("cls");
                printf("\n********************* Recherche **************************\n");
                int CV;
                printf("  Saisie le code de vente a cherche : ");
                scanf("%d", &CV);
                VenteElement* vv;
                if ((vv = chercherVente(*L, CV)) != NULL) {
                    printf("  il existe et leur  adresse est %d\n", vv);
                    printf("code: %d     date: %d/%d/%d       total: %2.lfDH\n", vv->vente->codeVente, vv->vente->date->jour, vv->vente->date->mois, vv->vente->date->annee, vv->vente->total);
                } else
                    printf(" il n'existe pas\a\a\a");

                break;
            }

            case 5: {
                system("cls");
                printf("  Fin de traitement  \n");
                break;
            }
            default: {
                system("cls");
                printf("  Votre choix n'est pas compatible avec les choix!!\n\a\a\a");
                break;
            }
        }

    } while (choix != 5);
    // L'enregistrement des donnes apres la sortie du boucle dans le fichier (gestion.txt)
    // printf("\n  l'enregistrement est entrain de s'effectue\n");
    // enregistrer(*L, pf_out);

    fclose(pf_out);
}

// ------------------------ MENU -----------------------------------//

//creation de la date du Vente
Date *createDate() {
    Date *date = (Date *)malloc(sizeof(Date));
    printf(" Entez  l'annee : ");
    scanf("%d", &date->annee);

    printf(" Entez  le mois : ");
    scanf("%d", &date->mois);

    printf(" Entrez le jour : ");
    scanf("%d", &date->jour);

    return date;
}

// afficher la date
void afficherDate(Date date) {
    printf("  le\t%d\t%d\t%d\n", date.jour, date.mois, date.annee);
}

// modifier la date
void modifierDate(Date **date) {
    int choix,
        new;
    printf("  Tapez 1 pour modifier le jour \n");
    printf("  Tapez 2 pour modifier le mois \n");
    printf("  Tapez 3 pour modifier l'annee \n");
    scanf("%d", &choix);
    switch (choix) {
        case 1: {
            printf("  Saisie le nouveau jour : ");
            scanf("%d", &new);
            (*date)->jour = new;
            break;
        }
        case 2: {
            printf("  Saisie le nouveau mois : ");
            scanf("%d", &new);
            (*date)->mois = new;
            break;
        }
        case 3: {
            printf("  Saisie la nouvelle annee  : ");
            scanf("%d", &new);
            (*date)->annee = new;
            break;
        }
        default: {
            printf(" Votre choix n'est pas compatibles avec les choix disponibles\n");
            break;
        }
    }
}

//creer une ligne de commande
Article *createLigneCommande(ProduitElement *P) {
    Article *nv;
    int test;
    int i = 0;
    double prix;
    char *designation = (char*)malloc(sizeof(char)*40);
    nv = (Article *)malloc(sizeof(Article));
    // nv->next = NULL;

    printf(" Saisie la Quantite : ");
    scanf("%d", &(nv->quantite));


        if (i != 0)
        printf("Votre code n'existe pas \n");

        printf("Tapez le code de produit : ");
        scanf("%d", &test);

        nv->produit = getProduitByCode(P, test);
        if(nv->produit == NULL){
        printf("Tapez la designation de produit : ");
        scanf("%s", designation);
        printf("Tapez le prix de produit : ");
        scanf("%lf", &prix);
         nv->produit =  createProduit(test,designation,prix);
        }
        i++;

    nv->subTotal = nv->produit->prix * (nv->quantite);
    // nv->TVA=nv->subTotal*1.6;
    return nv;
}

//fonction qui ajoute  la ligne de commande  a la liste chainnee

void ajouterLigneCommande(ArticleElement **listArticleElement, ProduitElement *P) {
    ArticleElement *nv;
    nv = (ArticleElement *)malloc(sizeof(ArticleElement));
    nv->article = createLigneCommande(P);
    nv->next = NULL;
    if (*listArticleElement == NULL) {
        *listArticleElement = nv;
        return;
    }
    ArticleElement *tmp = *listArticleElement;
    while (tmp->next) tmp = tmp->next;

    tmp->next = nv;
}

// Pour faire des modification sur une ligne de commande

void modifierLigneCommande(Vente *L) {
    int cm;  //codeModifier

    if (L->listArticle == NULL)
        printf("  Votre liste est deja vide \n");

    else {
        printf("  Sasie le code de produit de la ligne de commande que vous voulez modifier :  ");
        scanf("%d", &cm);

        Vente *p;
        p = L;

        while (p != NULL) {
            if (p->listArticle->article->produit->code == cm)
                break;

            p->listArticle = p->listArticle->next;
        }
        if (p->listArticle != NULL) {
            int choix;
            int Qty;
            printf("  Tapez 1 quantite\n");
            printf("  Tapez 2 produit\n");

            scanf("%d", &choix);

            switch (choix) {
                case 1: {
                    printf("  Saisie la nouvelle quantite : \n");
                    scanf(" %d ", &Qty);

                    p->total = p->total - p->listArticle->article->subTotal;
                    p->listArticle->article->quantite = Qty;
                    p->listArticle->article->subTotal = p->listArticle->article->quantite * p->listArticle->article->produit->prix;
                    p->total = p->total + p->listArticle->article->subTotal;
                    break;
                }
                case 2: {
                    int code;
                    char *designation;
                    double prix;
                    printf(" Tapez le code : ");
                    scanf(" %d  ", &code);

                    printf(" Tapez la nouvelle designation : ");
                    designation = allouerEspaceP();

                    printf("Tapez le nouveau prix : ");
                    scanf("%lf", &prix);

                    modifierProduit(p->listArticle->article->produit, code, designation, prix);
                    break;
                }
                default: {
                    printf("  Votre choix n'est pas compatible avec les choix disponibles \n");
                    break;
                }
            }
        } else
            printf("  Votre code n'est pas compatible avec les choix disponibles \n");
    }
}

//creation d une vente
Vente *createVente(ClientElement *client, ProduitElement *P) {
    Vente *nv;
    int nbr, i, test;
    char *nom = (char*)malloc(sizeof(char)*40);
    char *tel = (char*)malloc(sizeof(char)*40);
    char *prenom = (char*)malloc(sizeof(char)*40);
    ArticleElement *p;
    nv = (Vente *)malloc(sizeof(Vente));

    printf(" Saisie le code de votre vente : ");
    scanf("%d", &(nv->codeVente));

        printf(" Saisie le code de votre client : ");
        scanf("%d", &test);
        nv->client = chercherClient(client, test);
        if(nv->client == NULL){
            printf(" Saisie le nom de votre client : ");
        scanf("%s", nom);
        printf(" Saisie le prenom de votre client : ");
        scanf("%s", prenom);
        printf(" Saisie le tel de votre client : ");
        scanf("%s", tel);
            nv->client = createClient(test,nom,prenom,tel);
        }


    nv->date = createDate();

    nv->listArticle = NULL;

    printf("  Saisie le nombre des lignes de commandes : ");
    scanf("%d", &nbr);

    for (i = 1; i <= nbr; i++) {
        printf("  La %d ligne de commande :  \n ", i);

        ajouterLigneCommande(&nv->listArticle, P);
    }

    //  calculer le totale de la vente

    nv->total = 0;
    p = nv->listArticle;
    while (p != NULL) {
        nv->total += p->article->subTotal;
        p = p->next;
    }

    // rassembler les  lignes de commandes du meme produit

    ArticleElement *ptr, *tmp, *prev;

    for (ptr = nv->listArticle; ptr != NULL; ptr = ptr->next) {
        tmp = ptr->next;
        prev = ptr;

        while (tmp != NULL) {
            if (ptr->article->produit->code == tmp->article->produit->code) {
                p = tmp;
                ptr->article->quantite += tmp->article->quantite;

                ptr->article->subTotal = ptr->article->quantite * ptr->article->produit->prix;
                prev->next = tmp->next;

                tmp = tmp->next;

                free(p);
            } else {
                prev = tmp;
                tmp = tmp->next;
            }
        }
    }
    return nv;
}

// ajouter la vente a la liste des ventes

void ajouterVente(VenteElement **L, ProduitElement *P, ClientElement *C) {
    VenteElement *nv;
    nv = (VenteElement *)malloc(sizeof(VenteElement));

    nv->vente = createVente(C, P);

    nv->next = *L;
    *L = nv;
}

// la vente existe-elle dans la liste de Vente

VenteElement *chercherVente(VenteElement *L, int CV) {
    VenteElement *p;
    p = L;

    while (p != NULL) {
        if (p->vente->codeVente == CV)
            return p;
        p = p->next;
    }
    return NULL;
}

//  supprimer une vente de la liste des ventes
void supprimerVente(VenteElement **L, int CV) {
    if (*L == NULL)
        printf("  Votre liste est deja Vide !!!!! \n");

    else {
        VenteElement *p;
        p = *L;

        if ((*L)->vente->codeVente == CV) {
            *L = (*L)->next;
            free(p);
        } else {
            VenteElement *tmp;
            tmp = p;
            p = p->next;
            while (p != NULL) {
                if (p->vente->codeVente == CV) {
                    tmp->next = p->next;
                    free(p);
                    break;
                }
                tmp = p;
                p = p->next;
            }
        }
    }
}

 // modification  d'une vente
  //void modifierVente(VenteElement **L) {
    // if (*L == NULL) {
      //   printf("  Votre liste est deja vide\n ");
     //} else {
       //  VenteElement *p;
         //p = *L;

         //int CV, choix, nvCode;

         //printf("  Saisie le code de vente que vous voulez  modifier : ");
         //scanf(" %d ", &CV);

         //while (p != NULL) {
           //  if (p->vente->codeVente == CV)
                 //break;
             //p = p->next;
//         }
//         if (p != NULL) {
//             int code;

//             printf("  Tapez 1 pour modifier le code de vente                 \n");
//             printf("  Tapez 2 pour modifier la date du vente                 \n");
//             printf("  Tapez 3 pour modifier les lignes de commande du vente  \n");
//             printf("  Tapez 4 pour modifier le client qui a acheter la vente \n");
//             scanf("%d", &choix);

//             switch (choix) {
//                 case 1: {
//                     printf("  Saisie le nouveau  code ");
//                     scanf(" %d ", &code);
//                     p->vente->codeVente = code;
//                     break;
//                 }
//                 case 2: {
//                     modifierDate(&(p->vente->date));
//                     break;
//                 }
//                 case 3: {
//                     modifierLigneCommande(p->vente);
//                     break;
//                 }
//                 case 4: {
//                     break;
//                 }
//                 default: {
//                     printf("  Votre choix n'est pas compatible avec les choix dispnibles   \n");
//                     break;
//                 }
//             }
//         } else
//             printf("  Votre code n'existe pas dans la liste   \n");
//     }
// }

// Pour afficher les listes de commandes

void afficherArticleElement(ArticleElement *L) {
    if (L == NULL) return;
    ArticleElement *p;
    p = L;
    int i = 0;

    printf("\n--------------- La liste des commandes --------------\n");
    while (p != NULL) {
        printf(" \n*********** Ligne %d ***********\n ", ++i);
        afficherDetailProduit(p->article->produit);
        printf("\n  Quantite : %d \n", p->article->quantite);
        printf("  Totale de la ligne  : %2.lfDH", p->article->subTotal);

        //printf("  TVA : %lf ",(p->item->subTotal)*1.6);

        p = p->next;
        printf("\n\n******************************************\n\n");
    }
}

// Pour afficher la liste chainee de ventes
void afficherventeElement(VenteElement *L) {
    VenteElement *p;
    p = L;
    int i = 0;
    while (p != NULL) {
        printf("\n\n*********** Vente %d *************\n\n", ++i);
        printf("  Le code de la vente  : %d    \n", p->vente->codeVente);
        printf("  Le total             : %2.lf \n", p->vente->total);
        afficherDate(*(p->vente->date));
        printf("%d %s %s %s\n", p->vente->client->code, p->vente->client->nom, p->vente->client->prenom, p->vente->client->Tel);
        afficherArticleElement(p->vente->listArticle);
        p = p->next;

        printf("\n\n******************************************\n\n");
    }
}

void afficherVentes(VenteElement *L) {
    if (L == NULL) return;

    while (L) {
        printf("Vente       code: %d       Date: %d/%d/%d       total: %2.lf\n", L->vente->codeVente, L->vente->date->jour, L->vente->date->mois, L->vente->date->annee, L->vente->total);
        afficherArticleElement(L->vente->listArticle);
        L = L->next;
    }
}



/*int main(int argc, char const *argv[]) {
    ClientElement *clients = NULL;
    ProduitElement *produits = NULL;
    VenteElement *ventes = NULL;

    importClient(&clients);
    importProduits(&produits);

    menuVente(&ventes, clients, produits);

    return 0;
}
*/
