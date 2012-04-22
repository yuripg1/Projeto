#include <conio2.h>
#include <stdio.h>
#include <stdlib.h>
#include "desenhoTabuleiro.h"
#include "inteligenciaArtificial.h"
#include "processamentoJogadas.h"
#include "jogo.h"
void jogo(){
	int acabou=NAO,tecla,estadoJogo,posicao,novaPosicao,escolhaFeita,teclaValida;
	struct JOGO *jogo;
	jogo=inicializaJogo();
	jogo->corJogador=escolheCorJogador(jogo);
	jogo->profundidadeMinimax=profundidadeMinimax(jogo);
	escreveComandos();
	while(acabou==NAO){
		estadoJogo=fimDeJogo(jogo);
		while(estadoJogo==NAO){
			jogadorRodada(jogo);
			if(jogo->corJogador==jogo->corAtual){
				posicao=primeiroVazio(jogo);
				escolhaFeita=NAO;
				while(escolhaFeita==NAO){
					poeFoco(posicao);
					tecla=getch();
					if(((tecla=='d')||(tecla=='D'))&&(jogo->podeDesfazer==SIM)){
						tiraFoco(posicao);
						desfazJogadas(jogo);
						escolhaFeita=SIM;
					}
					if(tecla==ENTER){
						tiraFoco(posicao);
						processaJogada(jogo,posicao);
						escolhaFeita=SIM;
					}
					if(tecla==SETA){
						tecla=getch();
						if(tecla==SETA_ESQUERDA){
							novaPosicao=posicao-1;
							while((jogadaValida(jogo,novaPosicao)==NAO)&&(novaPosicao>(-1))){
								novaPosicao--;
							}
							if(novaPosicao!=(-1)){
								tiraFoco(posicao);
								poeFoco(novaPosicao);
								posicao=novaPosicao;
							}
						}
						if(tecla==SETA_DIREITA){
							novaPosicao=posicao+1;
							while((jogadaValida(jogo,novaPosicao)==NAO)&&(novaPosicao<61)){
								novaPosicao++;
							}
							if(novaPosicao!=61){
								tiraFoco(posicao);
								poeFoco(novaPosicao);
								posicao=novaPosicao;
							}
						}
					}
				}
			}
			else{
				processaJogada(jogo,jogadaComputador(jogo));
			}
			estadoJogo=fimDeJogo(jogo);
		}
		jogadorRodada(jogo);
		textbackground(DARKGRAY);
		textcolor(BLACK);
		if(estadoJogo==EMPATE){
			cputsxy(41,15,"O jogo acabou em empate!");
		}
		if(((estadoJogo==VITORIA_PRETO)&&(jogo->corJogador==PRETO))||((estadoJogo==VITORIA_BRANCO)&&(jogo->corJogador==BRANCO))){
			cputsxy(41,15,"Voce ganhou! O computador perdeu!");
		}
		if(((estadoJogo==VITORIA_PRETO)&&(jogo->corJogador==BRANCO))||((estadoJogo==VITORIA_BRANCO)&&(jogo->corJogador==PRETO))){
			cputsxy(41,15,"Voce perdeu! O computador ganhou!");
		}
		cputsxy(41,16,"Pressione ESC para sair.");
		gotoxy(1,1);
		teclaValida=NAO;
		while(teclaValida==NAO){
			tecla=getch();
			if(((tecla=='d')||(tecla=='D'))){
				if(jogo->jogadasFeitas==61){
					if(jogo->corJogador==PRETO){
						cputsxy(41,15,"                                 ");
						cputsxy(41,16,"                        ");
						desfazJogadas(jogo);
						teclaValida=SIM;
					}
				}
				else{
					cputsxy(41,15,"                                 ");
					cputsxy(41,16,"                        ");
					if(jogo->corAtual!=jogo->corJogador){
						desfazUmaJogada(jogo);
					}
					else{
						desfazJogadas(jogo);
					}
					teclaValida=SIM;
				}
			}
			if(tecla==ESC){
				acabou=SIM;
				teclaValida=SIM;
			}
		}
	}
	jogo=finalizaJogo(jogo);
}
struct JOGO *inicializaJogo(){
	struct JOGO *jogo;
	jogo=(struct JOGO*)malloc(sizeof(struct JOGO));
	jogo->tabuleiro=(int*)calloc(61,sizeof(int));
	jogo->ultimaJogada=SEM_JOGADA;
	jogo->penultimaJogada=SEM_JOGADA;
	jogo->antepenultimaJogada=SEM_JOGADA;
	jogo->corAtual=BRANCO;
	jogo->corJogador=BRANCO;
	jogo->profundidadeMinimax=0;
	jogo->jogadasFeitas=0;
	jogo->podeDesfazer=NAO;
	limpaTela();
	desenhaTabuleiro();
	return jogo;
}
int escolheCorJogador(struct JOGO *jogo){
	int corSelecionada=BRANCO;
	int tecla;
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(41,2,"Escolha a cor com que deseja jogar:");
	do{
		if(corSelecionada==BRANCO){
			textbackground(LIGHTRED);
		}
		if(corSelecionada==PRETO){
			textbackground(DARKGRAY);
		}
		cputsxy(41,3,"- Branco (comeca o jogo)");
		if(corSelecionada==BRANCO){
			textbackground(DARKGRAY);
		}
		if(corSelecionada==PRETO){
			textbackground(LIGHTRED);
		}
		cputsxy(41,4,"- Preto");
		gotoxy(1,1);
		tecla=getch();
		while((tecla!=ENTER)&&(tecla!=SETA)){
			tecla=getch();
		}
		if(tecla==SETA){
			tecla=getch();
			switch(tecla){
				case SETA_CIMA:		if(corSelecionada==PRETO){
										corSelecionada=BRANCO;
									}
									break;
				case SETA_BAIXO:	if(corSelecionada==BRANCO){
										corSelecionada=PRETO;
									}
									break;
			}
		}
	}
	while(tecla!=ENTER);
	return corSelecionada;
}
int profundidadeMinimax(struct JOGO *jogo){
	char profundidadeMinimax[3]="";
	int i=0,resposta,posicaoXAnterior=40;
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(41,6,"Defina a profundidade do minimax: (3-62)");
	gotoxy(41,7);
	while(i<3){
		profundidadeMinimax[i]=getch();
		if((profundidadeMinimax[i]==BACKSPACE)&&(i>0)){
			cputsxy(posicaoXAnterior,7," ");
			gotoxy(posicaoXAnterior,7);
			i--;
			posicaoXAnterior--;
			profundidadeMinimax[i]=' ';
		}
		if(i<2){
			if((profundidadeMinimax[i]>47)&&(profundidadeMinimax[i]<58)){
				putchar(profundidadeMinimax[i]);
				i++;
				posicaoXAnterior++;
			}
		}
		if(profundidadeMinimax[i]==ENTER){
			profundidadeMinimax[i]='\0';
			resposta=atoi(profundidadeMinimax);
			if((resposta>2)&&(resposta<63)){
				cputsxy(41,8,"                                ");
				gotoxy(1,1);
				return resposta;
			}
			else{
				cputsxy(41,8,"Valor invalido! Tente novamente.");
				cputsxy(41,7,"  ");
				gotoxy(41,7);
				i=0;
				posicaoXAnterior=40;
			}
		}
	}
	return 0;
}
void escreveComandos(){
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(41,9,"Comandos:");
	cputsxy(41,10,"[D] - Desfazer jogada");
	gotoxy(1,1);
}
void jogadorRodada(struct JOGO *jogo){
	textbackground(DARKGRAY);
	textcolor(BLACK);
	cputsxy(41,12,"Jogador da rodada:");
	if(jogo->corAtual==BRANCO){
		cputsxy(41,13,"Branco ");
		textbackground(WHITE);
		cputsxy(48,13,"   ");
	}
	if(jogo->corAtual==PRETO){
		cputsxy(41,13,"Preto ");
		textbackground(BLACK);
		cputsxy(47,13,"   ");
		textbackground(DARKGRAY);
		cputsxy(50,13," ");
	}
	gotoxy(1,1);
}
int primeiroVazio(struct JOGO *jogo){
	int posicao=0;
	while(jogadaValida(jogo,posicao)==NAO){
		posicao++;
	}
	return posicao;
}
struct JOGO *finalizaJogo(struct JOGO *jogo){
	free(jogo->tabuleiro);
	free(jogo);
	return NULL;
}
