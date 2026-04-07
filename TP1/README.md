# TP1 : Tableaux dynamiques

## Exercice 1 : Analyse comparative (Alpha = 2)

Nous avons commencé par inspecter les fichiers main des différents langages pour vérifier que la même expérience (insertions successives) y était reproduite à l'identique. Nous avons ensuite exécuté le script sh launch_analysis.sh afin de lancer les différents benchmarks, ce qui a généré les graphiques au format PDF dans le répertoire plots sur lesquels se base notre analyse.Nous avons comparé les performances des tableaux dynamiques en C, C++, Java et Python avec un facteur d'agrandissement $\alpha = 2$ (la capacité double à chaque fois que le tableau est plein).


### 1. Analyse du Temps (Vitesse)
D'après le graphique `dynamic_array_amortized_time_alpha_2.pdf` :

* **Le langage C (courbe violette)** est le plus rapide et le plus stable. Le temps amorti est très proche de zéro. Cela s'explique car le C est un langage **compilé** directement en langage machine, avec une gestion manuelle de la mémoire très légère.
* **Le langage Python (courbe jaune/orange)** est le plus lent, avec un coût amorti beaucoup plus élevé et constant. C'est un langage **interprété** : chaque opération nécessite plus d'instructions processeur (vérification de type dynamique, gestion des objets lourds `PyObject`).
* **Java et C++** se situent entre les deux. On observe que Java devient plus efficace au fur et à mesure, probablement grâce à la compilation "Just-In-Time" (JIT) de la JVM qui optimise le code à la volée.

### 2. Analyse de la Mémoire (Espace gaspillé)
D'après le graphique `dynamic_array_wasted_memory_alpha_2.pdf` :

* On observe une courbe en **dents de scie** caractéristique.
* **Le fonctionnement :** Quand le tableau est plein (ex: taille 100), on alloue un nouveau tableau de taille 200 ($\alpha = 2$). À cet instant précis, on a 100 cases vides, soit **50% de mémoire gaspillée**.
* Au fur et à mesure qu'on ajoute des éléments, ce gaspillage diminue jusqu'à 0, puis remonte brutalement à la prochaine réallocation.
* **Problème potentiel :** Ce scénario peut être critique sur des systèmes à mémoire limitée (embarqué) ou avec de très gros volumes de données. Par exemple, si on a un tableau de 1 Go et qu'on ajoute un élément, le programme va demander 2 Go. Si la RAM n'a pas 2 Go libres, le programme crashe, alors qu'on n'avait besoin que d'un tout petit peu plus de place.

### 3. Analyse des Copies
D'après le graphique `dynamic_array_copy_alpha_2.pdf` :

* Les pics verticaux représentent les moments où le tableau est "plein" et doit être recopié.
* On voit que ces pics sont **espacés de manière exponentielle** (1, 2, 4, 8, 16...). Cela confirme bien que la capacité double à chaque étape.
* Bien que ces copies soient coûteuses (hauteur des pics), elles sont de plus en plus rares, ce qui permet de garder un **coût amorti** (moyen) constant et faible (O(1)).

## Exercice 2 : Modification du facteur de croissance (Alpha = 1.5)

Dans cette partie, nous avons modifié l'implémentation en langage C pour utiliser un facteur d'agrandissement $\alpha = 1.5$ au lieu de $2$.

### 1. Modifications effectuées
* **Code Source (`arraylist.c`)** : La fonction `arraylist_enlarge_capacity` a été modifiée pour calculer la nouvelle capacité selon la formule : `a->capacity = (size_t)(a->capacity * 1.5)`.
* **Sauvegarde (`main.c`)** : Les noms des fichiers de sortie ont été renommés en `dynamic_array_..._alpha_1_5.plot` pour distinguer ces résultats de l'expérience précédente.
* **Automatisation** : Un nouveau fichier de configuration Gnuplot `my_plot_result_v2` a été créé pour générer les graphiques spécifiques à cette valeur d'alpha.

Isolation du langage (`my_plot_result_v2`) : Nous avons édité ce fichier pour ne conserver que les instructions de tracé concernant le langage C, afin d'isoler nos courbes. Nous avons également mis à jour les noms des fichiers PDF en sortie pour refléter la bonne valeur d'alpha (`_alpha_1_5.pdf`).

Mise à jour de l'exécution (`launch_analysis.sh`) : Le script a été modifié pour appeler Gnuplot en utilisant notre nouveau fichier de configuration (`gnuplot plots/my_plot_result_v2`). Enfin, nous avons relancé le script complet pour générer les nouveaux résultats.


### 2. Comparaison des résultats : Alpha = 2 vs Alpha = 1.5

#### Gestion de la mémoire (Gaspillage)
* **Observation** : Avec $\alpha = 2$, l'espace mémoire inutilisé montait jusqu'à environ $1 \times 10^6$ éléments juste après la dernière réallocation.
* **Impact du changement** : Avec $\alpha = 1.5$, le pic de gaspillage est réduit. Pour un million d'éléments insérés, la capacité maximale n'atteint plus 2 millions mais environ 1.5 million.
* **Conclusion** : Réduire $\alpha$ permet d'économiser de la mémoire vive, ce qui est crucial pour les systèmes avec des ressources limitées.

#### Nombre de copies et performance
* **Fréquence des réallocations** : En observant le graphique des copies, les pics sont plus nombreux avec $\alpha = 1.5$ qu'avec $\alpha = 2$. 
* **Explication** : Comme le tableau s'agrandit moins à chaque étape, il atteint sa saturation plus souvent, déclenchant plus fréquemment la fonction `arraylist_enlarge_capacity`.
* **Temps amorti** : Bien que les réallocations soient plus fréquentes, le coût amorti reste $O(1)$. Cependant, la "constante" de temps est légèrement plus élevée car le processeur passe plus de temps à copier des données.

### 3. Bilan sur le compromis (Trade-off)
Cette expérience démontre que le choix de $\alpha$ est un arbitrage :
1. **Privilégier le temps ($\alpha \approx 2$)** : Moins de copies, mais beaucoup de mémoire gaspillée.
2. **Privilégier l'espace ($\alpha \approx 1.5$)** : Moins de mémoire gaspillée, mais plus de travail pour le processeur.