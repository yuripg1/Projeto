#ifndef INTELIGENCIA_ARTIFICIAL_H
#define INTELIGENCIA_ARTIFICIAL_H
#define VAZIO 0
#define NAO 0
#define SIM 1
#define SEM_VIZINHO (-1)
#define DERROTA 0
#define EMPATE 1
#define CONTINUA 2
#define VITORIA 3
#define SEM_ALFA_BETA (-1)
int jogadaComputador(int *tabuleiro,int corComputador,int profundidadeMinimax,int jogadasFeitas);
char minimax(int *tabuleiro,char profundidade,char corAtual,char jogadasFeitas,char alfaBeta);
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
