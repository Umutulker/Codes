import random
import numpy as np

b = np.arange(-0.9, 1, 0.1)
b_1 = np.round(b, decimals=2)
x = []
m = 100  # 10,100,1000
n = 2
a = 1  # 0.5 oder 1
for i in range(m):
    s = []
    s_0 = 1  # immer x_0 = 1
    s_1 = np.random.choice(b_1)
    s_2 = np.random.choice(b_1)
    s.append(s_0)
    s.append(s_1)
    s.append(s_2)
    x.append(s)

#print("Eingabe: ", x)

grenze = []
for i in range(2):
    p = []
    p_1 = np.random.choice(b_1)
    p_2 = np.random.choice(b_1)
    p.append(p_1)
    p.append(p_2)
    grenze.append(p)

print("Grenze: ", grenze)

q = (grenze[0][1]-grenze[1][1])/(grenze[0][0]-grenze[1][0])
y = []
for i in range(m):
    if (x[i][2] - grenze[0][1] - q*(x[i][1] - grenze[0][0])) >= 0:
        y_i = 1
    else:
        y_i = -1
    y.append(y_i)
print("Ausgangspunkte: ", y)

w = np.random.randint(-5, 5, size=3)

stufe = 0
k = 0
while k < 1000:
    r = random.randint(0, m-1)
    t = np.dot(w, x[r])
    if t >= 0:
        h = 1
        if y[r] != h:
            w = w + np.dot(a, np.dot(x[r], (y[r]-h)))
            stufe += 1
    elif t < 0:
        h = (-1)
        if y[r] != h:
            w = w + np.dot(a, np.dot(x[r], (y[r]-h)))
            stufe += 1
    k += 1

count = 0
for j in range(m):
    t = np.dot(w, x[j])
    if t >= 0:
        h = 1
        if y[j] != h:
            print("Durchführungen waren nicht genug!")
            print(stufe)
            break
    elif t < 0:
        h = (-1)
        if y[j] != h:
            print("Durchführungen waren nicht genug!")
            print(stufe)
            break
    count = count + 1

h = []
if count == m:
    print(stufe)
    print("beste Gewichte w ist: ", w)
    for k in range(m):
        h_i = np.sign(np.dot(w, x[k]))
        h.append(h_i)
    print("Beste Hypothese: ", h)
    print("Es ist zu sehen, dass mit der geeigneten Gewichte die Ausgangspunkte und Hypothesewerte gleich sind. h^*(x) = h(x) = y")


#  Achtung: Es sollte mehrmals geläuft werden, um das richtige Gewichtsfunktion zu finden. Falls es kein gültige Funktion gibt, dann werden sie  "Durchführungen waren nicht genug!" sehen.