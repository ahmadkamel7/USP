//Ahmad Kamel Abdouni
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>


//######### ESCREVA O NROUSP AQUI
char* nroUSP() {
    return("11795825");
}


// ######### ESCREVA SEU NOME AQUI
char* nome() {
    return("Ahmad Kamel Abdouni");
}

// elemento da lista
typedef struct estr {
        int valor;
        struct estr* prox;
} NO;

// Busca pela chave ch na lista (ordem crescente) retornando p e ant
NO* buscaSeqOrd(int ch, NO* p, NO* *ant) {
    NO* p2 = p;
    *ant = NULL;
    while(p2) {
        if(p2->valor >= ch) break;
        *ant = p2;
        p2 = p2->prox;
    }

    if(p2) {
        if(p2->valor == ch) {
            return(p2);
        }
    }
    return(NULL);
}


// Inserção da chave ch na lista ordenada sem duplicações
void inserirNO (NO** p, int ch) {
    NO* novo;
    NO* ant;
    novo = buscaSeqOrd(ch, *p, &ant);
    novo = (NO*) malloc(sizeof(NO));
    novo->valor = ch;

    if(!*p) { // 1a. inserção em lista vazia
        *p = novo;
        novo->prox = NULL;
    }

    else {
        if(!ant) { // inserção no início da lista
            novo->prox = *p;
            *p = novo;
        }

        else { // inserção após um nó existente
            novo->prox = ant->prox;
            ant->prox = novo;
        }
    }
}

// Exibição da lista completa

 /* void exibirLista(NO** p) {
    NO* p2 = *p;
    while (p2) {
        printf("%d ", p2->valor);
        p2 = p2->prox;
    }
}

*/


//exclui elementos repetidos de uma lista
NO* excluirRepetidos (NO* p) {
    NO* aux;
    NO* aux2;

    if (p == NULL) { return NULL; }

    else {
        while (p->prox != NULL) {
            if (p->valor == p->prox->valor) {
                aux = p->prox;
                aux2 = aux->prox;
                free(p->prox);
                p->prox = aux2;
            }

            else {
                p = p->prox;
            }
        }
    }
    return p;
}


//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------

NO* uniao(NO* p1, NO* p2) {
	NO* resp;
	resp = NULL;

	excluirRepetidos(p1);
	excluirRepetidos(p2);

	if (p1 == NULL && p2 != NULL) {resp = p2;}
	if (p2 == NULL && p1 != NULL) {resp = p1;}
	if (p1 == NULL && p2 == NULL) { resp = NULL;}

	else {
	    while (p1) {
            inserirNO (&resp, p1->valor);
            p1 = p1->prox;
	    }

	    while (p2) {
            inserirNO (&resp, p2->valor);
            p2 = p2->prox;
	    }
	}
    excluirRepetidos(resp);
    return resp;
}
//----------------------------------------------------------------
// use main() apenas para fazer chamadas de teste ao seu programa
//----------------------------------------------------------------
int main() {

    // aqui vc pode incluir codigo para inserir elementos
	// de teste nas listas p1 e p2

	// o EP sera testado com chamadas deste tipo
	NO* teste = NULL;
	//teste = uniao(p1,p2);
	//exibirLista(&teste);

	NO* p1 = NULL;
	NO* p2 = NULL;

    // Inserção de elementos na lista p2

    for (int i = 0; i<20; i++) {
        int aux = rand()%50;
        inserirNO (&p1, aux);
    }

    for (int i = 0; i<20; i++) {
        int aux = rand()%50;
        inserirNO (&p2, aux);
    }

    //testes
    printf("Lista 1:\n ");
    //exibirLista(&p1);
    printf("\n");
    printf("Lista 2:\n ");
    //exibirLista(&p2);
    printf("\n");
    printf("Lista 1 sem repeticoes:\n ");
    excluirRepetidos(p1);
    //exibirLista(&p1);
    printf("\n");
    printf("Lista 2 sem repeticoes:\n ");
    excluirRepetidos(p2);
    //exibirLista(&p2);
    printf("\n");
    printf("Listas unidas:\n ");
    NO* t = uniao(p1, p2);
    //exibirLista(&t);
}

// por favor nao inclua nenhum código abaixo da função main()
