#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <math.h>

//Limite
#define LIM 5001

/*
expressao[]->string que conterá a expressão digitada pelo usuário
expressaoAux[]->String auxiliar em que ficará copiada a expressão digitada
letras[]->String em que ficarão as variáveis digitadas pelo usuário na expressão
valoresLetras[]->String em que ficarão os valores lógicos das variáveis em cada momento da resolução
*/
char expressao[LIM], expressaoAux[LIM], letras[(LIM - 1) / 2], valoresLetras[(LIM - 1) / 2];

/*
tlLetras = número de variáveis da expressão atual
carryOut = variável usada pela função somaUmBinario() para alterar os valores lógicos das variáveis
*/
int tlLetras, carryOut;

//Função para indicar se um determinado caractere é uma letra (1) ou não (0)
int eLetra(char letra);
//Função que indica se um caractere corresponde a um valor lógico ou não
int eNumero(char numero);
//Função que coloca todos os caracteres da expressão digitada em minúsculo 
void expressaoMinusculo();
//Função que altera os valores lógicos da expressão
void somaUmBinario();
//Função que altera a string da expressão após a realização do cálculo apenas para a negação. Usada também para
//remover parênteses da expressão
void remanejaExpressao(int inicio);
//Altera a string da expressão após o cálculo, mudando dois caracteres por vez
void remanejaExpressaoNegacao(int inicio);
//Administra a resolução da expressão
void resolveExpressao();
//Faz os cálculos lógicos
void calcula(int comeco, int fim);

int main()
{
	int i, j, pos;
		
	printf("Digite a expressao:\n");
	fflush(stdin);
	fgets(expressao, LIM, stdin);
	
	expressaoMinusculo();
	
	tlLetras = 0;
	
	for(i = 0; i < strlen(expressao); i++)
		if(eLetra(expressao[i]) == 1)
		{
			pos = 0;
			
			while(pos < tlLetras && (int)letras[pos] != (int)expressao[i])
				pos++;
				
			if(pos == tlLetras)
			{
				pos = 0;
				
				while(pos < tlLetras && (int)expressao[i] > (int)letras[pos])
					pos++;
					
				for(j = tlLetras; j > pos; j--)
					letras[j] = letras[j - 1];
						
				letras[pos] = expressao[i];
				
				tlLetras++;
			}
		}
		
	for(i = 0; i < tlLetras; i++)
		valoresLetras[i] = '0';
	
	for(j = 0; j <= tlLetras; j++)
			printf("--");
			
	printf("\n|");
			
	for(i = 0; i < tlLetras; i++)
		printf("%c|", letras[i]);
	printf("S|\n");
	
	for(j = 0; j <= tlLetras; j++)
			printf("--");
	printf("-\n");
	
	for(i = 0; i < pow(2, tlLetras); i++)
	{
		strcpy(expressaoAux, expressao);
		
		//Altera os caracteres das variaveis, colocando seus respectivos valores lógicos
		for(j = 0; j < strlen(expressaoAux); j++)
		{
			if(eLetra(expressaoAux[j]) == 1)
			{
				pos = 0;
				
				while(pos < tlLetras && (int)expressao[j] != (int)letras[pos])
					pos++;
					
				if(pos == tlLetras)
					printf("ERRO!!!!\n");
				else
				{
					expressaoAux[j] = valoresLetras[pos];	
				}
			}
			
		}
		
		printf("|");
		
		for(j = 0; j < tlLetras; j++)
			printf("%c|", valoresLetras[j]);	
			
		resolveExpressao();
		
		printf("%1.1s|\n", expressaoAux);
			
		for(j = 0; j <= tlLetras; j++)
			printf("--");
			
		printf("-\n");
		
		//Altera os valores lógicos das variáveis na tabela	
		if(i < pow(2, tlLetras) - 1)
			somaUmBinario();
			
	}
	
	getch();
}

int eNumero(char numero)
{
	if(numero == '1' || numero == '0')
		return 1;
	else
		return 0;
}

