#include <conio2.h>
#include <stdio.h>
#include <time.h>
#include "desenhoTabuleiro.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int corComputador,int profundidadeMinimax,int jogadasFeitas){
	int proximaJogada=(-1),resultado,melhorResultado=(-1),i;
	clock_t inicioMinimax,fimMinimax;
	inicioMinimax=clock();
	for(i=0;i<61;i++){
		if(jogadaValida(tabuleiro,i)==SIM){
			tabuleiro[i]=corComputador;
			resultado=(int)(minimax(tabuleiro,(char)(profundidadeMinimax-1),(char)(corComputador),(char)(jogadasFeitas+1)));
			if(resultado>melhorResultado){
				melhorResultado=resultado;
				proximaJogada=i;
			}
			tabuleiro[i]=VAZIO;
		}
	}
	fimMinimax=clock();
	textbackground(DARKGRAY);
	textcolor(BLACK);
	gotoxy(41,15);
	printf("Tempo de raciocinio: %1.3f",((float)(fimMinimax-inicioMinimax))/((float)CLOCKS_PER_SEC));
	return proximaJogada;
}
char minimax(int *tabuleiro,char profundidade,char corComputador,char jogadasFeitas){
	char i,resultado,melhorResultado,cor,max,primeiroResultado;

	// Verifica se o jogo acaba com algum resultado ou se continua
	primeiroResultado=(char)(resultadoJogo(tabuleiro,(int)(corComputador),(int)(jogadasFeitas)));

	// verifica se o jogo continua
	if(primeiroResultado==CONTINUA){

		// Verifica se não ultrapassou a profundidade limite
		if(profundidade>1){

			// Verifica de que cor a jogada será
			if((jogadasFeitas%2)==0){
				cor=BRANCO;
			}
			else{
				cor=PRETO;
			}

			// Verifica se este nível fará MIN ou MAX
			if(cor==corComputador){
				melhorResultado=(-1);
				max=SIM;
			}
			else{
				melhorResultado=4;
				max=NAO;
			}

			for(i=0;i<61;i++){

				// Verifica se é possível jogar em determinada posição
				if(jogadaValida(tabuleiro,i)==SIM){

					// Efetua sub-jogada
					tabuleiro[(int)(i)]=cor;

					// Aplica o minimax para esta sub-jogada
					resultado=minimax(tabuleiro,profundidade-1,corComputador,jogadasFeitas+1);

					// Calcula o MIN ou o MAX (dependendo do nível)
					if(max==NAO){
						if(resultado<melhorResultado){
							melhorResultado=resultado;
						}
					}
					else{
						if(resultado>melhorResultado){
							melhorResultado=resultado;
						}
					}

					// Restaura estado original do tabuleiro
					tabuleiro[(int)(i)]=VAZIO;

				}
			}

			// Retorna o MIN ou o MAX calculado acima
			return melhorResultado;

		}

	}

	// Retorna o resultado do tabuleiro
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
	for(i=0;i<3;i++){
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
	for(i=11;i<16;i++){
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
	for(i=26;i<33;i++){
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
	for(i=43;i<48;i++){
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
