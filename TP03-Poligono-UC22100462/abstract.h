#ifndef ABSTRACT_H
#define ABSTRACT_H

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

float calcularArea(Ponto* vertices, int numVertices);
void lerArquivo(const char* nomeArquivo, Estado *estado);

#endif
