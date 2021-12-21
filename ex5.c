#include <stdio.h>
#define MAX 10000

int Partition(int vet[], int inicio, int fim) //Funcao de particao
{
    int x, i;
    x = vet[fim];
    i = inicio - 1;

    for (int j = inicio; j < fim; j++)
    {
        if (vet[j] <= x)
        {
            i++;
            if (i != j)
            {
                int aux = vet[j];
                vet[j] = vet[i];
                vet[i] = aux;
            }
        }
    }

    vet[fim] = vet[i + 1];
    vet[i + 1] = x;

    return i + 1;
}

void QuickSort(int vet[], int inicio, int fim, int K) // Um QuickSort alterado
{
    int div;
    if (inicio < fim)
    {
        div = Partition(vet, inicio, fim);
        if(div==K) return; // Encontrei o indice do pivo e sua posicao esta estabelecida entao volto
        if(div>K) // Um if para verificar em que lado devo repetir o processo de QuickSort
            QuickSort(vet, inicio, div - 1, K);
        else if(div<K)
            QuickSort(vet, div + 1, fim, K);
        else return;
    }
}

int main()
{
    int K, N, vet[MAX];
    scanf("%d", &K);
    scanf("%d", &N);
    K -= 1;

    for (int i = 0; i < N; i++)
        if (scanf("%d", &vet[i]) != 1);

    QuickSort(vet, 0, N - 1, K);

    printf("%do menor elemento eh o %d\n", K+1, vet[K]);

    for (int i = 0; i < N; i++)
    {
        printf("%d ", vet[i]);
    }

    return 0;
}