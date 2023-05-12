import random
def random_suffix():
    suffix = ''
    for _ in range(3):
        suffix += str(random.randint(0, 9))
    return suffix

import matplotlib.pyplot as plt
import math
def plot_data(names, data, n, signature, exclude = [], target = []):
    x = range(len(data[0]))
    
    for (i, row) in enumerate(data):
        y = [i / n for i in row]
        if names[i] in exclude:
            continue
        if names[i] in target:
            plt.plot(x, y, label=names[i], linewidth=3)
        else:
            plt.plot(x, y, label=names[i])
    
    nlogn_y = [math.log2(n) for _ in x]

    plt.plot(x, nlogn_y, 'r--', label='nlogn')

    # x_ticks = [f"{2**i / n:.1f}" for i in x]
    # plt.xticks(x, x_ticks)

    plt.ylabel('# comparisons')
    plt.title(signature)

    #legend smaller
    plt.legend(prop={'size': 10})

    plt.rcParams["figure.figsize"] = (8, 6)

    plt.savefig(f"plots/{signature}.png")
    plt.show()

# load txt 
def read_data(signature):
    with open(f"data/{signature}.txt", 'r') as file:
        lines = file.readlines()
    
    # first line is names
    print(lines[0])
    names = lines[0].strip().split(' ')

    data = []
    for line in lines[1:]:
        row_data = [int(num) for num in line.strip().split(' ') if num]
        if row_data:
            data.append(row_data)

    return names, data

def experiment (type_pred, setting, n, rep, exclude = [], target = []):
    signature = f"{type_pred}_{setting}_{n}_{rep}"
    names, data = read_data(signature)
    # for (i, datum) in enumerate(data):
    #     print(names[i], datum)
    plot_data(names, data, n, signature, exclude, target)
    