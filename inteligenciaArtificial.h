#ifndef INTELIGENCIA_ARTIFICIAL_H
#define INTELIGENCIA_ARTIFICIAL_H
#include <time.h>
#include <windows.h>
struct RESULTADO{
	int numeroNiveis;
	clock_t tempo;
	int melhorJogada;
};
struct MINIMAX{
	clock_t tempoLimite;
	int jogadasFeitas;
	int profundidade;
	int *tabuleiro;
	int corComputador;
	struct RESULTADO *resultado;
};
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador);
DWORD WINAPI thread1(LPVOID lpParam);
DWORD WINAPI thread2(LPVOID lpParam);
int primeiroMax(clock_t tempoLimite,int jogadasFeitas,int profundidade,int *tabuleiro,int corComputador);
int minimax(clock_t tempoLimite,int *tabuleiro,int corComputador,int jogadasFeitas,int profundidade,int alfa,int beta);
int primeiroVazio(int *tabuleiro);
int primeiroVazio2(int *tabuleiro);
int formaSequencia(int *tabuleiro,int posicao,int sentidoVizinho);
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas);
int jogadaValida(int *tabuleiro,int jogada);
#endif
