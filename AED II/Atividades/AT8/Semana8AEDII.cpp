#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO;

int custoVertice (int v1, int v2, FILE* arq) {
    REGISTRO r;
    while(1==fread(&r,sizeof(REGISTRO),1,arq)) {
        if (r.v1 == v1 && r.v2 == v2) {
            return r.custo;
        }
    }
    return -1;
}

int main() {
    FILE* arq;
    char nomeArq[50];
    printf("Digite o nome do arquivo que deseja fazer a troca de registros(.txt): ");
    scanf("%s", nomeArq);
    //VERIFICA SE HÁ DADOS PRÉ-GRAVADOS
    
    if( (arq = fopen(nomeArq, "r+")) == NULL ) { //r+ = leitura e escrita
        printf("Arquivo nao encontrado...\n");
        fclose(arq);
    }

    else {
        int v1;
        printf("Digite o v1: ");
        scanf("%d", &v1);
        int v2;
        printf("Digite o v2: ");
        scanf("%d", &v2);

        int resp = custoVertice (v1,v2,arq);
        printf("%d ", resp);
        fclose(arq);
    }
    return 0;
}
