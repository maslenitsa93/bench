struct node
{
    int key;
    node* left = nullptr;
    node* right = nullptr;
};

class binary_tree
{
public:
    binary_tree();
    ~binary_tree();

    void clear();
    void insert(int key);
    void remove(int key);
    node* search(int key);

private:
    void free(node* leaf);
    void insert(int key, node* leaf);
    node* remove(int key, node* root);
    node* search(int key, node* leaf);

    node* root;
};
