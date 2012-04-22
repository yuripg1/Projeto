#ifndef JOGO_H
#define JOGO_H
#define ENTER 13
#define BACKSPACE 8
#define ESC 27
#define SETA 224
#define SETA_CIMA 72
#define SETA_BAIXO 80
#define SETA_ESQUERDA 75
#define SETA_DIREITA 77
struct JOGO{
	int *tabuleiro;
	int ultimaJogada;
	int penultimaJogada;
	int antepenultimaJogada;
	int corAtual;
	int corJogador;
	int profundidadeMinimax;
	int jogadasFeitas;
	int podeDesfazer;
};
void jogo();
struct JOGO *inicializaJogo();
int escolheCorJogador(struct JOGO *jogo);
int profundidadeMinimax(struct JOGO *jogo);
void escreveComandos();
void jogadorRodada(struct JOGO *jogo);
int primeiroVazio(struct JOGO *jogo);
struct JOGO *finalizaJogo(struct JOGO *jogo);
#endif
