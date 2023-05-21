#pragma once
#include "../settings/Interface.h"
#include "Utils.h"
#include <vector>
using namespace std;

extern vector<int> sorted, uni_preds, indexes;

extern vector<int> output_rank;

//for tim sort
extern vector<int> leftTemp, rightTemp;

//for OESM
extern vector<int> odd_l, odd_r, even_l, even_r, merged;

//for Kim Cook
extern vector<int> ordered, unordered1, unordered2;

//for Both
extern vector<int> p_to_A, inserted;
extern vector<int> left_sorted, right_sorted, left_bef, right_aft, combine, insert_par;
// extern vector<int> left_order, right_order, left_weight, right_weight;


//for DirtyClean2
extern vector<int> shuffledA;

class SortAlgorithm
{
public:
    virtual void sort(SortGame& game) {};
};

class Left
{
public:
    virtual void sort(SortGame& game) {};
};

class LIS : public SortAlgorithm {
public:
    LIS() = default;
    void sort(SortGame& game) override;
};


class LIS_small : public SortAlgorithm {
public:
    LIS_small() = default;
    void sort(SortGame& game) override;
};

class LIS_treap : public SortAlgorithm {
public:
    LIS_treap() = default;
    void sort(SortGame& game) override;
};

class BothAlgo : public SortAlgorithm {
public:
    //init functions
    BothAlgo() = default;

    void sort(SortGame& game) override;
};

class BothAlgo_small : public SortAlgorithm {
public:
    //init functions
    BothAlgo_small() = default;

    void sort(SortGame& game) override;
};

class DirtyClean2 : public SortAlgorithm {
public:
    //init functions
    DirtyClean2() = default;

    void sort(SortGame& game) override;
};

class DirtyClean2_freeze : public SortAlgorithm {
public:
    //init functions
    DirtyClean2_freeze() = default;

    void sort(SortGame& game) override;
};


class naiveDirtyClean2 : public SortAlgorithm {
public:
    //init functions
    naiveDirtyClean2() = default;

    void sort(SortGame& game) override;
};


class BlockMergeSort : public SortAlgorithm {
public:
    // Constructor
    BlockMergeSort() = default;

    void sort(SortGame& game) override;

private:
    // Function to find the minimum run length
    int calcMinRun(int n);

    // Function to perform insertion sort on small subarrays
    void insertionSort(SortGame& game, int left, int right);

    // Function to merge two sorted subarrays
    void merge(SortGame& game, int left, int mid, int right);

    // Main Block Merge Sort function
    void blockMergeSort(SortGame& game, int n);
};

class TimSort : public SortAlgorithm {
public:
    // Constructor
    TimSort() = default;

    void sort(SortGame& game) override;

private:
    // Function to perform insertion sort on small subarrays
    void insertionSort(SortGame& game, int left, int right);

    // Function to merge two sorted subarrays
    void merge(SortGame& game, int left, int mid, int right);

    // Main Tim Sort function
    void timSort(SortGame& game, int n);

    // Constants
    const int RUN = 32;
};



// class HeapSort : public SortAlgorithm {
// public:
//     // Constructor
//     HeapSort() = default;

//     void sort(SortGame& game) override;

// private:
//     // Function to build the max heap
//     void buildMaxHeap(SortGame& game, int n, std::vector<int>& indexes);
//     // Function to heapify the given subtree rooted at index i
//     void heapify(SortGame& game, int n, int i, std::vector<int>& indexes);
//     // Function to swap elements at two given indexes
//     void swap(int& a, int& b);
// };

// class LeftAlgo : public SortAlgorithm {
// public:
//     //init functions
//     LeftAlgo() = default;

//     void sort(SortGame& game) override;
// };



class MergeSort : public SortAlgorithm {
public:
    // Constructor
    MergeSort() = default;

    void sort(SortGame& game) override;

private:
    // Recursive merge sort function
    void mergeSort(SortGame& game, int low, int high);
    // Function to merge two sorted subarrays
    void merge(SortGame& game, int low, int mid, int high);
};

class QuickSort : public SortAlgorithm {
public:
    //init functions
    QuickSort() = default;

    void sort(SortGame& game) override;

private:
    static void quickSort(SortGame &game, int low, int high);
    static int partition(SortGame &game, int low, int high);
    static int randomPivot(SortGame &game, int low, int high);
};

class OESM: public SortAlgorithm {
public:
    OESM() = default;

    void sort(SortGame& game) override;
    void merge (SortGame &game, int st, int mid, int ed);
    void OESM_recursion(SortGame &game, int st, int ed);
    bool if_sorted(SortGame &game, int st, int ed);
};

class Cook_Kim: public SortAlgorithm {
public:
    Cook_Kim() = default;

    void sort(SortGame& game) override;
    void merge (SortGame &game, int st, int mid, int ed);
    void Cook_Kim_recursion(SortGame &game, int st, int ed);
    bool if_sorted(SortGame &game, int st, int ed);
};

// class AdaptiveMergeSort : public SortAlgorithm {
// public:
//     //init functions
//     AdaptiveMergeSort() = default;

//     void sort(SortGame& game) override;
// };




// class AdaptiveMergeSort : public SortAlgorithm {
// public:
//     //init functions
//     AdaptiveMergeSort() = default;

//     vector<int> sort(SortGame& game) override;
// };

// class InsertionSort : public SortAlgorithm {
// public:
//     //init functions
//     InsertionSort() = default;

//     void sort(SortGame& game) override;
// };

// class DirtyClean : public SortAlgorithm {
// public:
//     //init functions
//     DirtyClean() = default;

//     vector<int> sort(SortGame& game) override;
// };

// class naiveDirtyClean : public SortAlgorithm {
// public:
//     //init functions
//     naiveDirtyClean() = default;

//     vector<int> sort(SortGame& game) override;
// };



// class CleanQuickSort : public SortAlgorithm {
// public:
//     //init functions
//     CleanQuickSort() = default;

//     vector<int> sort(SortGame& game) override;

// private:
//     static void quickSort(SortGame &game, int low, int high, std::vector<int> &indexes);
//     static int partition(SortGame &game, int low, int high, std::vector<int> &indexes);
//     static int randomPivot(SortGame &game, int low, int high, std::vector<int> &indexes);
// };
