dividi esse arquivo em três: abrstract.h, funcoes.c e main.c:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

// Estrutura para armazenar informações do estado
typedef struct {
    char nomeEstado[100];
    char uf[3];
    int qtdVertices;
    float* paresVertices;
} Estado;

typedef struct {
    float X;
    float Y;
} Ponto;

// Função para calcular a área
float calcularArea(Ponto* vertices, int numVertices) {
    float area = 0.0;
    int i, j;

    for (i = 0; i < numVertices; i++) {
        j = (i + 1) % numVertices;
        area += (vertices[i].X * vertices[j].Y) - (vertices[j].X * vertices[i].Y);
    }

    return fabs(area) / 2.0;
}

// Função para ler um arquivo
void lerArquivo(const char* nomeArquivo, Estado *estado) {
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        perror("Erro ao abrir o arquivo");
        exit(1);
    }

    // Leitura das informações
    char linha[256];
    if (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *token = strtok(linha, ",");
        if (token != NULL) {
            strcpy(estado->nomeEstado, token);
            token = strtok(NULL, ",");
            if (token != NULL) {
                strcpy(estado->uf, token);
                token = strtok(NULL, ",");
                if (token != NULL) {
                    estado->qtdVertices = atoi(token);
                    estado->paresVertices = malloc(2 * estado->qtdVertices * sizeof(float));
                    token = strtok(NULL, " ");
                    for (int i = 0; i < 2 * estado->qtdVertices; i++) {
                        if (token != NULL) {
                            estado->paresVertices[i] = atof(token);
                            token = strtok(NULL, " ");
                        } else {
                            // Se não houver mais tokens, saia do loop
                            break;
                        }
                    }
                }
            }
        }
    }

    fclose(arquivo); // Não esqueça de fechar o arquivo
}

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
