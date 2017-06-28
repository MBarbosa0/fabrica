#include <stdio.h>
#include <stdlib.h>
#include "func.h"

				/* Sequencia das maquinas */
int s_cilindrico[5] = {TORNO, FRESA, TORNO, MANDRIL, NONE};
int s_conico[5] = {TORNO, MANDRIL, TORNO, NONE, NONE};
int s_esfericoAco[5] = {FRESA, MANDRIL, TORNO, NONE, NONE};
int s_esfericoTitan[5] = {FRESA, MANDRIL, TORNO, FRESA, TORNO};
				/* Tempo nas maquinas */
float ts_cilindrico[5] = {0.8, 0.5, 0.8, 1.2, 0};
float ts_conico[5] = {1.8, 2.1, 1.8, 0, 0};
float ts_esfeticoAco[5] = {0.5, 1.4, 1.0, 0, 0};
float ts_esfericoTitan[5] = {0.6, 1.5, 1.6, 0.6, 1.6};

void imprimeFila(Fila * l)
{
	Fila * p;
	p = l;
	if( p == NULL)
		printf("Fila vazia !\n");
	else
	{
		while(p != NULL)
		{
			printf("Rolamento: %s\n", p->peca->rolamento);
			p = p->prox;
		}
	}
}

Peca * criaCilindro()
{
	Peca * novo;
	int i;
	novo = (Peca*)malloc(sizeof(Peca));
	novo->rolamento = malloc(sizeof(char));
	novo->rolamento = "Cilíndrico";
	novo->prioridade = 1;
	novo->chegada = 21.5;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_cilindrico[i];
		novo->tempoRolamento[i] = tempoMaquina(ts_cilindrico[i]);
	}
	return novo;
}

Peca * criaConico()
{
	Peca * novo;
	int i;
	novo = (Peca*)malloc(sizeof(Peca));
	novo->rolamento = malloc(sizeof(char));
	novo->rolamento = "Cônico";
	novo->prioridade = 2;
	novo->chegada = 19.1;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_conico[i];
		novo->tempoRolamento[i] = tempoMaquina(ts_conico[i]);
	}
	return novo;
}

Peca * criaEsfericoAco()
{
	Peca * novo;
	int i;
	novo = (Peca*)malloc(sizeof(Peca));
	novo->rolamento = malloc(sizeof(char));
	novo->rolamento = "Esférico Aço";
	novo->prioridade = 3;
	novo->chegada = 8.0;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_esfericoAco[i];
		novo->tempoRolamento[i] = tempoMaquina(ts_esfeticoAco[i]);
	}
	return novo;
}

Peca * criaEsfericoTita()
{
	Peca * novo;
	int i;
	novo = (Peca*)malloc(sizeof(Peca));
	novo->rolamento = malloc(sizeof(char));
	novo->rolamento = "Esférico Titânio";
	novo->prioridade = 3;
	novo->chegada = 8.0;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_esfericoTitan[i];
		novo->tempoRolamento[i] = ts_esfericoTitan[i];
	}
	return novo;
}

Fila * criaFila()
{
	return NULL;
}

void insereFila(Fila ** l, Peca * p)
{
	Fila * atual, * novo, * anterior;
	novo = (Fila*)malloc(sizeof(Fila));

	atual = *l;
	anterior = NULL;
	novo->peca = p;
	if(atual == NULL)
	{
		novo->prox = NULL;
		*l = novo;
	}
	else
	{
		while(atual != NULL && novo->peca->prioridade > atual->peca->prioridade)
		{
			anterior = atual;
			atual = atual->prox;
		}
		novo->prox = atual;
		if(anterior == NULL)
			*l = novo;
		else
			anterior->prox = novo;
	}
}
int sizeFila(Fila * l)
{
	Fila * p;
	p = l;
	int tam=0;
	while(p != NULL)
	{
		tam++;
		p = p->prox;
	}
	return tam;
}
void criaFilasMaquinas(Fila * filasMaquinas[4])
{
	//Fila 0 e 1 são para o torno, 2 fresa, 3 mandril
	int i;
	for(i=0;i<4;i++)
	{
		filasMaquinas[i] = criaFila();
	}
}

void distribuiFila(Fila ** filasMaquinas[4], Peca * p, int pos)
{
	//Esse 'pos' é a posição na sequencia de maquina que a peca está
	int aux;
	aux = p->sequencia[pos];
	if(aux == TORNO)
	{
		if(sizeFila(filasMaquinas[0]) <= sizeFila(filasMaquinas[1]))
			insereFila(filasMaquinas[0], p);
		else
			insereFila(filasMaquinas[1], p);
	}
	else
		insereFila(filasMaquinas[aux], p);
}

float chegadaPedido(float param) {
	float u = 0;
	do {
		u - (float) (rand()%RAND_MAX) / RAND_MAX;
	} while ((u==0) || (u==1));
	return (float) (-param * log (u));
}



int achaMaquina(Peca * p, int pos)
{
	return p->sequencia[pos];
}
int main()
{
	Fila * filasMaquinas[4];
	criaFilasMaquinas(filasMaquinas);

	/* Isso deve acontecer para cada peca criada*/
	Peca * novo;
	novo = criaEsfericoTita();//Funcao que cria todas as pecas no tempo
	
	int aux;
	aux = achaMaquina(novo, 0);
	if(aux == TORNO)
	{
		if(sizeFila(filasMaquinas[0]) <= sizeFila(filasMaquinas[1]))
			insereFila(&filasMaquinas[0], novo);
		else
			insereFila(&filasMaquinas[1], novo);
	}
	else
		insereFila(&filasMaquinas[aux], novo);

	/*//*/

	//imprimir todas as filas
	for(int i=0;i<4;i++)
	{
		if(i == (TORNO-1) || i == TORNO)
			printf("=== Fila Torno ===\n");
		else if(i == FRESA)
			printf("=== Fila Fresa ===\n");
		else
			printf("=== Fila Mandril ===\n");
		imprimeFila(filasMaquinas[i]);
	}
	
}
