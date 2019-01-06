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

auto BM_GoogleTreeAdd = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            foo f;
            f.bar = i;
            google_tree[std::to_string(i)] = f;
        }
    }
};

auto BM_BoostTreeAdd = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            foo f;
            f.bar = i;
            boost_tree.put(std::to_string(i), f);
        }
    }
};

// Upsert

auto BM_GoogleTreeUpsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            foo f;
            f.bar = i * 10;
            google_tree[std::to_string(i)] = f;
        }
    }
};

auto BM_BoostTreeUpsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            foo f;
            f.bar = i * 10;
            boost_tree.put(std::to_string(i), f);
        }
    }
};

// Lookup

auto BM_GoogleTreeLookup = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            google_tree.find(std::to_string(i));
        }
    }
};

auto BM_BoostTreeLookup = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            boost_tree.find(std::to_string(i));
        }
    }
};

// Remove

auto BM_GoogleTreeRemove = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            google_tree.erase(std::to_string(i));
        }
    }
};

auto BM_BoostTreeRemove = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        for (int i = 1; i <= count; i++) {
            boost_tree.erase(std::to_string(i));
        }
    }
};

int main(int argc, char** argv) {
    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_GoogleTreeAdd_").append(std::to_string(i)).c_str(), BM_GoogleTreeAdd, i);
        benchmark::RegisterBenchmark(std::string("BM_BoostTreeAdd_").append(std::to_string(i)).c_str(), BM_BoostTreeAdd, i);
    }

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_GoogleTreeUpsert_").append(std::to_string(i)).c_str(), BM_GoogleTreeUpsert, i);
        benchmark::RegisterBenchmark(std::string("BM_BoostTreeUpsert_").append(std::to_string(i)).c_str(), BM_BoostTreeUpsert, i);
    }

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_GoogleTreeLookup_").append(std::to_string(i)).c_str(), BM_GoogleTreeLookup, i);
        benchmark::RegisterBenchmark(std::string("BM_BoostTreeLookup_").append(std::to_string(i)).c_str(), BM_BoostTreeLookup, i);
    }

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_GoogleTreeRemove_").append(std::to_string(i)).c_str(), BM_GoogleTreeRemove, i);
        benchmark::RegisterBenchmark(std::string("BM_BoostTreeRemove_").append(std::to_string(i)).c_str(), BM_BoostTreeRemove, i);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
