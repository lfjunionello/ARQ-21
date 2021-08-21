#include <stdio.h>
#include <string.h>

typedef struct _Endereco Endereco;

// registroCEP = struct.Struct("72s72s72s72s2s8s2s")

struct _Endereco
{
	char logradouro[72];
	char bairro[72];
	char cidade[72];
	char uf[72];
	char sigla[2];
	char cep[8];
	char lixo[2]; // Ao Espaço no final da linha + quebra de linha
};

int main(int argc, char**argv)
{
	FILE *f;
	Endereco e;
	int qt;
	int c;
	int stop;

	if(argc != 2)
	{
		fprintf(stderr, "USO: %s [Nome]", argv[0]);
		return 1;
	}

	c = 0;
	printf("Tamanho da Estrutura: %ld\n\n", sizeof(Endereco));
	f = fopen("cep.dat","r");
	qt = fread(&e,sizeof(Endereco),1,f);

	printf("Hey %s\n",strupr(argv[1]));

	while(qt > 0)
	{
		c++;
		// argv[1] < e.cep  => strcmp(argv[1],e.cep) < 0
		// argv[1] > e.cep  => strcmp(argv[1],e.cep) > 0
		// argv[1] == e.cep  => strcmp(argv[1],e.cep) == 0
		if(strstr(e.logradouro,argv[1]))
		{
			printf("%.72s\n%.72s\n%.72s\n%.72s\n%.2s\n%.8s\n===============\n",e.logradouro,e.bairro,e.cidade,e.uf,e.sigla,e.cep);
			stop++;
		}
		qt = fread(&e,sizeof(Endereco),1,f);

		if(stop==20){
			break;
		}		
	}
	printf("Total Lido: %d\n", c);
	fclose(f);
}

