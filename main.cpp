#include <benchmark/benchmark.h>
#include <boost/property_tree/ptree.hpp>
#include "BTree.h"
namespace pt = boost::property_tree;

ods::BTree<int> btree(1000);
pt::ptree ptree;

// Add

static void BM_BTreeAdd100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            btree.add(i);
        }
    }
}
BENCHMARK(BM_BTreeAdd100);

static void BM_PTreeAdd100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            ptree.put(std::to_string(i), i);
        }
    }
}
BENCHMARK(BM_PTreeAdd100);

// Lookup

static void BM_BTreeLookup100(benchmark::State& state) {
    for (auto _ : state) {
        for (int i = 1; i <= 100; i++) {
            btree.find(i);
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
