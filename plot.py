import random
def random_suffix():
    suffix = ''
    for _ in range(3):
        suffix += str(random.randint(0, 9))
    return suffix

import matplotlib.pyplot as plt
import math
import numpy as np
def plot_data(names, data, n, signature, exclude = [], target = []):
    x = list(range(len(data[0])))
    # print("shapes: ", len(names), len(data), len(data[0]))
    for (i, name) in enumerate(names):
        if name in exclude:
            continue
        # print(names[i])
        if "BothAlgo" in name:
            names[i] = "Two-sided Sort"
        elif "LIS" in name:
            names[i] = "Displacement Sort"
        elif name == "MergeSort":
            names[i] = "Merge Sort"
        elif name == "QuickSort":
            names[i] = "Quick Sort"
        elif name == "TimSort":
            names[i] = "Tim Sort"
        elif name == "Cook_Kim":
            names[i] = "Cook-Kim Sort"
        elif name == "DirtyClean2":
            names[i] = "Dirty-Clean Sort"    
    
    data = np.array(data)
    # print("data shape", data.shape)
    means = np.mean(data, axis=2) / n
    stds = np.std(data, axis=2) / n


    for i in range (len(names)):
        if names[i] in exclude:
            continue
        # print("ploting", x, names[i], means[i] / n, stds[i] / n)
        plt.plot(x, means[i], label=names[i], linewidth=2 if names[i] in target else 1)
        print(names[i], means[i][-1], stds[i][-1])
        plt.fill_between(x, means[i] - stds[i], means[i] + stds[i], alpha=0.15)

        
    nlogn_y = [math.log2(n) for _ in x]

    plt.plot(x, nlogn_y, 'r--')
    plt.rcParams["figure.figsize"] = (8, 6)


    # set x ticks
    x_ticks = [i / 20 for i in x]
    plt.xticks(x[::2], x_ticks[::2])

    plt.ylabel('# comparisons $/$ $n$', fontsize=22)
    # plt.title(signature)

    plt.legend(prop={'size': 12}, ncols = 2, loc='lower right')

    
    # decay2
    # plt.xlabel('#timesteps $/$ $n$', fontsize=22)
    # x_ticks = [int(i / 20 * 100) for i in x]
    # plt.xticks(x[::2], x_ticks[::2])

    #local
    # plt.xlabel('#classes $/$ $n$', fontsize=22)

    # country
    # plt.xlabel('gap in years', fontsize=22)
    # x_ticks = [i for i in x]
    # plt.xticks(x[::5], x_ticks[::5])

    # Good-Dominating 
    # plt.xlabel('damage ratio $r$', fontsize=20)
    # plt.title("")

    # Bad-Dominating 
    plt.xlabel('damage ratio $r$ (in edges)', fontsize=20)
    plt.title("")
    

    
    plt.savefig(f"plots/{signature}.png")
    plt.show()

# load txt 
def read_data(signature):
    with open(f"data/{signature}.txt", 'r') as file:
        lines = file.readlines()
    
    # first line is names
    print(lines[0])
    names = lines[0].strip().split(' ')
    num_algo, num_error, num_rep = [int(num) for num in lines[1].strip().split(' ') if num]

    data = []
    li = 2
    for i in range(num_algo):
        data_algo = []
        for j in range(num_error):
            row_data = [int(num) for num in lines[li].strip().split(' ') if num]
            data_algo.append(row_data)
            li += 1 
        data.append(data_algo)
    return names, data

def experiment (type_pred, setting, n, rep, exclude = [], target = []):
    signature = f"{type_pred}_{setting}_{n}_{rep}"
    names, data = read_data(signature)
    # for (i, datum) in enumerate(data):
    #     print(names[i], datum)
    plot_data(names, data, n, signature, exclude, target)
    