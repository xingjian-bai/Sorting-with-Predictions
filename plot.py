import random
def random_suffix():
    suffix = ''
    for _ in range(3):
        suffix += str(random.randint(0, 9))
    return suffix

import matplotlib.pyplot as plt
import math
import numpy as np
def plot_data(names, data, n, signature, exclude = [], target = [], setting = None):
    x = list(range(len(data[0])))
    x = [i / 20 for i in x]
    ratio_in_items = x

    for (i, name) in enumerate(names):
        if name in exclude:
            continue
        print(names[i])
        if "BothAlgo" in name:
            if "2" in name:
                names[i] = "Double-Hoover Sort"
            elif "3" in name:
                names[i] = "Double-Hoover Sort - New Imp"
            elif "small" in name:
                names[i] = "Double-Hoover Sort - Small"
            else:
                names[i] = "Two-sided Sort - old"
        elif "LIS" in name:
            if "treap" in name:
                names[i] = "Displacement Sort - treap"
            else:
                names[i] = "Displacement Sort"
        elif name == "MergeSort":
            names[i] = "Merge Sort"
        elif name == "QuickSort":
            names[i] = "Quick Sort"
        elif "TimSort" in name:
            names[i] = "Tim Sort"
            if "2" in name:
                names[i] += " (standard)"
        elif name == "Cook_Kim":
            names[i] = "Cook-Kim Sort"
        elif name == "DirtyClean3":
            names[i] = "Dirty-Clean Sort - old"   
        elif name == "DirtyClean4":
            names[i] = "Dirty-Clean Sort"   
        elif "Insertion" in name:
            names[i] = "Insertion Sort"
        elif name == "OESM":
            names[i] = "OESM"
        else:
            raise Exception("unknown name", name)
    
    data = np.array(data)
    # print("data shape", data.shape)
    means = np.mean(data, axis=2) / n
    stds = np.std(data, axis=2) / n


    for i in range (len(names)):
        if names[i] in exclude:
            continue


        cap = None
        if cap != None:
            c_mean = means[i][:cap]
            c_stds = stds[i][:cap]
            ratio_in_items = ratio_in_items[:cap]
            c_names = names[i][:cap]
        else:
            c_mean = means[i]
            c_stds = stds[i]
            c_names = names[i]

        plt.plot(ratio_in_items, c_mean, label=c_names, linewidth=2.5 if any(t in names[i] for t in target) else 1)
        plt.fill_between(ratio_in_items, c_mean - c_stds, c_mean + c_stds, alpha=0.15)

        
    nlogn_y = [math.log2(n) for _ in x]

    plt.plot(x, nlogn_y, 'r--')
    plt.rcParams["figure.figsize"] = (8, 6)


    # set x ticks
    # x_ticks = x
    # plt.xticks(x[::2], x_ticks[::2])

    plt.ylabel('# comparisons $/$ $n$', fontsize=22)
    # plt.title(signature)

    plt.legend(prop={'size': 14}, ncols = 2, loc='upper right')
    # plt.xticks(x[::5], x_ticks[::5])

    

    # set y ticks to be integers
    # plt.yticks(np.arange(2, 20, 2), np.arange(2, 20, 2))

    if setting == "local":
        # plt.ylim(0, 100)
        # plt.title(f"class setting (n={n})", fontsize=22)
        plt.xlabel('#classes $/$ $n$', fontsize=22)

    # country
    if setting == "country" or setting == "c":
        # plt.title(f"country population ranking (n={n})", fontsize=22)
        plt.xlabel('gap in years', fontsize=22)
        x_ticks = [int(i * 20) for i in x]
        print(x_ticks, x)
        plt.xticks(x[::5], x_ticks[::5])
        plt.legend(prop={'size': 12}, ncols = 2, loc='lower right')
    


    # Good-Dominating 
    if setting == "goodbad" or setting == "gb":
        # plt.title(f"Good-dominating setting (n={n})", fontsize=22)
        plt.xlabel('damage ratio $r$', fontsize=22)
        plt.legend(prop={'size': 14}, ncols = 2, loc='upper left')
        
        # set upperbound for y as 100
        # plt.ylim(0, 250)

    # Bad-Dominating 
    if setting == "badgood" or setting == "bg":
        plt.xlabel('damage ratio $r$', fontsize=22)
        # plt.title(f"Bad-dominating setting (n={n})", fontsize=22)
        plt.legend(prop={'size': 13}, ncols = 2, loc='upper right')
        # plt.ylim(0, 250)
    
    
    # for rebuttal
    # plt.legend(prop={'size': 16}, ncols = 2, loc='upper right', bbox_to_anchor=(1.0, 0.95))
    
    if setting == "new":
        print("new setting")
        plt.legend(prop={'size': 10}, ncols = 2, loc='upper right')
        plt.ylim(0, 20)
    
    # decay2
    if "decay2" in setting:
        #location is bottom right corner
        plt.legend(prop={'size': 12}, ncols = 2, loc='lower right')
        # plt.title(f"decay setting (n={n})", fontsize=22)
        plt.xlabel(f"#timesteps $/$ $n$", fontsize=22)
        scale = math.sqrt(n)
        if "1000" in setting: 
            scale = 1000
        else:
            scale = 100
        x_ticks = [int(i * scale) for i in x]
        plt.xticks(x[::2], x_ticks[::2])
    

    plt.savefig(f"plots/{signature}.png")

    # show with half line width
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
    plot_data(names, data, n, signature, exclude, target, setting = setting)
    