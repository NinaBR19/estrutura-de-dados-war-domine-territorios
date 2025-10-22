#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Estrutura do território
typedef struct {
    char nome[30];
    char cor[10];
    int tropas;
} Territorio;

// Funções do sistema
void cadastrarTerritorios(Territorio* mapa, int n);
void exibirTerritorios(Territorio* mapa, int n);
void atacar(Territorio* atacante, Territorio* defensor);
void liberarMemoria(Territorio* mapa);

int main() {
    srand(time(NULL)); // Garante aleatoriedade nos dados

    int n;
    printf("Digite o numero total de territorios: ");
    scanf("%d", &n);
    getchar(); // limpa o buffer

    // Alocação dinâmica dos territórios
    Territorio* mapa = (Territorio*) calloc(n, sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria.\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, n);

    int opcao;
    do {
        printf("\n==== MENU ====\n");
        printf("1 - Exibir territorios\n");
        printf("2 - Atacar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                exibirTerritorios(mapa, n);
                break;
            case 2: {
                int i, j;
                exibirTerritorios(mapa, n);

                printf("\nDigite o indice do territorio atacante: ");
                scanf("%d", &i);
                printf("Digite o indice do territorio defensor: ");
                scanf("%d", &j);

                // Verifica índices válidos
                if (i < 0 || i >= n || j < 0 || j >= n) {
                    printf("Indices invalidos!\n");
                    break;
                }

                // Verifica se não está atacando a si mesmo
                if (i == j) {
                    printf("Um territorio nao pode atacar a si mesmo!\n");
                    break;
                }

                // Verifica se o atacante e defensor têm cores diferentes
                if (strcmp(mapa[i].cor, mapa[j].cor) == 0) {
                    printf("Voce nao pode atacar um territorio da mesma cor!\n");
                    break;
                }

                atacar(&mapa[i], &mapa[j]);
                exibirTerritorios(mapa, n);
                break;
            }
            case 0:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }

    } while (opcao != 0);

    liberarMemoria(mapa);
    return 0;
}

// Função para cadastrar territórios
void cadastrarTerritorios(Territorio* mapa, int n) {
    for (int i = 0; i < n; i++) {
        printf("\nCadastro do territorio %d\n", i);
        printf("Nome: ");
        fgets(mapa[i].nome, 30, stdin);
        mapa[i].nome[strcspn(mapa[i].nome, "\n")] = '\0'; // remove \n

        printf("Cor do exercito: ");
        fgets(mapa[i].cor, 10, stdin);
        mapa[i].cor[strcspn(mapa[i].cor, "\n")] = '\0';

        printf("Quantidade de tropas: ");
        scanf("%d", &mapa[i].tropas);
        getchar();
    }
}

// Exibe os territórios cadastrados
void exibirTerritorios(Territorio* mapa, int n) {
    printf("\n=== ESTADO ATUAL DOS TERRITORIOS ===\n");
    for (int i = 0; i < n; i++) {
        printf("[%d] %s - Cor: %s - Tropas: %d\n",
               i, mapa[i].nome, mapa[i].cor, mapa[i].tropas);
    }
}

// Simulação de ataque entre territórios
void atacar(Territorio* atacante, Territorio* defensor) {
    if (atacante->tropas < 2) {
        printf("\nO territorio atacante precisa ter pelo menos 2 tropas para atacar!\n");
        return;
    }

    printf("\n--- Simulando ataque ---\n");
    int dadoAtacante = rand() % 6 + 1; // número entre 1 e 6
    int dadoDefensor = rand() % 6 + 1;

    printf("%s (Atacante) tirou: %d\n", atacante->nome, dadoAtacante);
    printf("%s (Defensor) tirou: %d\n", defensor->nome, dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nO atacante venceu a batalha!\n");
        strcpy(defensor->cor, atacante->cor); // muda o dono
        defensor->tropas = atacante->tropas / 2; // transfere metade das tropas
        atacante->tropas -= defensor->tropas / 2; // atacante perde algumas tropas
    } else if (dadoAtacante < dadoDefensor) {
        printf("\nO defensor resistiu ao ataque!\n");
        atacante->tropas -= 1; // atacante perde uma tropa
    } else {
        printf("\nEmpate! Ambos perdem uma tropa.\n");
        atacante->tropas -= 1;
        defensor->tropas -= 1;
    }

    if (atacante->tropas < 0) atacante->tropas = 0;
    if (defensor->tropas < 0) defensor->tropas = 0;
}

// Libera memória alocada dinamicamente
void liberarMemoria(Territorio* mapa) {
    free(mapa);
    printf("\nMemoria liberada com sucesso!\n");
}
prinft("Novo commit\n");