void calcula(int inicio, int fim)
{
	int pos;
	char res;

	do
	{
		//Procura negação
		pos = inicio;
		
		while(pos <= fim && expressaoAux[pos] != '!')
			pos++;
			
			
		if(pos <= fim && eNumero(expressaoAux[pos + 1]))//Deveria ser < fim, mas tudo bem...
		{
			
			//Tem uma negação na sentença
			if(expressaoAux[pos + 1] == '1')
				res = '0';
			else
				res = '1';
				
			expressaoAux[pos] = res;
			
			remanejaExpressaoNegacao(pos + 1);
			
			inicio = pos;
			fim -= 1;
		}
	}while(pos <= fim);
	
	do
	{
		//Procura conjunção
		pos = inicio;
		
		while(pos <= fim && expressaoAux[pos] != '.')
			pos++;
			
		if(pos <= fim && eNumero(expressaoAux[pos + 1]) && eNumero(expressaoAux[pos - 1]) )
		{
			if(expressaoAux[pos - 1] == '1' && expressaoAux[pos + 1] == '1')
				res = '1';
			else
				res = '0';
				
			expressaoAux[pos - 1] = res;
			remanejaExpressao(pos);
			
			inicio = pos - 1;
			fim -= 2;
		}	
			
	}while(pos <= fim);
	
	do
	{
		//Procura disjunção
		pos = inicio;
		
		while(pos <= fim && expressaoAux[pos] != '+') 
			pos++;	
			
		if(pos <= fim && eNumero(expressaoAux[pos + 1]) && eNumero(expressaoAux[pos - 1]) )
		{
			if(expressaoAux[pos - 1] == '1' || expressaoAux[pos + 1] == '1')
				res = '1';
			else
				res = '0';
				
			expressaoAux[pos - 1] = res;
			
			remanejaExpressao(pos);
			
			inicio = pos - 1;
			fim -= 2;
		}	
			
	}while(pos <= fim);
	
	do
	{
		//Procura condicional
		pos = inicio;
		
		while(pos <= fim && expressaoAux[pos] != '>' )
			pos++;
			
		if(pos <= fim && eNumero(expressaoAux[pos + 1]) && eNumero(expressaoAux[pos - 1]) )
		{
			if(expressaoAux[pos - 1] == '1' && expressaoAux[pos + 1] == '0')
				res = '0';
			else
				res = '1';
				
			expressaoAux[pos - 1] = res;
			
			remanejaExpressao(pos);
			
			inicio = pos - 1;
			fim -= 2;
		}	
			
	}while(pos <= fim);
	
	do
	{
		//Procura bicondicional
		pos = inicio;
		
		while(pos <= fim && expressaoAux[pos] != '=')
			pos++;
			
		if(pos <= fim && eNumero(expressaoAux[pos + 1]) && eNumero(expressaoAux[pos - 1]) )
		{
			if(expressaoAux[pos - 1] == expressaoAux[pos + 1] )
				res = '1';
			else
				res = '0';
				
			expressaoAux[pos - 1] = res;
			
			remanejaExpressao(pos);
			
			inicio = pos - 1;
			fim -= 2;
		}	
			
	}while(pos <= fim);
	
	do
	{
		//Procura disjunção exclusiva
		pos = inicio;
		
		while(pos <= fim && expressaoAux[pos] != '#')
			pos++;
			
		if(pos <= fim && eNumero(expressaoAux[pos + 1]) && eNumero(expressaoAux[pos - 1]) )
		{
			if(expressaoAux[pos - 1] != expressaoAux[pos + 1] )
				res = '1';
			else
				res = '0';
				
			expressaoAux[pos - 1] = res;
			
			remanejaExpressao(pos);
			
			inicio = pos - 1;
			fim -= 2;
		}	
			
	}while(pos <= fim);
}

void expressaoMinusculo()
{
	int i;
	
	for(i = 0; expressao[i] != '\0'; i++)
		if((int)expressao[i] >= 65 && (int)expressao[i] <= 90)
			expressao[i] += 32;
}

int eLetra(char letra)
{
	//Lembrando que todas as letras tem que estar em minúsculo
	if((int)letra >= 97 && (int)letra <= 122)
		return 1;
	else
		return 0;
}

void somaUmBinario()
{
	int i;
	
	carryOut = 0;
	
	i = tlLetras - 1;
	
	do
	{
		if(carryOut == 1)
		{
			if(valoresLetras[i] == '0')
			{
				valoresLetras[i] = '1';
				carryOut = 0;
			}
			else if(valoresLetras[i] == '1')
			{
				valoresLetras[i] = '0';
				carryOut = 1;
			}
		}
		else
		{
			if(valoresLetras[i] == '0')
			{
				valoresLetras[i] = '1';
				carryOut = 0;
			}
			else if(valoresLetras[i] == '1')
			{
				valoresLetras[i] = '0';
				carryOut = 1;
			}
		}
		
		i--;
	}while(carryOut == 1);
}

void remanejaExpressao(int inicio)
{
	int i;
	
	for(i = inicio; expressaoAux[i + 2] > (int)'\0'; i++){
		expressaoAux[i] = expressaoAux[i + 2];
	}
	
	expressaoAux[i] = expressaoAux[i + 2];

}

void remanejaExpressaoNegacao(int inicio)
{
	int i;
	
	i = inicio;
	
	for(i = inicio; expressaoAux[i + 1] > (int)'\0'; i++)
	{
		expressaoAux[i] = expressaoAux[i + 1];
	}
	
	expressaoAux[i] = expressaoAux[i + 1];
	
}

void resolveExpressao()
{
	int i, j, achou, comeco, final;
	
	while(strlen(expressaoAux) > 2)
	{
		achou = 0;
		
		for(i = 0; i < strlen(expressaoAux); i++)
		{
			if(expressaoAux[i] == '(')
			{	
				for(j = i + 1; j < strlen(expressaoAux); j++)
					if(expressaoAux[j] == ')')
					{
						comeco = i;
						final = j;
						achou = 1;
					}
			}
		}
		
		if(achou == 1)
		{
			//Expressão tem parenteses
			calcula(comeco, final);
			
			for(i = comeco; expressaoAux[i] != ')' && i < strlen(expressaoAux); i++)
				if(expressaoAux[i] == '(')
				{
					remanejaExpressaoNegacao(i);
				}
					
			remanejaExpressaoNegacao(i);
		}
		else
		{
			//Expressão não tem mais parênteses
			calcula(0, strlen(expressaoAux) - 2);
		}
	}

}
