#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h>

static char BLACK = 'b';
static char RED = 'r';

struct node {
    int key;
    char color;
    struct node *left, *right, *parent;
};

void insert_repair_tree(struct node *n);

void insert_recurse(struct node* root, struct node* n);

void insert_case1(struct node* n);

void insert_case2(struct node* n);

void insert_case3(struct node* n);

void insert_case4(struct node* n);

void insert_case4step2(struct node* n);

void delete_case1(struct node *n);

void delete_case2(struct node *n);

void delete_case3(struct node *n);

void delete_case4(struct node *n);

void delete_case5(struct node *n);

void delete_case6(struct node* n);

struct node *LEAF;

struct node* parent(struct node* n) {
 return n->parent; // NULL for root node
}

struct node* grandparent(struct node* n) {
 struct node* p = parent(n);
 if (p == NULL)
  return NULL; // No parent means no grandparent
 return parent(p); // NULL if parent is root
}

struct node* sibling(struct node* n) {
 struct node* p = parent(n);
 if (p == NULL)
  return NULL; // No parent means no sibling
 if (n == p->left)
  return p->right;
 else
  return p->left;
}

struct node* uncle(struct node* n) {
 struct node* p = parent(n);
 struct node* g = grandparent(n);
 if (g == NULL)
  return NULL; // No grandparent means no uncle
 return sibling(p);
}

void rotate_left(struct node* n) {
 struct node* nnew = n->right;
 struct node* p = parent(n);
 assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
 n->right = nnew->left; 
 nnew->left = n;
 n->parent = nnew;
 // handle other child/parent pointers
 if (n->right != NULL)
  n->right->parent = n;
 if (p != NULL) // initially n could be the root
 {
  if (n == p->left)
   p->left = nnew;
  else if (n == p->right) // if (...) is excessive
   p->right = nnew;
 }
 nnew->parent = p;
}

void rotate_right(struct node* n) {
 struct node* nnew = n->left;
 struct node* p = parent(n);
 assert(nnew != LEAF); // since the leaves of a red-black tree are empty, they cannot become internal nodes
 n->left = nnew->right;
 nnew->right = n;
 n->parent = nnew;
 // handle other child/parent pointers
 if (n->left != NULL)
  n->left->parent = n;
 if (p != NULL) // initially n could be the root
 {
  if (n == p->left)
   p->left = nnew;
  else if (n == p->right) // if (...) is excessive
   p->right = nnew;
 }
 nnew->parent = p;
}

struct node *insert(struct node* root, struct node* n) {
 // insert new node into the current tree
 insert_recurse(root, n);

 // repair the tree in case any of the red-black properties have been violated
 insert_repair_tree(n);

 // find the new root to return
 root = n;
 while (parent(root) != NULL)
  root = parent(root);
 return root;
}

void insert_recurse(struct node* root, struct node* n) {
 // recursively descend the tree until a leaf is found
 if (root != NULL && n->key < root->key) {
  if (root->left != LEAF) {
   insert_recurse(root->left, n);
   return;
  }
  else
   root->left = n;
 } else if (root != NULL) {
  if (root->right != LEAF){
   insert_recurse(root->right, n);
   return;
  }
  else
   root->right = n;
 }

 // insert new node n
 n->parent = root;
 n->left = LEAF;
 n->right = LEAF;
 n->color = RED;
}

void insert_repair_tree(struct node* n) {
 if (parent(n) == NULL) {
  insert_case1(n);
 } else if (parent(n)->color == BLACK) {
  insert_case2(n);
 } else if (uncle(n)->color == RED) {
  insert_case3(n);
 } else {
  insert_case4(n);
 }
}

void insert_case1(struct node* n)
{
 if (parent(n) == NULL)
  n->color = BLACK;
}

void insert_case2(struct node* n)
{
  return; /* Do nothing since tree is still valid */
}

