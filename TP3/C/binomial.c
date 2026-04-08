#include "binomial.h"
#include<stdio.h>
#include<stdlib.h>

arbre_t* binomial_create(int key) {
    // On alloue la mémoire pour un sommet seul -> arbre initial
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

//arbres triés par degré

//fusion_liste : qui trie -> on a deux tas qui vont être des ensembles d'arbres, on va en faire une seule liste où y a tous les tas et les deux arbres et on veut qu'elle soit triée en fonction du degré
//fusion_arbre : une fois qu'on a ces deux listes, on va fusionner les arbres de même degré
//attention aux cas critiques : ex pour la fusion -> si on a trois arbres du même degré -> il faut faire la fusion que sur les deux derniers éléments (1ere cd : est ce que le prochain arbre est de même degré ? 2eme cd : est ce que celui d'après aussi ? Si oui, on passe à l'arbre d'après et on fait la fusion)
//tri : ptr sur les deux, si 1 plus petit que l'autre, on l'ajoute sur la liste et on avance, si une des deux listes est finie on rajoute l'autre à la fin
//on retire sommet => detache ces enfants => deviennent des arbres => on fait consolidation /// il faut toujours maintenir proprio qu'on est inf à un degré et qu'on est ---

//fusionne les listes de racines de h1 et h2 par ordre croissant de degré
arbre_t* fusion_liste(tas_t *h1, tas_t *h2){
  if (h1->racine == NULL) return h2->racine;
  if (h2->racine == NULL) return h1->racine;
  arbre_t *debut = NULL;
  arbre_t **pos = &debut; // pointeur sur pointeur => faciliter insertion
  arbre_t *t1 = h1->racine;
  arbre_t *t2 = h2->racine;

  // on parcourt les deux listes
  while (t1 != NULL && t2 != NULL) {

      if(t1->degre <= t2->degre) {
        *pos = t1;
        t1 = t1->frere;
      } else {
        *pos = t2;
        t2 = t2->frere;
      }
      pos = &((*pos)->frere); // on avance position d"'écriture
  }
  if (t1 != NULL) { // ajout du reste
      *pos = t1;
  } else {
      *pos = t2;
  }
  return debut;
}

//fusion_liste : qui trie -> on a deux tas qui vont être des ensembles d'arbres, on va en faire une seule liste où y a tous les tas et les deux arbres et on veut qu'elle soit triée en fonction du degré
//fusion_arbre : une fois qu'on a ces deux listes, on va fusionner les arbres de même degré
//tri : ptr sur les deux, si 1 plus petit que l'autre, on l'ajoute sur la liste et on avance, si une des deux listes est finie on rajoute l'autre à la fin
//on retire sommet => detache ces enfants => deviennent des arbres => on fait consolidation /// il faut toujours maintenir proprio qu'on est inf à un degré et qu'on est ---


void fusion_arbre(tas_t *a1, tas_t *a2) {
  //on suppose que clé a1 <= clé a2 puis l'inverse
  if (a1-> racine->key <= a2-> racine->key) {
    //attention aux cas critiques : ex pour la fusion -> si on a trois arbres du même degré
    //-> il faut faire la fusion que sur les deux derniers éléments :
    //(1ere cd : est ce que le prochain arbre est de même degré ? 2eme cd : est ce que celui d'après aussi ? Si oui, on passe à l'arbre d'après et on fait la fusion)
  if((a1-> racine -> degre = a2 -> racine -> degre) && (a2-> racine -> degre = a2-> racine -> frere -> degre)){
    tas_t * h1;
    h1 -> racine = a2 -> racine;
    tas_t * h2;
    h2 -> racine = a2 -> racine -> frere;

    h2-> racine -> parent = h1;
    h2-> racine-> frere = h1-> racine->enfant; // a2 devient nouveau premier enfant de a1
    h1-> racine->enfant = h2;
    h1-> racine->degre = h1-> racine -> degre +1;
  } else {
    tas_t * h2;
    h2 -> racine = a2 -> racine;
    tas_t * h1;
    h1 -> racine = a2 -> racine -> frere;
    h2-> racine -> parent = h1;

    h2-> racine-> frere = h1-> racine->enfant; // a2 devient nouveau premier enfant de a1
    h1-> racine->enfant = h2;
    h1-> racine->degre = h1-> racine -> degre +1;
  }
}
}
// enlever racine, faire des enfants des racines dans une autre boite et les trier dans l'ordre inverse 