#ifndef INTELIGENCIA_ARTIFICIAL_H
#define INTELIGENCIA_ARTIFICIAL_H
#include <time.h>
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador);
int primeiroMax(clock_t tempoLimite,int jogadasFeitas,int profundidade,int *tabuleiro,int corComputador);
int minimax(clock_t tempoLimite,int *tabuleiro,int corComputador,int jogadasFeitas,int profundidade,int alfa,int beta);
int primeiroVazio(int *tabuleiro);
int primeiroVazio2(int *tabuleiro);
int temVizinho1(int *tabuleiro,int posicao);
int temVizinho2(int *tabuleiro,int posicao);
int temVizinho3(int *tabuleiro,int posicao);
int formaSequencia1(int *tabuleiro,int posicao);
int formaSequencia2(int *tabuleiro,int posicao);
int formaSequencia3(int *tabuleiro,int posicao);
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas);
int jogadaValida(int *tabuleiro,int jogada);
#endif
