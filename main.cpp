#include <iostream>
#include <chrono>
#include <thread>
#include <mutex>
#include <boost/thread/shared_mutex.hpp>
#include <boost/smart_ptr/detail/spinlock.hpp>
#include <boost/program_options.hpp>
#include "binary_tree.h"

using boost::shared_mutex;
using boost::shared_lock;
using boost::upgrade_lock;
using boost::upgrade_to_unique_lock;
namespace bpo = boost::program_options;

binary_tree bt;
std::mutex bt_mutex;
shared_mutex bt_shared_mutex;
boost::detail::spinlock bt_spinlock;

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

void inserter_spinlock() {
    ELAPSE_START;

    for (int i = 1; i <= 10000; i++) {
        std::lock_guard<boost::detail::spinlock> guard(bt_spinlock);
        bt.insert(i);
    }

    ELAPSE_END("Inserter (spinlock)");
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

void searcher_spinlock() {
    ELAPSE_START;

    for (int i = 10000; i >= 1; i--) {
        std::lock_guard<boost::detail::spinlock> guard(bt_spinlock);
        bt.search(i);
    }

    ELAPSE_END("Searcher (spinlock)");
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

void remover_spinlock() {
    ELAPSE_START;

    for (int i = 10000; i >= 1; i--) {
        std::lock_guard<boost::detail::spinlock> guard(bt_spinlock);
        bt.remove(i);
    }

    ELAPSE_END("Remover (spinlock)");
}

enum class lock_type {
    mutex,
    shared,
    spinlock
};

std::istream& operator>>(std::istream& in, lock_type& lt)
{
    std::string token;
    in >> token;
    if (token == "mutex")
        lt = lock_type::mutex;
    else if (token == "shared")
        lt = lock_type::shared;
    else if (token == "spinlock")
        lt = lock_type::spinlock;
    else
        in.setstate(std::ios_base::failbit);
    return in;
}

void bench(int writers, int readers, lock_type lt) {
    inserter(nullptr);

    std::function<void()> writer;
    switch (lt) {
    case lock_type::mutex:
        writer = remover;
        break;
    case lock_type::shared:
        writer = remover_shared;
        break;
    default:
        writer = remover_spinlock;
        break;
    }

    std::function<void()> reader;
    switch (lt) {
    case lock_type::mutex:
        reader = searcher;
        break;
    case lock_type::shared:
        reader = searcher_shared;
        break;
    default:
        reader = searcher_spinlock;
        break;
    }

    std::vector<std::thread> v;
    for (int i = 0; i < writers; ++i) {
        v.emplace_back(writer);
    }
    for (int i = 0; i < readers; ++i) {
        v.emplace_back(reader);
    }

    for (auto& t : v) {
        t.join();
    }
}

int main(int argc, char** argv) {
    int writers;
    int readers;
    lock_type lt;

    bpo::options_description desc("Allowed options");
    desc.add_options()
        (
            "writers", bpo::value<int>(&writers)->required(), "Count of writer threads"
        ) (
            "readers", bpo::value<int>(&readers)->required(), "Count of reader threads"
        ) (
            "lock-type", bpo::value<lock_type>(&lt)->required(), "Lock type: mutex, shared_mutex, or spinlock"
        );

    bpo::variables_map vm;
    bpo::store(bpo::parse_command_line(argc, argv, desc), vm);
    bpo::notify(vm);

    bench(writers, readers, lt);
    return 0;
}
