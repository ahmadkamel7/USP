//--------------------------------------------------------------//
// NOME : Ahmad Kamel Abdouni                                   //
//--------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 11795825;
}

//-------------------------------------------

// CHLINK eh um par <chave,link> - dentro de cada página há 3 CHLINKs
typedef struct {
	int chave;
	int linkdir;
} CHLINK;

// definicao de pagina da árvore / registro do arquivo
typedef struct {
	int np; // armazene aqui o nro da pagina no arquivo
	int cont; // armazene aqui a quantidade de chaves existentes no vetor CHLINK[]
	CHLINK item[3]; // a chave[0] eh desprezada, e o linkdir[0] eh na verdade o link esquerdo da chave[1]
} PAGINA;


bool buscaExistencia(FILE* arq, char nomearq[], int ch, int*raiz) {  
	if( (arq = fopen(nomearq, "r+b")) == NULL ) { //r+b = leitura e escrita binaria
		fclose(arq); //se o ponteiro de arquivo n apontar pra lugar nenhum só vaza
        return false;
    }
	PAGINA p0; //cria uma pagina auxiliar
    fseek(arq, (*raiz)*sizeof(PAGINA) ,SEEK_SET); //coloca o ponteiro do arquivo onde tá a raiz
	//Enquanto tiver página no arquivo (enquanto não chegar no fim da árvore)
 	while (fread(&p0,sizeof(PAGINA),1,arq) == 1 ) { 

	//Se a chave procurada é igual a 1º ou 2º chave da página, retorna true (já tem o elemento na árvore)
 		if( (p0.cont == 1 && p0.item[1].chave == ch) || (p0.cont == 2 && (p0.item[1].chave == ch || p0.item[2].chave == ch))) {
			return true;
		}
	//Se a chave procurada é menor que a 1º chave, vai pra linkdir[0]
 		if(p0.item[1].chave && ch < p0.item[1].chave) {
 			fseek(arq, (p0.item[0].linkdir)*sizeof(PAGINA),SEEK_SET);
		 }
	//Se há uma segunda chave na pagina e a chave procurada é maior que a 1º chave e menor que a 2º chave, vai pra linkdir[1]
		else if( p0.cont == 2 && (ch > p0.item[1].chave) && (ch < p0.item[2].chave) ) {
 			fseek(arq, (p0.item[1].linkdir)*sizeof(PAGINA),SEEK_SET);
		}
	//Se não há uma segunda chave e a chave procurada é maior que a 1º chave
		else if(p0.cont == 1) {
			if(p0.item[1].chave && (ch > p0.item[1].chave) ) {
				fseek(arq, (p0.item[1].linkdir)*sizeof(PAGINA),SEEK_SET);
			}
		}
	//Se a chave procurada é maior que a 2º chave, vai pra linkdir[2]
		else if(p0.cont == 2 && ch > p0.item[2].chave) {
			fseek(arq, (p0.item[2].linkdir)*sizeof(PAGINA),SEEK_SET);
		}
 	}
	fclose(arq); //fechar o arquivo!
 	return false; //se chegou aqui é porque não tá na árvore...retorna false
} 

int numeroDePaginas (FILE*arq, char nomearq[]) {
    int i = 0;
    PAGINA p;
	fseek(arq, 0*sizeof(PAGINA),SEEK_SET); //coloca o ponteiro de arquivo no começo pra contar do 0
    if (arq) { 
        while (fread(&p,sizeof(PAGINA),1,arq) == 1) {
            i++; //conta o numero de paginas da arvore (numero de paginas contidas no arquivo)
        }
    }
    return i;
}

