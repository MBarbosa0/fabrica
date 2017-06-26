#ifndef _func_h
#define _func_h

typedef struct peca
{
	char * rolamento;
	int prioridade;
	float chegada;
	int sequencia[5];
	float tempoMaquina[5];

}Peca;

typedef struct fila 
{
	struct peca * peca;
	struct fila * prox;
}Fila;

#endif