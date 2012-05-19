#ifndef INTELIGENCIA_ARTIFICIAL_H
#define INTELIGENCIA_ARTIFICIAL_H
#define VAZIO 0
#define NAO 0
#define SIM 1
#define SEM_VIZINHO (-1)
#define ALFA (-300)
#define DERROTA (-200)
#define EMPATE (-100)
#define CONTINUA 0
#define VITORIA 100
#define BETA 200
#define DERROTA_BRANCO (-201)
#define VITORIA_BRANCO 101
#define DERROTA_PRETO (-202)
#define VITORIA_PRETO 102
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador);
int primeiroMax(clock_t tempoLimite,int jogadasFeitas,int profundidade,int *tabuleiro,int corComputador);
int minimax(clock_t tempoLimite,int *tabuleiro,int corComputador,int jogadasFeitas,int profundidade,int alfa,int beta);
int qualquerVazio(int *tabuleiro);
int primeiroVazio(int *tabuleiro);
int temVizinho1(int *tabuleiro,int posicao);
int temVizinho2(int *tabuleiro,int posicao);
int temVizinho3(int *tabuleiro,int posicao);
int formaSequencia1(int *tabuleiro,int posicao);
int formaSequencia2(int *tabuleiro,int posicao);
int formaSequencia3(int *tabuleiro,int posicao);
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas);
int jogadaValida(int *tabuleiro,int jogada);
#endif
