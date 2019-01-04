#include <benchmark/benchmark.h>
#include <boost/property_tree/ptree.hpp>
#include "BTree.h"
namespace pt = boost::property_tree;

struct foo {
    foo() {
    }

    int bar = 0;
};

std::ostream& operator<<(std::ostream& os, const foo& f) {
    os << f.bar;
    return os;
}

std::istream& operator>>(std::istream& is, foo& f) {
    is >> f.bar;
    return is;
}

bool operator==(const foo& lhs, const foo& rhs) {
    return lhs.bar == rhs.bar;
}

// for BTree only
bool operator!=(const foo& lhs, const foo& rhs) {
    return lhs.bar != rhs.bar;
}

// for BTree only
bool operator<(const foo& lhs, const foo& rhs) {
    return lhs.bar < rhs.bar;
}

ods::BTree<foo> btree(1000);
pt::ptree ptree;

// Add

static void BM_BTreeAdd100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            foo f;
            f.bar = i;
            btree.add(f);
        }
    }
}
BENCHMARK(BM_BTreeAdd100);

static void BM_PTreeAdd100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            foo f;
            f.bar = i;
            ptree.put(std::to_string(i), f);
        }
    }
}
BENCHMARK(BM_PTreeAdd100);

// Lookup

static void BM_BTreeLookup100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            foo f;
            f.bar = i;
            btree.find(f);
        }
    }
}
BENCHMARK(BM_BTreeLookup100);

static void BM_PTreeLookup100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            ptree.find(std::to_string(i));
        }
    }
}
BENCHMARK(BM_PTreeLookup100);

BENCHMARK_MAIN();
