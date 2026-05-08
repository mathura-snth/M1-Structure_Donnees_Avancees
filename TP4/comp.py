import time
import random

# Version SANS compression de chemin
class UnionFindSansCompression:
    def __init__(self, n):
        self.parent = list(range(n))
        self.rank = [0] * n

    def find(self, x):
        # On remonte l'arbre sans modifier les parents en cours de route
        while self.parent[x] != x:
            x = self.parent[x]
        return x

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        if rootX != rootY:
            if self.rank[rootX] > self.rank[rootY]:
                self.parent[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parent[rootX] = rootY
            else:
                self.parent[rootY] = rootX
                self.rank[rootX] += 1

# Fonction Kruskal modifiée pour accepter la classe Union-Find en paramètre
def kruskal_custom(n, edges, uf_class):
    mst = []
    uf = uf_class(n)
    edges.sort(key=lambda x: x[2])
    for u, v, weight in edges:
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            mst.append((u, v, weight))
    return mst

if __name__ == "__main__":
    # Génération d'un grand graphe aléatoire dense
    n_sommets = 1000
    n_aretes = 150000
    grand_graphe = []
    for _ in range(n_aretes):
        u = random.randint(0, n_sommets - 1)
        v = random.randint(0, n_sommets - 1)
        if u != v:
            grand_graphe.append((u, v, random.randint(1, 100)))

    # Test AVEC compression
    debut = time.perf_counter()
    kruskal_custom(n_sommets, grand_graphe.copy(), UnionFind)
    temps_avec = time.perf_counter() - debut

    # Test SANS compression
    debut = time.perf_counter()
    kruskal_custom(n_sommets, grand_graphe.copy(), UnionFindSansCompression)
    temps_sans = time.perf_counter() - debut

    print(f"Temps avec compression : {temps_avec:.4f} secondes")
    print(f"Temps sans compression : {temps_sans:.4f} secondes")