#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "desenhoTabuleiro.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador){
	clock_t tempoInicio,tempoLimite;
	int melhorJogada,proximaJogada,analiseCompleta;
	tempoInicio=clock();
	tempoLimite=tempoInicio+((clock_t)(((float)(5*CLOCKS_PER_SEC))*0.995f));
	analiseCompleta=NAO;
	profundidade--;
	melhorJogada=qualquerVazio(tabuleiro);
	proximaJogada=melhorJogada;
	while((clock()<tempoLimite)&&(analiseCompleta==NAO)){
		proximaJogada=melhorJogada;
		if(profundidade<61){
			profundidade++;
			melhorJogada=primeiroMax(tempoLimite,profundidade,jogadasFeitas,tabuleiro,corComputador);
		}
		else{
			analiseCompleta=SIM;
		}
	}
	if(analiseCompleta==NAO){
		profundidade--;
	}
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(41,7,"  ");
	gotoxy(41,7);
	printf("%d",profundidade);
	gotoxy(41,15);
	printf("Tempo de raciocinio: %1.3f segundos",((float)(clock()-tempoInicio))/((float)CLOCKS_PER_SEC));
	return proximaJogada;
}
int primeiroMax(clock_t tempoLimite,int profundidade,int jogadasFeitas,int *tabuleiro,int corComputador){
	int i=30,resultado,jogadasOtimas[61],numeroJogadasOtimas=1,melhorResultado,proximo=0;
	if(clock()>tempoLimite){
		return 0;
	}
	profundidade--;
	jogadasFeitas++;
	melhorResultado=ALFA;
	while(i>(-1)){
		if(tabuleiro[i]==VAZIO){
			tabuleiro[i]=corComputador;
			resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas,profundidade,ALFA,BETA);
			tabuleiro[i]=VAZIO;
			if(resultado==melhorResultado){
				jogadasOtimas[numeroJogadasOtimas]=i;
				numeroJogadasOtimas++;
			}
			else{
				if(resultado>melhorResultado){
					melhorResultado=resultado;
					jogadasOtimas[0]=i;
					numeroJogadasOtimas=1;
				}
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
	return jogadasOtimas[rand()%numeroJogadasOtimas];
}
int minimax(clock_t tempoLimite,int *tabuleiro,int corComputador,int jogadasFeitas,int profundidade,int alfa,int beta){
	int primeiroResultado;
	if(clock()>tempoLimite){
		return CONTINUA;
	}
	primeiroResultado=resultadoJogo(tabuleiro,corComputador,jogadasFeitas);
	if(primeiroResultado==CONTINUA){
		if(profundidade!=0){
			int cor,i=30,resultado,proximo=0;
			if((jogadasFeitas%2)==0){
				cor=BRANCO;
			}
			else{
				cor=PRETO;
			}
			profundidade--;
			jogadasFeitas++;
			if(cor==corComputador){
				while(i>(-1)){
					if(tabuleiro[i]==VAZIO){
						tabuleiro[i]=cor;
						resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas,profundidade,alfa,beta);
						tabuleiro[i]=VAZIO;
						if(resultado>alfa){
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
				return alfa;
			}
			while(i>(-1)){
			if(tabuleiro[i]==VAZIO){
					tabuleiro[i]=cor;
					resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas,profundidade,alfa,beta);
					tabuleiro[i]=VAZIO;
					if(resultado<beta){
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
			return beta;
		}
		return CONTINUA;
	}
	if(primeiroResultado>CONTINUA){
		primeiroResultado-=jogadasFeitas;
	}
	else{
		primeiroResultado+=jogadasFeitas;
	}
	return primeiroResultado;
}
int qualquerVazio(int *tabuleiro){
	int posicao;
	posicao=(rand()%61);
	while(tabuleiro[posicao]!=VAZIO){
		posicao=(rand()%61);
	}
	return posicao;
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
