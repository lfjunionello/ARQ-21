#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(1)

#define N 8

typedef struct _Endereco Endereco;

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2];
};


int compara(const void* c1, const void* c2){
    
    return strncmp(((Endereco*)c1)->cep,((Endereco*)c2)->cep,8);

}

int main(int argc, char**argv){

    FILE *f, *saida;
	Endereco *e;
	long posicao, qtdRegistros, regsPorParte, regsParte;

	f = fopen("cep.dat","r");

	fseek(f,0,SEEK_END);
	posicao = ftell(f);
	qtdRegistros = posicao/sizeof(Endereco);
	regsPorParte = (qtdRegistros/N);

    char nomeArquivo[100];
    int i = 1;
    rewind(f);

    while(i <= N){

        if(i < N){
            regsParte = regsPorParte;
        }
        else{
            regsParte = qtdRegistros - (N-1)*regsPorParte;
        }

        e = (Endereco *)malloc(regsParte * sizeof(Endereco));

        fread(e, sizeof(Endereco), regsParte, f);
        qsort(e,regsParte,sizeof(Endereco),compara);
        //printf("Conteudo do e: %s \n",t);

        sprintf(nomeArquivo,"Cep-%03d.dat",i);

        saida = fopen(nomeArquivo,"w");
        fwrite(e,sizeof(Endereco),regsParte,saida);

        fclose(saida);
        free(e);

        i++;      
    }
    fclose(f);

    FILE *a, *b;
	Endereco ea, eb;
    int j = 1;
    char nomeArquivo1[100],nomeArquivo2[100];

    while(i < 2*N) {

        
        sprintf(nomeArquivo,"Cep-%03d.dat",i);
        i++;
        sprintf(nomeArquivo1,"Cep-%03d.dat",j);
        j++;
        sprintf(nomeArquivo2,"Cep-%03d.dat",j);
        j++;


        a = fopen(nomeArquivo1,"r");
        b = fopen(nomeArquivo2,"r");
        saida = fopen(nomeArquivo,"w");

        fread(&ea,sizeof(Endereco),1,a);
        fread(&eb,sizeof(Endereco),1,b);

        while(!feof(a) && !feof(b))
        {
            if(compara(&ea,&eb)<0)
            {
                fwrite(&ea,sizeof(Endereco),1,saida);
                fread(&ea,sizeof(Endereco),1,a);
            }
            else
            {
                fwrite(&eb,sizeof(Endereco),1,saida);
                fread(&eb,sizeof(Endereco),1,b);
            }
        }

        while(!feof(a))
        {
            fwrite(&ea,sizeof(Endereco),1,saida);
            fread(&ea,sizeof(Endereco),1,a);		
        }
        while(!feof(b))
        {
            fwrite(&eb,sizeof(Endereco),1,saida);
            fread(&eb,sizeof(Endereco),1,b);		
        }

        fclose(a);
        fclose(b);
        fclose(saida);



    }

    return 0;
}