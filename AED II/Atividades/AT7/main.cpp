#include <stdio.h>
#include <stdlib.h>

typedef struct aresta {
    struct aresta* prox;
    int v; // vértice de destino da aresta
    int peso; // opcional = peso da aresta
} NO;

typedef struct vert {
    NO* inicio;
} VERTICE;

typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO;

VERTICE * criarGrafo (int v) { //Recebe um nº fixo de vértices
    VERTICE * g = (VERTICE *) malloc(v*sizeof(VERTICE));
    int i;
    for (i=0; i<v; i++) {
        g[i].inicio = NULL;
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

int main() {
    VERTICE* g = criarGrafo(10); //de 0 a 9

    FILE* arq;
    char nomeArq[50];
    printf("Digite o nome do arquivo que deseja fazer a troca de registros(.txt): ");
    scanf("%s", nomeArq);
    //VERIFICA SE HÁ DADOS PRÉ-GRAVADOS
    if( (arq = fopen(nomeArq, "r+")) == NULL ) { //r+ = leitura e escrita
        printf("Arquivo não encontrado...\n");
    }

    else {
        REGISTRO arestaGrafo;
        while(1==fread(&arestaGrafo,sizeof(REGISTRO),1,arq)) {
            int partida = arestaGrafo.v1;
            int chegada = arestaGrafo.v2;
            int peso = arestaGrafo.custo;
            criaAresta (g,partida,chegada,peso,10);
        }
        fclose(arq);

    }

    //imprime(g,10);

    return 0;
}
