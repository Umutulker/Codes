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


def bfs(graph, start, ziel):
    besucht = []
    queue = []

    queue.append([start])  # addieren ertse knoten zu queue
    while queue:

        weg = queue.pop(0)  # ersten weg von queue nehmen (geloscht von queue!)

        knoten = weg[-1]  # letzte knoten von weg nehmen

        if knoten == ziel:  # falls die knoten ziel ist
            print("Markierte Liste:", besucht)
            return weg  # return den Weg

        for nachbar in graph.get(knoten, []): #nachbarknoten der letzten knoten
            if nachbar not in besucht:  # falls nachbarknoten nicht besucht wird
                if nachbar not in queue:  # falls nachbarknoten nicht in queue
                    neuerweg = list(weg)  # erstellen einen moglichen neuen weg von der liste des weges
                    neuerweg.append(nachbar)  # addieren nachbarknoten zu dem neuen weg
                    queue.append(neuerweg)  # addieren neuen weg zu queue
        besucht.append(knoten)  # markieren der knoten / addieren zu der liste von besucht


print(bfs(graph, 'W', 'Mu'))