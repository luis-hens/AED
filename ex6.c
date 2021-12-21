#include <stdio.h>
#include <string.h>

//Estruturando um texto como um conjunto de palavras
typedef struct
{
    char palavra[20];
} Text;

//Funcao para determinar validade da palavra
int alfabetico(char palavra[])
{
    for (int i = 0; i < strlen(palavra); i++)
    {
        if (palavra[i] < 'a' || palavra[i] > 'z')
            return 0;
    }
    return 1;
}

//Lendo os dados
int leitura(int *M, Text texto[], int vet[], int N, Text texto2[])
{
    for (int i = 1; i <= N; i++)
        scanf("%s", texto[i].palavra);
    
    scanf("%d", M);

    for (int i = 0; i < *M; i++)
    {
        if (scanf("%d", &vet[i]) != 1);
        texto2[i+1] = texto[vet[i]+1];
    }
    /*
    for (int i = 1; i <= N; i++) //Verificando validade da palavra
    {
        if (!alfabetico(texto[i].palavra))
        {
            printf("a palavra %s eh invalida", texto[i].palavra);
            return 0;
        }
    }
    */
    return 1;
}

void MaxHeapify(Text texto[], int i, int N)
{
    if(N==0) return;
    int left = 2 * i, right = (2 * i) + 1, max;

    if (left <= N && strcmp(texto[left].palavra, texto[i].palavra)>0)
        max = left;
    else
        max = i;

    if (right <= N && strcmp(texto[right].palavra, texto[max].palavra)>0)
        max = right;

    if(max!=i)
    {
        Text aux = texto[i];
        texto[i] = texto[max];
        texto[max] = aux;
        MaxHeapify(texto, max, N);
    }  
}

void BuildMaxHeap(Text texto[], int N)
{
    for(int i=N/2; i>0; i--)
        MaxHeapify(texto, i, N);
}

Text HeapExtractMax(Text texto[], int N)
{
    Text t;
    if(N<1)
    { 
        printf("Underflow error");
        return t;
    }
    Text max = texto[1];
    int last = N;
    texto[1] = texto[last];
    N--;
    MaxHeapify(texto, 1, N);
    return max;
}

Text HeapSort(Text texto[], int N)
{
    //BuildMaxHeap(texto, N);
    Text vet[N+1];
    int tam = N;
    while(N>0)
    {
        vet[N] = HeapExtractMax(texto, N);
        N--;
    }
    for(int i=1; i<=tam; i++){
        texto[i] = vet[i];
    }
}



int main()
{
    int N, M;
    scanf("%d", &N);
    Text texto[N + 1], texto2[N];
    int vet[N];

    if (!leitura(&M, texto, vet, N, texto2))
        return 0;
    
    BuildMaxHeap(texto2, M);

    printf("build_heap:");
    for (int i = 1; i <= M; i++)
        printf(" %s", texto2[i].palavra);

    HeapSort(texto2, M);

    printf("\npalavras:");
    for (int i = 1; i <= M; i++)
        printf(" %s", texto2[i].palavra);

    return 0;
}