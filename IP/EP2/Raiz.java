/*********************************************************************/
/**   ACH2001 - Introdução À Programação                            **/
/**   EACH-USP - Primeiro Semestre de 2020                          **/
/**   02 | matutino - Luciano Antonio Digiampietri                  **/
/**                                                                 **/
/**   Segundo Exercício-Programa                                    **/
/**                                                                 **/
/**   Ahmad Kamel Abdouni                  11795825                 **/
/**                                                                 **/
/**   06/05/2020                                                    **/
/*********************************************************************/

/*
	Cáculo para raiz quadrada
*/
public class Raiz {
	/*
		Calcula a raiz quadrada de um valor, com uma determinada
		precisão. Retorna esse valor, ou -1 quando:
		* a < 0
		* epsilon <= 0
		* epsilon >= 1
		
		Ou 0 (zero) quando a = 0
		
		Parâmetro:
			a - valor cuja raiz quadrada será calculada
			epsilon - precisão do cálculo
	*/
	static double modulo (double subtracao) {
		if (subtracao < 0) {
			return (-1 * subtracao);
		}
		
		else {
			return (subtracao);
		}
	}
	/*  Este método foi criado à parte para resolver o valor do módulo |inicio 2 - inicio1| (de acordo com os nomes dados às variáveis 
		no programa) no método raizQuadrada para que assim possamos realizar o cálculo de raiz pela metodologia de Newton. O método fun-
		ciona exatamente da mesma forma que a definição de módulo consta: Se o valor for negativo, retorne o seu oposto (para assim ficar 
		positivo), caso contrário, isto é, se o número for positivo, retorne o mesmo número. Neste caso, o número é representado pela 
		subtração de dois valores.
	*/
	
	static double raizQuadrada(double a, double epsilon) {
		double inicio1 = a / 2.0;
		double inicio2 = (1.0/2.0) * (inicio1 + (a/inicio1));
		/*  O método principal começa com as duas variáveis que dão início no processo de cálculo de raiz a partir da metodologia
			de Newton (dada pelas fórmulas no enunciado do exercício). Elas são vistas pelo método inteiro, justamente para que 
			elas sejam reconhecidas antes de entrarem em qualquer execução de laço e/ou condição. 
		*/
		if (a < 0 || epsilon <= 0 || epsilon >= 1) {
			return (-1);
		}
		/*  Foi aberto um condicional para atender todas as restrições dadas. Neste, em específico, o programa reconhece que deverá 
			retornar o valor -1 caso o parâmetro "a" seja menor que 0, ou caso o parâmetro "epsilon" seja menor ou igual a 0, ou caso o
			parâmetro "epsilon" seja maior ou igual a 1. De fato, o número no qual queremos calcular a raiz não pode ser menor do que zero,
			assim como a precisão do cálculo seria incoerente fora do intervalo ]0,1[.
			
		*/
		else if (a == 0) {
				return (0);
		}
		/*  Caso a primeira condição não seja atendida, nesta segunda condição, o programa retorna automaticamente o valor 0 caso o valor
			do parâmetro "a" também seja 0. 
		*/
		
		else {
			do {
				inicio2 = (1.0/2.0) * (inicio1 + (a/inicio1));
				double inicio3 = (1.0/2.0) * (inicio2 + (a/inicio2));
				inicio1 = inicio3;
			} while (modulo (inicio2 - inicio1) >= epsilon);
			return (inicio2);
		}
			
	}
	/*  Caso nem a primeira e nem a segunda condição sejam atendidas, finalmente, na terceira condição, a metodologia de Newton para o 
		cálculo de raiz quadrada será realizada. O processo de cálculo foi organizado por meio de um "do...while" que executa a variável inicio2
		em função da variável inicio1 com a fórmula dada no enunciado do exercício. Logo em seguida, o mesmo cálculo é feito, mas transformando
		o valor da variável inicio2 em inicio3 (uma nova variável). Depois, a variável inicio1 assume o valor da variável início3, para depois 
		este novo valor de inicio1 ser tranformado em um novo valor de inicio2, e esse processo é repetido *enquanto* |inicio2 - inicio1| >= epsilon, pois
		quando este módulo for menor, assim se ultrapassa o limite da precisão. Vale ressaltar que a variável inicio3 só foi criada para que o valor de inicio1 
		fosse alterado quando retornasse para a variável início2, ou seja, se inicio3 não existisse e fosse feito diretamente "inicio1 = inicio2", ambas as  
		variáveis assumiriam o mesmo valor e, portanto, quando subtraídas, dariam 0 e já cancelariam todo o processo de cálculo da raíz em um único passo. Por
		fim, o método retorna o valor de inicio2 que, no final de todos os cálculos do laço, mostrará em definitivo o valor da raiz de "a"
	*/

	public static void main(String[] args) {
		// escreva seu código (para testes) aqui

		// Exemplo de teste:
		double valor = 2;
		double precisao = 0.001;
		System.out.println("Raiz de : "+valor+" = "+raizQuadrada(valor, precisao));
	}
}
	