void insert_case3(struct node* n)
{
 parent(n)->color = BLACK;
 uncle(n)->color = BLACK;
 grandparent(n)->color = RED;
 insert_repair_tree(grandparent(n));
}

void insert_case4(struct node* n)
{
 struct node* p = parent(n);
 struct node* g = grandparent(n);

 if (n == g->left->right) {
  rotate_left(p);
  n = n->left;
 } else if (n == g->right->left) {
  rotate_right(p);
  n = n->right; 
 }

 insert_case4step2(n);
}

void insert_case4step2(struct node* n)
{
 struct node* p = parent(n);
 struct node* g = grandparent(n);

 if (n == p->left)
  rotate_right(g);
 else
  rotate_left(g);
 p->color = BLACK;
 g->color = RED;
}

void replace_node(struct node* n, struct node* child){
    child->parent = n->parent;
    if (n == n->parent->left)
        n->parent->left = child;
    else
        n->parent->right = child;
}

int is_leaf(struct node *n) {
    if (n->right == NULL && n->left == NULL)
        return 1;
    else return 0;
}

void delete_one_child(struct node* n)
{
 /*
  * Precondition: n has at most one non-leaf child.
  */
 struct node* child = is_leaf(n->right) ? n->left : n->right;

 replace_node(n, child);
 if (n->color == BLACK) {
  if (child->color == RED)
   child->color = BLACK;
  else
   delete_case1(child);
 }
 free(n);
}

void delete_case1(struct node* n)
{
 if (n->parent != NULL)
  delete_case2(n);
}

void delete_case2(struct node* n)
{
 struct node* s = sibling(n);

 if (s->color == RED) {
  n->parent->color = RED;
  s->color = BLACK;
  if (n == n->parent->left)
   rotate_left(n->parent);
  else
   rotate_right(n->parent);
 }
 delete_case3(n);
}

void delete_case3(struct node* n)
{
 struct node* s = sibling(n);

 if ((n->parent->color == BLACK) &&
     (s->color == BLACK) &&
     (s->left->color == BLACK) &&
     (s->right->color == BLACK)) {
  s->color = RED;
  delete_case1(n->parent);
 } else
  delete_case4(n);
}

void delete_case4(struct node* n)
{
 struct node* s = sibling(n);

 if ((n->parent->color == RED) &&
     (s->color == BLACK) &&
     (s->left->color == BLACK) &&
     (s->right->color == BLACK)) {
  s->color = RED;
  n->parent->color = BLACK;
 } else
  delete_case5(n);
}

void delete_case5(struct node* n)
{
 struct node* s = sibling(n);

 if  (s->color == BLACK) { /* this if statement is trivial,
due to case 2 (even though case 2 changed the sibling to a sibling's child,
the sibling's child can't be red, since no red parent can have a red child). */
/* the following statements just force the red to be on the left of the left of the parent,
   or right of the right, so case six will rotate correctly. */
  if ((n == n->parent->left) &&
      (s->right->color == BLACK) &&
      (s->left->color == RED)) { /* this last test is trivial too due to cases 2-4. */
   s->color = RED;
   s->left->color = BLACK;
   rotate_right(s);
  } else if ((n == n->parent->right) &&
             (s->left->color == BLACK) &&
             (s->right->color == RED)) {/* this last test is trivial too due to cases 2-4. */
   s->color = RED;
   s->right->color = BLACK;
   rotate_left(s);
  }
 }
 delete_case6(n);
}

void delete_case6(struct node* n)
{
 struct node* s = sibling(n);

 s->color = n->parent->color;
 n->parent->color = BLACK;

 if (n == n->parent->left) {
  s->right->color = BLACK;
  rotate_left(n->parent);
 } else {
  s->left->color = BLACK;
  rotate_right(n->parent);
 }
}

node* bst_find(struct node* root, int key) {
 node* z = root;
 while (z) {
  if (key > z->key) z = z->right;
  else if (key < z->key) z = z->left;
  else return z;
 }
 return nullptr;
}
