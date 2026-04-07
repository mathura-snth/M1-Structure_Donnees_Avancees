#ifndef __BINAIRE_H
#define __BINAIRE_H

#include <stddef.h>

/**
   Tableau dynamique d'entiers.
*/
typedef struct binaire_s{
  // Pointeur vers la zone de mémoire où les entiers seront stockées.
  int * data;
  // Taille réelle, ou capacité de stockage, du tableau.
  size_t capacity;
  // Nombre d'éléments stockés dans le tableau.
  size_t size;
} binaire_t;

/**
   Fonction d'initialisation d'un tableau dynamique.
   Complexité en temps/espace, pire et meilleur cas : O(1) 
   Attention, contrairement à ArrayList, ici on doit fixer la taille
   car le tas ne grandit pas.
   @return Un pointeur sur un tableau dynamique nouvellement alloué.
*/
binaire_t * binaire_create(size_t capacity);

/**
   Fonction de libération de la mémoire occupée par un tableau dynamique.
   Complexité en temps/espace, pire et meilleur cas : O(1)  
   @param a est un pointeur vers l'espace mémoire que la fonction va libérer.
*/
void binaire_destroy(binaire_t * a);

/**
   Ajoute une valeur dans le tableau.
   Complexité en temps/espace, pire cas : O(size)
   Complexité en temps/espace, meilleur cas : O(1)
   Complexité amortie : O(1)
   @param a est le tableau  auquel on souhaite ajouter une valeur.
   @param x est la valeur que l'on souhaite ajouter.
   @returns le nombre d'échanges effectués
*/
int binaire_ajout(binaire_t * a, int x);

/**
   Renvoie le nombre d'éléments stockés dans le tableau.
   Complexité en temps/espace, pire cas : O(1)
   @param a est un pointeur vers un tableau.
   @returns le nombre d'éléments stockés dans le tableau.
 */
size_t binaire_size(binaire_t * a);
/**
   Renvoie la capacité de stockage du tableau.
   Complexité en temps/espace, pire cas : O(1)
   @param a est un pointeur vers un tableau.
   @returns la capacité de stockage du tableau.
 */
size_t binaire_capacity(binaire_t * a);

/**
 * 
*/
int binaire_diminuer(binaire_t * a, int i);

size_t binaire_size(binaire_t * a);

size_t binaire_capacity(binaire_t * a);



void afficher_tas(binaire_t * a);




#endif
 
