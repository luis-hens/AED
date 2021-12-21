#include <stdio.h>
#include <iostream>
#define RED true
#define BLACK false
using namespace std;

struct Node
{
    int value;
    bool color;
    Node *left, *right, *parent;
};

typedef struct Node *ABB; // Estrutura da arvore criada

ABB inicialize(int value)
{
    ABB root = new Node();
    root->value = value;
    root->left = root->right = nullptr;
    root->parent = nullptr;
    root->color = RED;
    return root;
}

ABB search(ABB root, int value)
{
    if (root == nullptr || root->value == value)
        return root;
    else if (value <= root->value)
        return search(root->left, value);
    else
        return search(root->right, value);
}

void turn_left(ABB &root)
{
    ABB pB;
    pB = root->right;
    root->right = pB->left;
    pB->left = root;
    pB->color = root->color;
    root->color = RED;
    root = pB;
}

void turn_right(ABB &root)
{
    ABB pB;
    pB = root->left;
    root->left = pB->right;
    pB->right = root;
    pB->color = root->color;
    root->color = RED;
    root = pB;
}

bool color(ABB root)
{
    if (!root)
        return BLACK;
    else
        return root->color;
}

void change_color(ABB &root)
{
    root->color = !root->color;
    if (root->left)
        root->left->color = !root->left->color;
    if (root->right)
        root->right->color = !root->right->color;
}


void insert(ABB &root, int value)
{
    // iterative
}

ABB sucessor(ABB root)
{
    while (root != nullptr && root->left != nullptr)
        root = root->left;
    return root;
}

void erase(ABB &root, int value)
{
    if (root == nullptr)
        return;
    else if (value < root->value)
        erase(root->left, value);
    else if (value > root->value)
        erase(root->right, value);
    else
    {
        if (root->left == nullptr && root->right == nullptr)
        {
            delete root;
            root = nullptr;
        }
        else if (root->left == nullptr)
        {
            ABB temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr)
        {
            ABB temp = root;
            root = root->left;
            delete temp;
        }
        else
        {
            ABB temp = sucessor(root->right);
            root->value = temp->value;
            erase(root->right, temp->value);
        }
    }
}

int height(ABB root)
{
    if (root == nullptr)
        return -1;
    return max(height(root->left), height(root->right)) + 1;
}

int black_height(ABB root)
{
    if (root == nullptr)
        return 0;
    if (root->color == BLACK)
        return black_height(root->left) + 1;
    else
        return black_height(root->left);
}

void print_ABB(ABB root)
{
    if (root == nullptr)
        return;
    print_ABB(root->left);
    cout << root->value << " ";
    print_ABB(root->right);
}

void free_ABB(ABB &root)
{
    if (root == nullptr)
        return;
    free_ABB(root->left);
    free_ABB(root->right);
    delete root;
}

int main()
{
    ABB root = nullptr, test;
    int x;

    while (true)
    {
        cin >> x;
        if (x < 0)
            break;
        insert(root, x);
        root->color = BLACK;
    }

    cout << height(root) << ", ";
    cout << height(root->left) + 1 << ", ";
    cout << height(root->right) + 1 << "\n";

    while (true)
    {
        cin >> x;
        if (x < 0)
            break;
        test = search(root, x);
        if (!test)
        {
            insert(root, x);
            root->color = BLACK;
        }
        else
        {
            cout << height(test) << ", ";
            cout << height(test->left) + 1 << ", ";
            cout << height(test->right) + 1 << "\n";
        }
    }

    cin >> x;
    test = search(root, x);
    cout << black_height(test);

    free_ABB(root);
    return 0;
}