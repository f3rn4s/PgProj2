/*----------------------------------------------------------------------------
 * jogo do gamão em modo consola
 * ISEL, outubro de 2018
 * 
 * Build: gcc -o gamoncons -Wall -std=c99 gamoncons.c model.c utils.c
 * Execute: gamoncons
 * 
 *---------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdbool.h>
#include "model.h"
#include "utils.h"
#include  <ctype.h>

// nomes dos dois jogadores
char names[][9] = { "BRANCO", "VERMELHO" };

// os dois dados (a posição 0 não é usada)
int dados[3];

// os valores das duas variáveis seguintes alternam em cada jogada
int player; // WHITE or RED
int other;  // o outro jogador


/* funções auxiliares */

/**
 * Serve para apresentar uma mensagem de erro
 **/
void error(char msg[]) {
	printf("\nerro: %s\n", msg);
}

/**
 * Esta função serve para limpar caracteres na linha que não tenham sido recolhidos
 * de modo a não terem influência na próxima leitura
 **/
void clean_line() {
	int c;
	do { c=getchar(); } while (c != '\n');
}

/**
 * Nesta versão a função limita-se a actualizar as variáveis globais "player"  
 * e "other" que indicam o jogador corrente e o seu adversário
 */
void set_player(int color) {
	player = color;
	if (player == RED) other = WHITE; else other = RED;
}

// funções auxiliares à apresentação do tabuleiro de jogo

/**
 * Apresenta simplesmente uma barra de hiphens
 **/
void show_separator() {
	printf("|");
	for(int i=0; i < 14; ++i) 
		printf("----");
    printf("|\n");
}

/**
 * Apresenta a numeração dos lugares de cima e de baixo,
 * de modo a que a zona "home" de cada jogador tenha casas numeradas de 1 a 6
 **/
void show_places() {
	int i;
	printf("|");
	for (i=12; i > 6; --i) {
		printf("%4d", i);	
	}
 
	printf("|    |");
	
	for (i=6; i > 0; --i) {
		printf("%4d", i);	
	}
	printf("  |\n");
}


/**
 * Apresenta a parte intermédia como indicado no enunciado
 * do trabalho
 **/
void show_bar() {
	for(int i=0;i < 3; i++) {
		printf("|");
		for(int j=1; j <= 12; j++) {
			if (j == 7) {
				int cv=0, cb=0;
				if (i==0) {
					cv = bar_captured(RED);
					if (cv > 0) printf("|%2dV |", cv);
				}
				else if (i==2) {
					cb = bar_captured(WHITE);
					if (cb>0) printf("|%2dB |", cb);
				}
				if (cv == 0 && cb ==0) printf("|    |");
			}
			printf("    ");
		}
		printf("  |\n");
	}
}

/**
 * Apresenta as peças nas casas cujo início e fim são indicados (parte de cima
 * ou parte de baixo). O intervalo é sempre indicado vendo as casas da 
 * esquerda para a direita
 * Parâmetros:
 * 	start: início do intervalo de casas a apresentar
 *  end: fim do intervalo de casas a apresentar
 * 
 * 
 * Os valores são indicadas como indices dos arrays que armazenam
 * informação sobre a distribuição das peças de jogo.
 * 
 * Note-se que na parte superior, "start" é 23 (índica a última casa) e "end" é 12.
 * 
 **/
void show_pieces(int start, int end) {
	int step = (start > end) ? -1 : 1;
	int middle = (end+start)/2;
	printf("|");
	
	for(int i=start; i != end; i += step) {
		if (i == middle)
			printf("|    |");
		int n = pieces_at(i, RED);
		if (n > 0) printf("%3dV", n);
		else if ((n = pieces_at(i, WHITE)) > 0) {
			printf("%3dB", n);
		}
		else {
			printf("    ");
		}
	}
	printf("  |\n");
}

/**
 * Apresenta os dados que ainda estão disponíveis na jogada.
 * O valor dos dados jogados é marcado com zero na execução do respetivo lance (se bem sucedido)
 * de modo a não serem apresentados de novo.
 **/
