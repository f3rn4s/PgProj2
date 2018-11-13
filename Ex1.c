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

int do_random();
int do_random_for_game();
bool who_plays_first();
void play(bool c);

int main()
{
	play(who_plays_first());
	return 0;
}
int do_random()
{
	int random;
	srand(time(0));
	for(int i = 0; i<5; i++) 
        random = rand();

    return random;
}
int do_random_for_game()
{
	int a = do_random;
	if (a > 500 && a < 1500)
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
bool who_plays_first()
{
	
  	if(do_random >1556)
  	{
  		printf("Primeiro eu\n");
  		return false;
  	}
  	else
  	{
  		printf("Tu és o primeiro a jogar");
  		return true; 
  	}
}
void play(bool c)
{
	bool winner=false; // Para guardar o vencedor definir se 1 é PC e 0 Humano
	int a,x = 0; // Para
	int sum = 0;
	char b = 0;

		do
		{
			if(c == true)
			{
				x = do_random_for_game();
				sum += x;
				c = false;
				printf("Eu jogo %d , vai em %d\n", x ,sum );
			}
			if (c == false)
			{
				scanf(&a);
				sum += x;
				c == true;
				printf("A tua jogada: %d\n", x);
			}
		}while(sum <31);
		if (sum <= 31 && c == true)
		{
			printf("Desta vez ganhei eu. Boa sorte para a próxima\n");
		}
		if (sum <= 31 && c == false)
		{
			printf("Parabéns ganhaste!!!\n");
		}
		scanf("Novo jogo (s/n)", %b);
		if (b == 's')
		{
			play(c);
		}else{
			printf("Adeus e ate a proxima!\n");
			return 0;
		}
}

