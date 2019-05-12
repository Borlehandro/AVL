#include <stdio.h>
#include <stdlib.h>

typedef unsigned char uchar;
typedef struct Node Node;

struct Node {
    Node *left;
    Node *right;
    int key;
    uchar height;
};

void NewNode(Node *node) {
    node->left = NULL;
    node->right = NULL;
    node->key = 0;
    node->height = 0;
}

void FixHeight(Node *node) {
    unsigned char hl = node->left == NULL ? 0 : node->left->height;
    unsigned char hr = node->right == NULL ? 0 : node->right->height;
    node->height = (hl > hr ? hl : hr) + 1;
}

int getBalanceFactor(Node *root) {
    if (root == NULL || (root->left == NULL && root->right == NULL))
        return 0;
    if (root->left == NULL)
        return root->right->height;
    if (root->right == NULL)
        return -root->left->height;
    return (root->right->height) - (root->left->height);
}

Node *SmallRight(Node *node) { /// Correct
    Node *q = node->right;
    node->right = q->left;
    q->left = node;
    FixHeight(node);
    FixHeight(q);
    return q;
}

Node *SmallLeft(Node *node) { /// Correct
    Node *q = node->left;
    node->left = q->right;
    q->right = node;
    FixHeight(node);
    FixHeight(q);
    return q;
}

Node *BigRight(Node *node) { /// Correct
    node->right = SmallLeft(node->right);
    return SmallRight(node);
}

Node *BigLeft(Node *node) { /// Correct
    node->left = SmallRight(node->left);
    return SmallLeft(node);
}

Node *Balance(Node *node) { /// Correct
    FixHeight(node);
    if (getBalanceFactor(node) == 2) {
        if (getBalanceFactor(node->right) < 0)
            return BigRight(node);
        else
            return SmallRight(node);
    }
    if (getBalanceFactor(node) == -2) {
        if (getBalanceFactor(node->left) > 0)
            return BigLeft(node);
        else
            return SmallLeft(node);
    }
    return node;
}

Node *Insert(Node *root, int value) {
    if (root == NULL) {
        root = malloc(sizeof(Node));
        NewNode(root);
        root->key = value;
    } else {
        if (value < root->key)
            root->left = Insert(root->left, value);
        else
            root->right = Insert(root->right, value);
    }
    return Balance(root);
}

int main() {
    FILE *in = fopen("in.txt", "r");
    int n;
    fscanf(in, "%d\n", &n);
    Node *tree = NULL;
    for (int i = 0; i < n; i++) {
        int key;
        fscanf(in, "%d ", &key);
        tree = Insert(tree, key);
    }
    fclose(in);
    printf("%d", tree == NULL ? 0 : tree->height);
    return 0;
}