//
// Sort.cpp
// 2023-09-03
// Ivan Konishchev
//

#include "Sort.h"

bool Sort::isMultiThreads = true;
ThreadPool Sort::thPool;

void Sort::quicqSort(int *arr, long size)
{
    if (Sort::isMultiThreads)
    {
        Sort::thPool.start();
        quicksort(arr, 0, size);
        Sort::thPool.stop();
        return;
    }
    quicksort(arr, 0, size);
}

bool Sort::isSorted(const int *arr, long size)
{
    for (long i = 0; i < size - 1; i++)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }
    return true;
}

void Sort::quicksort(int *array, long left, long right)
{
    if (left >= right)
        return;
    long left_bound = left;
    long right_bound = right;

    long middle = array[(left_bound + right_bound) / 2];

    do
    {
        while (array[left_bound] < middle)
        {
            left_bound++;
        }
        while (array[right_bound] > middle)
        {
            right_bound--;
        }

        if (left_bound <= right_bound)
        {
            std::swap(array[left_bound], array[right_bound]);
            left_bound++;
            right_bound--;
        }
    } while (left_bound <= right_bound);

    if (right_bound - left > 100000 && Sort::isMultiThreads)
    {

        auto fL = thPool.push_task(quicksort, array, left, right_bound);
        quicksort(array, left_bound, right);
        while (fL.wait_for(std::chrono::seconds(0)) == std::future_status::timeout)
        {
            thPool.run_pending_task();
        }
    }
    else
    {
        quicksort(array, left, right_bound);
        quicksort(array, left_bound, right);
    }
}