//se a página só possui 1 nó. Maravilha! Adicione a chave nessa página - FUNCIONA
void InserirChave_FolhaIncompleta (FILE*arq, char nomearq[], PAGINA p, int ch) {

	int numPaginas = numeroDePaginas (arq,nomearq); //numero de paginas!! importante nas próximas linhas

    if(arq) { //se o arquivo existe
        if(p.cont == 1) { //se ele não tá totalmente ocupado
            if(ch < p.item[1].chave) { //se a chave a ser inserida é menor que a chave que já tá
                p.item[2].chave = p.item[1].chave;
                p.item[1].chave = ch; //elas trocam de posição

				//se a página não for uma folha
				if(p.item[0].linkdir != -1 || p.item[1].linkdir != -1 || p.item[2].linkdir != -1) {
					//O linkdir do meio faz referência à segunda página splitada (a com maior chave)
					//A primeira página splitada reaproveita a estrutura e não precisa ser referenciada (coisa de louco)
					//nesse caso é o linkdir do meio pq  como a chave a ser inserida é menor que a que já tava na página, significa que ela veio do linkdir[0]
					p.item[2].linkdir = p.item[1].linkdir; //puxa pra direita o linkdir[1] (ele vai pra linkdir[2])
					p.item[1].linkdir = numPaginas-1;
					/*linkdir[0] intacto, pq é a página reaproveitada do split com a menor chave*/
				}
            }

            else {
                p.item[2].chave = ch; //senão só inserir a chave nova direto na posição 2

				//se a página não for uma folha
				if(p.item[0].linkdir != -1 || p.item[1].linkdir != -1 || p.item[2].linkdir != -1) {
					//O linkdir do meio faz referência à segunda página splitada (a com maior chave)
					//A primeira página splitada reaproveita a estrutura e não precisa ser referenciada (coisa de louco)
					//nesse caso é o segundo linkdir pq como a chave a ser inserida é maior que a que já tava na página, significa que ela veio do linkdir[1]
					p.item[2].linkdir = numPaginas-1;
				} 
            }

            p.cont = 2; //atualiza o contador pra 2 
			/*np permanece inalterado!*/

			fseek(arq, (p.np)*sizeof(PAGINA),SEEK_SET); //coloca o ponteiro de arquivo no local q a folha tá
            fwrite(&p,sizeof(PAGINA),1,arq); //coloca a pagina no arquivo where it should be
        }
    }
}

