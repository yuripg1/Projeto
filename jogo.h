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
#define VAZIO 0
#define SIM 1
#define SEM_VIZINHO (-1)
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
void jogadorRodada(int corAtual);
int primeiroVazio(int *tabuleiro);
struct JOGO *finalizaJogo(struct JOGO *jogo);
void processaJogada(struct JOGO *jogo,int jogada);
void desfazJogadas(struct JOGO *jogo);
void desfazUmaJogada(struct JOGO *jogo);
int temVizinho1(int *tabuleiro,int posicao);
int temVizinho2(int *tabuleiro,int posicao);
int temVizinho3(int *tabuleiro,int posicao);
int formaSequencia1(int *tabuleiro,int posicao);
int formaSequencia2(int *tabuleiro,int posicao);
int formaSequencia3(int *tabuleiro,int posicao);
int fimDeJogo(int *tabuleiro,int jogadasFeitas);
int jogadaValida(int *tabuleiro,int jogada);
#endif
