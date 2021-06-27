import sys
import fileinput
import ntpath
from os import listdir
from os.path import isfile, join
import math
from collections import namedtuple

Point = namedtuple("Point", ['x', 'y'])


DEBUG = 0


def length(point1, point2):
    return math.floor(math.sqrt((point1.x - point2.x)**2 + (point1.y - point2.y)**2))


def parse_input(instance_path, instance_name):
    instance_file = open(instance_path, "r")
    input_data = instance_file.read()
    instance_file.close()

    # parse the input
    lines = input_data.split('\n')

    nodeCount = int(lines[0])

    points = []
    for i in range(1, nodeCount+1):
        line = lines[i]
        parts = line.split()
        points.append(Point(float(parts[0]), float(parts[1])))

    if DEBUG >= 1:
        print(f"Numero de vertices = {nodeCount}")

    if DEBUG >= 2:
        print("Lista de vertices:")
        for node in points:
            print(f"({node.x}, {node.y})")
        print()

    instance_sol_file = open(instance_name + ".sol", "r")
    solution_data = instance_sol_file.read()
    instance_sol_file.close()

    # parse the solution
    lines = solution_data.split('\n')

    firstLine = lines[0].split()
    sol_value = float(firstLine[0])
    secondLine = lines[1].split()

    # list_answer = list of ints indicating the order in which the nodes are visited
    list_answer = list(map(int, secondLine))

    return check_feasibility(nodeCount, points, sol_value, list_answer)


def check_feasibility(node_count, points, sol_value, list_answer):

    if (node_count != len(list_answer)):
        print("Solucao nao eh valida, pois numero de vertices na solucao esta incorreto")
        exit(0)

    list_aux = list_answer[:]
    list_aux.sort()

    for i in range(0, node_count - 1):
        if list_aux[i] == list_aux[i+1]:
            print("Solucao nao eh valida, pois existe vertice repetido")
            exit(0)

    obj = length(points[list_answer[-1]], points[list_answer[0]])
    for i in range(0, node_count - 1):
        obj += length(points[list_answer[i]], points[list_answer[i+1]])

    if sol_value != round(obj, 2):
        print(
            "Erro! Custo do circuito nao corresponde ao indicado na solucao.")
        exit(0)

    # it is a feasible solution =D
    return sol_value


if __name__ == '__main__':
    arglist = input().rstrip().split()
    instance_path = arglist[0]
    test_type = int(arglist[1])
    instance_name = ntpath.basename(instance_path)

    sol_value = parse_input(instance_path, instance_name)

    test_type = int(arglist[1])
    # test_type = int(input())

    if test_type == 0:
        print("Solucao eh valida.")
        exit(0)

    instance_list = ['tsp_51_1', 'tsp_100_3', 'tsp_200_2',
                     'tsp_574_1', 'tsp_1889_1', 'tsp_33810_1']
    good_values = [482, 23433, 35985, 40000, 378069, 78478868]
    great_values = [429, 20770, 29964, 37600, 323000, 67700000]


    i = instance_list.index(instance_name)

    if test_type == 1:
        if (sol_value <= good_values[i]):
            print("Parabens! Solucao eh boa.")
        else:
            print(
                f"Solucao nao eh boa, pois nao atingiu valor {good_values[i]}")

    if test_type == 2:
        if (sol_value <= great_values[i]):
            print("Parabens! Solucao parece ser otima.")
        else:
            print(
                f"Solucao nao eh otima, pois nao atingiu valor {great_values[i]}")
