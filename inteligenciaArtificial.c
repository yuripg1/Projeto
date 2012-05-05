#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "desenhoTabuleiro.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int corComputador,int jogadasFeitas,int profundidadeMinimax){
	int proximaJogada=(-1),resultado,melhorResultado,i,jogadasPossiveis[61],numeroJogadasPossiveis;
	clock_t tempoInicio,tempoLimite,tempoAtual;

	// Grava o tempo de início do raciocínio
	tempoInicio=clock();

	// Determina o tempo limite para o raciocícnio
	tempoLimite=tempoInicio+((clock_t)(((float)(5*CLOCKS_PER_SEC))*0.99f));

	// Joga na primeira posição vazia caso não consiga processar em tempo
	proximaJogada=primeiroVazio(tabuleiro);

	jogadasFeitas++;
	profundidadeMinimax--;
	do{
		numeroJogadasPossiveis=1;
		melhorResultado=ALFA;
		for(i=0;i<61;i++){

			// Verifica se é possível jogar em determinada posição
			if(tabuleiro[i]==VAZIO){

				// Efetua sub-jogada
				tabuleiro[i]=corComputador;

				// Aplica o minimax para esta sub-jogada
				resultado=minimax(tabuleiro,profundidadeMinimax,corComputador,jogadasFeitas,ALFA,BETA,tempoLimite);

				// Restaura estado original do tabuleiro
				tabuleiro[i]=VAZIO;

				// Calcula o MAX (e a candidata a próxima jogada)
				if(resultado>melhorResultado){
					melhorResultado=resultado;
					jogadasPossiveis[0]=i;
					numeroJogadasPossiveis=1;
				}

				// Adiciona a lista de jogadas possiveis
				if(resultado==melhorResultado){
					jogadasPossiveis[numeroJogadasPossiveis]=i;
					numeroJogadasPossiveis++;
				}

			}

		}
		tempoAtual=clock();

		// Aceita só os processamentos concluídos antes do tempo estourar
		if(tempoAtual<tempoLimite){

			// A próxima jogada será uma das opções ótimas
			proximaJogada=jogadasPossiveis[rand()%numeroJogadasPossiveis];

			// Aumenta a profundidade para a próxima tentativa (se der para aumentar)
			if(profundidadeMinimax<60){
				profundidadeMinimax++;
			}

		}

	}
	while(tempoAtual<tempoLimite);

	// Cores para as impressões na tela
	textbackground(DARKGRAY);
	textcolor(BLACK);

	// Imprime a profundidade alcançada no processamento
	cputsxy(41,7,"  ");
	gotoxy(41,7);
	printf("%d",profundidadeMinimax);

	// Imprime o tempo decorrido no raciocínio
	gotoxy(41,15);
	printf("Tempo de raciocinio: %1.3f segundos",((float)(clock()-tempoInicio))/((float)CLOCKS_PER_SEC));

	// Retorna qual deverá ser a próxima jogada
	return proximaJogada;
}
int minimax(int *tabuleiro,int profundidade,int corComputador,int jogadasFeitas,int alfa,int beta,clock_t tempoLimite){
	int primeiroResultado;

	// Interrompe o processamento caso tenha estourado o tempo
	if(clock()>tempoLimite){
		return CONTINUA;
	}

	// Calcula o resultado do estado atual do tabuleiro
	primeiroResultado=resultadoJogo(tabuleiro,corComputador,jogadasFeitas);

	// verifica se o jogo continua
	if(primeiroResultado==CONTINUA){

		// Verifica se não ultrapassou a profundidade limite
		if(profundidade!=0){

			int i=30,proximo=0,resultado,cor;
			profundidade--;

			// Verifica de que cor a jogada será
			if((jogadasFeitas%2)==0){
				cor=BRANCO;
			}
			else{
				cor=PRETO;
			}

			jogadasFeitas++;

			// Bloco onde é calculado o MAX
			if(cor==corComputador){
				while(i>(-1)){

					// Verifica se é possível jogar em determinada posição
					if(tabuleiro[i]==VAZIO){

						// Efetua sub-jogada
						tabuleiro[i]=cor;

						// Aplica o minimax para esta sub-jogada
						resultado=minimax(tabuleiro,profundidade,corComputador,jogadasFeitas,alfa,beta,tempoLimite);

						// Restaura estado original do tabuleiro
						tabuleiro[i]=VAZIO;

						// Calcula o MAX
						if(resultado>alfa){

							// Realização da poda beta
							if(beta<=resultado){
								return resultado;
							}

							alfa=resultado;
						}

					}
					if(proximo<0){
						proximo--;
					}
					else{
						proximo++;
					}
					proximo*=(-1);
					i+=proximo;
				}

				// Retorna o MAX calculado acima
				return alfa;

			}

			// Bloco onde é calculado o MIN
			while(i>(-1)){

				// Verifica se é possível jogar em determinada posição
				if(tabuleiro[i]==VAZIO){

					// Efetua sub-jogada
					tabuleiro[i]=cor;

					// Aplica o minimax para esta sub-jogada
					resultado=minimax(tabuleiro,profundidade,corComputador,jogadasFeitas,alfa,beta,tempoLimite);

					// Restaura estado original do tabuleiro
					tabuleiro[i]=VAZIO;

					// Calcula o MIN
					if(resultado<beta){

						// Realização da poda alfa
						if(resultado<=alfa){
							return resultado;
						}

						beta=resultado;
					}

				}
				if(proximo<0){
					proximo--;
				}
				else{
					proximo++;
				}
				proximo*=(-1);
				i+=proximo;
			}

			// Retorna o MIN calculado acima
			return beta;

		}

		return CONTINUA;

	}

	// Dá mais peso para vitórias e derrotas mais próximas (com menos jogadas)
	if(primeiroResultado>CONTINUA){
		primeiroResultado-=jogadasFeitas;
	}
	else{
		primeiroResultado+=jogadasFeitas;
	}

	// Retorna o resultado do estado atual do tabuleiro
	return primeiroResultado;

}
int primeiroVazio(int *tabuleiro){
	int posicao=0;
	while(jogadaValida(tabuleiro,posicao)==NAO){
		posicao++;
	}
	return posicao;
}
int temVizinho1(int *tabuleiro,int posicao){
	int vizinho;
	if((posicao==4)||(posicao==10)||(posicao==17)||(posicao==25)||(posicao==34)||(posicao==42)||(posicao==49)||(posicao==55)||(posicao==60)){
		return SEM_VIZINHO;
	}
	vizinho=posicao+1;
	if(tabuleiro[posicao]==tabuleiro[vizinho]){
		return vizinho;
	}
	return SEM_VIZINHO;
}
int temVizinho2(int *tabuleiro,int posicao){
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
	if(tabuleiro[posicao]==tabuleiro[vizinho]){
		return vizinho;
	}
	return SEM_VIZINHO;
}
int temVizinho3(int *tabuleiro,int posicao){
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
	if(tabuleiro[posicao]==tabuleiro[vizinho]){
		return vizinho;
	}
	return SEM_VIZINHO;
}
int formaSequencia1(int *tabuleiro,int posicao,int corJogador){
	int numeroVizinhos=1,vizinho=temVizinho1(tabuleiro,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos++;
		vizinho=temVizinho1(tabuleiro,vizinho);
	}
	if(numeroVizinhos==3){
		if(tabuleiro[posicao]==corJogador){
			return DERROTA;
		}
		return VITORIA;
	}
	if(numeroVizinhos==4){
		if(tabuleiro[posicao]==corJogador){
			return VITORIA;
		}
		return DERROTA;
	}
	return CONTINUA;
}
int formaSequencia2(int *tabuleiro,int posicao,int corJogador){
	int numeroVizinhos=1,vizinho=temVizinho2(tabuleiro,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos++;
		vizinho=temVizinho2(tabuleiro,vizinho);
	}
	if(numeroVizinhos==3){
		if(tabuleiro[posicao]==corJogador){
			return DERROTA;
		}
		return VITORIA;
	}
	if(numeroVizinhos==4){
		if(tabuleiro[posicao]==corJogador){
			return VITORIA;
		}
		return DERROTA;
	}
	return CONTINUA;
}
int formaSequencia3(int *tabuleiro,int posicao,int corJogador){
	int numeroVizinhos=1,vizinho=temVizinho3(tabuleiro,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos++;
		vizinho=temVizinho3(tabuleiro,vizinho);
	}
	if(numeroVizinhos==3){
		if(tabuleiro[posicao]==corJogador){
			return DERROTA;
		}
		return VITORIA;
	}
	if(numeroVizinhos==4){
		if(tabuleiro[posicao]==corJogador){
			return VITORIA;
		}
		return DERROTA;
	}
	return CONTINUA;
}
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas){
	int i,sequencia;
	for(i=26;i<33;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=18;i<24;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=35;i<41;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=11;i<16;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=43;i<48;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=5;i<9;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=50;i<54;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=0;i<3;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=56;i<59;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=56;i<61;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=50;i<56;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=43;i<50;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=35;i<42;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=26;i<33;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=18;i<24;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=11;i<16;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=0;i<25;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=26;i<33;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=35;i<41;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	for(i=43;i<48;i++){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				return sequencia;
			}
		}
	}
	if(jogadasFeitas==61){
		return EMPATE;
	}
	return CONTINUA;
}
int jogadaValida(int *tabuleiro,int jogada){
	if(tabuleiro[jogada]==VAZIO){
		return SIM;
	}
	return NAO;
}
