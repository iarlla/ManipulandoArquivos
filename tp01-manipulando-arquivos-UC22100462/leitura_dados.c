#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <string.h>

int main() {
    // Configura a localização para o português (para suportar acentuação)
    setlocale(LC_ALL, "Portuguese");

    // Declaração de ponteiros de arquivo para entrada e saída
    FILE *entrada, *saida;

    // Abre o arquivo de entrada para leitura e o arquivo de saída para escrita
    entrada = fopen("DadosEntrada.csv", "r");
    saida = fopen("SituacaoFinal.csv", "w");

    // Verifica se a abertura dos arquivos foi bem-sucedida
    if (entrada == NULL || saida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1); // Encerra o programa com código de erro
    }

    char linha[256];

    // Escreve o cabeçalho no arquivo de saída
    fprintf(saida, "Nome, Curso, Média, Situação\n");

    // Lê e descarta a primeira linha (cabeçalho) do arquivo de entrada
    fgets(linha, sizeof(linha), entrada);

    // Loop principal para ler e processar as linhas do arquivo de entrada
    while (fgets(linha, sizeof(linha), entrada)) {
        char *nome, *telefone, *curso;
        float nota1, nota2, media;

        // Usando strtok para separar os valores na linha com base na vírgula
        nome = strtok(linha, ",");
        telefone = strtok(NULL, ",");
        curso = strtok(NULL, ",");
        nota1 = atof(strtok(NULL, ","));
        nota2 = atof(strtok(NULL, ","));

        // Remover o caractere de nova linha do nome (caso ele exista)
        char *posicaoNovaLinha = strchr(nome, '\n');
        if (posicaoNovaLinha != NULL) {
            *posicaoNovaLinha = '\0'; // Substitui o '\n' por '\0' para terminar a string
        }

        // Calcula a média das notas
        media = (nota1 + nota2) / 2.0;

        // Determina a situação do aluno com base na média
        char *situacao = (media >= 7.0) ? "APROVADO" : "REPROVADO";
/*utiliza o operador ternário para determinar a situação do aluno com base na média. O operador ternário é uma forma concisa de expressar uma estrutura condicional.*/


        // Escreve os dados processados no arquivo de saída
        fprintf(saida, "%s, %s, %.2f, %s\n", nome, curso, media, situacao);
    }

    // Fecha os arquivos de entrada e saída
    fclose(entrada);
    fclose(saida);

    return 0; // Retorna 0 para indicar que o programa foi executado com sucesso
}
