# Sujet de TP 3: Tas Binaire

## Exercice 1: Tas binaire borné

**Consigne** : Développer une structure de tas binaire avec un tableau de taille fixe dès la création. Gérer l'erreur si le tas est plein. Ne permettre que l'ajout de clés et renvoyer le nombre d'échanges effectués par chaque opération.

**Ce qui a été réalisé :**
Nous avons implémenté cette structure en langage C.

- Structure fixe : La fonction binaire_create(size_t capacity) alloue un tableau data dont la taille ne changera plus.

- Gestion des erreurs : Dans la fonction binaire_ajout, nous avons ajouté une condition if (a->size >= a->capacity) qui affiche un message d'erreur sur stderr et interrompt l'insertion si la limite est atteinte, respectant ainsi la contrainte d'absence de redimensionnement dynamique.

- Comptage des échanges : Nous avons configuré notre structure comme un "Min-Heap" (le nœud parent a toujours une valeur inférieure à ses enfants). La fonction binaire_diminuer, chargée de faire remonter la clé insérée à sa bonne place, possède un compteur swap qui s'incrémente à chaque échange avec le parent, et renvoie ce total à la fonction appelante.

## Exercice 2: Benchmark

**Consigne** : Effectuer des expériences sur l'efficacité en temps et en mémoire (ordre croissant, décroissant, aléatoire) en générant des fichiers .pdf avec une nomenclature stricte.
### Exemple:

Pour la mesure du temps amorti de l'ajout d'un élément dans l'ordre croissant en `C`,
le fichier de sortie sera `fixed_binary_heap_amortized_time_C_INCREASING.pdf`

On a donc:
- MESURE peut valoir \{ amortized_time, wasted_memory, swap \}. 
- LANGAGE peut valoir \{ C, CPP, Java, Python\}
- ORDRE peut valoir \{ increasing, descrasing, random\}


**Ce qui a été réalisé :**
Nous avons adapté la fonction main (dans main_binaire.c) pour mener trois expériences distinctes avec $N = 1 000 000$ insertions.
L'analyseur (analyzer_binaire.c) a été utilisé pour tracker le temps, les échanges et la mémoire.

- Ordre Croissant : Boucle d'insertion de $0$ à $N-1$.
- Ordre Décroissant : Boucle d'insertion de $N$ à $1$
- Ordre Aléatoire : Boucle d'insertion utilisant la fonction rand().

Pour chaque variante, les données ont été compilées par Gnuplot pour générer les fichiers PDF attendus (ex: fixed_binary_heap_swap_C_decreasing.pdf, fixed_binary_heap_wasted_memory_C_random.pdf, etc.). Le bug d'affichage des nanosecondes négatives lors de l'enregistrement du temps a également été corrigé pour assurer la fiabilité des mesures.

## Exercice 3: Notes d’expériences

**Consigne** : Commentez le résultat de vos expériences.

1. Analyse de la Mémoire Inutilisée (wasted_memory)
   - Observation commune : Quelle que soit l'expérience (croissante, décroissante ou aléatoire), la courbe de la mémoire inutilisée est strictement identique. Elle forme une droite parfaite qui descend de $10^6$ cases vides au début, à $0$ à la fin de l'exécution.
   - Explication : Puisque le tableau a une capacité fixée à la création (binaire_create(1000000)), toute la mémoire est allouée d'un coup. Chaque insertion réduit le nombre de cases vides de exactement $1$
   - Conclusion : Le tas binaire borné ne souffre d'aucun pic de "gaspillage" dû à une réallocation (contrairement aux tableaux dynamiques du TP1), mais son défaut majeur est son manque de flexibilité : la mémoire est bloquée dès le départ, qu'on l'utilise ou non.

2. Analyse des Échanges (swap)
   L'ordre d'insertion révèle les différents cas de complexité de l'algorithme :
   - Ordre Croissant (Meilleur cas) : La courbe reste plate à $0$. Puisque nous utilisons un "Min-Heap", chaque élément inséré est plus grand que tous les précédents. Il se place donc tout à la fin de l'arbre et respecte déjà la règle d'ordre par rapport à son parent. La fonction binaire_diminuer s'arrête immédiatement. Complexité : $O(1)$.
   - Ordre Décroissant (Pire cas) : La courbe forme des paliers logarithmiques qui montent et plafonnent à $19$ échanges. Chaque nouvel élément inséré est le plus petit du tableau. Il est donc placé tout en bas du tas, puis doit être échangé avec ses parents jusqu'à remonter à la racine absolue de l'arbre. La hauteur maximale d'un arbre binaire parfait de $10^6$ nœuds étant $\log_2(10^6) \approx 19.93$, il est logique que le nombre d'échanges soit plafonné à $19$. Complexité : $O(\log N)$.
   - Ordre Aléatoire (Cas moyen) : La majorité des éléments ne nécessitent que très peu d'échanges (généralement 1 ou 2) pour trouver une position valide. La courbe oscille faiblement près de $0$.

3. Analyse du Temps (amortized_time)
   - Les graphiques de temps reflètent directement le comportement observé avec les échanges.
   - Dans le cas croissant, le temps amorti est extrêmement bas et parfaitement constant ($O(1)$) car aucune opération de tri n'est nécessaire.
   - Dans le cas décroissant, le processeur doit réaliser jusqu'à $19$ comparaisons et réaffectations mémoire par insertion. Le temps d'exécution brut est légèrement supérieur et l'on perçoit le coût d'insertion en $O(\log N)$.
   - Malgré la différence entre le meilleur et le pire cas, la structure d'arbre du Tas Binaire se montre extrêmement performante : même au moment le plus coûteux, le nombre d'opérations reste infime comparé à la taille totale des données ($20$ opérations pour $1 000 000$ d'éléments).