/*
    Não sei se o que eu fiz tá certo porque não sei como testar...mas tentei !
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 40

struct tabela {
    char nomes[MAX][10]; // Lista de nomes com nomes de até 10 caracteres
    int notas;
};


int main() {

    int prox = 0;
    char nomesTemp[MAX][10]; // Lista de nomes com nomes de até 10 caracteres
    int notasTemp[MAX];
    FILE* arq;

    char nomeArq[50];
    scanf("%s", nomeArq);

    //VERIFICA SE HÁ DADOS PRÉ-GRAVADOS
    if( (arq = fopen(nomeArq, "rb")) == NULL ) { //rb = leitura binária
        printf("Arquivo não encontrado...\n");
    }
    else {
        while (!feof(arq)) {
            fscanf(arq, "%[^/]%*c",nomesTemp[prox]); //Não lê nomes que tem espaçamento; deveria ter usado fgets
            fscanf(arq, "%d\n", &notasTemp[prox]);
            prox++;
        }
        fclose(arq);
    }


    struct tabela vetorNomesNotas[MAX];

    for (int i=0; i<MAX; i++) {
        strcpy(vetorNomesNotas[i].nomes, nomesTemp[i]);
        vetorNomesNotas[i].notas = notasTemp[i];
    }

    arq = fopen("sla.txt", "wb");
    if (arq == NULL) {
        printf("errou...\n");
    }
    else {
        int nomesBinarios = 0;
        nomesBinarios = fwrite(vetorNomesNotas, sizeof(struct tabela), MAX, arq);
        if (nomesBinarios < 1) printf("Arquivo vazio...\n");
        fclose(arq);
    }

    return 0;
}
