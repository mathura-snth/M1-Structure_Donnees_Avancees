TP 4 — MST avec Union-Find
==========================

Introduction
------------

Ce TP a pour objectif d’implémenter un arbre couvrant de poids minimum (ou
Minimum Spanning Tree - MST) à l’aide de la structure de données **Union-Find**.
Cette structure est efficace pour gérer les sous-ensembles dans des algorithmes
de graphes, comme celui de *Kruskal*, qui construit un MST en ajoutant les arêtes
les moins coûteuses tout en évitant les cycles.

Objectifs du TP
---------------

- Comprendre le concpet d’un arbre couvrant de poids minimum.
- Implémenter la structure de données Union-Find.
- Appliquer l’algorithme de Kruskal pour construre un MST en utilisant
  Union-Find.

Notions théoriques
------------------

### Arbre couvrant de poids minimum

Un arbre couvrant de poids minimum d’un graphe est un sous-graphe connexe
acyclique (un arbre) qui relie tous les sommets du graphe avec un poids total
minimum. Le poids est la somme des coûts des arêtes qui composent l’arbre.

### Structure de données Union-Find

Union-Find est une structure de données pour gérer des ensembles disjoints.
Elle prend en charge deux opérations principales :

- **Find**: Trouver le représentant (ou chef) d’un ensemble.
- **Union**: Fusionner deux ensembles.

Pour rendre ces opérations plus efficaces, on utilise les techniques de
*compression de chemin* et *union par rang*.

Algorithme de Kruskal
---------------------

L’algorithme de Kruskal est une approche par arêtes croissantes pour trouver un
MST. Les étapes sont les suivantes :

1. Trier toutes les arêtes du graphe par poids croissant.
2. Initialiser une structure Union-Find pour gérer les sous-ensembles.
3. Parcourir les arêtes triées. Pour chaque arête, si les deux extrémités sont
   dans des ensembles différents (vérifié avec `Find`), on les relie dans le MST
   et on fusionne les ensembles (avec `Union`).
4. Répéter jusqu’à ce que le MST ait n − 1  arêtes.

Mise en œuvre
-------------

### Structure Union-Find en pseudocode

Voici le pseudocode de la structure Union-Find avec compression de chemin et
union par rang :

```
Fonction Find(x)
    if parent[x] == x then
        return x
    else
        return parent[x] = Find(parent[x])

Procédure Union(x, y)
    rootX = Find(x)
    rootY = Find(y)
    if rootX ̸!= rootY then
        if rank[rootX] > rank[rootY] then
            parent[rootY] = rootX
        else
            parent[rootX] = rootY
            if rank[rootX] == rank[rootY] then
                rank[rootY] = rank[rootY] + 1
```

Exercices
---------

1. Implémentez la structure de données Union-Find en util- isant le pseudocode
   fourni.
2. Testez votre implémentation en utilisant l’algorithme de Kruskal sur
   différents graphes.
3. Comparez les performances de votre solution avec et sans compression de
   chemin.
4. Justifiez pourquoi l’algorithme de Kruskal produit toujours un arbre couvrant
   de poids minimum.


