graph = {'W': ['E', 'F', 'N'],
         'E': ['W'],
         'F': ['Ks', 'Ma', 'W'],
         'N': ['Mu', 'S', 'W'],
         'Ks': ['F', 'Mu'],
         'Ma': ['F', 'Kr'],
         'Kr': ['A', 'Ma'],
         'A': ['Kr', 'Mu'],
         'S': ['N'],
         'Mu': ['A', 'Ks', 'N'],
         }

# Kommentare sind in anderem Code verfugbar
def dfs(graph, start, ziel):
    stack = []
    besucht = []
    stack.append([start])
    while stack:
        weg = stack.pop(0)
        knoten = weg[-1]

        if knoten == ziel:
            return weg
        n = 0
        for nachbar in graph.get(knoten, []):
            if nachbar not in besucht:
                neuerweg = list(weg)
                neuerweg.append(nachbar)
                stack.insert(n, neuerweg)
                n = n + 1
        besucht.append(knoten)


print(dfs(graph, 'W', 'Mu'))
