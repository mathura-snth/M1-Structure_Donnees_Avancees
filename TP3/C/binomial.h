#ifndef BINOMIAL_H
#define BINOMIAL_H

typedef struct arbre_s {
    int key;
    int degre;
    struct arbre_s *parent;
    struct arbre_s *enfant;
    struct arbre_s *frere;
} arbre_t;

typedef struct tas_s {
    arbre_t *racine;
} tas_t;

// Création
arbre_t* binomial_create(int key);
tas_t* tas_create(void);

// Opérations principales demandées par l'énoncé
tas_t* tas_fusion(tas_t *h1, tas_t *h2);
tas_t* binomial_insert(tas_t *tas, int key);
int binomial_extract_min(tas_t *tas);

#endif