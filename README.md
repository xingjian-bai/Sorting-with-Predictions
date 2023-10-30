
# Learning Augmented Sorting
This repository is the official implementation of *Sorting with Predictions*.

# Run the code
To run the code, please run the following commands in terminal:
```
bash compile.sh
./main
```
Then, input the name and parameters of the settings you want to test. For example,
```
positional class 10000 10 # positional predictions, class setting, with 10000 items, repeated 10 times.
positional decay 1000 30 # positional predictions, decay setting, with 1000 items, repeated 30 times.
dirty good-dominating 10000 10 # dirty comparison predictions, good-dominating setting, with 10000 items, repeated 10 times.
```

To visualize the number of comparisons needed by each algorithm and baseline, check the python script `plot.ipynb`.

# Proposed algorithms
- The implementation of Double-Hoover Sort is at `algorithms/Both2.cpp`.
- The implementation of Displacement Sort is at `algorithms/LIS.cpp`.
- The implementation of Dirty-Clean Sort is at `algorithms/DirtyClean3.cpp`.