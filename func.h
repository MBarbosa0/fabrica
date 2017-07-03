#ifndef _func_h
#define _func_h

/*Constantes*/
#define TORNO 1
#define FRESA 2
#define MANDRIL 3
#define NONE 0

typedef struct peca
{
	char * rolamento;
	int prioridade;
	float chegada;
	int sequencia[5];
	float tempoRolamento[5];
	int maquinaAtual;
	float tempoTotal;

}Peca;

typedef struct fila 
{
	struct peca * peca;
	struct fila * prox;
	
}Fila;

void imprimeFila(Fila * l);

Peca * criaCilindrio();

Peca * criaConico();

Peca * criaEsfericoAco();

Peca * criaEsfericoTitan();

Fila * criaFila();

void insereFila(Fila ** l, Peca * p);

void criaFilasMaquinas(Fila * filasMaquinas[4]);
#endif
