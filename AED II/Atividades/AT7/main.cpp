#include <stdio.h>
#include <stdlib.h>

typedef struct aresta {
    struct aresta* prox;
    int v; // v�rtice de destino da aresta
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

VERTICE * criarGrafo (int v) { //Recebe um n� fixo de v�rtices
    VERTICE * g = (VERTICE *) malloc(v*sizeof(VERTICE));
    int i;
    for (i=0; i<v; i++) {
        g[i].inicio = NULL;
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

int main() {
    VERTICE* g = criarGrafo(10); //de 0 a 9

    FILE* arq;
    char nomeArq[50];
    printf("Digite o nome do arquivo que deseja fazer a troca de registros(.txt): ");
    scanf("%s", nomeArq);
    //VERIFICA SE H� DADOS PR�-GRAVADOS
    if( (arq = fopen(nomeArq, "r+")) == NULL ) { //r+ = leitura e escrita
        printf("Arquivo n�o encontrado...\n");
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
