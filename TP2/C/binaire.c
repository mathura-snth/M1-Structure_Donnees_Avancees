#include "binaire.h"
#include<stdio.h>
#include<stdlib.h>

// même structure qu'arrayList donc même fonctions create et destroy
// les enfants du sommet i sont à 2i et 2i+1 MAIS ATTENTION en C, les indices commencent à 0
// 1ère étape : définir les accesseurs et vérifier qu'ils fonctionnent

binaire_t * binaire_create(size_t capacity){
  binaire_t * res = (binaire_t *) malloc( sizeof(binaire_t) );
  res->data = (int *) malloc( sizeof(int) * capacity ); // la capacité est fixée
  res->capacity = capacity;
  res->size = 0;
  return res;
}

void binaire_destroy(binaire_t * a){
  if( a != NULL ){
    if( a->data != NULL )
      free( a->data );
    free( a );
  }
}

size_t binaire_size(binaire_t * a){
  return ( a!=NULL) ? a->size : -1;
}

size_t binaire_capacity(binaire_t * a){
  return ( a!=NULL) ? a->capacity : -1;
}

int binaire_ajout(binaire_t * a, int x){
  // si la taille est plus grande que la capacité -> erreur
  if(a -> size >= a -> capacity){
    fprintf(stderr, "Erreur : Le tas est rempli.\n");
    return -1;
  }
  // si la taille n'est pas plus grande que la capacité -> on ajoute x tout en bas 
  a -> data[a -> size] = x; // on ajoute x à la dernière position
  a -> size += 1; // on augmente le nombre d'éléments stockés
  return binaire_diminuer(a, a -> size -1); // on la place à sa bonne position (size-1 car on commence à 0)
}

// pour trouver le fils : en C on commence à 0 -> fils gauche = 2(i+1)-1 = 2i+1 || fils droit = 2(i+1)+1-1 = 2i+2 donc le parent de fils gauche : 
int binaire_diminuer(binaire_t * a, int i){ // avec int x la nouvelle valeur de l'élément a[i]
    int swap = 0;
// pas besoin de s occuper des décimales car C le fait déjà (tronque)
// comme les arbres binaires sont vus comme des tas
// (priorisation version min -> parent a toujours plus petite valeur que ses enfants)
// on va prendre l'élément qu'on vient d'ajouter pour bien le placer :
    while (i > 0) {
        int temp = a->data[i];
        size_t parent = (i - 1) / 2;
        if (a->data[i] < a->data[parent]) {// on échanger si l'enfant est plus petit
            int temp = a->data[i];
            a->data[i] = a->data[parent];
            a->data[parent] = temp;

            swap++;
            
            i = parent; // l'enfant devient le nouveau point de départ pour la prochaine itération
        } else {
            break;
        }
    }
    return swap;
}

void afficher_tas(binaire_t * a) {
    if(!a) return;
    printf("Tas (%lu/%lu) : [ ", a->size, a->capacity);
    for (size_t i = 0; i < a->size; i++) {
        printf("%d ", a->data[i]);
    }
    printf("]\n");
}