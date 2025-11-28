#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da Struct
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// --- PROTOTIPOS DAS FUNÇÕES ---
void cadastrarTerritorios(Territorio* lista, int qtd);
void exibirTerritorios(Territorio* lista, int qtd);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* lista);

int main() {
    Territorio* mapa; // Vetor dinâmico
    int qtdTerritorios;
    int idAtacante, idDefensor;
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL)); 

    printf("=== WAR: NIVEL AVENTUREIRO ===\n");
    
    // 1. Definição do tamanho do mapa (Alocação Dinâmica)
    printf("Quantos territorios deseja cadastrar no jogo? ");
    scanf("%d", &qtdTerritorios);

    // Alocação de memória usando calloc (inicializa com zero)
    // Sintaxe: (cast*) calloc(quantidade, tamanho_de_cada_item)
    mapa = (Territorio*) calloc(qtdTerritorios, sizeof(Territorio));

    if (mapa == NULL) {
        printf("Erro: Memoria insuficiente!\n");
        return 1;
    }

    // 2. Cadastro
    cadastrarTerritorios(mapa, qtdTerritorios);

    // 3. Exibição inicial
    printf("\n--- SITUACAO INICIAL ---\n");
    exibirTerritorios(mapa, qtdTerritorios);

    // 4. Lógica de Ataque
    printf("\n--- FASE DE ATAQUE ---\n");
    printf("Escolha o ID do territorio ATACANTE (1 a %d): ", qtdTerritorios);
    scanf("%d", &idAtacante);
    printf("Escolha o ID do territorio DEFENSOR (1 a %d): ", qtdTerritorios);
    scanf("%d", &idDefensor);

    // Ajuste de índice (usuário digita 1, vetor começa em 0)
    idAtacante--; 
    idDefensor--;

    // Validações básicas
    if (idAtacante < 0 || idAtacante >= qtdTerritorios || idDefensor < 0 || idDefensor >= qtdTerritorios) {
        printf("Erro: ID de territorio invalido.\n");
    } else if (idAtacante == idDefensor) {
        printf("Erro: Um territorio nao pode atacar a si mesmo.\n");
    } else if (strcmp(mapa[idAtacante].cor, mapa[idDefensor].cor) == 0) {
        printf("Erro: Nao e possivel atacar um territorio aliado (mesma cor).\n");
    } else {
        // Passamos os ENDEREÇOS (&) dos territórios específicos para a função
        atacar(&mapa[idAtacante], &mapa[idDefensor]);
    }

    // 5. Exibição pós-ataque
    printf("\n--- SITUACAO APOS BATALHA ---\n");
    exibirTerritorios(mapa, qtdTerritorios);

    // 6. Liberação de memória (Garbage Collection manual)
    liberarMemoria(mapa);
    printf("\nMemoria liberada. Jogo encerrado.\n");

    return 0;
}

// --- IMPLEMENTAÇÃO DAS FUNÇÕES ---

void cadastrarTerritorios(Territorio* lista, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("\nCadastrando Territorio ID %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %29s", lista[i].nome); // lista[i] acessa a struct, .nome acessa o campo
        printf("Cor do exercito: ");
        scanf(" %9s", lista[i].cor);
        printf("Numero de tropas: ");
        scanf("%d", &lista[i].tropas);
    }
}

void exibirTerritorios(Territorio* lista, int qtd) {
    for (int i = 0; i < qtd; i++) {
        printf("ID %d | %-15s | Cor: %-10s | Tropas: %d\n", 
               i + 1, lista[i].nome, lista[i].cor, lista[i].tropas);
    }
}

// A função recebe PONTEIROS, permitindo alterar os dados originais
void atacar(Territorio* atacante, Territorio* defensor) {
    printf("\n>>> INICIANDO COMBATE: %s vs %s <<<\n", atacante->nome, defensor->nome);
    
    // Simulação de dados (1 a 6)
    int dadoAtacante = (rand() % 6) + 1;
    int dadoDefensor = (rand() % 6) + 1;

    printf("Resultado dos dados -> Atacante: %d | Defensor: %d\n", dadoAtacante, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("VITORIA DO ATACANTE!\n");
        printf("O territorio %s foi conquistado!\n", defensor->nome);
        
        // Atualiza a cor do defensor para a cor do atacante
        strcpy(defensor->cor, atacante->cor);
        
        // Movimenta metade das tropas (lógica simplificada do desafio)
        int tropasMovidas = atacante->tropas / 2;
        defensor->tropas = tropasMovidas;
        atacante->tropas -= tropasMovidas;
        
    } else {
        printf("VITORIA DA DEFESA!\n");
        printf("O ataque falhou.\n");
        
        // Penalidade: Atacante perde 1 tropa
        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }
    }
}

void liberarMemoria(Territorio* lista) {
    free(lista);
}