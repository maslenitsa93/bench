#include <benchmark/benchmark.h>
#include <iostream>
#include "splaytree.h"
#include "rbtree.h"

void fill_splay(splay_tree<int>& sp_tree, auto count) {
    for (auto i = 1; i < count; i++) {
        sp_tree.insert(i);
    }
}

void fill_rb(struct node* rb_root, auto count) {
    for (auto i = 1; i < count; i++) {
        struct node* nod = (node*)malloc(sizeof(struct node));
        nod->key = i;
        rb_root = insert(rb_root, nod);
    }
}

// Insert

auto BM_SplayTreeInsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        splay_tree<int> sp_tree;
        fill_splay(sp_tree, count);
    }
};

auto BM_RbTreeInsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {

        struct node* rb_root = NULL;

        struct node *z;
        z = (node*)malloc(sizeof(struct node));
        z->key = 99999;
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;
        z->color = RED;
        rb_root = insert(rb_root, z);

        fill_rb(rb_root, count);

        state.PauseTiming();
        delete_one_child(rb_root);
        state.ResumeTiming();
    }
};

// Upsert

auto BM_SplayTreeUpsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        splay_tree<int> sp_tree;

        state.PauseTiming();

        fill_splay(sp_tree, count);

        state.ResumeTiming();

        fill_splay(sp_tree, count);
    }
};

auto BM_RbTreeUpsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {

        struct node* rb_root = NULL;

        struct node *z;
        z = (node*)malloc(sizeof(struct node));
        z->key = 99999;
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;
        z->color = RED;
        rb_root = insert(rb_root, z);

        state.PauseTiming();

        fill_rb(rb_root, count);

        state.ResumeTiming();

        fill_rb(rb_root, count);

        state.PauseTiming();
        delete_one_child(rb_root);
        state.ResumeTiming();
    }
};

// Remove

auto BM_SplayTreeRemove = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        splay_tree<int> sp_tree;

        state.PauseTiming();

        fill_splay(sp_tree, count);

        state.ResumeTiming();

        for (auto i = 1; i < count; i++) {
            sp_tree.erase(i);
        }
    }
};

auto BM_RbTreeRemove = [](benchmark::State& state, auto count) {
    for (auto _ : state) {

        struct node* rb_root = NULL;

        struct node *z;
        z = (node*)malloc(sizeof(struct node));
        z->key = 99999;
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;
        z->color = RED;
        rb_root = insert(rb_root, z);

        state.PauseTiming();

        fill_rb(rb_root, count);

        state.ResumeTiming();

        for (auto i = 1; i < count; i++) {
            struct node *found = bst_find(rb_root, i);
            if (found) delete_one_child(found);
        }

        state.PauseTiming();
        delete_one_child(rb_root);
        state.ResumeTiming();
    }
};

// Read

auto BM_SplayTreeRead = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        splay_tree<int> sp_tree;

        state.PauseTiming();

        fill_splay(sp_tree, count);

        state.ResumeTiming();

        for (auto i = 1; i < count; i++) {
            sp_tree.find(i);
        }
    }
};

auto BM_RbTreeRead = [](benchmark::State& state, auto count) {
    for (auto _ : state) {

        struct node* rb_root = NULL;

        struct node *z;
        z = (node*)malloc(sizeof(struct node));
        z->key = 99999;
        z->left = NULL;
        z->right = NULL;
        z->parent = NULL;
        z->color = RED;
        rb_root = insert(rb_root, z);

        state.PauseTiming();

        fill_rb(rb_root, count);

        state.ResumeTiming();

        for (auto i = 1; i < count; i++) {
            bst_find(rb_root, i);
        }

        state.PauseTiming();
        delete_one_child(rb_root);
        state.ResumeTiming();
    }
};

int main(int argc, char** argv) {
    srand(time(NULL));

    LEAF = (node*)malloc(sizeof(struct node));
    LEAF->color = BLACK;
    LEAF->left = NULL;
    LEAF->right = NULL;
    LEAF->key = 0;

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_SplayTreeInsert_").append(std::to_string(i)).c_str(), BM_SplayTreeInsert, i);
        benchmark::RegisterBenchmark(std::string("BM_RbTreeInsert_").append(std::to_string(i)).c_str(), BM_RbTreeInsert, i);
    }

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_SplayTreeUpsert_").append(std::to_string(i)).c_str(), BM_SplayTreeUpsert, i);
        benchmark::RegisterBenchmark(std::string("BM_RbTreeUpsert_").append(std::to_string(i)).c_str(), BM_RbTreeUpsert, i);
    }

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_SplayTreeRemove_").append(std::to_string(i)).c_str(), BM_SplayTreeRemove, i);
        benchmark::RegisterBenchmark(std::string("BM_RbTreeRemove_").append(std::to_string(i)).c_str(), BM_RbTreeRemove, i);
    }

    for (auto i = 100; i <= 1000; i+=100) {
        benchmark::RegisterBenchmark(std::string("BM_SplayTreeRead_").append(std::to_string(i)).c_str(), BM_SplayTreeRead, i);
        benchmark::RegisterBenchmark(std::string("BM_RbTreeRead_").append(std::to_string(i)).c_str(), BM_RbTreeRead, i);
    }

    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
