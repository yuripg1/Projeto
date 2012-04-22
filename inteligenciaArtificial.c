#include "processamentoJogadas.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(struct JOGO *jogo){
	int proximaJogada;
	int posicao=0;
	while(jogadaValida(jogo,posicao)==NAO){
		posicao++;
	}
	proximaJogada=posicao;
	return proximaJogada;
}
