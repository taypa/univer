import numpy as np
import matplotlib.pyplot  as plt
import scipy.linalg as lng
import random
from prettytable  import PrettyTable

def func(x: list) -> np.array:
    return np.array([[1, x[0], x[1], x[0] * x[1], x[0]**2, x[1]**2]])

def getM(p: list, x: list, m: int) -> np.array:
    M = np.zeros(shape=(m, m))
    n = len(p)

    for i in range(n):
        M += p[i] * (func(x[i]).T @ func(x[i]))

    return M

def getD(M: np.array) -> np.array:
    return lng.inv(M)

def d(x1: list, x2: list, D:np.array):
    return func(x1) @ D @ func(x2).T

def getDelta(x: list, xj: list, D: np.array, N: int) -> float:
    return ((1./ N) * (d(x,x,D) - d(xj, xj, D)) - \
    (1./ N**2) * (d(x,x,D) * d(xj,xj,D) - d(x,xj,D) ** 2))[0][0]

def findMaxX(dot: list, D: np.array, N: int, grid: np.array)->list[float, list]:
    maxDot = [grid[0], grid[0]]
    maxVal = getDelta(maxDot, dot, D, N)
    for x1 in grid:
        for x2 in grid:
            val = getDelta([x1,x2],  dot, D, N)
            if val > maxVal:
                maxVal = val
                maxDot = [x1, x2]
    return [maxVal, maxDot]

def findMaxPlan(x: list, D: np.array, N: int, grid: np.array):
    listOfMax = []

    for i in x:
        listOfMax.append(findMaxX(i, D, N, grid))
    return [*max(listOfMax), listOfMax.index(max(listOfMax))]

def printPlan(x: list, title: str) -> None:
    for i in x:
        plt.scatter(i[0],i[1])
    plt.title(title)
    plt.axhline(y=0, color='k')
    plt.axvline(x=0, color='k')
    plt.show()


def printTable(x,  p) -> None:
    x1,x2 = [], []
    for i in range(len(x)):
        x1.append(round(x[i][0], 3))
        x2.append(round(x[i][1], 3))

    table = PrettyTable()
    table.add_column('x1',x1)
    table.add_column('x2',x2)
    table.add_column('p',p)
    print(table)

eps = 1e-3
m = 6

n = [20,25,30,35,40]
dims = [10,20]
table = PrettyTable(["Количество наблюдений/Сетка", "10", "20"])
for N in n:
    row = [N]
    for gridDim in dims:
# N = 40
# gridDim = 20

        s = 0
        grid = np.linspace(-1,1,gridDim)
        p = [1/N for _  in range(N)]
        random.seed(42)
        x = [[random.choice(grid),random.choice(grid)] for _ in range(N)]

        # printPlan(x, f'Начальный план c {N} наблюдениями')
        # printTable(x,p)

        while True:
            s += 1
            M = getM(p, x,m)
            D = getD(M)

            res = findMaxPlan(x, D, N, grid)
            val, dot,idx = res[0], res[1], res[2]

            if val >= eps:
                x[idx] = dot
            else:
                break
            print('iter', s)
        row.append(lng.det(M))
        # printPlan(x, f'План на {s} итерации c {N} наблюдениями')
        # printTable(x,p)
    table.add_row(row)

print(table)