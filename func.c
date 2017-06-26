#include <stdio.h>
#include <stdlib.h>
#include "func.h"

//TORNO == 1, FRESA == 2, MANDRILL == 3, NADA == 0;
int s_cilindrico[5] = {1, 2, 1, 3, 0};
int s_conico[5] = {1, 3, 1, 0, 0};
int s_esfericoAco[5] = {2, 3, 1, 0, 0};
int s_esfericoTitan[5] = {2, 3, 1, 2, 1};

float ts_cilindrico[5] = {0.8, 0.5, 0.8, 1.2, 0};
float ts_conico[5] = {1.8, 2.1, 1.8, 0, 0};
float ts_esfeticoAco[5] = {0.5, 1.4, 1.0, 0, 0};
float ts_esfericoTitan[5] = {0.6, 1.5, 1.6, 0.6, 1.6};

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
		novo->tempoMaquina[i] = ts_cilindrico[i];
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
		novo->tempoMaquina[i] = ts_conico[i];
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
		novo->tempoMaquina[i] = ts_esfeticoAco[i];
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
		novo->tempoMaquina[i] = ts_esfericoTitan[i];
	}
	return novo;
}
int main()
{
	Peca * novo;
	novo = criaEsfericoTita();
	printf("Nome: %s - prioridade: %d - Chegada: %f\n", novo->rolamento, novo->prioridade, novo->chegada);
	for(int i=0;i<5;i++)
	{
		printf("S: %d\n", novo->sequencia[i]);
	}
	printf("=======================\n");
	for(int i=0;i<5;i++)
	{
		printf("Tempo: %f\n", novo->tempoMaquina[i]);
	}
	return 0;
}