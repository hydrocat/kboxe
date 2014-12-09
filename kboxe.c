#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//struct que define os movimentos
//*movimentos: aponta para um vetor que 
//contenha os valores dos movimentos.
//
//pontos: e a qtd de pontos do determinado
//jogador.
struct player{
	int *movimentos;
	int score;
};

//converte um movimento para um numero
//ga = 0, gb = 1
//da = 2, db = 3
int mov2num( char movimento[] ){
	if( strcmp( movimento, "ga") == 0 ){
		return 0;
	}else{
	if( strcmp( movimento, "gb") == 0){
		return 1;
	}else{
	if( strcmp( movimento, "da") == 0){
		return 2;
	}else{
	if( strcmp( movimento, "db") == 0){
		return 3;
	}else{
		return -1;
	}	
	}	
	}	
	}
}


//Checa se os argumentos tem um formato correto
//e imprime o help do jogo.
void argCheck( int argc, char argv[] ){
	if( argc == 1 ){
		printf("Faca movimentos !\n");
		printf("Utilize '-h' como paramentro para saber mais\n");
		exit(0);
	}else{
		if( argc == 2 && strcmp( argv, "-h" ) == 0 ){
		printf("Movimentos :\n");
		printf("Golpe:\n");
		printf("alto = ga, baixo = gb\n");
		printf("Defesa:\n");
		printf("alta = da, baixa = db\n");
		printf("\nExemplo :\n");
		printf("kboxe ga gb da\n");
		printf("O jogador fara um golpe alto, um baixo\n");
		printf("e uma defesa alta.\n");
		exit(0);
		}
	}
}

//Recebe a lista de movimentos e transforma num vetor com os codigos
//dos movimentos.
//Caso o movimento seja invalido, cancela a execucao do jogo.
int * mov2vet( char *mov[], int size ){

	int * movimentos = malloc( size * sizeof( int ) );

	int acao;
	int i=1;
	for(; i<=size; i++){


		acao = mov2num( mov[i] );

		if( acao == -1 ){
			printf("%s eh um movimento invalido\n",mov[i]);
			printf("kboxe -h para ajuda\n");
			exit(0);
		}else{
			movimentos[i] = acao;
		}
	}
return movimentos;
}

//Gera um vetor com movimentos aleatorios para o joador CPU.
int * fzMov( int size ){

	int *mov = malloc( size * sizeof( int ) );
	
	int i=0;
	for(; i<size; i++){
		//gera um numero de 0 ate 3.
		mov[i] = rand() % 3;
	}
return mov;
}

//Da os devidos pontos ao devido jogador de acordo com as 
//heuristicas de pontos do jogo.
//ga = 0, gb = 1
//da = 2, db = 3
void score( int mov1, int mov2, int *score1, int *score2 ){

	//se ambos movimentos sao do mesmo ataque, 
	//cada jogador ganha 1 pt.
	if( mov1 == mov2 ){
	
	//debug
	//printf("Movimentos iguais\n");
	//endDebug

		if( mov1 == 0 || mov1 == 1){

			//debug
			//printf("Movimentos de ataque iguais\n");
			//endDebug

			(*score1)++;
			(*score2)++;
		}
		//se ambos movimentos forem defesas,
		//niguem ganha nada.
	}
	
	//se o golpe for alto com a guarda baixa, a pontuacao e de 4 pt.
	if( mov1 == 0 || mov2 == 0 ){
	
		//debug
		//printf("Movimentos ga\n");
		//endDebug

		if( mov1 == 3 ){
			(*score2) += 4;

			//debug
			//printf("Jogador teve a guarda baixa \n");
			//endDebug
		}else{
	
		if( mov2 == 3 ){
			(*score1) += 4;
			//debug
			//printf("CPU teve a guarda baixa \n");
			//endDebug
		}
		}
	}

	
	//se o golpe for baixo, adiciona 2 pontos.
	//gb + da ou gb + ga
	if( mov1 == 1 || mov2 == 1 ){

		//debug
		//printf("Movimento de golpe baixo \n");
		//endDebug

		if( mov1 == 0 || mov1 == 2 ){
			(*score2) += 2;

			//debug
			//printf("CPU acertou o GB \n");
			//endDebug
		}else{

		if( mov2 == 0 || mov2 == 2 ){
			(*score1) += 2;
			//debug
			//printf("Jogador acertou o GB \n");
			//endDebug
		}
		}
	}
	
	//se for uma defesa bem sucedida, adiciona 1 ponto.
	if( mov1 == 2 && mov2 == 0 ){
			(*score1)++;
			//debug
			//printf("Jogador defendeu um GA \n");
			//endDebug
	}else{
	if( mov1 == 3 && mov2 == 1 ){
			(*score1)++;
			//debug
			//printf("Jogador defendeu um GB \n");
			//endDebug
	}else{
	if( mov1 == 0 && mov2 == 2 ){
			(*score2)++;
			//debug
			//printf("CPU defendeu um GA \n");
			//endDebug
	}else{
	if( mov1 == 1 && mov2 == 3 ){
			(*score2)++;
			//debug
			//printf("CPU defendeu um GB \n");
			//endDebug
	}

	}	

	}	

	}
}

