#include <stdio.h>
#include <stdlib.h>
#include "binomial.h"

int main() {
    printf("Création d'un tas binomial vide...\n");
    tas_t *mon_tas = tas_create();

    printf("Insertion de 10...\n");
    mon_tas = binomial_insert(mon_tas, 10);
    
    printf("Insertion de 20...\n");
    mon_tas = binomial_insert(mon_tas, 20);
    
    printf("Insertion de 5...\n");
    mon_tas = binomial_insert(mon_tas, 5);
    
    printf("Insertion de 15...\n");
    mon_tas = binomial_insert(mon_tas, 15);

    printf("Insertion de 2...\n");
    mon_tas = binomial_insert(mon_tas, 2);

    printf("\n--- Test de l'extraction ---\n");
    printf("Minimum extrait (attendu : 2)  -> %d\n", binomial_extract_min(mon_tas));
    printf("Minimum extrait (attendu : 5)  -> %d\n", binomial_extract_min(mon_tas));
    printf("Minimum extrait (attendu : 10) -> %d\n", binomial_extract_min(mon_tas));

    return EXIT_SUCCESS;
}