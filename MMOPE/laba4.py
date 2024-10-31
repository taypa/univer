import numpy as np
import random
import math
import matplotlib.pyplot as plt

def func(x,  theta):
    return np.array([[x[0] ** theta[1] * x[1] ** theta[2],
                     theta[0] * theta[1] * x[0] ** (theta[1] - 1) * x[1] ** theta[2],
                     theta[0] * x[0] ** theta[1] * x[1] ** (theta[2] - 1)  * theta[2]]])

def getM(x, theta, N):

    m = func(x[0], theta).shape[1]
    M = np.zeros(shape=(m, m))
    for i in range(len(x)):
        M += (1. / N) * ((func(x[i], theta).T @ func(x[i], theta)))

    return M

def getD(M: np.array) -> np.array:
    return np.linalg.inv(M)

def d(x1: list, x2: list, D: np.array, thetaHat: np.array):
    return func(x1, thetaHat) @ D @ func(x2, thetaHat).T

def getDelta(x: list, xj: list, D: np.array,
             N: int, thetaHat: np.array) -> float:
    return ((1./ N) * (d(x,x,D, thetaHat) - d(xj, xj, D, thetaHat)) - \
    (1./ N**2) * (d(x,x,D, thetaHat) * d(xj,xj,D, thetaHat) - d(x,xj,D, thetaHat) ** 2))

def findMaxX(dot: list, D: np.array, N: int,
             grid: np.array, thetaHat: np.array) -> list[float, list]:
    maxDot = [grid[0], grid[0]]
    maxVal = getDelta(maxDot, dot, D, N, thetaHat)
    for x1 in grid:
        for x2 in grid:
            val = getDelta([x1,x2],  dot, D, N, thetaHat)
            if val > maxVal:
                maxVal = val
                maxDot = [x1, x2]
    return [maxVal, maxDot]

def findMaxPlan(x: list, D: np.array, N: int,
                grid: np.array, thetaHat: np.array):
    listOfMax = []

    for i in x:
        listOfMax.append(findMaxX(i, D, N, grid, thetaHat))
    return [*max(listOfMax), listOfMax.index(max(listOfMax))]


def makePlan(grid: np.array, m: int = 10) -> list:
    return list(map(lambda _:[random.choice(grid), random.choice(grid)], range(m)))

def makeY(plan: list, theta: list, p: float = 0.2) -> list:
    y = list(map(lambda x: theta[0] * x[0] ** theta[1] * x[1] ** theta[2], plan))
    return list(map(lambda x: x + random.normalvariate(0, p * x), y))

def makeX(plan: list) -> np.array:
    return np.array(list(map(lambda x: [1.0, math.log(x[0]), math.log(x[1])],plan)))

def drawDet(y: list) -> None:
    plt.title('Изменения определителя информационной матрицы')
    plt.plot([i + 1 for i in range(len(y))], y)
    plt.show()

def drawPlan(plan: list, name: str) -> None:
    plt.title(f'{name}  план')
    for x, y in plan:
        plt.scatter(x, y)
    plt.show()

def makeOptPlan(thetaHat: np.array, plan: list, grid: list, N: int) -> list:
    eps = 1e-3
    iter = 0
    listDet = []
    while True:
        M = getM(plan, thetaHat, N)
        print('det M = ',  np.linalg.det(M))
        listDet.append(np.linalg.det(M))
        D = getD(M)
        print('iter: ', iter)
        res = findMaxPlan(plan, D, N, grid, thetaHat)

        val, dot,idx = res[0], res[1], res[2]
        if val >= eps:
            plan[idx] = dot
        else:
            break
        iter += 1

    drawDet(listDet)

    return plan

def MNK(X: np.array, y:list) -> np.array:
    thetaHat = np.linalg.inv(X.T @  X) @ X.T @ y
    thetaHat[0] = math.e ** thetaHat[0]
    return thetaHat

def RSS(X: np.array, y: list, thetaHat: np.array) -> float:
    yHat = X @ thetaHat
    return (y - yHat) @ (y - yHat)

def getExper(theta:np.array, plan: list) -> tuple[float, float]:
    ARSS = 0
    AHat = 0
    for _ in range(100):
        y = makeY(plan, theta)
        y = np.log(y)
        X = makeX(plan)

        thetaHat = MNK(X, y)
        ARSS += RSS(X, y, thetaHat)
        AHat += (thetaHat - theta) @ (thetaHat - theta)
    
    ARSS /= 100
    AHat /= 100

    return ARSS, AHat

random.seed(42)
N = 15
grid = np.linspace(1, 10, 91)
plan = makePlan(grid)
theta = [0.1, 0.3, 0.6]
y = makeY(plan, theta)
X = makeX(plan)
y = np.log(y)

thetaHat = MNK(X, y)
print('ThetaHat', thetaHat)
firstPlan = makePlan(grid, N)
drawPlan(firstPlan, 'Случайный')

ARSS, AHat = getExper(theta, firstPlan)
print('Случайный план')
print(firstPlan)
print('Avg RSS ',  ARSS)
print('Средняя норма отклонения ', AHat)


optPlan = makeOptPlan(thetaHat, firstPlan,  grid, N)
drawPlan(optPlan, 'Оптимальный')

ARSS, AHat = getExper(theta, optPlan)
print('Оптимальный план')
print(optPlan)
print('Avg RSS ',  ARSS)
print('Средняя норма отклонения ', AHat)