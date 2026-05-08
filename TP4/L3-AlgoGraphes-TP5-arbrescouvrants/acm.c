/**
 * \file acm.c
 * \brief Calcul et représentation d'arbres couvrant minimaux (implémentation)
 * \version 3
 * \date novembre 2023
 */
#include "acm.h"

#include <stdlib.h>
#include <stdio.h>
#include <float.h>

/*************** Prim */

graph_mat *gm_acm_prim(const graph_mat *g, unsigned depart)
{
	return NULL;
}

/*************** Kruskal */
/* type et fonctions auxiliaires pour Kruskal : ne pas modifier */

/**
 * \brief Type \a struct edge avec cout
 *
 * Une arête est représentée par ses deux extrémités :
 * \a v et \a w et sa valeur \a value
 * Pour l'unicité de la représentation, on supposera que
 * \f$ v \leq w \f$.
 * On accèdera directement aux champs de cette structure.
 */
struct edge {
	int v; /**<plus petite extrémité de l'arête */
	int w; /**<plus grande extrémité de l'arête */
	double value; /**<coût de l'arête */
};

/**
 * \brief Compare les arêtes par coût
 * \param e1 adresse de la première arête
 * \param e2 adresse de la deuxième arête
 * \return -1, 0 ou 1 selon que le coût de e1 est respectivement inférieur,
 * égal ou supérieur au coût de e2.
 *
 * Cette fonction n'est utilisée que par \a sort_edges et ne doit pas être
 * modifiée.
 */
static int cmp_edges(const void *e1, const void *e2)
{
	const struct edge *f1 = e1;
	const struct edge *f2 = e2;
	if (f1->value == f2->value)
		return 0;
	if (f1->value < f2->value)
		return -1;
	return 1;
}

/**
 * \brief Trie les arêtes du graph_mat par coût croissant
 * \param g adresse du graph_mat à lire
 * \return un pointeur vers un tableau des arêtes de g triées par coût
 * croissant. Les boucles sont supprimées et en cas d'arêtes multiple, seule
 * l'arête de plus petit coût est présente dans le tableau. Si l'allocation du
 * tableau a échoué, la valeur de retour est \a NULL.
 *
 * La fonction appelante devra libérer la mémoire allouée au tableau avec la
 * fonction \a free.
 */
static struct edge *sort_edges(const graph_mat *g)
{
	unsigned v, w, i = 0;
	struct edge *tab = malloc(gm_m(g) * sizeof(struct edge));
	if (!tab)
		return NULL;
	for (v = 0; v < gm_n(g); ++v)
		for (w = v + 1; w < gm_n(g); ++w)
			if (gm_mult_edge(g, v, w)) {
				tab[i].v = v;
				tab[i].w = w;
				tab[i].value = gm_val_edge(g, v, w);
				++i;
			}
	qsort(tab, i, sizeof(struct edge), cmp_edges);
	return tab;
}
/* Calcul de l'ACM par Kruskal : à remplir ! */

graph_mat *gm_acm_kruskal(const graph_mat *g)
{
	return NULL;
}

int gm_write_dot_with_mst(const graph_mat *g, const graph_mat *acm, const char *nom_fichier)
{
	unsigned u, v;
	FILE *f = fopen(nom_fichier, "w");
	if (!f) { perror("fopen"); return -1; }
	fputs("graph {\n", f);
	for (u = 0; u < gm_n(g); ++u)
		fprintf(f, "\t%d;\n", u);
	fputs("\n", f);
	fputs("\tsubgraph g {\n", f);
	for (u = 0; u < gm_n(g); ++u)
		for (v = u; v < gm_n(g); ++v)
			if (gm_mult_edge(g, u, v) &&
				( u == v || !gm_mult_edge(acm, u, v)))
					fprintf(f, "\t\t%d -- %d [label = %.2f];\n",
						u, v, gm_val_edge(g, u, v));
	fputs("\t}\n", f);
	fputs("\tsubgraph acm {\n\t\tedge [color = red]\n", f);
	for (u = 0; u < gm_n(acm); ++u)
		for (v = u; v < gm_n(acm); ++v)
			if (gm_mult_edge(acm, u, v))
				fprintf(f, "\t\t %d -- %d [fontcolor = red, label = %.2f];\n",
					u, v, gm_val_edge(acm, u, v));
	fputs("\t}\n}\n", f);
	fclose(f);
	return 0;
}
