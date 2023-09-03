//
// ThreadPool.h
// 2023-09-03
// Ivan Konishchev
//

#pragma once

#include <queue>
#include <future>
#include <thread>
#include <condition_variable>
#include <vector>
#include "BlockedQueue.h"
#include <functional>
#include <stack>

void taskFunc(int *, long start, long end);
// удобное определение для сокращения кода
typedef std::packaged_task<void()> task_type;
typedef std::future<void> res_type;
// тип указатель на функцию, которая является эталоном для функций задач
typedef void (*FuncType)(int *, long start, long end);

class ThreadPool
{
public:
    ThreadPool();
    // запуск:
    void start();
    // остановка:
    void stop();
    // проброс задач
    res_type push_task(FuncType f, int *arr, long start, long end);
    // функция входа для потока
    void threadFunc(int qindex);
    void run_pending_task();

private:
    // количество потоков
    int m_thread_count;
    // потоки
    std::vector<std::thread> m_threads;
    // очереди задач для потоков
    std::vector<BlockedQueue<task_type>> m_thread_queues;
    // для равномерного распределения задач
    int m_index;
};
