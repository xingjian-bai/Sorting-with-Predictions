#pragma once
#include "../settings/Interface.h"
#include <vector>

class SortAlgorithm {
public:
    // 对SortGame中的数字数组A进行排序，并返回排序后的数组
    virtual std::vector<int> sort(SortGame& game) = 0;
};

class BlockMergeSort : public SortAlgorithm {
public:
    // Constructor
    BlockMergeSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Function to find the minimum run length
    int calcMinRun(int n);

    // Function to perform insertion sort on small subarrays
    void insertionSort(SortGame& game, int left, int right, std::vector<int>& indexes);

    // Function to merge two sorted subarrays
    void merge(SortGame& game, int left, int mid, int right, std::vector<int>& indexes);

    // Main Block Merge Sort function
    void blockMergeSort(SortGame& game, int n, std::vector<int>& indexes);
};

class BothAlgo : public SortAlgorithm {
public:
    //init functions
    BothAlgo() = default;

    std::vector<int> sort(SortGame& game) override;
};

class HeapSort : public SortAlgorithm {
public:
    // Constructor
    HeapSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Function to build the max heap
    void buildMaxHeap(SortGame& game, int n, std::vector<int>& indexes);
    // Function to heapify the given subtree rooted at index i
    void heapify(SortGame& game, int n, int i, std::vector<int>& indexes);
    // Function to swap elements at two given indexes
    void swap(int& a, int& b);
};

class LeftAlgo : public SortAlgorithm {
public:
    //init functions
    LeftAlgo() = default;

    std::vector<int> sort(SortGame& game) override;
};

class LIS : public SortAlgorithm {
public:
    //init functions
    LIS() = default;

    std::vector<int> sort(SortGame& game) override;
};

class MergeSort : public SortAlgorithm {
public:
    // Constructor
    MergeSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Recursive merge sort function
    void mergeSort(SortGame& game, int low, int high, std::vector<int>& indexes);
    // Function to merge two sorted subarrays
    void merge(SortGame& game, int low, int mid, int high, std::vector<int>& indexes);
};

class QuickSort : public SortAlgorithm {
public:
    //init functions
    QuickSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    static void quickSort(SortGame &game, int low, int high, std::vector<int> &indexes);
    static int partition(SortGame &game, int low, int high, std::vector<int> &indexes);
    static int randomPivot(SortGame &game, int low, int high, std::vector<int> &indexes);
};


class TimSort : public SortAlgorithm {
public:
    // Constructor
    TimSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    // Function to perform insertion sort on small subarrays
    void insertionSort(SortGame& game, int left, int right, std::vector<int>& indexes);

    // Function to merge two sorted subarrays
    void merge(SortGame& game, int left, int mid, int right, std::vector<int>& indexes);

    // Main Tim Sort function
    void timSort(SortGame& game, int n, std::vector<int>& indexes);

    // Constants
    const int RUN = 32;
};

class AdaptiveMergeSort : public SortAlgorithm {
public:
    //init functions
    AdaptiveMergeSort() = default;

    std::vector<int> sort(SortGame& game) override;
};

class InsertionSort : public SortAlgorithm {
public:
    //init functions
    InsertionSort() = default;

    std::vector<int> sort(SortGame& game) override;
};

class DirtyClean : public SortAlgorithm {
public:
    //init functions
    DirtyClean() = default;

    std::vector<int> sort(SortGame& game) override;
};

class naiveDirtyClean : public SortAlgorithm {
public:
    //init functions
    naiveDirtyClean() = default;

    std::vector<int> sort(SortGame& game) override;
};

class DirtyClean2 : public SortAlgorithm {
public:
    //init functions
    DirtyClean2() = default;

    std::vector<int> sort(SortGame& game) override;
};

class CleanQuickSort : public SortAlgorithm {
public:
    //init functions
    CleanQuickSort() = default;

    std::vector<int> sort(SortGame& game) override;

private:
    static void quickSort(SortGame &game, int low, int high, std::vector<int> &indexes);
    static int partition(SortGame &game, int low, int high, std::vector<int> &indexes);
    static int randomPivot(SortGame &game, int low, int high, std::vector<int> &indexes);
};
