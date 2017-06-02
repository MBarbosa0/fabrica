#include <stdio.h>
#include <stdlib.h>

typedef struct lista
{
	float tempo;
	char * peca;
	struct lista*prox;
} Lista;

Lista * inicializar()
{
	return NULL;
}

Lista * inserir (Lista * l, char * p, float t)
{
	Lista * novo;
	novo = (Lista*) malloc(sizeof(Lista));
	if (novo == NULL)
		exit(1);
	novo->tempo = t;
	novo->peca = p;
	novo->prox = l;
	return novo;
}

void imprimir(Lista * l)
{
	Lista * p;
	for(p=l; p != NULL; p = p->prox)
		printf("Peça = %s com tempo = %.2f\n", p->peca,p->tempo);
}

void liberar(Lista * l)
{
	Lista * p;
	Lista * t;
	p = l;
	while (p != NULL)
	{
		t = p->prox;
		free(p);
		p = t;
	}
}
//Arrumar aqui...
Lista * valorarquivo(Lista * l, char fnome[50])
{
	FILE * arq = fopen(fnome, "r");
	char peca[50];
	float tempo;

	while((fscanf(arq, "%s %f\n",peca, &tempo)) != EOF)
	{
		l = inserir(l, peca, tempo);
	}
	return l;

}
int main(){
	Lista * l = inicializar();
	l = valorarquivo(l, "dados.in");
	imprimir(l);
	liberar(l);
	return 0 ;
}