#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include "binaire.h"
#include "analyzer_binaire.h"

# define N 1000000

int main() {
  int i;
  // Tableau dynamique.
  binaire_t * a = binaire_create(N);

  // Analyse du temps pris par les opérations.
  analyzer_t * time_analysis = analyzer_create();
  // Analyse du nombre d'échanges faits.
  analyzer_t * swap_analysis = analyzer_create(); // nb de copy -> nb de swap
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis = analyzer_create();

  // Mesure de la durée d'une opération.
  struct timespec before, after;
  clockid_t clk_id = CLOCK_REALTIME;
  // utilisé comme COMPTEUR pour savoir combien d'échanges ont été effectués.
  int swap;

  for(i = 0; i < N ; i++){
    // Ajout d'un élément et mesure du temps pris par l'opération.
    clock_gettime(clk_id, &before);

    swap = binaire_ajout(a, N - i);
    
    clock_gettime(clk_id, &after);
   
    // Enregistrement du temps pris par l'opération
    analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec);
    // Enregistrement du nombre de copies efféctuées par l'opération.
    // S'il y a eu réallocation de mémoire, il a fallu recopier tout le tableau.
    analyzer_append(swap_analysis, swap);
    // Enregistrement de l'espace mémoire non-utilisé.
    analyzer_append(memory_analysis,binaire_capacity(a)-binaire_size(a));
  }

  // Affichage de quelques statistiques sur l'expérience.
  fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis));
  fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis));
  fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis));
  fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis));

  // Sauvegarde les données de l'expérience.
  save_values(time_analysis, "../plots/fixed_heap_time_c.plot");
  save_values(swap_analysis, "../plots/fixed_heap_swap_c.plot");
  save_values(memory_analysis, "../plots/fixed_heap_memory_c.plot");

  // Nettoyage de la mémoire avant la sortie du programme
  binaire_destroy(a);
  analyzer_destroy(time_analysis);
  analyzer_destroy(swap_analysis);
  analyzer_destroy(memory_analysis);
  return EXIT_SUCCESS;
}