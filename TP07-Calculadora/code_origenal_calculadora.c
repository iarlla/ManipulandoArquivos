#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

// Definição da estrutura da pilha
typedef struct No {
    double dado;
    struct No *proximo;
} No;

typedef struct {
    No *topo;
} Pilha;

// Função auxiliar para converter uma substring em um número
double converterSubstringParaNumero(const char *str) {
    char *endptr;
    return strtod(str, &endptr);
}

// Função auxiliar para imprimir os elementos da pilha (apenas para depuração)
void imprimirPilha(const Pilha *pilha) {
    No *atual = pilha->topo;
    while (atual != NULL) {
        printf("%.2f ", atual->dado);
        atual = atual->proximo;
    }
    printf("\n");
}

// Função para inicializar a pilha
void inicializar(Pilha *pilha) {
    pilha->topo = NULL;
}

// Função para empilhar um valor na pilha
void empilhar(Pilha *pilha, double valor) {
    No *novoNo = (No *)malloc(sizeof(No));
    if (novoNo == NULL) {
        printf("Erro: Falha na alocação de memória\n");
        exit(EXIT_FAILURE);
    }
    novoNo->dado = valor;
    novoNo->proximo = pilha->topo;
    pilha->topo = novoNo;
}

// Função para desempilhar um valor da pilha
double desempilhar(Pilha *pilha) {
    if (pilha->topo != NULL) {
        No *temp = pilha->topo;
        double valor = temp->dado;
        pilha->topo = temp->proximo;
        free(temp);
        return valor;

    } else {
        printf("Erro: Pilha vazia\n");
        imprimirPilha(pilha);
        //exit(EXIT_FAILURE);
    }
}

// Função principal para avaliar uma expressão em notação pós-fixada
double avaliarExpressaoPosfixada(const char *expressao) {
    Pilha pilha;
    inicializar(&pilha);

    for (int i = 0; expressao[i] != '\0'; ++i) {
        // Se for um dígito, converte para double e empilha
        if (isdigit(expressao[i]) || expressao[i] == '.') {
            char numeroStr[50];  // Tamanho arbitrário, ajuste conforme necessário
            int j = 0;
            while (isdigit(expressao[i]) || expressao[i] == '.') {
                numeroStr[j++] = expressao[i++];
            }
            numeroStr[j] = '\0';
            double numero = converterSubstringParaNumero(numeroStr);
            empilhar(&pilha, numero);
        } else if (expressao[i] == ' ' || expressao[i] == '\t') {
            // Ignora espaços em branco
            continue;
        } else {
            // Se for um operador, ...
            double operando2 = desempilhar(&pilha);
            double operando1 = desempilhar(&pilha);
            switch (expressao[i]) {
                case '+':
                    empilhar(&pilha, operando1 + operando2);
                    break;
                case '-':
                    empilhar(&pilha, operando1 - operando2);
                    break;
                case '*':
                    empilhar(&pilha, operando1 * operando2);
                    break;
                case '/':
                    if (operando2 != 0.0) {
                        empilhar(&pilha, operando1 / operando2);
                    } else {
                        printf("Erro: Divisão por zero\n");
                        exit(EXIT_FAILURE);
                    }
                    break;
                case '^':
                    empilhar(&pilha, pow(operando1, operando2));
                    break;
                case 'l':
                    empilhar(&pilha, log10(operando2));
                    break;
                case 's':
                    empilhar(&pilha, sin(operando2));
                    break;
                case 'c':
                    empilhar(&pilha, cos(operando2));
                    break;
                case 't':
                    empilhar(&pilha, tan(operando2));
                    break;
                default:
                    printf("Erro: Operador inválido\n");
                    exit(EXIT_FAILURE);
            }
        }
    }

    // O resultado final estará no topo da pilha
    return desempilhar(&pilha);
}

int main() {
    const char *expressao = "3 4 + 5 *";
    double resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 1: (3 + 4) * 5 = %.2f\n", resultado);

    expressao = "7 2 * 4 +";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 2: 7 * 2 + 4 = %.2f\n", resultado);

    expressao = "8 5 2 4 + * +";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 3: 8 + (5 * (2 + 4)) = %.2f\n", resultado);

    expressao = "6 2 / 3 + 4 *";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 4: (6 / 2 + 3) * 4 = %.2f\n", resultado);
    
    expressao = "9 5 2 8 * 4 + * +";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 5: 9 + (5 * (2 + 8 * 4)) = %.2f\n", resultado);

    expressao = "2 3 + l 5 / ";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 6: log(2 + 3) / 5 = %.2f\n", resultado);

    expressao = "10 l 3 ^ 2 +";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 7: 3^log10 + 2 = %.2f\n", resultado);

    expressao = "45 60 + 30 c *";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 8: (45 + 60) * cos(30) = %.2f\n", resultado);

    expressao = "0.5 45 s 2 ^ +";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 9: 2 ^ sen(45) + 0,5 = %.2f\n", resultado);

    expressao = "3 4 + 5 t *";
    resultado = avaliarExpressaoPosfixada(expressao);
    printf("Teste 10: (3 + 4) * tan(5) = %.2f\n", resultado);

    return 0;
}
