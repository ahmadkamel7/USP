//--------------------------------------------------------------//
// NOME : Ahmad Kamel Abdouni                                   //
//--------------------------------------------------------------//

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>

// ######### ESCREVA O NROUSP AQUI
int nroUSP() {
    return 11795825;
}

//-------------------------------------------

// nos das listas de adjacencias
typedef struct adj {
	int v;
	struct adj* prox;
} NO;

// vertices
typedef struct {
	NO* inicio;
} VERTICE;

VERTICE * criarGrafo (int v) { //Recebe um n� fixo de v�rtices
    VERTICE * g = (VERTICE *) malloc(v*sizeof(VERTICE));
    int i;
    for (i=0; i<v; i++) {
        g[i].inicio = NULL;
    }
    return (g);
}

NO * criarAdj (int v) { //Os par�metros s�o o v�rtice final da aresta e o peso dela
    NO * temp = (NO *) malloc(sizeof(NO)); //Aloca espa�o para um n� na lista de adjac�ncias (n� = adjac�ncia)
    temp->v = v; //Associa ao n� o v�rtice final da aresta
    temp->prox = NULL; // Campo prox � NULL. O n� atual � tratado como um n� isolado
    return temp; //Retorna o n�
}

//M�todo que cria uma aresta dirigida. Para uma n�o-dirigida, basta cham�-lo 2 vezes invertendo v1 e v2
int criaAresta (VERTICE*v, int v1, int v2, int nVertices) { //v: grafo; v1: v�rtice inicial ; v2: v�rtice final; p: peso
    if (!v) { return 0; } //testa a exist�ncia do grafo
    if ((v1 < 0) || v1 >= nVertices) { return 0; } //testa se o v�rtice inicial da aresta existe
    if ((v2 < 0) || v2 >= nVertices) { return 0; } //testa se o v�rtice final da aresta existe
    NO * novo = criarAdj(v2); //Cria adjac�ncia com o v�rtice final
    novo->prox = v[v1].inicio; //Coloca essa adjac�ncia na lista de adjac�ncias do v�rtice inicial
    v[v1].inicio =  novo; //Coloca essa adjac�ncia na lista de adjac�ncias do v�rtice inicial
    return 1; //Retorna true
}

//M�todo para Inserir elemento no >FINAL< da lista. M�todo auxiliar pra lista que ser� a resposta (j� testado e funciona!)
void inserirElemLista(int ch, NO** l) {
    //cria um novo n�
    NO* novo = (NO*) malloc(sizeof(NO*));
    novo->v = ch;
    novo->prox = NULL;
    //se o inicio da lista � NULL, a lista est� vazia e, ent�o, o n� novo � o inicio
    if((*l) == NULL) {(*l) = novo;}
    //Sen�o, procuramos o ultimo n� e fazemos o n� novo ser adicionado depois dele
    else {
        NO* ultimo = (*l);
        while(ultimo->prox != NULL) {
            ultimo = ultimo->prox;
        }
        ultimo->prox = novo;
    }
}

void excluirElemLista(NO**l) {
  if((*l) != NULL) {

    if((*l)->prox == NULL) {
      (*l) = NULL;
    }
    else {
      NO* temp = (*l);
      while(temp->prox->prox != NULL)
        temp = temp->prox;

      NO* ultimo = temp->prox;
      temp->prox = NULL;
      free(ultimo);
    }
  }
}

//M�todo para saber se o caminho atual (uma lista) tem o tamanho permitido.
//M�todo auxiliar pra lista que ser� a resposta (j� testado e funciona!)
bool ignorarCaminhoMaiorDoQueDeveriaSer (NO** l, int tamanhoPermitido) {
    NO*p = (*l);
    int contador = -1;
    if(!p || tamanhoPermitido < 1) { return false; }
    else {
        while(p) {
            contador++;
            p = p->prox;
        }
    }
    if (contador > tamanhoPermitido) { return false; }
    return true;
}

void juntarListas (NO** w1, NO** w2) { //incorpora a lista w2 na lista w1

    NO* nav = (*w2);
    while(nav){
        inserirElemLista(nav->v, w1);
        nav = nav->prox;
    }
}

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------


void fazTudo(VERTICE* g, NO** l, NO** resp, int x1, int x2, int d, bool visitou []) {
    visitou[x1] = true;

    if (x1 == x2) {
        bool hey = ignorarCaminhoMaiorDoQueDeveriaSer (l, d); //v� se o caminho atual tem tamanho dentro do aceit�vel
        if(hey) { //se tiver tamanho aceit�vel
            juntarListas (resp, l); //adiciona a lista do caminho atual na lista de respostas
        }
        visitou[x1] = false;
       return;
    }

    NO* p = g[x1].inicio;
    while (p) {
        int temp = p->v;
        if ( visitou[temp] == false)  {
            inserirElemLista(temp,l);
            fazTudo(g,l,resp,temp,x2,d, visitou);
            excluirElemLista(l);
        }
        p = p->prox;
    }
     visitou[x1] = false;
}


NO* caminhos_max_d(VERTICE* g, int n, int x, int y, int d) {
    if (!g || n < 0 || x < 1 || y > n || d < 1) { return NULL; }
    NO* resp = NULL;
    NO* caminhoAtual = NULL;
    inserirElemLista(x,&caminhoAtual);

    bool visitou[n+1];
    for (int i=0; i<n+1; i++) {
        visitou[i] = false;
    }

    fazTudo(g, &caminhoAtual,&resp, x, y, d, visitou);
    return resp;
}


//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
// mas nao entregue o codido de main() nem inclua nada
// abaixo deste ponto
//---------------------------------------------------------

int main() {
    /*
    //if nroUSP()==0 printf("\n\nNro USP nao informado!!!\n\n");

	VERTICE *gr = criarGrafo(6);
    criaAresta(gr,1,2,6);
    criaAresta(gr,2,3,6);
    criaAresta(gr,3,1,6);
    criaAresta(gr,3,5,6);
    criaAresta(gr,4,2,6);
    criaAresta(gr,4,3,6);
    criaAresta(gr,5,4,6);
    criaAresta(gr,4,5,6);
    //imprime(gr, 5);

    //VERTICE* g = NULL;

    NO* fim = caminhos_max_d(gr, 6, 4, 5, 1);
    printf("\n");
    while (fim) {
        printf("%d ", fim->v);
        fim = fim->prox;
    }
    */
}
