# Sujet de TP 3 : Tas Binomial

Dans le cadre de ce TP, nous avons développé une structure de Tas Binomial en langage C. Contrairement aux tas binaires classiques stockés dans des tableaux, le tas binomial est implémenté sous forme d'une forêt d'arbres binomiaux, ce qui nécessite une gestion fine des pointeurs.

## 1. Choix de la structure de données (Les Nœuds)

Pour représenter un tas binomial, nous avons opté pour une représentation par liens de parenté et de fratrie. Chaque nœud (arbre) possède la structure suivante :
* `key` : La valeur stockée (entier).
* `degre` : L'ordre de l'arbre binomial (nombre d'enfants directs).
* `parent` : Pointeur vers le nœud parent.
* `enfant` : Pointeur vers le premier enfant (le plus à gauche).
* `frere` : Pointeur vers le frère immédiatement à droite.

Le Tas Binomial (`tas_t`) est simplement défini par un pointeur `racine` qui pointe vers le premier arbre de la liste des racines. Cette structure *Enfant-gauche / Frère-droit* est optimale car elle permet de représenter des arbres avec un nombre arbitraire d'enfants tout en gardant une taille de nœud fixe en mémoire ($O(1)$ par nœud).

## 2. Choix d'implémentation des Opérations fondamentales

### A. La Fusion de deux tas (L'opération centrale)
La fusion est le cœur du tas binomial. Nous l'avons séparée en sous-fonctions pour plus de clarté :
1. **`fusion_liste`** : Cette fonction fusionne les listes des racines des deux tas pour créer une seule liste triée par ordre croissant de degré.
2. **`fusion_arbre`** : Cette fonction lie deux arbres de *même degré*. Pour respecter la propriété du Min-Heap, la racine ayant la plus grande clé devient le premier `enfant` de la racine ayant la plus petite clé, et le degré du parent est incrémenté.
3. **Consolidation** : Un parcours de la liste fusionnée lie systématiquement les arbres de même degré jusqu'à ce qu'il n'y ait plus qu'au maximum un arbre de chaque degré. La complexité globale de cette fusion est maintenue en $O(\log N)$.

### B. L'Ajout d'une clé (Insertion)
Plutôt que de coder une logique d'insertion complexe de zéro, nous avons réutilisé la puissance de la fusion.
* **Logique :** Pour ajouter une valeur $X$, nous créons un nouveau tas binomial vierge, nous y insérons $X$ (qui devient un arbre de degré 0), puis nous appelons notre fonction de fusion entre le tas principal et ce mini-tas.
* **Avantage :** Le code est extrêmement court, réutilisable et garantit une complexité amortie en $O(1)$ (et $O(\log N)$ dans le pire des cas).

### C. L'Extraction du minimum (`extract_min`)
Le tas binomial est un Min-Heap, le minimum est donc obligatoirement l'une des racines de la liste principale.
* **Logique :** 1. Nous parcourons la liste des racines pour trouver celle contenant la valeur minimale.
  2. Nous détachons cette racine de la liste.
  3. Nous récupérons tous ses enfants. Par définition, les enfants d'un arbre binomial d'ordre $K$ sont des arbres binomiaux d'ordres $K-1, K-2, ..., 0$. Nous inversons l'ordre de ces enfants pour en faire une nouvelle liste valide de racines (triée par degré croissant).
  4. Nous créons un tas temporaire avec cette nouvelle liste, que nous fusionnons avec le reste du tas d'origine.
* **Complexité :** La recherche du minimum prend $O(\log N)$, l'inversion prend $O(\log N)$ et la fusion prend $O(\log N)$. L'opération entière respecte donc la limite théorique de $O(\log N)$.

## Conclusion
Le tas binomial est plus complexe à coder qu'un tas binaire dans un tableau à cause de la manipulation intensive des pointeurs. Cependant, cette implémentation nous permet d'obtenir une opération de fusion de deux tas de taille $N$ en $O(\log N)$, contre $O(N)$ pour un tas binaire classique, ce qui rend cette structure redoutable pour les algorithmes nécessitant de fréquentes fusions d'ensembles de données.