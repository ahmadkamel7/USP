/*********************************************************************/
/**   ACH2001 - Introdução À Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2020                          **/
/**   02 | matutino - Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   Primeiro Exercício-Programa                                   **/
/**                                                                 **/
/**   Ahmad Kamel Abdouni                  11795825                 **/
/**                                                                 **/
/**   15/04/2020                                                    **/
/*********************************************************************/

/*
	Caixa eletrônico das Ilhas Weblands, com estoque ilimitado de cédulas
	de B$50,00, B$10,00, B$5,00 e B$1,00.
*/
public class CaixaEletronico {
	// Número de cédulas de B$50,00
	static int n50;
	
	// Número de cédulas de B$10,00
	static int n10;

	// Número de cédulas de B$5,00
	static int n5;
	
	// Número de cédulas de B$1,00
	static int n1;
	
	/*
		Método:
			Determina a quantidade de cada nota necessária para totalizar
			um determinado valor de retirada, de modo a minimizar a quantidade
			de cédulas entregues.
		
			Abastece as variáveis globais n50,n10, n5 e n1 com seu respectivo
			número de cédulas.
		
		Parâmetro:
			valor - O valor a ser retirado
	*/
	static void fazRetirada(int valor) {
		/*
			1 - Logo de início, por meio de uma condição, o método avalia se o parâmetro "valor" é positivo ou não. Caso ele seja positivo (>0), cada 
			variável (representando o número de notas respectivo ao número indicado no nome da varável) é executada normalmente como o esperado e,
			caso contrário, todas reservam o valor -1.
			
			2 - Dentro da condição de valores positivos (a esperada), cada variável funciona de uma forma diferente:
			
				2.1 - a variável "n50" recebe a quantia estipulada no parâmetro "valor" e a divide por 50, ficando apenas com a parte inteira da divisão,
				já que é uma variável inteira e, portanto, só armazena valores inteiros. Assim, o resultado dessa divisão mostra exatamente o número máximo 
				de cédulas de 50 reais
				
				2.2 - A variável "n10" funciona da seguinte forma: ela recebe a quantia integral do parâmetro "valor", subtrai dessa quantia o valor já 
				utilizado pela variável "n50" para calcular o número de notas de 50 (número esse representado por "50 * n50") e só então, a partir do
				resultado da subtração, faz-se a divisão por 10, ficando apenas com a parte inteira. Dessa forma, a variável consegue estipular quantas
				 notas de 10 são necesárias a partir do dinheiro restante (isto é, desconsiderando a quantia já utilizada na variável "n50").
				
				2.3 - A variável "n5" de forma similar à "n10": ela recebe a quantia integral do parâmetro "valor", subtrai dessa quantia o valor já 
				utilizado pela variável "n50" para calcular o número de notas de 50 (número esse representado por "50 * n50") e também o valor já
				utilizado pela variável "n10" para calcular o número de notas de 10 (número esse representado por "10 * n10") e só então, a partir do
				resultado da subtração, faz-se a divisão por 5, ficando apenas com a parte inteira. Dessa forma, a variável consegue estipular quantas
			    notas de 5 são necesárias a partir do dinheiro restante (isto é, desconsiderando a quantia já utilizada nas variáveis "n50" e "n10").
				
				2.4 - Por fim, a variável "n1" armazena o valor restante inutilizado pela variável n5 na divisão para encontrar o número de notas de 5. Por 
				ser uma divisão que só capta valores inteiros (pois as variáveis são inteiras), o restante da divisão por 5 (explicitado pelo uso de "%") fica 
				a cargo da variável "n1", sendo o resto da divisão exatamente o número de notas de 1 que existirão.
			
			3 - Por se tratar de um método "void", não há retorno. Portanto, após definidas as variáveis desejadas, o método está encerrado.
		*/
		if (valor > 0) {
			n50 = valor / 50;
			n10 = (valor - (50 * n50)) / 10;
			n5 = (valor - (50 * n50) - (10 * n10)) / 5;
			n1 = (valor - (50 * n50) - (10 * n10)) % 5;
		}
		else {
			n50 = -1;
			n10 = -1;
			n5 = -1;
			n1 = -1;
		}
	}
	public static void main(String[] args) {
		// método meramente criado para fins de teste favor não julgar :-)
		fazRetirada(28);
		System.out.println("Notas de 50: "+n50);
		System.out.println("Notas de 10: "+n10);
		System.out.println("Notas de 5:  "+n5);
		System.out.println("Notas de 1:  "+n1);
	}
}