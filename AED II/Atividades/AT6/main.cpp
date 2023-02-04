#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

struct tipo_registro {
    char nrousp[7];
    char nome[20];
    int idade;
    int valido; //1: valido; 0: excluido (invalido)
};

int main() {
    struct tipo_registro alunoAux[2];
    FILE* arq;
    int r1; //byte inicial do registro 1
    int r2; //byte inicial do registro 2

    char nomeArq[50];
    printf("Digite o nome do arquivo que deseja fazer a troca de registros(.txt): ");
    scanf("%s", nomeArq);


    //VERIFICA SE HÁ DADOS PRÉ-GRAVADOS
    if( (arq = fopen(nomeArq, "r+")) == NULL ) { //r+ = leitura e escrita
        printf("Arquivo não encontrado...\n");
    }
    else {

        printf("Digite o byte inicial do registro 1: ");
        scanf("%d", &r1);
        printf("Digite o byte inicial do registro 2: ");
        scanf("%d", &r2);

        //Coloca o ponteiro do arquivo na frente de r2, pega o regitro que tá lá e coloca na posição 0 do vetor de structs
        fseek(arq, r2, SEEK_SET);
        fread(&alunoAux[0], sizeof(tipo_registro),1,arq);
        //Coloca o ponteiro do arquivo na frente de r1, pega o regitro que tá lá e coloca na posição 1 do vetor de structs
        fseek(arq, r1, SEEK_SET);
        fread(&alunoAux[1], sizeof(tipo_registro),1,arq);

        //pega o que tá em alunoAux[0] (registro do r2) e sobrescreve onde tá o r1
        fseek(arq, r1, SEEK_SET);
        fwrite(&alunoAux[0], sizeof(tipo_registro),1,arq);
        //pega o que tá em alunoAux[0] (registro do r1) e sobrescreve onde tá o r2
        fseek(arq, r2, SEEK_SET);
        fwrite(&alunoAux[1], sizeof(tipo_registro),1,arq);

        fclose(arq);
    }

    return 0;

}

