#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "inteligenciaArtificial.h"
CRITICAL_SECTION gravacaoResultado;
int proximo[61]={	1,(-1),3,4,10,
					0,7,2,9,16,17,
					5,6,8,15,23,24,25,
					11,12,13,14,31,32,33,34,
					18,19,20,21,22,39,40,41,42,
					26,27,28,29,38,47,48,49,
					35,36,37,45,46,54,55,
					43,44,51,52,53,60,
					50,56,57,58,59};
int vizinhanca[183]={	1,2,3,4,SEM_VIZINHO,
						6,7,8,9,10,SEM_VIZINHO,
						12,13,14,15,16,17,SEM_VIZINHO,
						19,20,21,22,23,24,25,SEM_VIZINHO,
						27,28,29,30,31,32,33,34,SEM_VIZINHO,
						36,37,38,39,40,41,42,SEM_VIZINHO,
						44,45,46,47,48,49,SEM_VIZINHO,
						51,52,53,54,55,SEM_VIZINHO,
						57,58,59,60,SEM_VIZINHO,
						SEM_VIZINHO,SEM_VIZINHO,SEM_VIZINHO,SEM_VIZINHO,SEM_VIZINHO,
						0,1,2,3,4,SEM_VIZINHO,
						5,6,7,8,9,10,SEM_VIZINHO,
						11,12,13,14,15,16,17,SEM_VIZINHO,
						18,19,20,21,22,23,24,25,SEM_VIZINHO,
						27,28,29,30,31,32,33,34,
						36,37,38,39,40,41,42,
						44,45,46,47,48,49,
						51,52,53,54,55,
						6,7,8,9,10,
						12,13,14,15,16,17,
						19,20,21,22,23,24,25,
						27,28,29,30,31,32,33,34,
						35,36,37,38,39,40,41,42,SEM_VIZINHO,
						43,44,45,46,47,48,49,SEM_VIZINHO,
						50,51,52,53,54,55,SEM_VIZINHO,
						56,57,58,59,60,SEM_VIZINHO,
						SEM_VIZINHO,SEM_VIZINHO,SEM_VIZINHO,SEM_VIZINHO,SEM_VIZINHO};
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador){
	clock_t tempoInicio,tempoLimite;
	HANDLE thread[2]={0,0};
	struct MINIMAX dados[2];
	struct RESULTADO resultado;
	tempoInicio=clock();
	tempoLimite=tempoInicio+((clock_t)(CLOCKS_PER_SEC*5));
	resultado.numeroNiveis=0;
	resultado.tempo=tempoInicio;
	resultado.melhorJogada=primeiroVazio2(tabuleiro);
	InitializeCriticalSection(&gravacaoResultado);
	dados[0].tempoLimite=tempoLimite;
	dados[0].jogadasFeitas=jogadasFeitas;
	dados[0].profundidade=profundidade;
	dados[0].tabuleiro=(int*)calloc(61,sizeof(int));
	memcpy(dados[0].tabuleiro,tabuleiro,61*sizeof(int));
	dados[0].corComputador=corComputador;
	dados[0].resultado=(&(resultado));
	thread[0]=CreateThread(NULL,0,thread1,&(dados[0]),0,NULL);
	dados[1].tempoLimite=tempoLimite;
	dados[1].jogadasFeitas=jogadasFeitas;
	dados[1].profundidade=profundidade+1;
	dados[1].tabuleiro=(int*)calloc(61,sizeof(int));
	memcpy(dados[1].tabuleiro,tabuleiro,61*sizeof(int));
	dados[1].corComputador=corComputador;
	dados[1].resultado=(&(resultado));
	thread[1]=CreateThread(NULL,0,thread2,&(dados[1]),0,NULL);
	WaitForMultipleObjects(2,thread,TRUE,INFINITE);
	CloseHandle(thread[0]);
	CloseHandle(thread[1]);
	DeleteCriticalSection(&gravacaoResultado);
	free(dados[0].tabuleiro);
	free(dados[1].tabuleiro);
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(41,15,"Tempo de raciocinio:");
	gotoxy(41,16);
	printf("%2d niveis em %1.3f segundos",resultado.numeroNiveis,((float)(resultado.tempo-tempoInicio))/((float)CLOCKS_PER_SEC));
	gotoxy(1,1);
	return resultado.melhorJogada;
}
DWORD WINAPI thread1(LPVOID lpParam){
	clock_t tempoAtual;
	int melhorJogada,analiseFeita=NAO;
	struct MINIMAX dados;
	dados=(*((struct MINIMAX*)lpParam));
	do{
		melhorJogada=primeiroMax(dados.tempoLimite,dados.profundidade,dados.jogadasFeitas,dados.tabuleiro,dados.corComputador);
		tempoAtual=clock();
		if(tempoAtual<=dados.tempoLimite){
			EnterCriticalSection(&gravacaoResultado);
			if(dados.resultado->numeroNiveis<dados.profundidade){
				dados.resultado->numeroNiveis=dados.profundidade;
				dados.resultado->tempo=tempoAtual;
				dados.resultado->melhorJogada=melhorJogada;
			}
			LeaveCriticalSection(&gravacaoResultado);
			dados.profundidade+=2;
			if(dados.profundidade>61)
				analiseFeita=SIM;
		}
		else
			analiseFeita=SIM;
	}while(analiseFeita==NAO);
	return 0;
}
DWORD WINAPI thread2(LPVOID lpParam){
	clock_t tempoAtual;
	int melhorJogada,analiseFeita=NAO;
	struct MINIMAX dados;
	dados=(*((struct MINIMAX*)lpParam));
	do{
		melhorJogada=primeiroMax(dados.tempoLimite,dados.profundidade,dados.jogadasFeitas,dados.tabuleiro,dados.corComputador);
		tempoAtual=clock();
		if(tempoAtual<=dados.tempoLimite){
			EnterCriticalSection(&gravacaoResultado);
			if(dados.resultado->numeroNiveis<dados.profundidade){
				dados.resultado->numeroNiveis=dados.profundidade;
				dados.resultado->tempo=tempoAtual;
				dados.resultado->melhorJogada=melhorJogada;
			}
			LeaveCriticalSection(&gravacaoResultado);
			dados.profundidade+=2;
			if(dados.profundidade>61)
				analiseFeita=SIM;
		}
		else
			analiseFeita=SIM;
	}while(analiseFeita==NAO);
	return 0;
}
int primeiroMax(clock_t tempoLimite,int profundidade,int jogadasFeitas,int *tabuleiro,int corComputador){
	int i=30,resultado,melhorJogada=30,melhorResultado=ALFA;
	do{
		if(tabuleiro[i]==VAZIO){
			tabuleiro[i]=corComputador;
			resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas+1,profundidade-1,melhorResultado,BETA);
			tabuleiro[i]=VAZIO;
			if(resultado>melhorResultado){
				melhorJogada=i;
				melhorResultado=resultado;
			}
		}
		i=proximo[i];
	}while(i>=0);
	return melhorJogada;
}
int minimax(clock_t tempoLimite,int *tabuleiro,int corComputador,int jogadasFeitas,int profundidade,int alfa,int beta){
	int primeiroResultado=resultadoJogo(tabuleiro,corComputador,jogadasFeitas),cor=(jogadasFeitas%2)?PRETO:BRANCO,i=30,resultado;
	if(primeiroResultado!=CONTINUA){
		if(primeiroResultado>=CONTINUA)
			return VITORIA;
		if(primeiroResultado==DERROTA)
			return (DERROTA+jogadasFeitas);
		return CONTINUA;
	}
	if((profundidade==0)||(clock()>tempoLimite))
		return CONTINUA;
	if(cor==corComputador){
		do{
			if(tabuleiro[i]==VAZIO){
				tabuleiro[i]=cor;
				resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas+1,profundidade-1,alfa,beta);
				tabuleiro[i]=VAZIO;
				if(resultado>alfa){
					if(beta<=resultado)
						return resultado;
					alfa=resultado;
				}
			}
			i=proximo[i];
		}while(i>=0);
		return alfa;
	}
	do{
		if(tabuleiro[i]==VAZIO){
			tabuleiro[i]=cor;
			resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas+1,profundidade-1,alfa,beta);
			tabuleiro[i]=VAZIO;
			if(resultado<beta){
				if(resultado<=alfa)
					return resultado;
				beta=resultado;
			}
		}
		i=proximo[i];
	}while(i>=0);
	return beta;
}
int primeiroVazio(int *tabuleiro){
	int posicao=0;
	while(tabuleiro[posicao]!=VAZIO)
		posicao++;
	return posicao;
}
int primeiroVazio2(int *tabuleiro){
	int posicao=30;
	while(tabuleiro[posicao]!=VAZIO)
		posicao=proximo[posicao];
	return posicao;
}
int formaSequencia(int *tabuleiro,int posicao,int sentidoVizinho){
	int vizinho=vizinhanca[(61*sentidoVizinho)+posicao],corPosicao=tabuleiro[posicao],numeroVizinhos=1,sair=NAO;
	do{
		if((vizinho!=SEM_VIZINHO)&&(corPosicao==tabuleiro[vizinho])){
			vizinho=vizinhanca[(61*sentidoVizinho)+vizinho];
			numeroVizinhos--;
		}
		else
			sair=SIM;
	}while(sair==NAO);
	if(numeroVizinhos<0){
		if(numeroVizinhos==(-1))
			return DERROTA+corPosicao;
		return VITORIA+corPosicao;
	}
	return CONTINUA;
}
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas){
	int i=26,sequencia,vitoria=NAO,derrota=NAO;
	do{
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia(tabuleiro,i,0);
			if(sequencia!=CONTINUA){
				if(sequencia>VITORIA){
					if((sequencia-VITORIA)==corJogador)
						return VITORIA;
					return DERROTA;
				}
				i=58;
				if((sequencia-DERROTA)==corJogador)
					derrota=SIM;
				else
					vitoria=SIM;
			}
		}
		i++;
	}while(i<33);
	if(i!=59){
		i=18;
		do{
			if(tabuleiro[i]!=VAZIO){
				sequencia=formaSequencia(tabuleiro,i,0);
				if(sequencia!=CONTINUA){
					if(sequencia>VITORIA){
						if((sequencia-VITORIA)==corJogador)
							return VITORIA;
						return DERROTA;
					}
					i=58;
					if((sequencia-DERROTA)==corJogador)
						derrota=SIM;
					else
						vitoria=SIM;
				}
			}
			i++;
		}while(i<24);
		if(i!=59){
			i=35;
			do{
				if(tabuleiro[i]!=VAZIO){
					sequencia=formaSequencia(tabuleiro,i,0);
					if(sequencia!=CONTINUA){
						if(sequencia>VITORIA){
							if((sequencia-VITORIA)==corJogador)
								return VITORIA;
							return DERROTA;
						}
						i=58;
						if((sequencia-DERROTA)==corJogador)
							derrota=SIM;
						else
							vitoria=SIM;
					}
				}
				i++;
			}while(i<41);
			if(i!=59){
				i=11;
				do{
					if(tabuleiro[i]!=VAZIO){
						sequencia=formaSequencia(tabuleiro,i,0);
						if(sequencia!=CONTINUA){
							if(sequencia>VITORIA){
								if((sequencia-VITORIA)==corJogador)
									return VITORIA;
								return DERROTA;
							}
							i=58;
							if((sequencia-DERROTA)==corJogador)
								derrota=SIM;
							else
								vitoria=SIM;
						}
					}
					i++;
				}while(i<16);
				if(i!=59){
					i=43;
					do{
						if(tabuleiro[i]!=VAZIO){
							sequencia=formaSequencia(tabuleiro,i,0);
							if(sequencia!=CONTINUA){
								if(sequencia>VITORIA){
									if((sequencia-VITORIA)==corJogador)
										return VITORIA;
									return DERROTA;
								}
								i=58;
								if((sequencia-DERROTA)==corJogador)
									derrota=SIM;
								else
									vitoria=SIM;
							}
						}
						i++;
					}while(i<48);
					if(i!=59){
						i=5;
						do{
							if(tabuleiro[i]!=VAZIO){
								sequencia=formaSequencia(tabuleiro,i,0);
								if(sequencia!=CONTINUA){
									if(sequencia>VITORIA){
										if((sequencia-VITORIA)==corJogador)
											return VITORIA;
										return DERROTA;
									}
									i=58;
									if((sequencia-DERROTA)==corJogador)
										derrota=SIM;
									else
										vitoria=SIM;
								}
							}
							i++;
						}while(i<9);
						if(i!=59){
							i=50;
							do{
								if(tabuleiro[i]!=VAZIO){
									sequencia=formaSequencia(tabuleiro,i,0);
									if(sequencia!=CONTINUA){
										if(sequencia>VITORIA){
											if((sequencia-VITORIA)==corJogador)
												return VITORIA;
											return DERROTA;
										}
										i=58;
										if((sequencia-DERROTA)==corJogador)
											derrota=SIM;
										else
											vitoria=SIM;
									}
								}
								i++;
							}while(i<54);
							if(i!=59){
								i=0;
								do{
									if(tabuleiro[i]!=VAZIO){
										sequencia=formaSequencia(tabuleiro,i,0);
										if(sequencia!=CONTINUA){
											if(sequencia>VITORIA){
												if((sequencia-VITORIA)==corJogador)
													return VITORIA;
												return DERROTA;
											}
											i=58;
											if((sequencia-DERROTA)==corJogador)
												derrota=SIM;
											else
												vitoria=SIM;
										}
									}
									i++;
								}while(i<3);
								if(i!=59){
									i=56;
									do{
										if(tabuleiro[i]!=VAZIO){
											sequencia=formaSequencia(tabuleiro,i,0);
											if(sequencia!=CONTINUA){
												if(sequencia>VITORIA){
													if((sequencia-VITORIA)==corJogador)
														return VITORIA;
													return DERROTA;
												}
												i=58;
												if((sequencia-DERROTA)==corJogador)
													derrota=SIM;
												else
													vitoria=SIM;
											}
										}
										i++;
									}while(i<59);
								}
							}
						}
					}
				}
			}
		}
	}
	i=60;
	do{
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia(tabuleiro,i,1);
			if(sequencia!=CONTINUA){
				if(sequencia>VITORIA){
					if((sequencia-VITORIA)==corJogador)
						return VITORIA;
					return DERROTA;
				}
				i=11;
				if((sequencia-DERROTA)==corJogador)
					derrota=SIM;
				else
					vitoria=SIM;
			}
		}
		i--;
	}while(i>42);
	if(i!=10){
		i=41;
		do{
			if(tabuleiro[i]!=VAZIO){
				sequencia=formaSequencia(tabuleiro,i,1);
				if(sequencia!=CONTINUA){
					if(sequencia>VITORIA){
						if((sequencia-VITORIA)==corJogador)
							return VITORIA;
						return DERROTA;
					}
					i=11;
					if((sequencia-DERROTA)==corJogador)
						derrota=SIM;
					else
						vitoria=SIM;
				}
			}
			i--;
		}while(i>34);
		if(i!=10){
			i=32;
			do{
				if(tabuleiro[i]!=VAZIO){
					sequencia=formaSequencia(tabuleiro,i,1);
					if(sequencia!=CONTINUA){
						if(sequencia>VITORIA){
							if((sequencia-VITORIA)==corJogador)
								return VITORIA;
							return DERROTA;
						}
						i=11;
						if((sequencia-DERROTA)==corJogador)
							derrota=SIM;
						else
							vitoria=SIM;
					}
				}
				i--;
			}while(i>25);
			if(i!=10){
				i=23;
				do{
					if(tabuleiro[i]!=VAZIO){
						sequencia=formaSequencia(tabuleiro,i,1);
						if(sequencia!=CONTINUA){
							if(sequencia>VITORIA){
								if((sequencia-VITORIA)==corJogador)
									return VITORIA;
								return DERROTA;
							}
							i=11;
							if((sequencia-DERROTA)==corJogador)
								derrota=SIM;
							else
								vitoria=SIM;
						}
					}
					i--;
				}while(i>17);
				if(i!=10){
					i=15;
					do{
						if(tabuleiro[i]!=VAZIO){
							sequencia=formaSequencia(tabuleiro,i,1);
							if(sequencia!=CONTINUA){
								if(sequencia>VITORIA){
									if((sequencia-VITORIA)==corJogador)
										return VITORIA;
									return DERROTA;
								}
								i=11;
								if((sequencia-DERROTA)==corJogador)
									derrota=SIM;
								else
									vitoria=SIM;
							}
						}
						i--;
					}while(i>10);
				}
			}
		}
	}
	i=0;
	do{
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia(tabuleiro,i,2);
			if(sequencia!=CONTINUA){
				if(sequencia>VITORIA){
					if((sequencia-VITORIA)==corJogador)
						return VITORIA;
					return DERROTA;
				}
				i=47;
				if((sequencia-DERROTA)==corJogador)
					derrota=SIM;
				else
					vitoria=SIM;
			}
		}
		i++;
	}while(i<25);
	if(i!=48){
		i=26;
		do{
			if(tabuleiro[i]!=VAZIO){
				sequencia=formaSequencia(tabuleiro,i,2);
				if(sequencia!=CONTINUA){
					if(sequencia>VITORIA){
						if((sequencia-VITORIA)==corJogador)
							return VITORIA;
						return DERROTA;
					}
					i=47;
					if((sequencia-DERROTA)==corJogador)
						derrota=SIM;
					else
						vitoria=SIM;
				}
			}
			i++;
		}while(i<33);
		if(i!=48){
			i=35;
			do{
				if(tabuleiro[i]!=VAZIO){
					sequencia=formaSequencia(tabuleiro,i,2);
					if(sequencia!=CONTINUA){
						if(sequencia>VITORIA){
							if((sequencia-VITORIA)==corJogador)
								return VITORIA;
							return DERROTA;
						}
						i=47;
						if((sequencia-DERROTA)==corJogador)
							derrota=SIM;
						else
							vitoria=SIM;
					}
				}
				i++;
			}while(i<41);
			if(i!=48){
				i=43;
				do{
					if(tabuleiro[i]!=VAZIO){
						sequencia=formaSequencia(tabuleiro,i,2);
						if(sequencia!=CONTINUA){
							if(sequencia>VITORIA){
								if((sequencia-VITORIA)==corJogador)
									return VITORIA;
								return DERROTA;
							}
							i=47;
							if((sequencia-DERROTA)==corJogador)
								derrota=SIM;
							else
								vitoria=SIM;
						}
					}
					i++;
				}while(i<48);
			}
		}
	}
	if(vitoria!=NAO)
		return VITORIA;
	if(derrota!=NAO)
		return DERROTA;
	if(jogadasFeitas==61)
		return EMPATE;
	return CONTINUA;
}
int jogadaValida(int *tabuleiro,int jogada){
	if(tabuleiro[jogada]==VAZIO)
		return SIM;
	return NAO;
}
