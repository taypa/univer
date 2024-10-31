import numpy as np
import matplotlib.pyplot  as plt
import scipy.linalg as lng

f = []

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

def getFunc(M: np.array) -> float:
    return np.log(lng.det(M))

def DOptim(M: np.array) -> float:
    return lng.det(M)

def findX(D: np.array) -> tuple[float, list]:
    grid = np.linspace(-1, 1, 401)

    point_max = [grid[0], grid[0]]
    fi_max = (func(point_max) @ D @ func(point_max).T)[0][0]

    for p1 in grid:
        for p2 in grid:
            tmp = [p1, p2]
            f = (func(tmp) @ D @ func(tmp).T)[0][0]
            
            if f > fi_max:
                fi_max = f
                point_max = tmp

    return fi_max, point_max

def addP(p: list, x: list, curFunc: float) -> list:
    fun = curFunc - 1
    gamma = 2
    a = 1 / len(p)
    
    while fun <= curFunc:
        newP = p.copy()
    
        for i in range(len(p)):
            newP[i] = (1-a) * newP[i]
    
        newP.append(a)
        fun = getFunc(getM(newP, x, 6))
        a /= gamma
    
    return newP

def findCloseDots(X: list, x1: list) -> int:
    mu = 0.1

    for i in range(len(X)):
        vec = np.array([x1[0] - X[i][0], x1[1] - X[i][1]])
        scal = vec @ vec
    
        if np.sqrt(scal) ** 2 < mu:
            return i
    
    return -1

def removeDots(x: list, p: list) -> tuple [list, list]:
    newX = [x[0]]
    newP = [p[0]]
    for i in range(1, len(x)):
        idx = findCloseDots(newX, x[i])
    
        if idx == -1:
            newX.append(x[i])
            newP.append(p[i])
        else:
            newP[idx] += p[i]
    
    return newX, newP

def delSmallWeights(x: list, p: list) -> tuple[list, list]:
    s = 0
    idx = 0
    eps = 0.02

    for i in range(len(p)):
        if p[i] < eps:
            s += p[i]
            p[i] = 0
            x[i] = [0,0]
            idx += 1

    for _ in range(idx):
        p.remove(0)
        x.remove([0, 0])

    s /= len(p)

    for i in range(len(p)):
        p[i] += s
    
    return x, p

def addNewPoint(x: list, p: list) -> tuple[float, float, list, list]:
    M = getM(p, x, 6)
    D = getD(M)

    curFunc = getFunc(M)
    fi_max, point_max = findX(D)
    x.append(point_max)
    p = addP(p, x, curFunc)
    eps = abs(fi_max) * 0.01
    delta = abs(-fi_max + np.trace(np.dot(M, D)))
    return delta, eps, x, p

def writeData(filename: str, x: list, p: list) -> None:
    with open(f'{filename}.txt', 'w') as f:
        for i in x:
            f.write(f'{str(i[0])} {str(i[1])}\n')
        for i in p:
            f.write(str(i) + "\n")
    f.close()
    
if __name__ == "__main__":
    # Формируем входные данные, согласно варианту
    line = np.linspace(-1, 1, 5)
    x = []
    for i in line:
        for j in line:
            x.append([i,j])
    p = np.ones((25,)) * 0.04
    p = p.tolist()

    s, iter_out = 0, 0 
    m ,n = 6, 25
    delta, cond = 1, 2
    ex, eps = 1, 0.01

    ex_l, eps_l = [],[]

    for i in x:
        plt.scatter(i[0], i[1])
    plt.title('Начальный план')
    plt.axhline(y=0, color='k')
    plt.axvline(x=0, color='k')
    plt.show()

    # Задаем начальные значения
    M = getM(p, x, m)
    D = getD(M)

    while abs(ex) > eps:
        # Формирование плана
        while cond > delta:
            cond, delta, x, p = addNewPoint(x,  p)
            if s % 10 == 0:
                print('ITER ', s)
            s += 1
        if iter_out == 0:
            writeData("output_dirty",  x, p)
            
        # Очистка плана
        x, p = removeDots(x, p)
        if iter_out % 10 == 0:
            writeData(f"removeDots{iter_out}",  x, p)

        x, p = delSmallWeights(x, p)
        if iter_out % 10 == 0:
            writeData(f"deletedSmallWeights{iter_out}",  x, p)


        M = getM(p, x, 6)
        curFunc = getFunc(M)
        f.append(curFunc)
        ex, eps, x, p = addNewPoint(x,  p)
        ex_l.append(ex)
        eps_l.append(eps)
        print("ITER OUT ", iter_out)
        print(eps, " ", ex)
        iter_out += 1

    writeData('optimal', x, p)

    plt.plot(range(len(f)), f)
    plt.title('График изменения функционала')
    plt.show()

    plt.plot(range(len(ex_l)), ex_l, label='Условие')
    plt.plot(range(len(eps_l)), eps_l, label='delta')
    plt.title('График изменения необходимых и достаточных условий оптимальности')
    plt.show()

    for i in x:
        plt.scatter(i[0], i[1])
    plt.title('Оптимальный план')
    plt.axhline(y=0, color='k')
    plt.axvline(x=0, color='k')
    plt.show()