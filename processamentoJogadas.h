#ifndef PROCESSAMENTO_JOGADAS_H
#include "jogo.h"
#define PROCESSAMENTO_JOGADAS_H
#define VAZIO 0
#define SIM 1
#define NAO 0
#define VITORIA_BRANCO 1
#define VITORIA_PRETO 2
#define EMPATE 3
#define SEM_VIZINHO (-1)
void processaJogada(struct JOGO *jogo,int jogada);
void desfazJogadas(struct JOGO *jogo);
void desfazUmaJogada(struct JOGO *jogo);
int temVizinho1(struct JOGO *jogo,int posicao);
int temVizinho2(struct JOGO *jogo,int posicao);
int temVizinho3(struct JOGO *jogo,int posicao);
int formaSequencia1(struct JOGO *jogo,int posicao);
int formaSequencia2(struct JOGO *jogo,int posicao);
int formaSequencia3(struct JOGO *jogo,int posicao);
int fimDeJogo(struct JOGO *jogo);
int jogadaValida(struct JOGO *jogo,int jogada);
#endif
