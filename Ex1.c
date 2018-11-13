/*Realize um programa para jogar o “jogo do 31” entre o computador e um jogador humano.
 Cada jogador joga alternadamente um valor inteiro de entre três possíveis (1, 2 ou 3) 
 que vai acumulando com o total das jogadas anteriores. Ganha o primeiro jogador que 
 primeiro atingir (ou ultrapassar) o valor 31. Deve ser escolhido aleatoriamente quem 
 joga da primeira vez. O jogo tem uma estratégia vencedora que deve ser seguida na 
 programação da jogada do computador, mas no caso de ser o computador o primeiro a jogar
  a sua jogada deve ser aleatória. Durante uma sessão de utilização do programa podem ser
   realizados vários jogos, jogando em primeiro lugar o vencedor do jogo anterior.
Ao lado exemplifica-se o funcionamento do jogo num cenário em que o computador é o primeiro
 a jogar, para servir de referência na sua implementação.*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int do_random();
int do_random_for_game();
bool who_plays_first();
void play(bool c);
void is_winner(int a, bool b );

int main()
{
	play(who_plays_first());
	return 0;
}
int do_random() //Funcao random universal para ser usado para qualquer situacao

//https://www.tutorialspoint.com/c_standard_library/c_function_srand.htm

{
	int random;
	time_t t;

	srand((unsigned) time(&t));

	for(int i = 0; i < 5; i++) 
        random = (int)(rand() % 2225);

    return random;
}
int do_random_for_game() // função para retirar valores random com valores 1,2 e 3
{
	int a = 0;
	a = do_random();
	if (a > 750 && a < 1500)
	{
		return a = 2;
	}
	else if(a >= 1500 )
	{
		return a = 3;
	}
	else
	{
		return a = 1;
	}
}
bool who_plays_first() //Funcao para saber quem joga primeiro
{
	
  	if(do_random() > 1450)
  	{
  		printf("Primeiro eu\n");
  		return false;
  	}
  	else
  	{
  		printf("Tu és o primeiro a jogar: ");
  		return true; 
  	}
}
void play(bool c)  //Funcao que contem o algoritmo do jogo
{
	int a,x = 0; // Para
	int sum = 0;
	
		do
		{
			if(c == false) //PC
			{
				x = do_random_for_game(); //Buscar um valor entre 1 e 3
				sum += x;
				c = true;
				printf("Eu jogo %d , vai em %d\n", x ,sum );
				if (sum >=31) // Verificar se é necessário
				{
					break;
				}
			}
			if (c == true) //Humano
			{
				scanf("%d",&a); // Falta validar valores entre  1 e 3 inseridos pelo utilizador
				sum += a;
				c = false;
				printf("A tua jogada: %d\n", a);
			}

		}while(sum <31);

		printf("Sum = %d", sum);
		is_winner(sum,c); 

		
}
void is_winner(int a, bool b) // Para verificar quem ganhou e pergunta se quer jogar novamente
{
	char k;

	if ( a-31 == 0 && b == true )
	{
		printf("(1if) Desta vez ganhei eu. Boa sorte para a próxima\n");
		printf("Novo jogo (s/n): ");
		scanf(" %c", &k);
	}
	if ( a-31 != 0 && b == true )
	{
		printf("(2if) Parabéns ganhaste!!!\n");
		printf("Novo jogo (s/n): ");
		scanf(" %c", &k);
	}
	if ( a-31 == 0 && b == false )
	{
		printf("(3if) Parabéns ganhaste!!!\n");
		printf("Novo jogo (s/n): ");
		scanf( " %c", &k);
	}
	if ( a-31 != 0 && b == false )
	{
		printf("(4if) Desta vez ganhei eu. Boa sorte para a próxima\n");
		printf("Novo jogo (s/n): ");
		scanf(" %c", &k);
	}
	if (k == 's')
	{
		play(b);
	}else
	{
		printf("Adeus e ate a proxima!\n");
	}
}

