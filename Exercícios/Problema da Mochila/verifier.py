import sys
import fileinput
import ntpath
from os import listdir
from os.path import isfile, join
from collections import namedtuple
Item = namedtuple("Item", ['index', 'value', 'weight'])

DEBUG = 0

def check_feasibility(instance_path):
    instance_file = open(instance_path, "r")
    input_data = instance_file.read()
    instance_file.close()

    # parse the input
    lines = input_data.split('\n')

    firstLine = lines[0].split()
    item_count = int(firstLine[0])
    capacity = int(firstLine[1])

    items = []

    for i in range(1, item_count+1):
        line = lines[i]
        parts = line.split()
        items.append(
            Item(i-1, int(parts[0]), int(parts[1])))

    if DEBUG >= 1:
        print(f"numero de itens = {item_count}")
        print(f"capacidade da mochila = {capacity}")

    if DEBUG >= 2:
        print("Itens na ordem em que foram lidos")
        for item in items:
            print(item)
        print()

    
    print(ntpath.basename(instance_path))
    instance_sol_file = open(ntpath.basename(instance_path) + ".sol", "r")
    solution_data = instance_sol_file.read()
    instance_sol_file.close()

    # parse the solution
    lines = solution_data.split('\n')

    firstLine = lines[0].split()
    sol_value = int(firstLine[0])
    secondLine = lines[1].split()
    # transforming secondiLine from a list of string to a list of ints
    binary_list_answer = list(map(int, secondLine))

    # binary_list_answer = list of strings ["0" or "1"] indicating if item is or isnt in the knapsack
    # items_list = list of tuples with (value, weight) of each item

    knapsack = []
    knapsack_value = 0
    knapsack_weight = 0

    item_index = 0
    for item in binary_list_answer:
        if item == 1:
            knapsack.append(item_index)
            knapsack_value += items[item_index].value
            knapsack_weight += items[item_index].weight
        item_index += 1

    if DEBUG >= 1:
        print(f"knapsack: {knapsack}")
        print(f"knapsack value: {knapsack_value}")
        print(f"knapsack weight: {knapsack_weight}")

    if sol_value != knapsack_value:
        print("Erro! Valor da mochila nao corresponde ao indicado na solucao.")
        exit(0)

    if knapsack_weight > capacity:
        print("Solucao nao eh valida, pois ultrapassa a capacidade da mochila")
        exit(0)

    # it is a feasible solution =D
    return knapsack_value


#if len(sys.argv) > 1:
#    instance_path = sys.argv[1].strip()
#    print(instance_path)
#else:
#    print('This verifier requires an input file and a test type (0-2).  Please select one from the data directory (i.e. python verifier.py ./data/ks_30_0 2)')
#    exit(0)

arglist = input().rstrip().split()
instance_path = arglist[0]
test_type = int(arglist[1])

sol_value = check_feasibility(instance_path)


if test_type == 0:
    print("Solucao eh valida.")
    exit(0)

instance_list = ['ks_30_0', 'ks_50_0', 'ks_200_0',
                 'ks_400_0', 'ks_1000_0', 'ks_10000_0']
good_values = [92000, 141956, 100062,
               3966813, 109869, 1099870]
great_values = [99798, 142156, 100236,
                3967180, 109899, 1099893]

instance_name = ntpath.basename(instance_path)
i = instance_list.index(instance_name)

if test_type == 1:
    if (sol_value >= good_values[i]):
        print("Parabens! Solucao eh boa.")
    else:
        print(f"Solucao nao eh boa, pois nao atingiu valor {good_values[i]}")

if test_type == 2:
    if (sol_value >= great_values[i]):
        print("Parabens! Solucao parece ser otima.")
    else:
        print(
            f"Solucao nao eh otima, pois nao atingiu valor {great_values[i]}")
