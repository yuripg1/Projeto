#include "jogo.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int ultimaJogada,int penultimaJogada,int corAtual,int corJogador,int profundidadeMinimax,int jogadasFeitas){
	int proximaJogada;
	int posicao=0;
	while(jogadaValida(tabuleiro,posicao)==NAO){
		posicao++;
	}
	proximaJogada=posicao;
	return proximaJogada;
}
