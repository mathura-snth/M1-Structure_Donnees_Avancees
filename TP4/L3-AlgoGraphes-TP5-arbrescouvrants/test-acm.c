/**
 * test-acm.c
 * \version 3
 * \date novembre 2023
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "graph_mat-2.h"
#include "acm.h"

int main()
{
	graph_mat *g = gm_init(7);
	gm_add_edge(g, 0, 1, 7.);
	gm_add_edge(g, 0, 3, 5.);
	gm_add_edge(g, 1, 3, 9.);
	gm_add_edge(g, 1, 2, 8.);
	gm_add_edge(g, 1, 4, 7.);
	gm_add_edge(g, 2, 4, 5.);
	gm_add_edge(g, 3, 4, 15.);
	gm_add_edge(g, 3, 5, 6.);
	gm_add_edge(g, 4, 5, 8.);
	gm_add_edge(g, 4, 6, 9.);
	gm_add_edge(g, 5, 6, 11.);
	{ /* partie Prim */
		graph_mat *acm = gm_acm_prim(g, 0);
		if (acm != NULL) {
			gm_write_dot_with_mst(g, acm,
					"acm_prim.dot");
			system("dot -Tx11 acm_prim.dot");
			gm_free(acm);
		}
	}
	{ /* partie Kruskal */
		graph_mat *acm = gm_acm_kruskal(g);
		if (acm != NULL) {
			gm_write_dot_with_mst(g, acm,
					"acm_prim.dot");
			system("dot -Tx11 acm_prim.dot");
			gm_free(acm);
		}
	}
	gm_free(g);
	return EXIT_SUCCESS;
}
