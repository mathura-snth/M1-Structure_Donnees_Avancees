#include "binomial.h"
#include <stdio.h>
#include <stdlib.h>

arbre_t* binomial_create(int key) {
    arbre_t *res = (arbre_t *) malloc(sizeof(arbre_t));
    res->degre = 0;
    res->key = key;
    res->parent = NULL;
    res->enfant = NULL;
    res->frere = NULL;    
    return res;
}

tas_t* tas_create() {
    tas_t *tas = (tas_t *) malloc(sizeof(tas_t));
    if (tas != NULL) {
        tas->racine = NULL;
    }
    return tas;
}

// Sous-fonction 1 : Fusionne les listes de racines par ordre croissant de degré
arbre_t* fusion_liste(tas_t *h1, tas_t *h2){
    if (h1 == NULL || h1->racine == NULL) return h2 ? h2->racine : NULL;
    if (h2 == NULL || h2->racine == NULL) return h1->racine;
    
    arbre_t *debut = NULL;
    arbre_t **pos = &debut;
    arbre_t *t1 = h1->racine;
    arbre_t *t2 = h2->racine;

    while (t1 != NULL && t2 != NULL) {
        if(t1->degre <= t2->degre) {
            *pos = t1;
            t1 = t1->frere;
        } else {
            *pos = t2;
            t2 = t2->frere;
        }
        pos = &((*pos)->frere);
    }
    if (t1 != NULL) {
        *pos = t1;
    } else {
        *pos = t2;
    }
    return debut;
}

// Sous-fonction 2 : Accroche l'arbre 'y' comme enfant de l'arbre 'z'
void binomial_link(arbre_t *y, arbre_t *z) {
    y->parent = z;
    y->frere = z->enfant;
    z->enfant = y;
    z->degre++;
}

// OPÉRATION 1 : La fusion complète de deux tas
tas_t* tas_fusion(tas_t *h1, tas_t *h2) {
    tas_t *res = tas_create();
    res->racine = fusion_liste(h1, h2);
    
    if (res->racine == NULL) return res;

    arbre_t *prev_x = NULL;
    arbre_t *x = res->racine;
    arbre_t *next_x = x->frere;

    while (next_x != NULL) {
        // Cas 1 & 2 : Degrés différents, ou 3 arbres de même degré
        if ((x->degre != next_x->degre) || 
            (next_x->frere != NULL && next_x->frere->degre == x->degre)) {
            prev_x = x;
            x = next_x;
        } 
        // Cas 3 : Même degré, x a une clé plus petite
        else if (x->key <= next_x->key) {
            x->frere = next_x->frere;
            binomial_link(next_x, x);
        } 
        // Cas 4 : Même degré, next_x a une clé plus petite
        else {
            if (prev_x == NULL) {
                res->racine = next_x;
            } else {
                prev_x->frere = next_x;
            }
            binomial_link(x, next_x);
            x = next_x;
        }
        next_x = x->frere;
    }
    return res;
}

// OPÉRATION 2 : Ajout d'une clé
tas_t* binomial_insert(tas_t *tas, int key) {
    tas_t *nouveau_tas = tas_create();
    nouveau_tas->racine = binomial_create(key);
    // On fusionne le tas principal avec le nouveau mini-tas
    return tas_fusion(tas, nouveau_tas);
}

// OPÉRATION 3 : Extraction du minimum
int binomial_extract_min(tas_t *tas) {
    if (tas == NULL || tas->racine == NULL) {
        fprintf(stderr, "Erreur : Tas vide\n");
        return -1;
    }

    arbre_t *min_node = tas->racine;
    arbre_t *prev_min = NULL;
    arbre_t *next = min_node->frere;
    arbre_t *prev = min_node;

    // A. Trouver la racine minimale
    while (next != NULL) {
        if (next->key < min_node->key) {
            min_node = next;
            prev_min = prev;
        }
        prev = next;
        next = next->frere;
    }

    // B. Retirer la racine minimale de la liste
    if (prev_min == NULL) {
        tas->racine = min_node->frere;
    } else {
        prev_min->frere = min_node->frere;
    }

    // C. Inverser la liste de ses enfants
    arbre_t *enfant = min_node->enfant;
    arbre_t *prev_enfant = NULL;
    while (enfant != NULL) {
        arbre_t *next_enfant = enfant->frere;
        enfant->frere = prev_enfant;
        enfant->parent = NULL;
        prev_enfant = enfant;
        enfant = next_enfant;
    }

    // D. Fusionner les enfants inversés avec le reste du tas
    tas_t *tas_enfants = tas_create();
    tas_enfants->racine = prev_enfant;

    tas_t *tas_final = tas_fusion(tas, tas_enfants);
    tas->racine = tas_final->racine;

    int valeur_min = min_node->key;
    
    // Libération mémoire
    free(min_node);
    free(tas_enfants);
    free(tas_final);

    return valeur_min;
}