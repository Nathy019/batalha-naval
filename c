#include <stdio.h>

// Declaracao das variaveis globais
char tabuleiroJogador[5][5];  // Tabuleiro do jogador
char tabuleiroOponente[5][5]; // Tabuleiro do oponente
int x, y;                      // Coordenadas para posicionamento e palpites
int turnoJogador = 1;          // Indica se e a vez do jogador 1 (1) ou do jogador 2 (0)
int vencedor = 0;              // Indica se ha vencedor

// Funcao para inicializar o tabuleiro com agua (representado por '.')
void inicializarTabuleiro(char tabuleiro[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            tabuleiro[i][j] = '.';
        }
    }
}

// Funcao para exibir o tabuleiro (nao mostra o navio, apenas acertos/erros)
void exibirTabuleiro(char tabuleiro[5][5]) {
    printf("\n  0 1 2 3 4\n");
    for (int i = 0; i < 5; i++) {
        printf("%d ", i);
        for (int j = 0; j < 5; j++) {
            if (tabuleiro[i][j] == 'N') {
                printf(". ");  // Nao exibe o navio, so coloca um ponto invisivel
            } else {
                printf("%c ", tabuleiro[i][j]);  // Exibe os acertos e erros
            }
        }
        printf("\n");
    }
}

// Funcao para posicionar o navio no tabuleiro
int posicionarNavio(char tabuleiro[5][5], int x, int y) {
    if (tabuleiro[x][y] == '.') {
        tabuleiro[x][y] = 'N';  // 'N' representa o navio
        return 1;  // Navio colocado com sucesso
    } else {
        printf("Posicao ja ocupada! Tente novamente.\n");
        return 0;  // Nao conseguiu colocar o navio
    }
}

// Funcao para fazer o palpite e verificar se acertou ou errou
int fazerPalpite(char tabuleiro[5][5], int x, int y) {
    if (tabuleiro[x][y] == 'N') {
        tabuleiro[x][y] = 'X';  // Marca o acerto com 'X' na posicao exata
        return 1;  // Retorna 1 para indicar que foi um acerto
    } else if (tabuleiro[x][y] == '.') {
        tabuleiro[x][y] = 'O';  // Marca um erro com 'O'
        return 0;  // Retorna 0 para indicar que foi um erro
    }
    return -1;  // Indica que a posicao ja foi atacada
}

// Funcao para verificar se o jogador venceu
int verificarVencedor(char tabuleiro[5][5]) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (tabuleiro[i][j] == 'N') {  // Se ainda houver navio nao atingido
                return 0;  // O jogo continua
            }
        }
    }
    return 1;  // Se nao houver mais navios, o jogador venceu
}

int main() {
    // Inicializa os tabuleiros
    inicializarTabuleiro(tabuleiroJogador);
    inicializarTabuleiro(tabuleiroOponente);

    // Jogador 1 posiciona seu navio
    printf("Jogador 1, insira as coordenadas para posicionar o seu navio.\n");
    while (1) {
        printf("Digite as coordenadas (linha) para o navio: ");
        scanf("%d", &x);
        printf("Digite as coordenadas (coluna) para o navio: ");
        scanf("%d", &y);
        if (x >= 0 && x < 5 && y >= 0 && y < 5 && posicionarNavio(tabuleiroJogador, x, y)) {
            break;
        }
    }

    // Jogador 2 posiciona seu navio
    printf("Jogador 2, insira as coordenadas para posicionar o seu navio.\n");
    while (1) {
        printf("Digite as coordenadas (linha) para o navio: ");
        scanf("%d", &x);
        printf("Digite as coordenadas (coluna) para o navio: ");
        scanf("%d", &y);
        if (x >= 0 && x < 5 && y >= 0 && y < 5 && posicionarNavio(tabuleiroOponente, x, y)) {
            break;
        }
    }

    // Inicio do jogo
    while (!vencedor) {
        if (turnoJogador) {
            // Jogador 1 faz seu palpite
            printf("\nVez do Jogador 1:\n");
            exibirTabuleiro(tabuleiroOponente);  // Exibe o tabuleiro do oponente
            printf("Digite as coordenadas (linha) do palpite: ");
            scanf("%d", &x);
            printf("Digite as coordenadas (coluna) do palpite: ");
            scanf("%d", &y);
            if (x >= 0 && x < 5 && y >= 0 && y < 5) {
                int resultado = fazerPalpite(tabuleiroOponente, x, y);
                if (resultado == 1) {
                    printf("Jogador 1 acertou!\n");
                } else if (resultado == 0) {
                    printf("Jogador 1 errou.\n");
                } else {
                    printf("Jogada ja realizada. Tente outra posicao.\n");
                    continue;  // Volta para o comeco do loop sem mudar o turno
                }

                // Verifica se o jogador 1 venceu
                vencedor = verificarVencedor(tabuleiroOponente);
                if (!vencedor) {
                    turnoJogador = 0;  // Passa a vez para o jogador 2
                }
            } else {
                printf("Coordenadas invalidas, tente novamente.\n");
            }
        } else {
            // Jogador 2 faz seu palpite
            printf("\nVez do Jogador 2:\n");
            exibirTabuleiro(tabuleiroJogador);// Exibe o tabuleiro do jogador
            printf("Digite as coordenadas (linha) do palpite: ");
            scanf("%d", &x);
            printf("Digite as coordenadas (coluna) do palpite: ");
            scanf("%d", &y);
            if (x >= 0 && x < 5 && y >= 0 && y < 5) {
                int resultado = fazerPalpite(tabuleiroJogador, x, y);
                if (resultado == 1) {
                    printf("Jogador 2 acertou!\n");
                } else if (resultado == 0) {
                    printf("Jogador 2 errou.\n");
                } else {
                    printf("Jogada ja realizada. Tente outra posicao.\n");
                    continue;  // Volta para o comeco do loop sem mudar o turno
                }

                // Verifica se o jogador 2 venceu
                vencedor = verificarVencedor(tabuleiroJogador);
                if (!vencedor) {
                    turnoJogador = 1;  // Passa a vez para o jogador 1
                }
            } else {
                printf("Coordenadas invalidas, tente novamente.\n");
            }
        }
    }

    // Exibe o vencedor
    if (vencedor == 1) {
        if (turnoJogador == 1) {  // Jogador 1 venceu
                exibirTabuleiro(tabuleiroOponente);
            printf("\nJogador 1 venceu! Parabens!\n");
        } else {  // Jogador 2 venceu
            exibirTabuleiro(tabuleiroJogador);
            printf("\nJogador 2 venceu! Parabens!\n");
        }
    }

    return 0;
}

