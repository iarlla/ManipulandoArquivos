#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

// Função para trocar duas strings
void swap(char **str1, char **str2) {
    char *temp = *str1;
    *str1 = *str2;
    *str2 = temp;
}

// Função para a etapa de partição do Quicksort
int partition(char *arr[], int low, int high, int *compares, int *swaps) {
    char *pivot = arr[high]; // Escolhe o elemento mais à direita como pivô
    int i = (low - 1); // Índice do menor elemento

    for (int j = low; j <= high - 1; j++) {
        (*compares)++; // Incrementa o contador de comparações
        // Compara as palavras e verifica se arr[j] < pivot
        if (strcmp(arr[j], pivot) < 0) {
            i++; // Incrementa o índice do menor elemento
            (*swaps)++; // Incrementa o contador de trocas
            swap(&arr[i], &arr[j]); // Troca arr[i] e arr[j]
        }
    }

    (*swaps)++; // Incrementa o contador de trocas
    swap(&arr[i + 1], &arr[high]); // Coloca o pivô no lugar correto
    return (i + 1); // Retorna o índice do pivô
}

// Função Quicksort principal
void quicksort(char *arr[], int low, int high, int *compares, int *swaps) {
    if (low < high) {
        int pi = partition(arr, low, high, compares, swaps); // Obtém o índice do pivô
        quicksort(arr, low, pi - 1, compares, swaps); // Ordena a partição esquerda
        quicksort(arr, pi + 1, high, compares, swaps); // Ordena a partição direita
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese_Brazil.1252");
    int o = 0; // Inicializa o contador de ordem de palavras
    int u = 0; // Inicializa o contador de ordem de palavras

    // Definição do vetor de palavras
    char *arr[20] = {
        "maca", "banana", "pera", "uva", "laranja", "abacaxi", "limao", "manga", "abacate", "kiwi",
        "cereja", "morango", "pessego", "goiaba", "melancia", "framboesa", "amora", "caqui", "figo", "papaya"
    };

    int compares = 0; // Inicializa o contador de comparações
    int swaps = 0; // Inicializa o contador de trocas

    int n = sizeof(arr) / sizeof(arr[0]); // Calcula o tamanho do vetor
    quicksort(arr, 0, n - 1, &compares, &swaps); // Chama a função Quicksort para ordenar o vetor

    // Imprime o número de trocas e comparações
    printf("Número de trocas: %d\n", swaps);
    printf("Número de comparações: %d\n", compares);
    printf("Vetor ordenado:\n");

    // Imprime o vetor ordenado com a ordem de palavras
    for (int i = 0; i < n; i++) {
        o++;
        printf("(%d)\t%s\n", o, arr[i]);
    }

    // Calcula a mediana
    char *mediana;
    if (n % 2 == 0) {
        // Se o número de palavras for par, a mediana é a média das duas palavras do meio
        char *middle1 = arr[n / 2 - 1];
        char *middle2 = arr[n / 2];
        mediana = malloc(strlen(middle1) + strlen(middle2) + 1);
        strcpy(mediana, middle1);
        strcat(mediana, "/");
        strcat(mediana, middle2);
    } else {
        // Se o número de palavras for ímpar, a mediana é a palavra central
        mediana = strdup(arr[n / 2]);
    }

    // Imprime a mediana
    printf("\nMediana: %s\n", mediana);

    // Gera o arquivo de saída
    FILE *outputFile = fopen("saida.txt", "w");
    if (outputFile == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        return 1;
    }

    // Escreve o número de trocas, comparações e o vetor ordenado no arquivo
    fprintf(outputFile, "Número de trocas: %d\n", swaps);
    fprintf(outputFile, "Número de comparações: %d\n\n", compares);
    fprintf(outputFile, "Vetor ordenado:\n");

    // Escreve o vetor ordenado com a ordem de palavras no arquivo
    for (int i = 0; i < n; i++) {
        u++;
        fprintf(outputFile, "(%d)\t%s\n", u, arr[i]);
    }

    // Escreve a mediana no arquivo
    fprintf(outputFile, "\nMediana: %s\n", mediana);

    // Libera a memória alocada para a mediana
    free(mediana);

    fclose(outputFile); // Fecha o arquivo de saída

    return 0; // Retorna 0 para indicar sucesso
}
