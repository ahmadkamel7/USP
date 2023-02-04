#include <iostream>
#include <stdio.h>
#include <string.h>
using namespace std;


bool procuraPalavra (FILE *f, char procurado[]) {
    char x[1024]; //tamanho máximo da palavra
    while (fscanf(f, "%s", x) == 1) {
        int valor = strcmp(x,procurado); //compara se as strings são iguais. Retorna 0 se forem e qq outro inteiro se n forem
        if(valor==0)
            return true;
    }
    return false;
}

int main() {
    FILE *arq;
    char nomeArq[10000];
    printf("Digite o nome do arquivo (com .txt): ");
    scanf("%s", nomeArq);

    arq = fopen(nomeArq, "r");
    if (arq == NULL){
        printf("Arquivo %s nao encontrado...",nomeArq);
        printf("\n");
        return 1;
    }

    else {
        char procurado[10000];
        printf("Digite a palavra que procura: ");
        scanf("%s", procurado);
        bool eai = procuraPalavra (arq, procurado);
        if (eai) { printf("true"); }
        if (!eai) { printf("false"); }
        printf("\n");
    }
    fclose(arq);
    return 0;
}
