#include <stdio.h>
#include <stdlib.h>

// Structure for AVL Tree Node
struct Node {
    int key;
    struct Node *left;
    struct Node *right;
    int height;
};

// Function to get maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

// Function to get height of the tree
int height(struct Node *N) {
    if (N == NULL)
        return 0;
    return N->height;
}

// Function to create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*) malloc(sizeof(struct Node));
    node->key = key;
    node->left = NULL;
    node->right = NULL;
    node->height = 1; // New node is initially at leaf
    return node;
}

// Right rotate subtree rooted with y
struct Node* rightRotate(struct Node* y) {
    struct Node* x = y->left;
    struct Node* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    // Return new root
    return x;
}

// Left rotate subtree rooted with x
struct Node* leftRotate(struct Node* x) {
    struct Node* y = x->right;
    struct Node* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    // Return new root
    return y;
}

// Get Balance factor of node N
int getBalance(struct Node* N) {
    if (N == NULL)
        return 0;
    return height(N->left) - height(N->right);
}

// Recursive function to insert a key in the subtree
struct Node* insert(struct Node* node, int key) {
    // Step 1: Normal BST insertion
    if (node == NULL)
        return newNode(key);

    if (key < node->key)
        node->left = insert(node->left, key);
    else if (key > node->key)
        node->right = insert(node->right, key);
    else // Equal keys not allowed
        return node;

    // Step 2: Update height
    node->height = 1 + max(height(node->left), height(node->right));

    // Step 3: Get balance factor
    int balance = getBalance(node);

    // Step 4: If node is unbalanced, then fix it

    // Left Left Case
    if (balance > 1 && key < node->left->key)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

// Function to find height (used for level order)
int findHeight(struct Node* root) {
    if (root == NULL)
        return 0;
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);
    return max(leftHeight, rightHeight) + 1;
}

// Function to print nodes at a given level
void printLevel(struct Node* root, int level) {
    if (root == NULL)
        return;
    if (level == 1)
        printf("%d ", root->key);
    else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Function to print Level Order Traversal
void levelOrder(struct Node* root) {
    int h = findHeight(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
        printf("\n");
    }
}

// Main function
int main() {
    struct Node* root = NULL;
    int n, key;

    printf("Enter number of nodes to insert: ");
    scanf("%d", &n);

    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }

    printf("\nLevel Order Traversal of AVL Tree:\n");
    levelOrder(root);

    return 0;
}
