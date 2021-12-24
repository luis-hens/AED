#include <stdio.h>
#include <iostream>
using namespace std;

struct Node
{
    int value;
    Node *left, *right;
};

typedef struct Node *ABB; //Estrutura da arvore criada

ABB inicialize(int value) 
{
    ABB root = new Node();
    root->value = value;
    root->left = root->right = nullptr;
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

void insert(ABB &root, int value)
{
    if (root == nullptr)
        root = inicialize(value);
    else if (value <= root->value)
        insert(root->left, value);
    else
        insert(root->right, value);
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
    }

    cout << height(root) << ", ";
    cout << height(root->left) + 1 << ", ";
    cout << height(root->right) + 1 << "\n";

    while (true)
    {
        cin >> x;
        if (x < 0)
            break;
        search(root, x) ? erase(root, x) : insert(root, x);
    }

    cin >> x;
    test = search(root, x);

    if (test == nullptr)
        cout << "Valor nao encontrado";
    else
    {
        cout << height(test) << ", ";
        cout << height(test->left) + 1 << ", ";
        cout << height(test->right) + 1;
    }

    // O código comentado a seguir foi usado apenas para teste
    /*
    cout << "Digite um valor para deletar: ";
    cin >> y;
    erase(root, y);
    */

    /*
    cout << "Digite um número: ";
    cin >> y;
    s = search(root, y);
    cout << "Número pertence? " << (s? "true" : "false") << "\n";
    */

    //print_ABB(root);
    //cout << "\n\n";
    free_ABB(root);
    return 0;
}