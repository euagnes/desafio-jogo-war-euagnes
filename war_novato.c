#include <stdio.h>
#include <string.h>

/*
 * Definição da Struct Territorio
 * Requisito: Agrupar nome, cor e quantidade de tropas.
 */
struct Territorio {
    char nome[30];
    char cor[10];
    int tropas;
};

int main() {
    // Declaração do vetor de structs para 5 territórios
    struct Territorio mapa[5];
    int i;

    printf("=== CONFIGURACAO INICIAL DO JOGO WAR ===\n");
    printf("Cadastro de 5 Territorios iniciais.\n\n");

    // Input
    // Loop para cadastro dos territórios
    for (i = 0; i < 5; i++) {
        printf("--- Cadastro do Territorio %d ---\n", i + 1);

        // Leitura do Nome
        // O espaço antes do %s serve para limpar o buffer do teclado
        printf("Nome do territorio (sem espacos): ");
        scanf(" %29s", mapa[i].nome);

        // Leitura da Cor
        printf("Cor do exercito (ex: Azul, Vermelho): ");
        scanf(" %9s", mapa[i].cor);

        // Leitura das Tropas
        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        
        printf("\n");
    }

    // Output
    // Exibe os dados após o cadastro
    printf("========================================\n");
    printf("      RESUMO DO MAPA E EXERCITOS        \n");
    printf("========================================\n");

    for (i = 0; i < 5; i++) {
        // Formatação alinhada para facilitar a leitura
        printf("Territorio %d: %-20s | Cor: %-10s | Tropas: %d\n", 
               i + 1, 
               mapa[i].nome, 
               mapa[i].cor, 
               mapa[i].tropas);
    }
    printf("========================================\n");

    return 0;
}