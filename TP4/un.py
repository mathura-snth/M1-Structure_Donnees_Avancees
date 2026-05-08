class UnionFind:
    def __init__(self, n):
        # Chaque élément est son propre parent au départ
        self.parent = list(range(n))
        # Le rang (profondeur de l'arbre) est initialisé à 0
        self.rank = [0] * n

    def find(self, x):
        if self.parent[x] != x:
            # Compression de chemin : on rattache le nœud directement à la racine
            self.parent[x] = self.find(self.parent[x])
        return self.parent[x]

    def union(self, x, y):
        rootX = self.find(x)
        rootY = self.find(y)
        
        if rootX != rootY:
            # Union par rang : l'arbre le plus petit est attaché sous la racine de l'arbre le plus grand
            if self.rank[rootX] > self.rank[rootY]:
                self.parent[rootY] = rootX
            elif self.rank[rootX] < self.rank[rootY]:
                self.parent[rootX] = rootY
            else:
                self.parent[rootY] = rootX
                self.rank[rootX] += 1
                
def kruskal(n, edges):
    mst = []
    uf = UnionFind(n)
    
    # 1. Trier toutes les arêtes du graphe par poids croissant
    edges.sort(key=lambda x: x[2]) 
    
    # 2 & 3. Parcourir les arêtes et utiliser Union-Find
    for u, v, weight in edges:
        if uf.find(u) != uf.find(v):
            uf.union(u, v)
            mst.append((u, v, weight))
            
    return mst

# --- TEST DE L'ALGORITHME ---
if __name__ == "__main__":
    # Graphe d'exemple : 6 sommets (0 à 5)
    # Format des arêtes : (sommet_u, sommet_v, poids)
    aretes = [
        (0, 1, 4), (0, 2, 4), (1, 2, 2), (1, 3, 5), 
        (2, 3, 5), (2, 4, 9), (3, 5, 6), (4, 5, 3)
    ]
    nombre_de_sommets = 6

    mon_mst = kruskal(nombre_de_sommets, aretes)
    
    print("Arêtes de l'Arbre Couvrant de Poids Minimum :")
    poids_total = 0
    for u, v, poids in mon_mst:
        print(f"Sommet {u} -- Sommet {v} (Poids: {poids})")
        poids_total += poids
    print(f"Poids total du MST : {poids_total}")