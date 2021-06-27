#!/usr/bin/python
# -*- coding: utf-8 -*-

import time
import math
from collections import namedtuple

Point = namedtuple("Point", ['x', 'y'])


DEBUG = 1


def length(point1, point2):
    return math.floor(math.sqrt((point1.x - point2.x)**2 + (point1.y - point2.y)**2))


def solve_it(input_data):
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

    return TSPnaive(nodeCount, points)


def TSPnaive(nodeCount, points):

    # Modify this code to run your optimization algorithm

    # build a trivial solution
    # visit the nodes in the order they appear in the file
    solution = range(0, nodeCount)

    # calculate the length of the tour
    obj = length(points[solution[-1]], points[solution[0]])
    for index in range(0, nodeCount-1):
        obj += length(points[solution[index]], points[solution[index+1]])

    # prepare the solution in the specified output format
    output_data = '%.2f' % obj + '\n'
    output_data += ' '.join(map(str, solution))

    return output_data


if DEBUG >= 1:
    start = time.time()

if __name__ == '__main__':
    import sys
    if len(sys.argv) > 2:
        file_location = sys.argv[1].strip()
        with open(file_location, 'r') as input_data_file:
            input_data = input_data_file.read()
        output_data = solve_it(input_data)
        print(output_data)
        solution_file_location = sys.argv[2].strip()
        solution_file = open(solution_file_location, "w")
        solution_file.write(output_data)
        solution_file.close()
    else:
        print('This test requires an input file and an output file. Please select one from the data directory. (i.e. python solver.py ./data/tsp_51_1 ./sols/tsp_51_1.sol)')

if DEBUG >= 1:
    end = time.time()
    print(end - start)
