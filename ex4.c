#include <stdio.h>

int merge_modificado(int vet[], int A[], int inicio, int meio, int fim, int K)
{
    int i = inicio, j = meio, aux = inicio;
    int contador = 0;
    int ii = inicio, jj = meio;

    while (ii < meio && jj <= fim) //While para contar os pares (separado do while de ordenacao)
    {
        if (vet[ii] > vet[jj] * K)
        {
            contador = contador + (meio - ii);
            jj++;
        }
        else
        {
            ii++;
        }
    }

    while ((i <= meio - 1) && (j <= fim)) //while usado para pre-ordenar o vetor
    {
        if (vet[i] <= vet[j])
        {
            A[aux++] = vet[i++];
        }
        else
        {
            A[aux++] = vet[j++];
        }
    }

    while (i <= meio - 1) //Esses proximos whiles terminam de ordenar
        A[aux++] = vet[i++];

    while (j <= fim)
        A[aux++] = vet[j++];

    for (i = inicio; i <= fim; i++) // Aqui eu faco vet receber o vetor ordenado
        vet[i] = A[i];

    return contador;
}

int merge_sort(int vet[], int A[], int inicio, int fim, int K)
{
    int meio, contador = 0;
    if (fim > inicio)
    {
        meio = (fim + inicio) / 2;
        int i = inicio, j = meio;
        contador += merge_sort(vet, A, inicio, meio, K);
        contador += merge_sort(vet, A, meio + 1, fim, K);
        contador += merge_modificado(vet, A, inicio, meio + 1, fim, K);
    }

    return contador;
}

int main()
{
    int N, K;
    scanf("%d", &N);
    scanf("%d", &K);
    int vet[N], A[N];
    for (int i = 0; i < N; i++)
        if (scanf("%d", &vet[i]) != 1)
            ;

    printf("%d", merge_sort(vet, A, 0, N - 1, K));
    return 0;
}