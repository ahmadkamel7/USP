/*********************************************************************/
/**   ACH2001 - Introdução à Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2020                          **/
/**   02 | matutino - Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   Terceiro Exercício-Programa                                   **/
/**                                                                 **/
/**   Ahmad Kamel Abdouni                   11795825          		**/
/**                                                                 **/
/**   01/06/2020                                             		**/
/*********************************************************************/

/*
	Jogo da Velha - programa para verificar o status de um jogo.
	
	Lista de Status calculado:
    0 - Jogo não iniciado: o tabuleiro está 'vazio', isto é sem peças X e O;
    1 - Jogo encerrado1: o primeiro jogador (que usa as peças X) é o ganhador;
    2 - Jogo encerrado2: o segundo jogador (que usa as peças O) é o ganhador;
    3 - Jogo encerrado3: empate - todas as casas do tabuleiro estão preenchidas com X e O, mas nenhum dos jogadores ganhou;
    4 - Jogo já iniciado e em andamento: nenhuma das alternativas anteriores.	
*/


public class JogoDaVelha {
	static final char pecaX = 'X';
	static final char pecaY = 'O';
	static final char espacoVazio = ' ';
	
	static int ganhadorXouO (char[][] vencedorXouO, char letraXouO, int numVencedor) {
		int statusDoGanhador = -1;
		for (int i = 0; i < vencedorXouO.length; i++) {
			for (int j = 0; j < vencedorXouO[0].length; j++) {
				if (vencedorXouO[i][0] == letraXouO && vencedorXouO[i][1] == letraXouO && vencedorXouO[i][2] == letraXouO) { statusDoGanhador = numVencedor; }
				if (vencedorXouO[0][j] == letraXouO && vencedorXouO[1][j] == letraXouO && vencedorXouO[2][j] == letraXouO) { statusDoGanhador = numVencedor; }
				if (vencedorXouO[0][0] == letraXouO && vencedorXouO[1][1] == letraXouO && vencedorXouO[2][2] == letraXouO) { statusDoGanhador = numVencedor; }
				if (vencedorXouO[0][2] == letraXouO && vencedorXouO[1][1] == letraXouO && vencedorXouO[2][0] == letraXouO) { statusDoGanhador = numVencedor; }
			}
		}
		return (statusDoGanhador);
	}
	
	/*
		O método extra "ganhadorXouO" funciona com o propósito de descobrir se uma pessoa foi vencedora no jogo da velha. Para isso, o método percorre por 
		todos os elementos do arranjo que compõe o jogo da velha (a partir do uso combinado de for's) e percebe se há um padrão de três caracteres iguais 
		na mesma coluna ou na mesma linha (a partir dos dois primeiros if's) ou na mesma diagonal (a partir dos dois últimos if's). Esses "três caracteres
		iguais" seriam ou a letra "X" ou a letra "O" e todo o direcionamento para elas, respeitando a ordem de inicio do jogo, será planejado colocado em
		prática no método-chave deste EP ("verificaStatus")
	*/

	static int verificaStatus(char[][] tabuleiro) {
		int status = -1; 
		//valor padrão -1 para inicializar a variável interna que, ao decorrer do método, receberá novos valores conforme o orientado pelo jogo da velha
		
		status = ganhadorXouO (tabuleiro, pecaX, 1);
		if (status == -1) { status = ganhadorXouO (tabuleiro, pecaY, 2);}
		/* 
			Na linha 54, a variável status recebe um novo valor baseado na possível vitória do jogador X, que inicia jogando. Ela recebe o valor -1 nova-
			mente caso o jogador X não tenha ganhado (se ele não ganha, o método "vencedorXouO" retorna -1), e caso ele ganhe, recebe o valor 1, que
			representa o código que atribui vitoria para o jogador X.
			
			Considerando a derrota do jogador do X, a variável status recebe o valor -1 e o método verificaStatus continua rodanddo. Dessa vez, com o 
			mesmo procedimento do jogador X, haverá a verificação da suposta vitória do jogador O. Caso ele ganhe, status recebe o valor 2 - que representa
			o código que atribui vitória ao jogador O - e caso ele perca, novamente status recebe o valor -1 e o método "verificaStatus" continua rodando
			
		*/
		
		int contador = 0;
		for (int i = 0; i < tabuleiro.length; i++) {
			for (int j = 0; j < tabuleiro[0].length; j++) {
				if (tabuleiro[i][j] == espacoVazio) { contador += 1; }
			}	
		}
		
		if (contador == 9) { status = 0; }
		if (contador == 0 && status != 1 && status != 2) { status = 3; }
		if (contador != 0 && contador != 9 && status != 1 && status != 2) { status = 4; }
		/*
			Foi criada uma variável inteira ("contador") para contabilizar o número de casas vazias do tabuleiro. Para isso, foi criada uma combinação
			de for's para percorrer o tabuleiro inteiro e, a cada espaço vazio encontrado, a variável contador (inicializada com 0) recebe 1 unidade.
			
			No final desse processo, o programa prossegue com mais 3 condições:
			
			A partir do novo valor de contador, se ele carrega consigo o valor 9, signfica que há 9 casas vazias no tabuleiro e, portanto, o jogo
			ainda não começou. Com isso, a partir dessa condição, status recebe o novo valor 0.
			
			Na segunda condição, se o contador continua com o valor 0, significa que não há nenhuma casa vazia no jogo e portanto, ou deu empate, ou
			alguém venceu na última rodada. Para diferenciar os dois casos, a condição prevê que, além de contador ser necessariamente igual a 0, o
			status atual deve ser diferente de 1 e 2, para assim não confundir o tabuleiro completo com os vencedores já previstos no início desse método.
			Assim, respeitando as três condições, significa que houve empate no jogo e, portanto, status recebe o novo valor 3.
			
			Por fim, na última condição, se o contador for diferente de 0 e de 9 (ou seja, se o tabuleiro não estiver nem cheio e nem vazio) e se o status 
			for diferente de 1 e 2 (ou seja, não houve vencedor), significa que o jogo está em andamento e, portanto, recebe o novo valor 4.
		*/
	
		return status;
		/*
			status é retornado para saber a atual conjuntura do jogo da velha.
		*/
	}
	
	/*
		TESTE
	*/
	public static void main(String[] args) {
		char[][] tab0 = {{' ',' ',' '},{' ',' ',' '},{' ',' ',' '}};
		char[][] tab1 = {{'X','X','X'},{'O','O',' '},{' ',' ',' '}};
		char[][] tab2 = {{'O','X','X'},{'X','O','O'},{' ',' ','O'}};
		char[][] tab3 = {{'O','X','X'},{'X','O','O'},{'O','X','X'}};
		char[][] tab4 = {{' ',' ',' '},{'X','O','X'},{' ',' ',' '}};

		System.out.println("Status calculado: " + verificaStatus(tab0));
		System.out.println("Status esperado para o tabuleiro0: 0\n");

		System.out.println("Status calculado: " + verificaStatus(tab1));
		System.out.println("Status esperado para o tabuleiro1: 1\n");

		System.out.println("Status calculado: " + verificaStatus(tab2));
		System.out.println("Status esperado para o tabuleiro2: 2\n");
		
		System.out.println("Status calculado: " + verificaStatus(tab3));
		System.out.println("Status esperado para o tabuleiro1: 3\n");
		
		System.out.println("Status calculado: " + verificaStatus(tab4));
		System.out.println("Status esperado para o tabuleiro4: 4\n");
		

	}
}