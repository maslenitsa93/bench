#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>
#include "binary_tree.h"

using boost::shared_mutex;
using boost::shared_lock;
using boost::upgrade_lock;
using boost::upgrade_to_unique_lock;    

binary_tree bt;
std::mutex bt_mutex;
shared_mutex bt_shared_mutex;

#define ELAPSE_START \
    struct timespec start, finish; \
    double elapsed; \
    clock_gettime(CLOCK_MONOTONIC, &start)

#define ELAPSE_END(PRINT_TITLE) \
    clock_gettime(CLOCK_MONOTONIC, &finish); \
    elapsed = (finish.tv_sec - start.tv_sec); \
    elapsed += double(finish.tv_nsec - start.tv_nsec) / 1000000000; \
    if (PRINT_TITLE) { \
        printf("%s: %f\n", PRINT_TITLE, elapsed); \
    }

void inserter(const char* log) {
    ELAPSE_START;

    for (int i = 1; i <= 10000; i++) {
        bt_mutex.lock();
        bt.insert(i);
        bt_mutex.unlock();
    }

    ELAPSE_END(log);
}

void inserter_shared() {
    ELAPSE_START;

    for (int i = 1; i <= 10000; i++) {
        upgrade_lock<shared_mutex> lock(bt_shared_mutex);
        upgrade_to_unique_lock<shared_mutex> unique_lock(lock);
        bt.insert(i);
    }

    ELAPSE_END("Inserter (shared mutex)");
}

void searcher() {
    ELAPSE_START;

    for (int i = 10000; i >= 1; i--) {
        bt_mutex.lock();
        bt.search(i);
        bt_mutex.unlock();
    }

    ELAPSE_END("Searcher (mutex)");
}

void searcher_shared() {
    ELAPSE_START;

    for (int i = 10000; i >= 1; i--) {
        shared_lock<shared_mutex> lock(bt_shared_mutex);
        bt.search(i);
    }

    ELAPSE_END("Searcher (shared mutex)");
}

void remover() {
    ELAPSE_START;

    for (int i = 10000; i >= 1; i--) {
        bt_mutex.lock();
        bt.remove(i);
        bt_mutex.unlock();
    }

    ELAPSE_END("Remover (mutex)");
}

void remover_shared() {
    ELAPSE_START;

    for (int i = 10000; i >= 1; i--) {
        upgrade_lock<shared_mutex> lock(bt_shared_mutex);
        upgrade_to_unique_lock<shared_mutex> unique_lock(lock);
        bt.remove(i);
    }

    ELAPSE_END("Remover (shared mutex)");
}

void mrmw_rl_simple() {
    std::cout << "--- MR_MW REMOVE/LOOKUP SIMPLE: ---" << std::endl;
    inserter(nullptr);
    std::thread w1(remover); std::thread w2(remover);
    std::thread r1(searcher); std::thread r2(searcher);
    w1.join(); w2.join(); r1.join(); r2.join();
}

void mrmw_rl_shared() {
    std::cout << "--- MR_MW REMOVE/LOOKUP SHARED: ---" << std::endl;
    inserter(nullptr);
    std::thread w1(remover_shared); std::thread w2(remover_shared);
    std::thread r1(searcher_shared); std::thread r2(searcher_shared);
    w1.join(); w2.join(); r1.join(); r2.join();
}

void mrsw_rl_simple() {
    std::cout << "--- MR_SW REMOVE/LOOKUP SIMPLE: ---" << std::endl;
    inserter(nullptr);
    std::thread w1(remover);
    std::thread r1(searcher); std::thread r2(searcher);
    w1.join(); r1.join(); r2.join();
}

void mrsw_rl_shared() {
    std::cout << "--- MR_SW REMOVE/LOOKUP SHARED: ---" << std::endl;
    inserter(nullptr);
    std::thread w1(remover_shared);
    std::thread r1(searcher_shared); std::thread r2(searcher_shared);
    w1.join(); r1.join(); r2.join();
}

int main(int argc, char** argv) {
    if (argc >= 2) {
        mrsw_rl_shared();
    } else {
        mrsw_rl_simple();
    }
    return 0;
}