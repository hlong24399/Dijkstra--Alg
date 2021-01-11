from numpy import random as r

NUMBER_OF_COR = 10
NUMBER_OF_EDGE = 25
'''
Using numpy.random to generate random vertices and edges as needed

Note that:
    NUMBER_OF_EDGE have to be smaller or equal to Combination(NUMBER_OF_COR,2), since it is a simple undirected graph.
'''


def main():
    corfile = open("cor.txt", "w")
    xs = [r.randint(10,1190) for i in range(NUMBER_OF_COR)]
    ys = [r.randint(10,990) for i in range(NUMBER_OF_COR)]
    for i in range(NUMBER_OF_COR):
        # print(f"{i} {xs[i]} {ys[i]}")
        corfile.write(f"{i} {xs[i]} {ys[i]}\n")

    edgefile = open("edge.txt", "w")
    w = [r.randint(0,10) for i in range(NUMBER_OF_EDGE)]
    t = [(r.randint(0,NUMBER_OF_COR),r.randint(0,NUMBER_OF_COR))]
    flag = False
    while len(t) < NUMBER_OF_EDGE:
        a = r.randint(0,NUMBER_OF_COR)
        b = r.randint(0,NUMBER_OF_COR)
        for i in t:
            if (a,b) == (i[0],i[1]) or (b,a) == (i[0],i[1]) or (a,b) in t or a == b:
                flag = True
        if flag == False:
            t.append((a,b))
        else:
            flag = False

    for i in range(NUMBER_OF_EDGE):
        edgefile.write(f"{t[i][0]} {t[i][1]} {w[i]}\n")
main()
