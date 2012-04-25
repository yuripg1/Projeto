#ifndef INTELIGENCIA_ARTIFICIAL_H
#define INTELIGENCIA_ARTIFICIAL_H
#define NAO 0
#define VITORIA_BRANCO 1
#define VITORIA_PRETO 2
#define EMPATE 3
int jogadaComputador(int *tabuleiro,int ultimaJogada,int penultimaJogada,int corAtual,int corJogador,int profundidadeMinimax,int jogadasFeitas);
#endif
