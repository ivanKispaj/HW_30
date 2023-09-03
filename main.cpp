//
// main.cpp
// 2023-09-03
// Ivan Konishchev
//

#include <iostream>
#include "Sort.h"

int main(int argc, const char *argv[])
{
    srand(0);
    long size = 100000000;
    int *array = new int[size];
    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % 500000;
    }

    time_t start, end;
    std::cout << "start\n";
    Sort::isMultiThreads = true;
    time(&start);
    Sort::quicqSort(array, size);
    time(&end);

    double seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    if (!Sort::isSorted(array, size))
    {
        std::cout << "Unsorted" << std::endl;
    }

    for (long i = 0; i < size; i++)
    {
        array[i] = rand() % 500000;
    }
    std::cout << "start one thread:\n";
    Sort::isMultiThreads = false;
    // однопоточный запуск
    time(&start);
    Sort::quicqSort(array, size);
    time(&end);
    seconds = difftime(end, start);
    printf("The time: %f seconds\n", seconds);

    if (!Sort::isSorted(array, size))
    {
        std::cout << "Unsorted" << std::endl;
    }

    delete[] array;

    return 0;
}
