#include "abstract.h"
#include <stdio.h>
#include <stdlib.h>

int main() {
    int numArquivos = 27; // Número de arquivos a serem lidos, por exemplo
    Estado estados[numArquivos];

    // Supondo que você queira ler "uf0.txt" e "uf1.txt"
    for (int b = 0; b < numArquivos; b++) {
        char nomeArquivo[10]; // Aloque espaço suficiente para o nome do arquivo
        snprintf(nomeArquivo, sizeof(nomeArquivo), "uf%d.txt", b);

        lerArquivo(nomeArquivo, &estados[b]);
    }

    // Imprimir e salvar os dados em um único arquivo
    FILE* saida = fopen("todasUF.txt", "w");
    if (saida == NULL) {
        perror("Erro ao abrir o arquivo de saída");
        exit(1);
    }

    for (int b = 0; b < numArquivos; b++) {
        printf("Nome do Estado: %s\n", estados[b].nomeEstado);
        printf("UF: %s\n", estados[b].uf);
        printf("Quantidade de Vértices: %d\n", estados[b].qtdVertices);

        fprintf(saida, "Nome do Estado: %s\n", estados[b].nomeEstado);
        fprintf(saida, "UF: %s\n", estados[b].uf);
        fprintf(saida, "Quantidade de Vértices: %d\n", estados[b].qtdVertices);

        printf("Pares de Vértices:\n");
        fprintf(saida, "Pares de Vértices:\n");

        for (int i = 0; i < estados[b].qtdVertices; i++) {
            printf("(%.2f, %.2f)\n", estados[b].paresVertices[i * 2], estados[b].paresVertices[i * 2 + 1]);
            fprintf(saida, "(%.2f, %.2f)\n", estados[b].paresVertices[i * 2], estados[b].paresVertices[i * 2 + 1]);
        }

        // Calcular a área
        Ponto* vertices = malloc(estados[b].qtdVertices * sizeof(Ponto));
        for (int i = 0; i < estados[b].qtdVertices; i++) {
            vertices[i].X = estados[b].paresVertices[i * 2];
            vertices[i].Y = estados[b].paresVertices[i * 2 + 1];
        }
        float area = calcularArea(vertices, estados[b].qtdVertices);
        printf("Área: %.2f km²\n\n", area);
        fprintf(saida, "Área: %.2f km²\n\n", area);

        free(vertices); // Liberar a memória alocada para vertices
    }

    fclose(saida);

    // Liberar a memória alocada para os paresVertices
    for (int b = 0; b < numArquivos; b++) {
        free(estados[b].paresVertices);
    }

    return 0;
}
