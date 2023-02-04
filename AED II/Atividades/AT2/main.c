#include <stdio.h>
#include <stdlib.h>
#define true 1
#define false 0

typedef struct aresta {
    struct aresta* prox;
    int v; // vértice de destino da aresta
    int peso; // opcional = peso da aresta
} NO;

typedef struct vert {
    NO* inicio;
    int flag; //0 = não visitado; 1 = visitado e tem adjacente não visitado; 2 = visitado e não tem mais adjacente não visitado
    int temChave; //vê se o nó tem chave ou não. True e False definidos como int's logo acima
} VERTICE;

VERTICE * criarGrafo (int v) { //Recebe um nº fixo de vértices
    VERTICE * g = (VERTICE *) malloc(v*sizeof(VERTICE));
    int i;
    for (i=0; i<v; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].temChave = false;
    }
    return (g);
}

NO * criarAdj (int v, int peso) { //Os parâmetros são o vértice final da aresta e o peso dela
    NO * temp = (NO *) malloc(sizeof(NO)); //Aloca espaço para um nó na lista de adjacências (nó = adjacência)
    temp->v = v; //Associa ao nó o vértice final da aresta
    temp->peso = peso; //e seu peso
    temp->prox = NULL; // Campo prox é NULL. O nó atual é tratado como um nó isolado
    return temp; //Retorna o nó
}

//Método que cria uma aresta dirigida. Para uma não-dirigida, basta chamá-lo 2 vezes invertendo v1 e v2
int criaAresta (VERTICE*v, int v1, int v2, int p, int nVertices) { //v: grafo; v1: vértice inicial ; v2: vértice final; p: peso
    if (!v) { return 0; } //testa a existência do grafo
    if ((v1 < 0) || v1 >= nVertices) { return 0; } //testa se o vértice inicial da aresta existe
    if ((v2 < 0) || v2 >= nVertices) { return 0; } //testa se o vértice final da aresta existe
    NO * novo = criarAdj(v2, p); //Cria adjacência com o vértice final
    novo->prox = v[v1].inicio; //Coloca essa adjacência na lista de adjacências do vértice inicial
    v[v1].inicio =  novo; //Coloca essa adjacência na lista de adjacências do vértice inicial
    return 1; //Retorna true
}

void imprime (VERTICE * v, int nVertices) {
    if (!v) {return;} //testando a existência do grafo
    //printf("Vertices: %d. Arestas: %d. \n", gr->nVertices, gr->nArestas); //Mostra-se um cabeçalho geral
    int i;
    for (i = 0; i< nVertices; i++) { //Para cada vértice no grafo:
        printf("v%d: ",i); //Imprimo o nº do vértice
        NO *ad = v[i].inicio;
        while (ad) {
            printf("v%d(%d) ", ad->v, ad->peso); //Imprimo a lista de adjacência do vértice (while inteiro)
            ad = ad->prox;
        }
        printf("\n");
    }
}

//SEMPRE QUE EU QUISER EXTRAIR ALGUMA INFORMAÇÃO, COLOCO NOS PARÂMETROS: tipodafunção * nome da função
// Inicializo ela no main e depois pego a informação retornada por fora
void prof (VERTICE* g, int i) {
    g[i].flag = 1; //vértice i foi descoberto
    NO* p = g[i].inicio;

    while (p) { //Para cada caminho que parte de i em direção a um novo vértice (ainda não descoberto)
        if (g[p->v].flag == 0) //faça uma busca. O par (i, p->v) é a aresta examinada
            prof(g,p->v);
        p = p->prox;
    }
    g[i].flag = 2; //Vértice i é concluído quando todas as arestas que partem dele foram examindas
}

void salasComChaves(VERTICE* g, int i, NO** tchubirubs) { //g : grafo; i: vértice i como ponto de partida; tchubirubs: lista retornada por parâmetro
    if (g[i].temChave == true && g[i].flag == 0) { //Se o vértice tem chave
        NO* aux = (NO*) malloc(sizeof(NO)); //crio nó pra colocar na nova lista
        aux->v = i; //coloco a referência ao vértice q tem chave
        aux->prox = (*tchubirubs); //o próximo da minha lista recebe o inicio de tchubirubs, dando a ideia de que aux é o novo começo
        (*tchubirubs) = aux; //o inicio de ychubirubs é oficialmente o aux
    }
    g[i].flag = 1; //vértice i foi descoberto

    NO* p = g[i].inicio;

    while (p) { //Para cada caminho que parte de i em direção a um novo vértice (ainda não descoberto)
        if (g[p->v].flag == 0) { //faça uma busca. O par (i, p->v) é a aresta examinada
            salasComChaves(g,p->v, tchubirubs);
        }
        p = p->prox;
    }
    g[i].flag = 2; //Vértice i é concluído quando todas as arestas que partem dele foram examinda
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
