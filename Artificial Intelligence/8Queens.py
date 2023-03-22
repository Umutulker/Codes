import random
import numpy as np
from numpy.random import choice
# p = 10   population size, even numbers for crossover
# n = 8   number of queens
# mp = 0.01  mutation probability
# pi = []   initial population
# pn = []   next population
# weight_list = []
best_fitness = int(8 * 7 / 2)


def create_population(p, n):
    pi = []
    for k in range(0, p):
        r = [random.randint(0, n - 1) for i in range(8)]
        pi.append(r)

    return pi  # initial population


def fitnessfn(p, n, Q):
    fit = []
    for k in range(0, p):
        clash = 0
        for y in range(0, n - 1):
            for i in range(y + 1, n):  # horizontal
                if Q[k][y] == Q[k][i]:
                    clash = clash + 1

                elif Q[k][y] == (Q[k][i] - (i - y)):
                    clash = clash + 1

                elif Q[k][y] == (Q[k][i] + (i - y)):
                    clash = clash + 1

        fit.append(int(best_fitness - clash))
    return fit


def weight(p, f):
    weight_list = []
    for i in range(0, p):
        weight_list.append(f[i] / sum(f))
    return weight_list


def selection(p, w):
    temp_array = [None] * p
    for i in range(0, p):
        temp_array[i] = i
    copy = np.random.choice(temp_array, p, w)
    return copy


def crossover(p, n, s, cp, Q):
    cspicked = []
    for i in range(0, p, 2):
        picked = []
        picked.append(Q[s[i]])
        picked.append(Q[s[i + 1]])
        random_probability = random.random()
        if random_probability <= cp:
            crossover_point = random.randint(0, n - 2)
            edge = crossover_point + 1

            cspicked1 = picked[0][:]  # crossover will happen
            cspicked2 = picked[1][:]

            while edge < n:  # crossover process
                cspicked1[edge] = picked[1][edge]
                edge += 1
            edge = crossover_point + 1
            while edge < n:
                cspicked2[edge] = picked[0][edge]
                edge += 1
            cspicked.append(cspicked1)
            cspicked.append(cspicked2)
        else:
            ncspicked1 = picked[0][:]  # crossover will not happen
            ncspicked2 = picked[1][:]
            cspicked.append(ncspicked1)
            cspicked.append(ncspicked2)
    return cspicked


def mutation(p, n, mp):
    pn = []
    for i in range(0, p):
        for j in range(0, n):
            random_probability = random.random()
            if random_probability <= mp:
                mutated_value = random.randint(0, n - 1)
                if mutated_value != c[i][j]:
                    c[i][j] = mutated_value
        pn.append(c[i])

    return pn


pop = create_population(10, 8)
# print(pop)

solutions = []
flag = False
while True:

    f = fitnessfn(10, 8, pop)
    # print(f)
    w = weight(10, f)
    # print(w)
    s = selection(10, w)
    # print(s)
    c = crossover(10, 8, s, 0.01, pop)
    # print(c)
    m = mutation(10, 8, 0.4)
    # print(m)
    Q = m

    fit_control = fitnessfn(10, 8, Q)

    for i in range(0, 10):
        if fit_control[i] == best_fitness:
            flag = True
            solutions.append(Q[i])
            print("Fitness value of one of the solutions: ", fit_control[i])
            print("One of the solutions: ", Q[i])
            break
    if flag:
        break

    pop = Q
