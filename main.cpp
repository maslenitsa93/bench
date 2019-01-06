#include <benchmark/benchmark.h>
#include <boost/property_tree/ptree.hpp>
#include "btree_map.h"
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


btree::btree_map<std::string, foo> google_tree;
pt::ptree boost_tree;

// Add

static void BM_GoogleTreeAdd100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            foo f;
            f.bar = i;
            google_tree[std::to_string(i)] = f;
        }
    }
}
BENCHMARK(BM_GoogleTreeAdd100);

static void BM_BoostTreeAdd100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            foo f;
            f.bar = i;
            boost_tree.put(std::to_string(i), f);
        }
    }
}
BENCHMARK(BM_BoostTreeAdd100);

// Lookup

static void BM_GoogleTreeLookup100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            google_tree.find(std::to_string(i));
        }
    }
}
BENCHMARK(BM_GoogleTreeLookup100);

static void BM_BoostTreeLookup100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            boost_tree.find(std::to_string(i));
        }
    }
}
BENCHMARK(BM_BoostTreeLookup100);

// Remove

static void BM_GoogleTreeRemove100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            google_tree.erase(std::to_string(i));
        }
    }
}
BENCHMARK(BM_GoogleTreeRemove100);

static void BM_BoostTreeRemove100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            boost_tree.erase(std::to_string(i));
        }
    }
}
BENCHMARK(BM_BoostTreeRemove100);

BENCHMARK_MAIN();
