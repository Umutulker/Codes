import random
import numpy as np
import warnings

x = []
m = 100  # 10,100,1000
n = 2
a = 0.01  # 0.1 , 0.01 , 0.001
b = np.arange(-0.9, 1, 0.1)
b_1 = np.round(b, decimals=2)
grenze_x = 0
c = 0

for i in range(m):
    s = []
    s_0 = 1  # immer x_0 = 1
    s_1 = random.choice(b_1)
    s_2 = random.choice(b_1)
    s.append(s_0)
    s.append(s_1)
    s.append(s_2)
    x.append(s)

print("Eingabe: ", x)

grenze = []
for i in range(2):
    p = []
    p_1 = np.random.choice(b_1)
    p_2 = np.random.choice(b_1)
    p.append(p_1)
    p.append(p_2)
    grenze.append(p)

print("Grenze: ", grenze)
v = grenze[0][1]-grenze[1][1]
o = grenze[0][0]-grenze[1][0]

if v == 0:
    q = 0
    eq = grenze[1][1]
    grenze_x = grenze[1][0]
    c = eq - (q*grenze_x)
elif o == 0:
    grenze_x = grenze[1][0]
    q = 4563456
else:
    q = v/o
    eq = grenze[1][1]
    grenze_x = grenze[1][0]
    c = eq - (q*grenze_x)

y = []
if q == 4563456:
    for i in range(m):
        if x[i][1] >= grenze_x:
            y_i = 1
        else:
            y_i = 0
        y.append(y_i)
else:
    eq = grenze[1][1]
    grenze_x = grenze[1][0]
    c = eq - (q*grenze_x)
    for i in range(m):
        eq = q*x[i][1] + c
        if x[i][2] >= eq:
            y_i = 1
        else:
            y_i = 0
        y.append(y_i)
print("Ausgabe: ", y)

#training:
w = np.random.randint(-20, 20, size=3)
stufe = 0
k = 0
while k < 2000:
    r = random.randint(0, m-1)
    z = np.dot(w, np.transpose(x))
    sigfunk = 1/(1 + np.exp(-z))
    if sigfunk[r] >= 0.5:
        h = 1
        if y[r] != h:
            diff = []
            for i in range(m):
                diff_t = sigfunk[i] - y[i]
                diff.append(diff_t)
            w = w - ((a / m)*(np.dot(np.transpose(x), diff)))
            stufe += 1
    elif sigfunk[r] < 0.5:
        h = 0
        if y[r] != h:
            diff = []
            for i in range(m):
                diff_t = sigfunk[i] - y[i]
                diff.append(diff_t)
            w = w - ((a / m)*(np.dot(np.transpose(x), diff)))
            stufe += 1
    k += 1

count = 0
z = np.dot(w, np.transpose(x))
sigfunk = 1/(1 + np.exp(-z))
for j in range(m):
    if sigfunk[j] >= 0.5:
        h = 1
        if y[j] != h:
            print("Durchführungen waren nicht genug!")
            print(stufe)
            break
    elif sigfunk[j] < 0.5:
        h = 0
        if y[j] != h:
            print("Durchführungen waren nicht genug!")
            print(stufe)
            break
    count = count + 1

h = []
if count == m:
    print(stufe)
    print("beste Gewichte w ist: ", w)

warnings.filterwarnings('ignore')  # für np.exp warning.

#  Achtung: Es sollte mehrmals geläuft werden, um das richtige Gewichtsfunktion zu finden. Falls es kein gültige Funktion gibt, dann werden sie  "Durchführungen waren nicht genug!" sehen.
