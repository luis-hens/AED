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

ABB turn_left(ABB root)
{
    ABB pB;
    pB = root->right;
    root->right = pB->left;
    if (root->right)
        root->right->parent = root;

    pB->left = root;

    pB->parent = root->parent;

    if (root->parent)
        if (root == root->parent->left)
            root->parent->left = pB;
        else
            root->parent->right = pB;

    pB->left = root;
    root->parent = pB;
    return pB;
}

ABB turn_right(ABB root)
{
    ABB pB;
    pB = root->left;
    root->left = pB->right;
    if (root->left)
        root->left->parent = root;

    pB->right = root;

    pB->parent = root->parent;

    if (root->parent)
        if (root == root->parent->right)
            root->parent->right = pB;
        else
            root->parent->left = pB;

    pB->right = root;
    root->parent = pB;
    return pB;
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

void change_color2(ABB &root)
{
    root->color = BLACK;
    if (root->left)
        root->left->color = RED;
    if (root->right)
        root->right->color = RED;
}

void insertion_balance(ABB &root, ABB &z)
{

    while (true)
    {
        if (color(z->parent) == RED && color(z) == RED)
        {
            if (z->parent->parent)
            {
                ABB B = z;
                ABB A = z->parent;
                ABB C = z->parent->parent;
                ABB D = nullptr;

                if (A == C->right)
                {
                    D = z->parent->parent->left;
                    if (color(D) == RED)
                        change_color(C);
                    else if (A->left == B)
                    {
                        A = turn_right(A);
                        C = turn_left(C);
                        change_color2(A);
                    }
                    else
                    {
                        C = turn_left(C);
                        change_color2(A);
                    }
                }
                else
                {
                    D = z->parent->parent->right;
                    if (color(D) == RED)
                        change_color(C);
                    else if (A->right == B)
                    {
                        A = turn_left(A);
                        C = turn_right(C);
                        change_color2(A);
                    }
                    else
                    {
                        C = turn_right(C);
                        change_color2(A);
                    }
                }
            }
        }
        z = z->parent;
        if (!z)
            break;
    }
}

void insert(ABB &root, int value)
{
    ABB x = root;
    ABB y = nullptr;
    ABB z = inicialize(value);

    while (x)
    {
        y = x;
        if (z->value < x->value)
            x = x->left;
        else
            x = x->right;
    }
    z->parent = y;

    if (!y)
        root = z;
    else if (z->value < y->value)
        y->left = z;
    else
        y->right = z;
    if (z)
        insertion_balance(root, z);
    while (root->parent)
        root = root->parent;
}

ABB sucessor(ABB root)
{
    while (root != nullptr && root->left != nullptr)
        root = root->left;
    return root;
}

void erase_balance(ABB &root, ABB &z)
{

}

void erase(ABB &root, ABB &z)
{
    if(!z->left && !z->right)
    {
        if (z == z->parent->left)
            z->parent->left = nullptr;
        else
            z->parent->right = nullptr;
        delete z;
    }
    else if (!z->left && z->right)
    {
        if (z == z->parent->left)
        {
            z->parent->left = z->right;
            z->right->parent = z->parent->left;
            delete z;
        }
        else
        {
            z->parent->right = z->right;
            z->right->parent = z->parent->right;
            delete z;
        }
    }
    else if (z->left && !z->right)
    {
        if (z == z->parent->left)
        {
            z->parent->left = z->left;
            z->left->parent = z->parent->left;
            delete z;
        }
        else
        {
            z->parent->right = z->left;
            z->left->parent = z->parent->right;
            delete z;
        }
    }
    else
    {
        ABB temp = sucessor(z->right);
        z->value = temp->value;
        erase(z->right, temp);
    }
    if(color(z)==BLACK)
        erase_balance(root, z);
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
            //cout << height(test) << ", ";
            //cout << height(test->left) + 1 << ", ";
            //cout << height(test->right) + 1 << "\n";
            erase(root, test);
        }
    }

    print_ABB(root);

    /*
    cin >> x;
    test = search(root, x);
    if (test)
        cout << black_height(test);
    else
        cout << "Valor nao encontrado";
    */
    free_ABB(root);
    return 0;
}