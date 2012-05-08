#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "desenhoTabuleiro.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador){
	clock_t tempoInicio,tempoLimite,ultimoNivel;
	int melhorJogada,proximaJogada,analiseCompleta,profundidadeInicial;
	tempoInicio=clock();
	tempoLimite=tempoInicio+((clock_t)(((float)(5*CLOCKS_PER_SEC))*0.995f));
	analiseCompleta=NAO;
	profundidadeInicial=profundidade;
	profundidade--;
	melhorJogada=qualquerVazio(tabuleiro);
	ultimoNivel=clock();
	proximaJogada=melhorJogada;
	textbackground(DARKGRAY);
	textcolor(BLACK);
	while((clock()<tempoLimite)&&(analiseCompleta==NAO)){
		proximaJogada=melhorJogada;
		ultimoNivel=clock();
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
	cputsxy(67,7," ");
	gotoxy(41,7);
	if(profundidadeInicial>profundidade){
		profundidade=0;
	}
	printf("%d niveis em %1.3f segundos",profundidade,((float)(ultimoNivel-tempoInicio))/((float)CLOCKS_PER_SEC));
	cputsxy(41,15,"Tempo de raciocinio:");
	gotoxy(41,16);
	printf("%1.3f segundos",((float)(clock()-tempoInicio))/((float)CLOCKS_PER_SEC));
	return proximaJogada;
}
int primeiroMax(clock_t tempoLimite,int profundidade,int jogadasFeitas,int *tabuleiro,int corComputador){
	int i=0,resultado,jogadasOtimas[61],numeroJogadasOtimas=1,melhorResultado=ALFA;
	profundidade--;
	jogadasFeitas++;
	while(i<61){
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
		i++;
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
			profundidade--;
			if((jogadasFeitas%2)==0){
				cor=BRANCO;
			}
			else{
				cor=PRETO;
			}
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
		return (primeiroResultado-jogadasFeitas);
	}
	return (primeiroResultado+jogadasFeitas);
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
	if((posicao==34)||(posicao==25)||(posicao==42)||(posicao==17)||(posicao==49)||(posicao==10)||(posicao==55)||(posicao==4)||(posicao==60)){
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
	if((posicao==34)||(posicao==25)||(posicao==17)||(posicao==10)||(posicao<4)){
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
	if(numeroVizinhos>2){
		if(numeroVizinhos==3){
			if(tabuleiro[posicao]==corJogador){
				return DERROTA;
			}
			return VITORIA;
		}
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
	if(numeroVizinhos>2){
		if(numeroVizinhos==3){
			if(tabuleiro[posicao]==corJogador){
				return DERROTA;
			}
			return VITORIA;
		}
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
	if(numeroVizinhos>2){
		if(numeroVizinhos==3){
			if(tabuleiro[posicao]==corJogador){
				return DERROTA;
			}
			return VITORIA;
		}
		if(tabuleiro[posicao]==corJogador){
			return VITORIA;
		}
		return DERROTA;
	}
	return CONTINUA;
}
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas){
	int i=26,sequencia,vitoria=NAO,derrota=NAO;

	while(i<33){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=18;
	}
	while(i<24){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=35;
	}
	while(i<41){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=11;
	}
	while(i<16){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=43;
	}
	while(i<48){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=5;
	}
	while(i<9){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=50;
	}
	while(i<54){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=0;
	}
	while(i<3){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=59){
		i=56;
	}
	while(i<59){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=58;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	i=60;
	while(i>42){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=11;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i--;
	}
	if(i!=10){
		i=41;
	}
	while(i>34){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=11;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i--;
	}
	if(i!=10){
		i=32;
	}
	while(i>25){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=11;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i--;
	}
	if(i!=10){
		i=23;
	}
	while(i>17){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=11;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i--;
	}
	if(i!=10){
		i=15;
	}
	while(i>10){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia2(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=11;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i--;
	}
	i=0;
	while(i<25){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=47;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=48){
		i=26;
	}
	while(i<33){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=47;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=48){
		i=35;
	}
	while(i<41){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=47;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(i!=48){
		i=43;
	}
	while(i<48){
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia3(tabuleiro,i,corJogador);
			if(sequencia!=CONTINUA){
				i=47;
				if(sequencia==VITORIA){
					vitoria=SIM;
				}
				else{
					derrota=SIM;
				}
			}
		}
		i++;
	}
	if(vitoria!=NAO){
		if(derrota!=NAO){
			return EMPATE;
		}
		return VITORIA;
	}
	if(derrota!=NAO){
		return DERROTA;
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