void show_dices() {
	if (dados[1] != 0) printf("dado1 = %d", dados[1]);
	if (dados[2] != 0) {
		if (dados[1] != 0) printf(", ");
		printf("dado2 = %d\n", dados[2]);
	}
	else printf("\n");
	printf("\n");
	
}


/**
 * Invoca as funções necessárias para desenha o tebuleiro de jogo
 **/
void show_board() {
	printf("\n");
	
	// casas da parte superior
	show_places();
	
	// separador da parte superior
	show_separator();
	
	// peças nas casas da parte superior
	show_pieces(23, 11);
	
	// zona intermédia entre a parte superior e inferior onde é colocada
	// informação das peças capturadas
	show_bar();
	
	// peças nas casas da parte inferior
	show_pieces(0, 12);
	
	// separador da parte inferior
	show_separator();
	
	// casas da parte inferior
	show_places();
		
	printf("\n");
}


/* funções auxiliares na recolha de valores */

/**
 * Serve para ler o comando a executar no lance
 * Nesta versão só há dois comandos possíveis:
 * // comando libertar peça
 * L 1 | 2 
 * // Comando mover peça
 * M 1 | 2 <lugar(1 a 12)><pos>, onde "pos> pode ser (C)ima ou (B)aixo
 * 
 * O parâmetro "throw" assume os valores 1 ou 2 e serve para indicar
 * se o comando é do primeiro ou do segundo lance da jogada
 *
 * Esta função só recolhe a letra do comando. Os argumentos
 * do comando são recolhidos na função correspondente
 **/
char get_cmd(int throw) {
	char cmd;
	bool success;
	
	do {
		// apresentar sempre o(s) dado(s) a jogar
		show_dices();
		printf("Jogada %d(%s)? ", throw, names[player]);

		scanf("%c", &cmd);
		cmd = toupper(cmd);
		if (! (success = (cmd == 'L' || cmd == 'M'))) {
			error("Comando inválido!");
			clean_line();
		}
	}
	while (!success);
	return cmd;
}

/**
 * Recolhe o valor que indica o dado (1 ou 2) a utilizar no lance 
 * Se houver algum erro retorna 0
 **/
int get_dice() {
	int d;
	int res = scanf("%d", &d);
	if (res == 0 || d > 2 || d < 1) {
		return 0;
	}
	return d;
}


/* comandos */

/**
 * Comando para efetuar a libertação de peça capturada
 * 
 * Recolhe e valida o argumento do comando
 * E aplica a correspondente libertação de peça, se possível.
 * No caso de haver algum erro no valor introduzido ou
 * se a libertação indicada não é possível, a função apresenta
 * a correspondente mensagem de erro e retorna false.
 * Se tudo correr bem retorna true.
 **/
bool free_captured_piece() {
	int c = bar_captured(player);
	if (c ==0) error("O jogador não tem peças capturadas!");
	else {
		int d = get_dice();
		if (d == 0 || dados[d] ==0) {
			error("dado inválido!");
			return false;
		}
		int place = place_home_other(dados[d], player);
		if (!place_is_open(place, player)) {
			error("A casa não está livre!");
			return false;
		}
		// all ok, let's proceed
		 
		bar_remove(player);
		int res = piece_put(place, 1 , player);
		if (res == 1)  // a piece was captured
			bar_put(other);
		// marcar dado como usado
		dados[d] =0;
		return true;
	}
	return false;
}

/**
 * Comando para executar um movimento de peça não capturada
 * 
 * Recolhe e valida os argumentos do movimento
 * E aplica o correspondente movimento, se possível.
 * No caso de haver algum erro nos valores introduzidos ou
 * se o movimento indicado não é possível, a função apresenta
 * a correspondente mensagem de erro e retorna false.
 * Se tudo correr bem retorna true.
 */