// bubble sort - FUNCIONA
void bubbleSort (int arr[], int n) {
    for (int i = 0; i < n-1; i++) {     
        for (int j = 0; j < (n-(i+1)); j++) {
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

PAGINA chave_Split (FILE*arq, char nomearq[], PAGINA p, int ch) {
	int aux[3]; //cria um arranjo auxiliar de tamanho 3

	if(arq) { //se o arquivo existir...
		if (p.cont ==2) { //se a pagina já tem 2 nos
			aux[0] = p.item[1].chave; //coloca as 2 chaves da pagina e...
			aux[1] = p.item[2].chave; //...a chave que deseja-se adicionar no arranjo auxiliar
			aux[2] = ch; 
			bubbleSort(aux, 3); //e taca bubble sort neles

			p.item[1].chave = aux[0]; //o menor item ficará na página já existente (será reaproveitada)
			p.cont = 1; //mas agora o contador é 1 ao invés de 2 (o que tiver no 2 ficou com deus)
			/*Como aproveita a pagina ja existente, o np permanece igual*/

			PAGINA direita;  //o maior item fica numa nova pagina
			direita.item[1].chave = aux[2]; //a chave dessa nova página é a maior das 3 chaves
			direita.cont = 1; //o contador é 1 !

			int a = numeroDePaginas (arq, nomearq); //Coloca num inteiro o nº total de paginas que existem no arquivo
			direita.np = a; //O numero da pagina será exatamente equivalente ao nº total de paginas (ja q a chave da raiz originalmente é 0 - ou seja, pagina 1 - nº pagina 0; pagina 2 - nº pagina 1....)

			//se a a pagina (reaproveitada) que sofreu split é uma folha, a página criada que não tem nenhum linkdir vai ter todos os seus virados para -1, porque ela também é uma folha!
			if(p.item[0].linkdir == -1 && p.item[1].linkdir == -1 && p.item[2].linkdir == -1) {
				direita.item[0].linkdir = -1;
				direita.item[1].linkdir = -1;
				direita.item[2].linkdir = -1;
			}

			//se não tiver assim é pq a pagina que ta sofrendo split não é folha eai o rolê é loko (olhar desenho [que eu fiz])
			else {

				//se a chave a ser inserida é a menor das 3, significa que ela veio do linkdir[0] da pagina atual
				if (ch == aux[0]) {
					direita.item[0].linkdir = p.item[1].linkdir; //pega o que já tava na pagina atual (reaproveitada)
					direita.item[1].linkdir = p.item[2].linkdir; //pega o que já tava na pagina atual (reaproveitada)
					direita.item[2].linkdir = -1; //tem ngm

					/*linkdir[0] do p já tá onde deveria*/
					p.item[1].linkdir = a-1; //É A PAGINA COM A MAIOR CHAVE QUE FOI SPLITADA ANTES DA ATUAL!!!
					p.item[2].linkdir = -1; //tem ngm
				}

				//se a chave a ser inserida é a do meio, significa que ela veio do linkdir[1] da pagina atual
				if (ch == aux[1]) {
					direita.item[0].linkdir = a-1; //É A PAGINA COM A MAIOR CHAVE QUE FOI SPLITADA ANTES DA ATUAL!!!
					direita.item[1].linkdir = p.item[2].linkdir; //pega o que já tava na pagina atual (reaproveitada)
					direita.item[2].linkdir = -1; //tem ngm

					/*linkdir[0] do p já tá onde deveria*/
					/*linkdir[1] do p já tá onde deveria*/
					p.item[2].linkdir = -1; //tem ngm
				}

				//se a chave a ser inserida é a maior das 3, significa que ela veio do linkdir[2] da pagina atual
				if(ch == aux[2]) {
					direita.item[0].linkdir = p.item[2].linkdir; //pega o que já tava na pagina atual (reaproveitada)
					direita.item[1].linkdir = a-1; //pega o que já tava na pagina atual (reaproveitada)
					direita.item[2].linkdir = -1; //tem ngm

					/*linkdir[0] do p já tá onde deveria*/
					/*linkdir[1] do p já tá onde deveria*/
					p.item[2].linkdir = -1; //tem ngm

				}
			}		
			
			fseek(arq, (p.np)*sizeof(PAGINA),SEEK_SET); //coloca o ponteiro de arquivo na pagina atual
			fwrite(&p,sizeof(PAGINA),1,arq); //e sobrescreve ela no arquivo do novo jeito que foi dado a ela!
			fseek(arq, a*sizeof(PAGINA),SEEK_SET); //coloca o ponteiro de arquivo nessa nova posição
			fwrite(&direita,sizeof(PAGINA),1,arq); //e escreve a página nela
		}
	}


	PAGINA vaiSubir; //cria uma pagina pra armazenar o valor que vai subir e o endereço da pagina atual
	vaiSubir.item[1].chave = aux[1];
	vaiSubir.item[2].chave = p.np; //serve pra encontrar o pai dela depois (onde aux[1] deverá ser inserido)
    return vaiSubir; //retorna a pagina
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

void inserirDeVerdade (FILE*arq, char nomearq[], int* raiz, int ch, int numWord, int linkEsquerdo) {

	PAGINA atual; //cria uma pagina atual a ser analisada
	fseek(arq, (numWord)*sizeof(PAGINA),SEEK_SET); //coloca o ponteiro de arquivo em cima da pagina que deve ser lida atualmente
	fread(&atual,sizeof(PAGINA),1,arq); //faz a leitura de arquivo e coloca o conteúdo na página atual criada

	//Se a página atual não for uma folha
	if(atual.item[0].linkdir != -1 || atual.item[1].linkdir != -1 || atual.item[2].linkdir != -1) {
        //Se a página atual não tem nenhum linkdir apontando pro linkEsquerdo (se a página atual não é a que eu quero inserir)
        //"se algum dos meus linkdirs aponta pro np da pagina chamada anteriormente nessa chamada da recursão, então eu, pagina, sou pai dessa pagina da recursao anterior"
		if(atual.item[0].linkdir != linkEsquerdo && atual.item[1].linkdir != linkEsquerdo && atual.item[2].linkdir != linkEsquerdo) {

		//Se a chave procurada é menor que a 1º chave, vai pra linkdir[0]
			if(atual.item[1].chave && ch < atual.item[1].chave) {
				inserirDeVerdade (arq,nomearq, raiz, ch, atual.item[0].linkdir, linkEsquerdo);
			}

		//Se a chave procurada é maior que a 1º chave e menor que a 2º chave, vai pra linkdir[1]
			if( atual.cont == 2 && (ch > atual.item[1].chave) && (ch < atual.item[2].chave) ) {
				inserirDeVerdade (arq,nomearq, raiz, ch, atual.item[1].linkdir, linkEsquerdo);
			}
		//Se a chave procurada é maior que a 1º chave e essa é a única chave que a página tem, vai pra linkdir[1]
			if(atual.cont == 1) {
				if(atual.item[1].chave && (ch > atual.item[1].chave) ) {
					inserirDeVerdade (arq,nomearq, raiz, ch, atual.item[1].linkdir, linkEsquerdo);
				}
			}
		//Se a chave procurada é maior que a 2º chave, vai pra linkdir[2]
			if(atual.cont == 2 && ch > atual.item[2].chave) {
				inserirDeVerdade (arq,nomearq, raiz, ch, atual.item[2].linkdir, linkEsquerdo);
			}
			return;
		}
	}

	//Se a pagina tem espaço para ser inserida, MARAVILHA! Vai ser inserida diretamente na pagina (cuidando de todos os linkdir)
	if (atual.cont == 1) {
		InserirChave_FolhaIncompleta(arq, nomearq, atual, ch);
		return;
	}

	//Se a inserção é na pagina raiz...
	if (atual.cont == 2 && atual.np == (*raiz)) {
		// chave_split retorna a pagina que contem a chave que será da nova raiz (a que deveria subir) além de fazer os splits
		PAGINA novaRaizChave = chave_Split (arq,nomearq, atual, ch); 
		//o np da nova pagina raiz será o valor equivalente ao numero total de paginas na arvore
		int novoNPraiz = numeroDePaginas (arq,nomearq); 

		PAGINA umaNovaRaiz;  //a pagina da nova raiz é criada
		umaNovaRaiz.item[1].chave = novaRaizChave.item[1].chave;  //sua chave é a retornada ali em cima pela pagina com a chave

		umaNovaRaiz.cont = 1; //só tem 1 chave -> contador = 1
		umaNovaRaiz.np = novoNPraiz; //o numero da pagina da nova raiz (ja ta explicado ali em cima)

		//sua pagina filha esquerda é a splitada com menor valor, que reaproveita o espaço da pagina atual que se esfarelou!
		umaNovaRaiz.item[0].linkdir = atual.np;
		//sua pagina filha direita é a splitada com maior valor e o np dela é o nº total de paginas antigo (o atual -1)
		umaNovaRaiz.item[1].linkdir = novoNPraiz-1;

		//linkdir[2] não tem nada!!!
		umaNovaRaiz.item[2].linkdir = -1;

		fwrite(&umaNovaRaiz,sizeof(PAGINA),1,arq); //ADICIONA A RAIZ NO ARQUIVO
		(*raiz) = umaNovaRaiz.np; //UMA NOVA RAIZ! 
		return;
	}

	//se n for nenhuma dessas situações, hora dos surtos
	else {
		PAGINA vaiSubir = chave_Split(arq,nomearq, atual, ch); //retorna o metodo do meio e faz os splits maravilhosamente
        //o metodo retorna uma pagina com o valor que deve subir e o numero da pagina atual 
        //quando a chave subir, encontraremos o lugar que ela deve ser inserida com esse np
		inserirDeVerdade (arq,nomearq,raiz, vaiSubir.item[1].chave, *raiz, vaiSubir.item[2].chave); 
        //insere tudo aí, faz a zona e afins
		return;
	}
}


void inserir(char nomearq[], int* raiz, int ch) {
	FILE* arq;
	if( (*raiz) == -1) { //Se o arquivo estiver vazio = se não houver árvore = se árvore for nula
		arq = fopen(nomearq, "wb"); //crie um arquivo e escreva a partir dele...
		PAGINA raizz; //...uma página raiz
		raizz.item[1].chave = ch; //A primeira chave da árvore fica na página raiz na posição 1 

		raizz.item[0].linkdir = -1; //por ser a criação da raiz, ela ainda n possui filhos
		raizz.item[1].linkdir = -1; //todos os linkdir são colocados com null
		raizz.item[2].linkdir = -1; //inclusive esse aqui!

		raizz.cont = 1; // A página possui oficialmente uma chave 
		raizz.np = 0; //Por ser a raiz, atribui-se como 0 o valor da página
		(*raiz) = 0; //atualiza o valor da (*raiz) pra 0
		fwrite(&raizz,sizeof(PAGINA),1,arq); //a página é escrita no arquivo
		fclose(arq); //o arquivo é fechado
	}

	else { //se a raiz n for -1, então o arquivo não tá vazio! Tem uma árvore nele!
		bool temChave = buscaExistencia(arq,nomearq,ch, raiz); //Primeiro verifica-se se a chave já está contida na árvore

		if (!temChave) { //Se não estiver
			arq = fopen(nomearq, "r+b"); //Um arquivo é aberto para leitura e escrita
			if (arq) { //Se ele não apontar pra null
                //aux representa os np's que serão atualizados na recursão
				int aux = *raiz; //por alguma razão criei uma variável local pro que já tava no parâmetro mas blz
				int lixo = 67896789; // lixo é nada por enquanto, mas vai ser na inserção o linkdir da pagina que será filha do pai que a gnt vai estar procurando na recursão (n faz sentido nenhum lendo aqui, melhor ver no metodo lá msm)
				inserirDeVerdade(arq,nomearq,raiz, ch, aux, lixo);  //Chama a função de inserção auxiliar (a faz-tudo)
			}
			fclose(arq); //Depois de inserir, fecha-se o arquivo
		}
	}
}


/*
int main() {
    FILE* arq;
    char c [] = "problemaBusca.txt";
    int raiz = -1;

    inserir(c, &raiz, 1);
	inserir(c, &raiz, 2);
	inserir(c, &raiz, 3);
    inserir(c, &raiz, 4);
    inserir(c, &raiz, 5);
    inserir(c, &raiz, 6);
    inserir(c, &raiz, 7);
    inserir(c, &raiz, 8);
    inserir(c, &raiz, 9);

    arq = fopen(c, "rb");
        PAGINA aux;
		while (fread(&aux, sizeof(PAGINA),1,arq) == 1) {
			if (aux.cont == 1) {
				printf("nPagina: %d  chave1: %d linkdir[0]: %d linkdir[1]: %d linkdir[2]: %d \n", aux.np, aux.item[1].chave, aux.item[0].linkdir, aux.item[1].linkdir, aux.item[2].linkdir);
			}
			if (aux.cont == 2) {
				printf("nPagina: %d  chave1: %d chave2: %d linkdir[0]: %d linkdir[1]: %d linkdir[2]: %d \n", aux.np, aux.item[1].chave, aux.item[2].chave, aux.item[0].linkdir, aux.item[1].linkdir, aux.item[2].linkdir);
			}
		}
	fclose(arq);
    //fclose(arq);

*/