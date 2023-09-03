//
// Sort.h
// 2023-09-03
// Ivan Konishchev
//

#pragma once
#include <iostream>
#include <future>
#include <thread>
#include <mutex>
#include "ThreadPool.h"

class Sort
{
private:
    Sort() = default;

    static ThreadPool thPool;
    static void quicksort(int *array, long left, long right);

public:
    ~Sort() = default;
    static bool isMultiThreads;
    static void quicqSort(int *arr, long size);
    static bool isSorted(const int *arr, long size);
};
