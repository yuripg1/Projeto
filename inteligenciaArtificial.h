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
int jogadaComputador(int *tabuleiro,int corComputador,int jogadasFeitas);
int minimax(int *tabuleiro,int profundidade,int corComputador,int jogadasFeitas,int alfa,int beta,clock_t tempoLimite);
int primeiroVazio(int *tabuleiro);
int temVizinho1(int *tabuleiro,int posicao);
int temVizinho2(int *tabuleiro,int posicao);
int temVizinho3(int *tabuleiro,int posicao);
int formaSequencia1(int *tabuleiro,int posicao,int corJogador);
int formaSequencia2(int *tabuleiro,int posicao,int corJogador);
int formaSequencia3(int *tabuleiro,int posicao,int corJogador);
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas);
int jogadaValida(int *tabuleiro,int jogada);
#endif
