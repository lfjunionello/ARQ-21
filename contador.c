#include <stdio.h>

// stdout, stdin, stderr

int main(int argc, char** argv)
{
	FILE *entrada;
	int c, count_uc=0, count_lc=0, count_num=0, count_blank=0, count_line=0;

	if(argc != 2)
	{
		fprintf(stderr,"Erro na chamada do comando.\n");
		fprintf(stderr,"Uso: %s [ARQUIVO].\n", argv[0]);
		return 1;
	}

	entrada = fopen(argv[1],"r");
	if(!entrada)
	{
		fprintf(stderr,"Arquivo %s não pode ser aberto para leitura\n", argv[1]);
		return 1;
	}


	c = fgetc(entrada);
	while(c != EOF)
	{
		if (c >= 'A' && c <= 'Z'){
			count_uc++;
		}	

		else if(c >= 'a' && c <= 'z'){
			count_lc++;
		}

		else if(c >= '0' && c<='9'){
			count_num++;
		}	

		else if( c == ' '){
			count_blank++;
		}

		else if(c == '\n'){
			count_line++;
		}

		c = fgetc(entrada);
	}

	printf("Quantidade de letras maiusculas: %d \n", count_uc);
	printf("Quantidade de letras minusculas: %d \n", count_lc);
	printf("Quantidade de numeros: %d \n", count_num);
	printf("Quantidade de espacos em branco : %d \n", count_blank);
	printf("Quantidade de quebras de linhas: %d \n", count_line);


	fclose(entrada);
	return 0;
}