//transforma um numero de volta para a string do movimento.
//0 = ga, 1 = gb
//2 = da, 3 = db
char * num2mov( int movimento ){
	switch( movimento ){
		case 0:
			return "ga";
			break;
		case 1:
			return "gb";
			break;
		case 2:
			return "da";
			break;
		case 3:
			return "db";
			break;
		default:
			return "Movimento Indefinido";
			break;
		}
}

//Escreve na tela a sequencia de movimentos do jogador
//e do CPU e os pontos de cada um.
void printPlacar( struct player jogador, struct player cpu, int rounds ){
	int i=0;
	printf("+-----------------+\n");
	printf("|Jogador x     CPU|\n");
	printf("+-----------------+\n");
	for(; i<rounds ;i++){

		char acao1[2];
		char acao2[2];
		strcpy( acao1, num2mov( jogador.movimentos	[i+1] ) );
		strcpy( acao2, num2mov( cpu.movimentos		[i+1] ) );

		printf("|%s	 x	%s|\n",acao1, acao2);
	}

	printf("+-----------------+\n");
	printf("|%d       x       %d|\n", jogador.score, cpu.score);
	printf("+-----------------+\n");
	
	if(jogador.score > cpu.score){
		printf("+  Voce Ganhou !  +\n");
	}else{
	
	if(cpu.score > jogador.score){
		printf("+  Voce Perdeu !  +\n");
	}else{
		printf("+    Empatou !    +\n");
	}
	}	

	printf("+-----------------+\n");
}	

//faz a comparacao entre os movimentos do jogador e do CPU
//e finaliza o programa dando o vencedor.
void fight( struct player *jogador, struct player *cpu, int rounds ){
	
	int i=0;
	for(; i<rounds ;i++){
		score( jogador->movimentos[i+1], cpu->movimentos[i+1], 
			&jogador->score, &cpu->score );
	}
}

//Main ;)
int main( int argc, char *argv[] ){

	//checando caso o argumento seja -h
	//ou, nao haja argumentos.
	argCheck( argc, argv[1]);

	//inicializando o srand para fazer os
	//movimentos do jogador CPU.
	srand( time(NULL) );

	//iniciando ambos jogadores.
	struct player jogador;
	struct player cpu;
	
	jogador.movimentos 	= mov2vet( argv, argc-1);
	cpu.movimentos 		= fzMov  ( argc-1 );

	jogador.score 	= 0;
	cpu.score	= 0; 

	//Get Ready, Fight !
	fight( &jogador, &cpu , argc-1);

	//imprime o placar comparando os movimentos
	printPlacar( jogador, cpu, argc-1 );

return 0;
}
