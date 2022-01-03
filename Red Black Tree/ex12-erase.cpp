//  UNCOMPLETE CODE
//  the erase method has a lot of bugs, still need to work on them
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

ABB turn_left(ABB &root)
{
    ABB pB;
    pB = root->right;
    root->right = pB->left;
    if (root->right)
        root->right->parent = root;

    pB->left = root;

    if(root->parent)
        pB->parent = root->parent;
    else
        pB->parent = nullptr;

    if (root->parent)
        if (root == root->parent->left)
            root->parent->left = pB;
        else
            root->parent->right = pB;

    pB->left = root;
    root->parent = pB;
    root = pB;
    return pB;
}

ABB turn_right(ABB &root)
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
    root = pB;
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

void erase_balance(ABB &root, ABB &x)
{
    ABB w;
    while (x != root && color(x) == BLACK)
    {
        if (!x)
            break;
        if(!x->parent)
            break;
        ABB aux = x->parent;
        if (x == x->parent->left)
        {
            w = x->parent->right;
            if (color(w) == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                if(x->parent==root)
                    x->parent = turn_left(root);
                else
                    x->parent = turn_left(x->parent);
                x->parent = aux;
                w = x->parent->right;
            }
            if (color(w->left) == BLACK && color(w->right) == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (color(w->right) == BLACK)
                {
                    w->left->color = BLACK;
                    w->color = RED;
                    w = turn_right(w);
                }
                w = x->parent->right;
                w->color = x->parent->color;
                x->parent->color = BLACK;
                w->right->color = BLACK;
                x->parent = turn_left(x->parent);
                x = root;
            }
        }
        else
        {
            w = x->parent->left;
            if (color(w) == RED)
            {
                w->color = BLACK;
                x->parent->color = RED;
                if(x->parent==root)
                    x->parent = turn_left(root);
                else
                    x->parent = turn_left(x->parent);
                x->parent = aux;
                w = x->parent->left;
            }
            if (color(w->right) == BLACK && color(w->left) == BLACK)
            {
                w->color = RED;
                x = x->parent;
            }
            else
            {
                if (color(w->right) == BLACK)
                {
                    w->right->color = BLACK;
                    w->color = RED;
                    w = turn_right(w);
                }
                w = x->parent->left;
                w->color = x->parent->color;
                x->parent->color = BLACK;
                if(w->left)
                    w->left->color = BLACK;
                x->parent = turn_left(x->parent);
                x = root;
            }
        }
    }
    if (x && x!=root)
        x->color = BLACK;
}

ABB erase(ABB &root, ABB &z, int &signal)
{
    ABB temp, x = nullptr;
    if (!z->left)
    {
        if (!z->right)
        {
            if (!z->parent)
                return z;
            else if (z == z->parent->right)
            {
                ABB aux = z->parent;
                if (color(z) == BLACK)
                    erase_balance(root, z);
                delete aux->right;
                signal = 1;
                aux->right = nullptr;
                return aux;
            }
            else
            {
                ABB aux = z->parent;
                if (color(z) == BLACK)
                    erase_balance(root, z);
                delete aux->left;
                signal = 1;
                aux->left = nullptr;
                return aux;
            }
        }
        else
        {
            if (!z->parent)
            {
                ABB aux = z->right;
                if (color(aux) == BLACK)
                    erase_balance(root, z);
                else
                    aux->color = BLACK;
                aux->parent = nullptr;
                root = aux;
                return root;
            }
            else if (z == z->parent->right)
            {
                ABB aux = z->parent;
                ABB aux2 = z->right;
                if (color(aux2) == BLACK)
                    erase_balance(root, z);
                else
                    aux2->color = BLACK;
                delete aux->right;
                signal = 1;
                aux->right = aux2;
                aux2->parent = aux;
                return aux;
            }
            else
            {
                ABB aux = z->parent;
                ABB aux2 = z->right;
                if (color(aux2) == BLACK)
                    erase_balance(root, z);
                else
                    aux2->color = BLACK;
                delete aux->right;
                signal = 1;
                aux->left = aux2;
                aux2->parent = aux;
                return aux;
            }
        }
    }
    else
    {
        if (!z->right)
        {
            if (!z->parent)
            {
                ABB aux = z->left;
                if (color(aux) == BLACK)
                    erase_balance(root, z);
                else
                    aux->color = BLACK;
                aux->parent = nullptr;
                root = z->left;
                return root;
            }
            else if (z == z->parent->right)
            {
                ABB aux = z->parent;
                ABB aux2 = z->left;
                if (color(aux2) == BLACK)
                    erase_balance(root, z);
                else
                    aux2->color = BLACK;
                delete aux->left;
                signal = 1;
                aux->right = aux2;
                aux2->parent = aux;
                return aux;
            }
            else
            {
                ABB aux = z->parent;
                ABB aux2 = z->left;
                if (color(aux2) == BLACK)
                    erase_balance(root, z);
                else
                    aux2->color = BLACK;
                delete aux->left;
                signal = 1;
                aux->left = aux2;
                aux2->parent = aux;
                return aux;
            }
        }
        else
        {
            temp = sucessor(z->right);
            z->value = temp->value;
            // z->color = temp->color;
            temp = erase(z->right, temp, signal);
            if (!signal)
                delete temp;
            signal = 1;
            return z;
        }
    }
    return z;
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

int red_height(ABB root)
{
    if (root == nullptr)
        return 0;
    if (root->color == RED)
        return max(red_height(root->left), red_height(root->right)) + 1;
    else
        return max(red_height(root->left), red_height(root->right));
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
    ABB root = nullptr, test, temp;
    int x, signal = 0;

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
            temp = erase(root, test, signal);
            if (!signal)
                delete temp;
            signal = 0;
        }
    }

    cin >> x;
    test = search(root, x);
    if (test)
        cout << red_height(test);
    else
        cout << "Valor nao encontrado";

    free_ABB(root);
    return 0;
}