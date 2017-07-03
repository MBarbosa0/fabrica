#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
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
	novo->tempoTotal = 0;
	novo->maquinaAtual = 0;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_cilindrico[i];
		novo->tempoRolamento[i] = ts_cilindrico[i];
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
	novo->tempoTotal = 0;
	novo->maquinaAtual = 0;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_conico[i];
		novo->tempoRolamento[i] = ts_conico[i];
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
	novo->tempoTotal = 0;
	novo->maquinaAtual = 0;
	for(i=0;i<5;i++)
	{
		novo->sequencia[i] = s_esfericoAco[i];
		novo->tempoRolamento[i] = ts_esfeticoAco[i];
	}
	return novo;
}

Peca * criaEsfericoTitan()
{
	Peca * novo;
	int i;
	novo = (Peca*)malloc(sizeof(Peca));
	novo->rolamento = malloc(sizeof(char));
	novo->rolamento = "Esférico Titânio";
	novo->prioridade = 3;
	novo->chegada = 8.0;
	novo->tempoTotal = 0;
	novo->maquinaAtual = 0;
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

float chegadaPedido(float param) {
	float u=0;
	do {
	u = (float) (rand()%RAND_MAX) / RAND_MAX;
	} while ((u==0) || (u==1));
	return (float) (-param * log (u));
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

void distribuiMaquina(Fila * filasMaquinas[4], Peca * pecas[4], int posMenor, int pos)
{
	int aux;
	aux = pecas[posMenor]->sequencia[pos];
	if(aux == TORNO)
	{
		/*Como sao dois tornos, tenq achar oq tem menos na fila*/
		if(sizeFila(filasMaquinas[0]) <= sizeFila(filasMaquinas[1]))
			insereFila(&filasMaquinas[0], pecas[posMenor]);
		else
			insereFila(&filasMaquinas[1], pecas[posMenor]);
	}
	else
		insereFila(&filasMaquinas[aux], pecas[posMenor]);
}

void manipulaTempo(Fila * filasMaquinas[4], Peca * pecas[4], float tempos[4])
{
	/*Gerar tempos e encontrar o cara com menor tempo para ser colocado na fila*/
	int posMenor,i;
	float menor;
	float oldtime;

	/*
	//Para ver os tempos de entradas
	for(int i=0;i<4;i++)
	{
		printf("Tempos: %f\n", tempos[i]);
	}
	printf("\n");
	*/

	menor = tempos[0];
	posMenor = 0;
	for(i=1;i<4;i++)
	{
		if(tempos[i] < menor)
		{
			menor = tempos[i];
			posMenor = i;
		}
	}

	/* Sistema para garantir que o novo tempo gerado nao seja menor que o anterior*/
	oldtime = tempos[posMenor];
	tempos[posMenor] = chegadaPedido(pecas[posMenor]->chegada);
	while(tempos[posMenor] < oldtime)
	{
		tempos[posMenor] =  chegadaPedido(pecas[posMenor]->chegada);
	}

	
	//printf("\n");

	distribuiMaquina(filasMaquinas, pecas, posMenor, 0 );
	
}

Fila * retirarFila(Fila * l)
{
	Fila * p;
	Fila * ant = NULL;
	p = l;

	while(p->prox != NULL)
	{
		ant = p;
		p = p->prox;	
	}

	if(p == NULL)
		return l;
	if(ant == NULL)
		l = p->prox;
	else if(ant != NULL)
	{
		l->prox = p->prox;
		l = ant;
	}

	free(p);
	return l;
}

float tempoMaquina(float ts_estadia[5], int pos) 
{
    return 2.0 * ts_estadia[pos] * rand() / (RAND_MAX + 1.0); 
}

void distribuiMaquinaSimples(Fila * filasMaquinas[4], Peca * peca, int pos)
{
	int aux;
	aux = peca->sequencia[pos];
	if(aux == TORNO)
	{
		/*Como sao dois tornos, tenq achar oq tem menos na fila*/
		if(sizeFila(filasMaquinas[0]) <= sizeFila(filasMaquinas[1]))
			insereFila(&filasMaquinas[0], peca);
		else
			insereFila(&filasMaquinas[1], peca);
	}
	else
		insereFila(&filasMaquinas[aux], peca);
}

void atribuiTempo(Fila * fila, int posAtual, float menor)
{
	Fila * p;
	p = fila;
	float x;
	while(p != NULL)
	{
		x = tempoMaquina(p->peca->tempoRolamento, posAtual);
		p->peca->tempoTotal += x + menor;
		p = p->prox;
	}
	
}

void zerarMatriz(double mat[4][2])
{
	int i, j;
	for(i=0; i<4;i++)
	{
		for(j=0;j<2;j++)
		{
			mat[i][j] = 0.0;
		}
	}
}

void contaPeca(Peca * p, double mat[4][2])
{
	if(p->prioridade == 1)
	{
		mat[0][0]++;
		mat[0][1] += p->tempoTotal;
	}
	else if(p->prioridade == 2)
	{
		mat[1][0]++;
		mat[1][1] += p->tempoTotal;
	}
	else if(strcmp(p->rolamento, "Esférico Aço") == 0)
	{
		mat[2][0]++;
		mat[2][1] += p->tempoTotal;
	}
	else
	{
		mat[3][0]++;
		mat[3][1] += p->tempoTotal;
	}
}

int main()
{
	int i,posAtual = 0;
	float menor,tempoDeOperacao;
	printf("Tempo maximo de operação: ");
	scanf("%f", &tempoDeOperacao);

	Fila * filasMaquinas[4];

	Fila * k;
	int saux;

	double matResposta[4][2];
	zerarMatriz(matResposta);

	criaFilasMaquinas(filasMaquinas);

	Peca * pecas[4];

	pecas[0] = criaCilindro();
	pecas[1] = criaConico();
	pecas[2] = criaEsfericoAco();
	pecas[3] = criaEsfericoTitan();

	float tempos[4];
	for(i=0;i<4;i++)
	{
		tempos[i] = chegadaPedido(pecas[i]->chegada);
	}

	while(tempoDeOperacao > 0)
	{

		manipulaTempo(filasMaquinas, pecas, tempos);
		menor = tempos[0];

		/* Para fazer a passagem de tempo baseado no menor tempo de chegada*/
		for(i=1;i<4;i++)
		{
			if(tempos[i] < menor)
			{
				menor = tempos[i];
		
			}
		}

		for(i=0;i<4;i++)
		{
			atribuiTempo(filasMaquinas[i], posAtual,menor);
			k=filasMaquinas[i];
			if(filasMaquinas[i] != NULL)
			{
				while(k->prox != NULL)
				{	
					k = k->prox;
				}
				
				saux = k->peca->sequencia[posAtual+1];
				
				if(saux == TORNO)
				{
					if(sizeFila(filasMaquinas[0]) <= sizeFila(filasMaquinas[1]))
					{
						insereFila(&filasMaquinas[0], k->peca);
					}
					else
						insereFila(&filasMaquinas[1], k->peca);
				}
				else if(saux == FRESA)
					insereFila(&filasMaquinas[2], k->peca);
				else if(saux == MANDRIL)
					insereFila(&filasMaquinas[3], k->peca);
				else if(saux == NONE)
				{
					contaPeca(k->peca, matResposta);
				}
				filasMaquinas[i] = retirarFila(filasMaquinas[i]);	
			}
		}
		posAtual++;
		tempoDeOperacao -= menor;
	}
	
	//Vai sair na versao final
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

	printf("===================================================\n");
	printf("\n");
	for(i=0;i<4;i++)
	{
		matResposta[i][1] /= matResposta[i][0];
	}
		printf("Qnt de cilíndrico: %.0f - Tempo médio: %f\n", matResposta[0][0],matResposta[0][1]);
		printf("Qnt de cônico: %.0f - Tempo médio: %f\n", matResposta[1][0],matResposta[1][1]); 
		printf("Qnt de esférico aço: %.0f - Tempo médio: %f\n", matResposta[2][0],matResposta[2][1]); 
		printf("Qnt de esférico titânio: %.0f - Tempo médio: %f\n", matResposta[3][0],matResposta[3][1]); 
}