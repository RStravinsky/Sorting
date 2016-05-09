#ifndef SORT_H
#define SORT_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <string>
#include <algorithm>
#include <cmath>
#include <assert.h>
#include <QDebug>

#define DEBUG 1

class Sort
{
private:
    int * pSourceArray;
    int * pSourceArray_CONST;
    void DisplayArray(std::string _strType, clock_t _t=0);
    void GenerateArray();
    void quicksort(int *array, int left, int right);
    void findminmax(int * array, int size, int&max, int&min);
    void shiftRight(int* array, int low, int high);
    void heapify(int* array, int low, int high);
    void margesort(int * array, int left, int right);
    void Marge(int * array, int left, int middle, int right);
    int   iSize;
    int * pom;

public:
    Sort(unsigned int _iSize);
    ~Sort();
    static const int MAX_ARRAY = 10000;
    void BubbleSort();
    void SelectionSort();
    void QuickSort();
    void InsertSort();
    void CountingSort();
    void HeapSort();
    void MargeSort();
};

#endif // SORT_H
