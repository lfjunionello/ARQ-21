#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct _Endereco Endereco;

struct _Endereco{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
}; 

int buscaBinaria(FILE *f, char *target,long primeiro,long ultimo,int count){  // Retorna a quantidade de passos

	Endereco e;
	long meio;
	fseek(f,0,SEEK_SET);

	if(ultimo >= primeiro){

		count++;
		meio = (primeiro+ultimo)/2;

		//printf("\nINICIO: %ld\tMEIO: %ld\tFINAL: %ld\n",primeiro,meio,ultimo); //Print para ver cada passo

		fseek(f,(meio*sizeof(Endereco)),SEEK_SET);

		fread(&e, sizeof(Endereco), 1, f);

		if(strncmp(target,e.cep,8) == 0){
			printf("========================\n");
			printf("\nLogradouro: %.72s\nBairro: %.72s\nCidade: %.72s\nUF: %.72s\nSigla: %.2s\nCEP: %.8s\n\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			return count;
		}

		else{
			if(strncmp(target,e.cep,8) > 0){
				buscaBinaria(f,target,meio+1,ultimo,count);
			}
			
			else if(strncmp(target,e.cep,8) < 0){
				buscaBinaria(f,target,primeiro,meio-1,count);
			}
		}
	}
	else{
		printf("Não foi possivel encountrar o CEP\n");
		return count;
	}

}

int main(int argc, char**argv){

	FILE *f;
    Endereco e;
    
	int count = 0;
	char target[8];
	long tamanhoArquivo, primeiro, ultimo;

	if(argc != 2){
		fprintf(stderr, "USO: %s [CEP]", argv[0]);
		return 1;
	}

	strncpy(target,argv[1],8);

	f = fopen("cep_ordenado.dat","r");

	fseek(f,0,SEEK_END);
	tamanhoArquivo = ftell(f);

	fseek(f,0,SEEK_SET);

	primeiro = 0;
	ultimo = (tamanhoArquivo/sizeof(Endereco))-1;

	count = buscaBinaria(f, target, primeiro, ultimo, count);

	printf("========================\n");
	printf("PASSOS TOTAIS: %i",count);

    	
	fclose(f);
	return 0;
}
