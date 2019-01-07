#include <benchmark/benchmark.h>
#include "splaytree.h"
#include "rbtree.h"


// Insert

auto BM_SplayTreeInsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        splay_tree<int> sp_tree;
        for (int i = 1; i < count; i++) {
            sp_tree.insert(i);
        }
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

        for (int i = 1; i < count; i++) {
            struct node* nod = (node*)malloc(sizeof(struct node));
            nod->key = i;
            rb_root = insert(rb_root, nod);
        }
    }
};

// Upsert

auto BM_SplayTreeUpsert = [](benchmark::State& state, auto count) {
    for (auto _ : state) {
        splay_tree<int> sp_tree;
        for (int i = 1; i < count; i++) { // TODO do not count bench
            sp_tree.insert(i);
        }
        for (int i = 1; i < count; i++) {
            sp_tree.insert(i);
        }
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

        for (int i = 1; i < count; i++) { // TODO do not count bench
            struct node* nod = (node*)malloc(sizeof(struct node));
            nod->key = i;
            rb_root = insert(rb_root, nod);
        }

        for (int i = 1; i < count; i++) {
            struct node* nod = (node*)malloc(sizeof(struct node));
            nod->key = i;
            rb_root = insert(rb_root, nod);
        }
    }
};

int main(int argc, char** argv) {
    srand(time(NULL));

    LEAF = (node*)malloc(sizeof(struct node));
    LEAF->color = BLACK;
    LEAF->left = NULL;
    LEAF->right = NULL;
    LEAF->key = 0;

    benchmark::RegisterBenchmark(std::string("BM_SplayTreeInsert_").append(std::to_string(100)).c_str(), BM_SplayTreeInsert, 1000);
    benchmark::RegisterBenchmark(std::string("BM_RbTreeInsert_").append(std::to_string(100)).c_str(), BM_RbTreeInsert, 1000);
    benchmark::RegisterBenchmark(std::string("BM_SplayTreeUpsert_").append(std::to_string(100)).c_str(), BM_SplayTreeUpsert, 1000);
    benchmark::RegisterBenchmark(std::string("BM_RbTreeUpsert_").append(std::to_string(100)).c_str(), BM_RbTreeUpsert, 1000);
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();
    return 0;
}
