//Ahmad Kamel Abdouni
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <malloc.h>
#include <string.h>
#include <cstring>

// ######### ESCREVA O NROUSP AQUI
const char* nroUSP() {
    return("11795825");
}


// ######### ESCREVA SEU NOME AQUI
const char* nome() {
    return("Ahmad Kamel Abdouni");
}

// elemento da pilha
typedef struct estrutura {
	struct estrutura *prox;
       	int tipo; // 1=char e 2=float
       	union {
              	char simbolo;
              	float valor;
       	};
} NO;

typedef struct {
    NO* topo;
} PDINAM;

// Inicialização da pilha dinâmica
void inicializarPdinam(PDINAM* p) {
    p->topo = NULL;
}

// Inserir os numeros e caracteres no topo
void pushCharFloat(char mat,  PDINAM* p) {
    NO* novo = (NO*) malloc(sizeof(NO));
    if (mat == '1' || mat == '2' || mat == '3' || mat == '4' || mat == '5' || mat == '6' || mat == '7' || mat == '0' || mat == '8' || mat == '9') {
        novo->tipo = 2;
        //novo->simbolo = NULL;
        float aux = (float)mat - 48.0;
        novo->valor = aux;
        novo->prox = p->topo;
        p->topo = novo;
    }
    else if (mat == ')' || mat == '(' || mat == '-' || mat == '+' || mat == '*' || mat == '/') {
        novo->tipo = 1;
        //novo->valor = NULL;
        novo->simbolo = mat;
        novo->prox = p->topo;
        p->topo = novo;
    }
}

void pushFloat(float ch, PDINAM* p) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->tipo = 2;
    novo->valor = ch;
    novo->prox = p->topo;
    p->topo = novo;
}


// Retirar char ou float do topo
char popChar(PDINAM* p) {
    NO* aux;
    if(!p->topo) return(-1);
    aux = p->topo;
    char ch;
    ch = aux->simbolo;
    p->topo = p->topo->prox;
    free(aux);
    return(ch);
}

float popFloat(PDINAM* p) {
    NO* aux;
    if(!p->topo) return(-1);
    aux = p->topo;
    float ch;
    ch = aux->valor;
    p->topo = p->topo->prox;
    free(aux);
    return(ch);
}

// contas à parte
float continhas(float a, float b, char operador){
    switch(operador){
        case '+': return (a + b);
        case '-': return (a - b);
        case '*': return (a * b);
        case '/': return (a / b);
    }
    return 0;
}

//------------------------------------------//
// O EP consiste em implementar esta funcao //
// e outras funcoes auxiliares que esta     //
// necessitar                               //
//------------------------------------------//

// funcao principal (retorna float e int)
float calcular(char* expressao, int* codigo) {
    float resp = 0.0;
    *codigo = 999;

    PDINAM* pilha = (PDINAM*) malloc(sizeof(PDINAM*));

    if (expressao[0] != '(') {
            *codigo = -1;
            return resp;
    }

    int contador = 0;
    int k =0;
    while (expressao[k]) {
        if (expressao[k] == '(') { contador++; }
        if (expressao[k] == ')') { contador--; }
        k++;
    }
    if (contador != 0) {
        *codigo = -1;
        return resp;
    }

    int i=0;
    while (expressao[i]) {
        if (expressao[i] == ')') {

            float aux; char aux2;float aux3;

            if (pilha->topo->tipo != 2) {
                    *codigo = -1;
                    break;
            }
            else { aux = popFloat(pilha); }
            if (pilha->topo->tipo != 1 && pilha->topo->simbolo != '+' && pilha->topo->simbolo != '-'
                && pilha->topo->simbolo != '*' && pilha->topo->simbolo != '/') {
                    *codigo = -1;
                    break;
            }
            else { aux2 = popChar(pilha); }
            if (pilha->topo->tipo != 2) {
                    *codigo = -1;
                    break;
            }
            else { aux3 = popFloat(pilha);}
            if (pilha->topo->tipo != 1 && pilha->topo->simbolo != '(') {
                    *codigo = -1;
                    break;
            }
            else { popChar(pilha); }
            float resultParc;

            if (aux2 == '/') {
                if (aux != 0) { resultParc = continhas(aux3, aux, aux2); }
                if (aux == 0) {
                        *codigo = 0;
                        break;
                }
            }

            else { resultParc = continhas(aux3, aux, aux2); }
            pushFloat(resultParc, pilha);
        }

        else {
            pushCharFloat(expressao[i], pilha);
        }
        i++;
    }

    if (*codigo == 0 || *codigo == -1) { return resp; }

    if (pilha->topo->valor || pilha->topo->valor == 0) {
        resp = pilha->topo->valor;
        *codigo = 1;
    }

    return resp;
}


//----------------------------------------------------------------//
// use main() apenas para fazer chamadas de teste ao seu programa //
//----------------------------------------------------------------//
int main() {
	//o EP sera testado com chamadas deste tipo
    /*
	char exp[200];
	strcpy(exp, "(4/0)");

	int codigo;

	float resp = calcular(exp,&codigo);
	if (codigo == 0) { printf("deu certo \n"); }
	if (codigo == -1) { printf("nossa oq rolou \n"); }
	if (codigo == 1) { printf("nossa oq rolooooooou \n"); }
	if (codigo == 999) { printf("puts \n"); }
	printf("%f", resp);
    */
	//testes();
}
