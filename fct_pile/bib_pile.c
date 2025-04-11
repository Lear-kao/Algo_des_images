#include "../header/headrs_type.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


pile* empiler(pile **p, int x, int y) {
    pile *nouveau = malloc(sizeof(pile));
    if (nouveau == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    nouveau->x = x;
    nouveau->y = y;
    nouveau->suite = *p;
    *p = nouveau;
}

pile* depiler(pile *p, int **valeur_retour) {
    if (p == NULL) {
        printf("Pile vide\n");
        return NULL;
    }

    pile *temp = p;
    *valeur_retour[0] = p->x;
    *valeur_retour[1] = p->y;
    p = p->suite;
    free(temp);
    return p;
}


int rechercher(pile *p, int x, int y) {
    while (p != NULL) {
        if (p->x == x && p->y == y)
            return 1; // trouvé
        p = p->suite;
    }
    return 0; // non trouvé
}

void afficher_pile(pile *p) {
    printf("Pile : ");
    while (p != NULL)
    {
        printf("%d-%d -> ", p->x, p->y);
        p = p->suite;
    }
    printf("NULL\n");
}
