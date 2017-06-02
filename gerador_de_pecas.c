#include <stdio.h>
#include <stdlib.h>
#include <time.h>
	int s_conico[4] = {2,1,3,4};
	int s_esferico[4] = {1,4,2,4};
	int s_cilindrico[4] = {1,2,3,4};
	
typedef struct peca{
	char * nome;
	int prioridade;
	int sequencia[4];
	float tempo;
}peca;

peca cria_peca(peca * p1,char *nome, int prioridade, int sequencia[4], float tempo;){
		p1 = malloc(sizeof(peca));
		p1->nome = nome;
		p1->prioridade = prioridade;
		for(int i=0;i<4;i++){
			p1->sequencia[i] = sequencia[i];
		}
		
		p1->tempo = tempo;
		
		return p1;
}

int main(){
	
		//Chamar p1 e atribuir à funcao	
		printf("%s \n%d \n%f \n", p1->nome,p1->prioridade, p1->tempo);
		for(int i=0;i<4;i++){
			printf("%d ", p1->sequencia[i]);
		}
	}	