#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include "constantes.h"
#include "inteligenciaArtificial.h"
int jogadaComputador(int *tabuleiro,int profundidade,int jogadasFeitas,int corComputador){
	clock_t tempoInicio,tempoLimite,ultimoNivel;
	int melhorJogada,proximaJogada,analiseCompleta,profundidadeInicial;
	tempoInicio=clock();
	tempoLimite=tempoInicio+((clock_t)(((float)CLOCKS_PER_SEC)*4.98f));
	analiseCompleta=NAO;
	profundidadeInicial=profundidade;
	profundidade--;
	melhorJogada=primeiroVazio2(tabuleiro);
	ultimoNivel=clock();
	proximaJogada=melhorJogada;
	while((clock()<tempoLimite)&&(analiseCompleta==NAO)){
		proximaJogada=melhorJogada;
		ultimoNivel=clock();
		if(profundidade<61){
			profundidade++;
			melhorJogada=primeiroMax(tempoLimite,profundidade,jogadasFeitas,tabuleiro,corComputador);
		}
		else
			analiseCompleta=SIM;
	}
	if(analiseCompleta==NAO)
		profundidade--;
	if(profundidadeInicial>profundidade)
		profundidade=0;
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(67,7," ");
	gotoxy(41,7);
	printf("%d niveis em %1.3f segundos",profundidade,((float)(ultimoNivel-tempoInicio))/((float)CLOCKS_PER_SEC));
	cputsxy(41,15,"Tempo de raciocinio:");
	gotoxy(41,16);
	printf("%1.3f segundos",((float)(clock()-tempoInicio))/((float)CLOCKS_PER_SEC));
	gotoxy(1,1);
	return proximaJogada;
}
int primeiroMax(clock_t tempoLimite,int profundidade,int jogadasFeitas,int *tabuleiro,int corComputador){
	int i=30,resultado,melhorJogada=30,melhorResultado=ALFA,proximo=0;
	do{
		if(tabuleiro[i]==VAZIO){
			tabuleiro[i]=corComputador;
			resultado=minimax(tempoLimite,tabuleiro,corComputador,jogadasFeitas+1,profundidade-1,melhorResultado,BETA);
			tabuleiro[i]=VAZIO;
			if(resultado>melhorResultado){
				melhorResultado=resultado;
				melhorJogada=i;
			}
		}
		proximo=(proximo<0)?((proximo-1)*(-1)):((proximo+1)*(-1));
		i+=proximo;
	}while(i>=0);
	textbackground(DARKGRAY);
	textcolor(BLACK);
	if(clock()<tempoLimite){
		if(melhorResultado>CONTINUA){
			cputsxy(41,18,"E provavel que voce perca.       ");
			textbackground(LIGHTRED);
			cputsxy(67,18," ");
		}
		else
			if(melhorResultado<EMPATE){
				cputsxy(41,18,"E provavel que voce ganhe.       ");
				textbackground(LIGHTGREEN);
				cputsxy(67,18," ");
			}
			else
				cputsxy(41,18,"Nao ha estimativa de resultado.  ");
	}
	gotoxy(1,1);
	return melhorJogada;
}
int minimax(clock_t tempoLimite,int *tabuleiro,int corComputador,int jogadasFeitas,int profundidade,int alfa,int beta){
	int primeiroResultado;
	primeiroResultado=resultadoJogo(tabuleiro,corComputador,jogadasFeitas);
	if(primeiroResultado==CONTINUA){
		if(profundidade!=0){
			int cor,i=30,resultado,proximo=0;
			cor=(jogadasFeitas%2)?PRETO:BRANCO;
			if(clock()>tempoLimite)
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
					proximo=(proximo<0)?((proximo-1)*(-1)):((proximo+1)*(-1));
					i+=proximo;
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
				proximo=(proximo<0)?((proximo-1)*(-1)):((proximo+1)*(-1));
				i+=proximo;
			}while(i>=0);
			return beta;
		}
		return CONTINUA;
	}
	if(primeiroResultado>=CONTINUA)
		return VITORIA;
	if(primeiroResultado==DERROTA)
		return (DERROTA+jogadasFeitas);
	return CONTINUA;
}
int primeiroVazio(int *tabuleiro){
	int posicao=0;
	while(tabuleiro[posicao]!=VAZIO){
		posicao++;
	}
	return posicao;
}
int primeiroVazio2(int *tabuleiro){
	int posicao=30,proximo=0;
	while(tabuleiro[posicao]!=VAZIO){
		proximo=(proximo<0)?((proximo-1)*(-1)):((proximo+1)*(-1));
		posicao+=proximo;
	}
	return posicao;
}
int temVizinho1(int *tabuleiro,int posicao){
	int vizinho;
	if((posicao==34)||(posicao==25)||(posicao==42)||(posicao==17)||(posicao==49)||(posicao==10)||(posicao==55)||(posicao==4)||(posicao==60))
		return SEM_VIZINHO;
	vizinho=posicao+1;
	if(tabuleiro[posicao]==tabuleiro[vizinho])
		return vizinho;
	return SEM_VIZINHO;
}
int temVizinho2(int *tabuleiro,int posicao){
	int vizinho;
	if((posicao<5)||(posicao==34)||(posicao==25)||(posicao==17)||(posicao==10))
		return SEM_VIZINHO;
	if((posicao>25)&&(posicao<43))
		vizinho=posicao-8;
	else
		if((posicao>17)&&(posicao<50))
			vizinho=posicao-7;
		else
			vizinho=((posicao>10)&&(posicao<56))?(posicao-6):(posicao-5);
	if(tabuleiro[posicao]==tabuleiro[vizinho])
		return vizinho;
	return SEM_VIZINHO;
}
int temVizinho3(int *tabuleiro,int posicao){
	int vizinho;
	if((posicao>54)||(posicao==34)||(posicao==42)||(posicao==49))
		return SEM_VIZINHO;
	if((posicao>17)&&(posicao<35))
		vizinho=posicao+9;
	else
		if((posicao>10)&&(posicao<43))
			vizinho=posicao+8;
		else
			vizinho=((posicao>4)&&(posicao<50))?(posicao+7):(posicao+6);
	if(tabuleiro[posicao]==tabuleiro[vizinho])
		return vizinho;
	return SEM_VIZINHO;
}
int formaSequencia1(int *tabuleiro,int posicao){
	int numeroVizinhos=1,vizinho=temVizinho1(tabuleiro,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos--;
		vizinho=temVizinho1(tabuleiro,vizinho);
	}
	if(numeroVizinhos<0){
		if(numeroVizinhos==(-1))
			return DERROTA+tabuleiro[posicao];
		return VITORIA+tabuleiro[posicao];
	}
	return CONTINUA;
}
int formaSequencia2(int *tabuleiro,int posicao){
	int numeroVizinhos=1,vizinho=temVizinho2(tabuleiro,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos--;
		vizinho=temVizinho2(tabuleiro,vizinho);
	}
	if(numeroVizinhos<0){
		if(numeroVizinhos==(-1))
			return DERROTA+tabuleiro[posicao];
		return VITORIA+tabuleiro[posicao];
	}
	return CONTINUA;
}
int formaSequencia3(int *tabuleiro,int posicao){
	int numeroVizinhos=1,vizinho=temVizinho3(tabuleiro,posicao);
	while(vizinho!=SEM_VIZINHO){
		numeroVizinhos--;
		vizinho=temVizinho3(tabuleiro,vizinho);
	}
	if(numeroVizinhos<0){
		if(numeroVizinhos==(-1))
			return DERROTA+tabuleiro[posicao];
		return VITORIA+tabuleiro[posicao];
	}
	return CONTINUA;
}
int resultadoJogo(int *tabuleiro,int corJogador,int jogadasFeitas){
	int i=26,sequencia,vitoria=NAO,derrota=NAO;
	do{
		if(tabuleiro[i]!=VAZIO){
			sequencia=formaSequencia1(tabuleiro,i);
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
				sequencia=formaSequencia1(tabuleiro,i);
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
					sequencia=formaSequencia1(tabuleiro,i);
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
						sequencia=formaSequencia1(tabuleiro,i);
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
							sequencia=formaSequencia1(tabuleiro,i);
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
								sequencia=formaSequencia1(tabuleiro,i);
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
									sequencia=formaSequencia1(tabuleiro,i);
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
										sequencia=formaSequencia1(tabuleiro,i);
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
											sequencia=formaSequencia1(tabuleiro,i);
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
			sequencia=formaSequencia2(tabuleiro,i);
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
				sequencia=formaSequencia2(tabuleiro,i);
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
					sequencia=formaSequencia2(tabuleiro,i);
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
						sequencia=formaSequencia2(tabuleiro,i);
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
							sequencia=formaSequencia2(tabuleiro,i);
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
			sequencia=formaSequencia3(tabuleiro,i);
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
				sequencia=formaSequencia3(tabuleiro,i);
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
					sequencia=formaSequencia3(tabuleiro,i);
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
						sequencia=formaSequencia3(tabuleiro,i);
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
