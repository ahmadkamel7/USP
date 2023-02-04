#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef struct aresta {
    struct aresta* prox;
    int v; // v�rtice de destino da aresta
    int peso; // opcional = peso da aresta
} NO;

typedef struct vert {
    NO* inicio;
    int flag; //0 = n�o visitado; 1 = visitado e tem adjacente n�o visitado; 2 = visitado e n�o tem mais adjacente n�o visitado
    int temChave; //v� se o n� tem chave ou n�o. True e False definidos como int's logo acima
} VERTICE;

VERTICE * criarGrafo (int v) { //Recebe um n� fixo de v�rtices
    VERTICE * g = (VERTICE *) malloc(v*sizeof(VERTICE));
    int i;
    for (i=0; i<v; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].temChave = false;
    }
    return (g);
}

NO * criarAdj (int v, int peso) { //Os par�metros s�o o v�rtice final da aresta e o peso dela
    NO * temp = (NO *) malloc(sizeof(NO)); //Aloca espa�o para um n� na lista de adjac�ncias (n� = adjac�ncia)
    temp->v = v; //Associa ao n� o v�rtice final da aresta
    temp->peso = peso; //e seu peso
    temp->prox = NULL; // Campo prox � NULL. O n� atual � tratado como um n� isolado
    return temp; //Retorna o n�
}

//M�todo que cria uma aresta dirigida. Para uma n�o-dirigida, basta cham�-lo 2 vezes invertendo v1 e v2
int criaAresta (VERTICE*v, int v1, int v2, int p, int nVertices) { //v: grafo; v1: v�rtice inicial ; v2: v�rtice final; p: peso
    if (!v) { return 0; } //testa a exist�ncia do grafo
    if ((v1 < 0) || v1 >= nVertices) { return 0; } //testa se o v�rtice inicial da aresta existe
    if ((v2 < 0) || v2 >= nVertices) { return 0; } //testa se o v�rtice final da aresta existe
    NO * novo = criarAdj(v2, p); //Cria adjac�ncia com o v�rtice final
    novo->prox = v[v1].inicio; //Coloca essa adjac�ncia na lista de adjac�ncias do v�rtice inicial
    v[v1].inicio =  novo; //Coloca essa adjac�ncia na lista de adjac�ncias do v�rtice inicial
    return 1; //Retorna true
}

void imprime (VERTICE * v, int nVertices) {
    if (!v) {return;} //testando a exist�ncia do grafo
    //printf("Vertices: %d. Arestas: %d. \n", gr->nVertices, gr->nArestas); //Mostra-se um cabe�alho geral
    int i;
    for (i = 0; i< nVertices; i++) { //Para cada v�rtice no grafo:
        printf("v%d: ",i); //Imprimo o n� do v�rtice
        NO *ad = v[i].inicio;
        while (ad) {
            printf("v%d(%d) ", ad->v, ad->peso); //Imprimo a lista de adjac�ncia do v�rtice (while inteiro)
            ad = ad->prox;
        }
        printf("\n");
    }
}

//SEMPRE QUE EU QUISER EXTRAIR ALGUMA INFORMA��O, COLOCO NOS PAR�METROS: tipodafun��o * nome da fun��o
// Inicializo ela no main e depois pego a informa��o retornada por fora
void prof (VERTICE* g, int i) {
    g[i].flag = 1; //v�rtice i foi descoberto
    NO* p = g[i].inicio;

    while (p) { //Para cada caminho que parte de i em dire��o a um novo v�rtice (ainda n�o descoberto)
        if (g[p->v].flag == 0) //fa�a uma busca. O par (i, p->v) � a aresta examinada
            prof(g,p->v);
        p = p->prox;
    }
    g[i].flag = 2; //V�rtice i � conclu�do quando todas as arestas que partem dele foram examindas
}

void salasComChaves(VERTICE* g, int i, NO** tchubirubs) { //g : grafo; i: v�rtice i como ponto de partida; tchubirubs: lista retornada por par�metro
    if (g[i].temChave == true && g[i].flag == 0) { //Se o v�rtice tem chave
        NO* aux = (NO*) malloc(sizeof(NO)); //crio n� pra colocar na nova lista
        aux->v = i; //coloco a refer�ncia ao v�rtice q tem chave
        aux->prox = (*tchubirubs); //o pr�ximo da minha lista recebe o inicio de tchubirubs, dando a ideia de que aux � o novo come�o
        (*tchubirubs) = aux; //o inicio de ychubirubs � oficialmente o aux
    }
    g[i].flag = 1; //v�rtice i foi descoberto

    NO* p = g[i].inicio;

    while (p) { //Para cada caminho que parte de i em dire��o a um novo v�rtice (ainda n�o descoberto)
        if (g[p->v].flag == 0) { //fa�a uma busca. O par (i, p->v) � a aresta examinada
            salasComChaves(g,p->v, tchubirubs);
        }
        p = p->prox;
    }
    g[i].flag = 2; //V�rtice i � conclu�do quando todas as arestas que partem dele foram examinda
}

int main() {
    /*
    VERTICE *gr = criarGrafo(5);
    criaAresta(gr,0,1,2,5);
    criaAresta(gr,1,2,4,5);
    criaAresta(gr,2,0,12,5);
    criaAresta(gr,2,4,40,5);
    criaAresta(gr,3,1,3,5);
    criaAresta(gr,4,3,8,5);
    imprime(gr, 5);

    printf("\n");

    for (int i=0; i<5; i++) {
        if (i%2 == 0)
            gr[i].temChave = true;
        else
            gr[i].temChave = false;
    }

    NO* teste = NULL;
    salasComChaves(gr,4,&teste);

    while (teste) {
        printf("%d ", teste->v);
        teste = teste->prox;
    }
    */

    return 0;
}
