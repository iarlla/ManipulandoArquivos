#include "abstract.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <locale.h>

float calcularArea(Ponto* vertices, int numVertices) {
    float area = 0.0;
    int i, j;

    for (i = 0; i < numVertices; i++) {
        j = (i + 1) % numVertices;
        area += (vertices[i].X * vertices[j].Y) - (vertices[j].X * vertices[i].Y);
    }

    return fabs(area) / 2.0;
}

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
