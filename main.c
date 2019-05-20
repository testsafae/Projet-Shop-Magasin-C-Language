#include <stdio.h>
#include <stdlib.h>
#include "Produits.h"
#include "Client.h"
#include "Vente.h"

int main()
{
 printf("\n\n*************WelcomeTo--SF--Shop**************\n\n");
 int choix;

    printf("  Tapez 1 pour la gestion de Produit \n");
    printf("  Tapez 2 pour la gestion de Client  \n");
    printf("  Tapez 3 pour la gestion de vente   \n");
    scanf("%d", &choix);
    switch (choix) {
        case 1: {
            ProduitElement *L=NULL;
            menuProduit(&L);

            break;
        }
        case 2: {
            ClientElement *C=NULL;
            menuClient(&C);

            break;
        }
        case 3: {
            VenteElement *vl = NULL;
            ClientElement *lc = NULL;
            ProduitElement *lp = NULL;
            menuVente(&vl,lc,lp);

            break;
        }
        default: {
            printf(" Votre choix n'est pas compatibles avec les choix disponibles\n");
            break;
        }
    }




    return 0;
}
