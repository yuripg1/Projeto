#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "desenhoTabuleiro.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int corComputador,int profundidadeMinimax,int jogadasFeitas){
	int proximaJogada=(-1),resultado,melhorResultado=ALFA,i,jogadasPossiveis[61],numeroJogadasPossiveis=1;
	clock_t inicioMinimax,fimMinimax;

	// Grava o tempo de início do raciocínio
	inicioMinimax=clock();

	for(i=0;i<61;i++){

		// Verifica se é possível jogar em determinada posição
		if(jogadaValida(tabuleiro,i)==SIM){

			// Efetua sub-jogada
			tabuleiro[i]=corComputador;

			// Aplica o minimax para esta sub-jogada
			resultado=minimax(tabuleiro,profundidadeMinimax-1,corComputador,jogadasFeitas+1,melhorResultado);

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

			// Restaura estado original do tabuleiro
			tabuleiro[i]=VAZIO;

		}

	}

	// Escolhe qual das candidatas será a próxima jogada
	proximaJogada=jogadasPossiveis[rand()%numeroJogadasPossiveis];

	// Grava o tempo de fim do raciocínio
	fimMinimax=clock();

	// Imprime o tempo decorrido no raciocínio
	textbackground(DARKGRAY);
	textcolor(BLACK);
	gotoxy(41,15);
	printf("Tempo de raciocinio: %1.3f segundos",((float)(fimMinimax-inicioMinimax))/((float)CLOCKS_PER_SEC));

	// Retorna qual deverá ser a próxima jogada
	return proximaJogada;
}
int minimax(int *tabuleiro,int profundidade,int corComputador,int jogadasFeitas,int alfaBeta){
	int primeiroResultado;

	// Calcula o resultado do estado atual do tabuleiro
	primeiroResultado=resultadoJogo(tabuleiro,corComputador,jogadasFeitas);

	// verifica se o jogo continua
	if(primeiroResultado==CONTINUA){

		// Verifica se não ultrapassou a profundidade limite
		if(profundidade!=0){

			int i=0,resultado,melhorResultado,cor;

			// Verifica de que cor a jogada será
			if((jogadasFeitas%2)==0){
				cor=BRANCO;
			}
			else{
				cor=PRETO;
			}

			// Bloco onde é calculado o MAX
			if(cor==corComputador){
				melhorResultado=ALFA;
				while(i<61){

					// Verifica se é possível jogar em determinada posição
					if(jogadaValida(tabuleiro,i)!=NAO){

						// Efetua sub-jogada
						tabuleiro[i]=cor;

						// Aplica o minimax para esta sub-jogada
						resultado=minimax(tabuleiro,profundidade-1,corComputador,jogadasFeitas+1,melhorResultado);

						// Restaura estado original do tabuleiro
						tabuleiro[i]=VAZIO;

						// Calcula o MAX
						if(resultado>melhorResultado){
							melhorResultado=resultado;
						}

					}
					i++;
				}

				// Retorna o MAX calculado acima
				return melhorResultado;

			}

			// Bloco onde é calculado o MIN
			melhorResultado=BETA;
			while(i<61){

				// Verifica se é possível jogar em determinada posição
				if(jogadaValida(tabuleiro,i)!=NAO){

					// Efetua sub-jogada
					tabuleiro[i]=cor;

					// Aplica o minimax para esta sub-jogada
					resultado=minimax(tabuleiro,profundidade-1,corComputador,jogadasFeitas+1,melhorResultado);

					// Restaura estado original do tabuleiro
					tabuleiro[i]=VAZIO;

					// Calcula o MIN
					if(resultado<melhorResultado){
						melhorResultado=resultado;
					}

				}
				i++;
			}

			// Retorna o MIN calculado acima
			return melhorResultado;

		}

		return CONTINUA;

	}

	// Dá mais peso para vitórias e derrotas mais próximas (com menos jogadas)
	if(resultadoBom(primeiroResultado)!=NAO){
		primeiroResultado-=jogadasFeitas;
	}
	else{
		primeiroResultado+=jogadasFeitas;
	}

	// Retorna o resultado do estado atual do tabuleiro
	return primeiroResultado;

}
int resultadoBom(int resultado){
	if(resultado>CONTINUA){
		return SIM;
	}
	return NAO;
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
	int numeroVizinhos=1,vizinho;
	vizinho=temVizinho1(tabuleiro,posicao);
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
	int numeroVizinhos=1,vizinho;
	vizinho=temVizinho2(tabuleiro,posicao);
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
	int numeroVizinhos=1,vizinho;
	vizinho=temVizinho3(tabuleiro,posicao);
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
