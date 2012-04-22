#include "desenhoTabuleiro.h"
#include "processamentoJogadas.h"
void processaJogada(struct JOGO *jogo,int jogada){
	jogo->tabuleiro[jogada]=jogo->corAtual;
	desenhaJogada(jogada,jogo->corAtual,jogo->ultimaJogada);
	jogo->antepenultimaJogada=jogo->penultimaJogada;
	jogo->penultimaJogada=jogo->ultimaJogada;
	jogo->ultimaJogada=jogada;
	jogo->jogadasFeitas++;
	if(jogo->corJogador==jogo->corAtual){
		jogo->podeDesfazer=SIM;
	}
	switch(jogo->corAtual){
		case BRANCO:	jogo->corAtual=PRETO;
						break;
		case PRETO:		jogo->corAtual=BRANCO;
						break;
	}
}
void desfazJogadas(struct JOGO *jogo){
	jogo->tabuleiro[jogo->ultimaJogada]=VAZIO;
	jogo->tabuleiro[jogo->penultimaJogada]=VAZIO;
	desenhaDesfazer(jogo->ultimaJogada,jogo->penultimaJogada,jogo->antepenultimaJogada);
	jogo->ultimaJogada=jogo->antepenultimaJogada;
	jogo->penultimaJogada=SEM_JOGADA;
	jogo->antepenultimaJogada=SEM_JOGADA;
	jogo->jogadasFeitas-=2;
	jogo->podeDesfazer=NAO;
}
void desfazUmaJogada(struct JOGO *jogo){
	jogo->tabuleiro[jogo->ultimaJogada]=VAZIO;
	desenhaMeioDesfazer(jogo->ultimaJogada,jogo->penultimaJogada);
	jogo->ultimaJogada=jogo->penultimaJogada;
	jogo->penultimaJogada=jogo->antepenultimaJogada;
	jogo->antepenultimaJogada=SEM_JOGADA;
	jogo->jogadasFeitas--;
	jogo->podeDesfazer=NAO;
	switch(jogo->corAtual){
		case BRANCO:	jogo->corAtual=PRETO;
						break;
		case PRETO:		jogo->corAtual=BRANCO;
						break;
	}
}
int temVizinho1(struct JOGO *jogo,int posicao){
	int vizinho;
	if((posicao==4)||(posicao==10)||(posicao==17)||(posicao==25)||(posicao==34)||(posicao==42)||(posicao==49)||(posicao==55)||(posicao==60)){
		return SEM_VIZINHO;
	}
	vizinho=posicao+1;
	if(jogo->tabuleiro[posicao]==jogo->tabuleiro[vizinho]){
		return vizinho;
	}
	return SEM_VIZINHO;
}
int temVizinho2(struct JOGO *jogo,int posicao){
	int vizinho;
	if((posicao<5)||(posicao==10)||(posicao==17)||(posicao==25)||(posicao==34)){
		return SEM_VIZINHO;
	}
	if((posicao>25)&&(posicao<43)){
		vizinho=posicao-8;
	}
	else{
		if((posicao>17)&&(posicao<50)){
			vizinho=posicao-7;
		}
		else{
			if((posicao>10)&&(posicao<56)){
				vizinho=posicao-6;
			}
			else{
				vizinho=posicao-5;
			}
		}
	}
	if(jogo->tabuleiro[posicao]==jogo->tabuleiro[vizinho]){
		return vizinho;
	}
	return SEM_VIZINHO;
}
int temVizinho3(struct JOGO *jogo,int posicao){
	int vizinho;
	if((posicao==34)||(posicao==42)||(posicao==49)||(posicao>54)){
		return SEM_VIZINHO;
	}
	if((posicao>17)&&(posicao<35)){
		vizinho=posicao+9;
	}
	else{
		if((posicao>10)&&(posicao<43)){
			vizinho=posicao+8;
		}
		else{
			if((posicao>4)&&(posicao<50)){
				vizinho=posicao+7;
			}
			else{
				vizinho=posicao+6;
			}
		}
	}
	if(jogo->tabuleiro[posicao]==jogo->tabuleiro[vizinho]){
		return vizinho;
	}
	return SEM_VIZINHO;
}
int formaSequencia1(struct JOGO *jogo,int posicao){
	int numeroVizinhos=1,vizinho;
	vizinho=temVizinho1(jogo,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos++;
		vizinho=temVizinho1(jogo,vizinho);
	}
	if(numeroVizinhos==3){
		if(jogo->tabuleiro[posicao]==PRETO){
			return VITORIA_BRANCO;
		}
		return VITORIA_PRETO;
	}
	if(numeroVizinhos==4){
		return jogo->tabuleiro[posicao];
	}
	return NAO;
}
int formaSequencia2(struct JOGO *jogo,int posicao){
	int numeroVizinhos=1,vizinho;
	vizinho=temVizinho2(jogo,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos++;
		vizinho=temVizinho2(jogo,vizinho);
	}
	if(numeroVizinhos==3){
		if(jogo->tabuleiro[posicao]==PRETO){
			return VITORIA_BRANCO;
		}
		return VITORIA_PRETO;
	}
	if(numeroVizinhos==4){
		return jogo->tabuleiro[posicao];
	}
	return NAO;
}
int formaSequencia3(struct JOGO *jogo,int posicao){
	int numeroVizinhos=1,vizinho;
	vizinho=temVizinho3(jogo,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos++;
		vizinho=temVizinho3(jogo,vizinho);
	}
	if(numeroVizinhos==3){
		if(jogo->tabuleiro[posicao]==PRETO){
			return VITORIA_BRANCO;
		}
		return VITORIA_PRETO;
	}
	if(numeroVizinhos==4){
		return jogo->tabuleiro[posicao];
	}
	return NAO;
}
int fimDeJogo(struct JOGO *jogo){
	int i,sequencia;
	for(i=0;i<3;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=5;i<9;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=11;i<16;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=18;i<24;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=26;i<33;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=35;i<41;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=43;i<48;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=50;i<54;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=56;i<59;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=11;i<16;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=18;i<24;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=26;i<33;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=35;i<42;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=43;i<61;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=0;i<25;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=26;i<33;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=35;i<41;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	for(i=43;i<48;i++){
		if(jogo->tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(jogo,i);
			if(sequencia!=NAO){
				return sequencia;
			}
		}
	}
	if(jogo->jogadasFeitas==61){
		return EMPATE;
	}
	return NAO;
}
int jogadaValida(struct JOGO *jogo,int jogada){
	if(jogo->tabuleiro[jogada]==VAZIO){
		return SIM;
	}
	return NAO;
}