bool move_piece() {
	int place;
	char dir;
 
 
	if (bar_captured(player)>0) {
		error("O jogador  tem peças capturadas!");
		return false;
	}
	int d = get_dice();
	if (d == 0 || dados[d] ==0) { 
		error("dado inválido!"); return false; 
	}
	int res = scanf("%d%c", &place, &dir);
	if (res != 2) { error("formato inválido!"); return false; }
	dir = toupper(dir);
	
	if (place < 1 || place > NPLACES/2) error("lugar inválido!");
	else if (dir != 'B' && dir != 'C') error("posição do lugar inválida!");
	else {
		// converter lugar para formato interno
		if (dir == 'B') place = 12 - place; else place = 11 + place;
		// obter casa destino
		int dest;
		if (player == RED) dest = (place + 24 - dados[d]) %24; 
		else dest = (place + dados[d])%24;
		
		if (pieces_at(place, player) ==0) error("A casa origem não tem peças do jogador!");
		else if (!place_is_open(dest, player)) error("A casa destino não está livre!");
		else {
			// all ok, let's proceed
			 
			piece_remove(place, player);
			res = piece_put(dest, 1, player);
			if (res == 1)  // a piece was captured
				bar_put(other);
			// marcar dado como usado
			dados[d] =0;
			return true;
		}
	}
	return false;	
}


/* controle de jogo */

/**
 * A função retorna true se for possivel ao jogador corrente jogar
 * Note que o jogador pode ter ou não peças capturadas
 */
bool check_possible_play() {
	bool canPlay = false;
 
	if (bar_captured(player)) {
		canPlay = bar_any(dados[1], dados[2], player);
	}
	else {
		canPlay = place_any(dados[1], dados[2], player);
	}
	if (!canPlay) {
		printf("\n\n%s não pode jogar. Vai jogar o jogador %s\n\n",
			names[player], names[other]);
	}
	 
	return canPlay;
				
}

/**
 * Esta função executa um dos lances da jogada
 * Neste momento há dois comandos possíveis:
 * L: libertar peça capturada
 * M: movimentar peça
 * No comando L indica-se o dado a aplicar na jogada (1 ou 2)
 * No comando M indica-se o dado(1 ou 2), a casa(1 a 12) e a posição -(C)ima, (B)aixo
 **/
void play_one_dice(int number) {bool success=false;
	do {
		char cmd = get_cmd(number);
		
		switch(cmd) {
			case 'L' : success = free_captured_piece(); break;
			case 'M' : success = move_piece(); break;
			default: break;
		}
		
		clean_line(); // não deixar caracteres no input para a próxima jogada
	}
	while(!success);
}

/**
 * lances correspondente à jogada do jogador corrente
 * Os dados são lançados e, se for possível o lance na jogada,
 * invoca-se a função play_one_dice para realizar esse lance
 **/
void play() {
	// simular o lançamento dos dados
	dados[1] = irand(1, 6);
	dados[2] = irand(1, 6);
	printf("jogador %s lançou dados: ", names[player]);
	show_dices();
	// se possível jogar os dois dados, um de cada vez
	for(int i=1; i <= 2 && check_possible_play(); ++i) {
		 play_one_dice(i);
		 show_board();
	}
	printf("\n\n");

}


/**
 * Ciclo correspondente às jogadas de um jogo
 * Após a chamada ao método "play"  (jogada do jogador corrente)
 * avalia-se a situação de vitória, terminando o jogo nesse caso,
 * ou trocando o jogador.
 */
void game_run() {
	bool end=false;
	show_board();
	do {	
		play();
		if (game_win(player))
			end = true;
		else
			set_player(player == RED ? WHITE: RED);
	}
	while(!end);
	
	printf("\n\nO jogador %s venceu o jogo. Parabéns!\n\n", names[player]);
		
}

 
int main() {
	// iniciar o gerador de números (pseudo) aleatórios
	rand_start();
	
	// começar sempre com jogador branco
	set_player(WHITE);
	
	// iniciar estado do tabuleiro
	game_init();
	
	// jogar
	game_run();
	return 0;
}
