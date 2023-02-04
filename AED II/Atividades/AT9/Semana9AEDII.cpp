#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int v1;
	int v2;
	int custo;
} REGISTRO_OLD;

typedef struct {
	int v1;
	int v2;
	int nroRegArq;
} REGISTRO_NEW;

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
        REGISTRO_NEW tabela[100];
        REGISTRO_OLD r;

        int i = 0;
        while(1==fread(&r,sizeof(REGISTRO_OLD),1,arq)) {
            tabela[i].v1 = r.v1;
            tabela[i].v2 = r.v2;
            tabela[i].nroRegArq = i;
            i++;
        }
        fclose(arq);
    }

    return 0;
}