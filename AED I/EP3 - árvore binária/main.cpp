//Ahmad Kamel Abdouni
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// ######### ESCREVA O NROUSP AQUI
const char* nroUSP() {
    return("11795825");
}


// no da arvore
typedef struct estr {
        int chave;
        struct estr *esq;
	struct estr *dir;
} NO;

int menorChave(NO* p) {
    if(!p) { return 99999; }
    int atual = p->chave;
    if (p) {
        int e = menorChave(p->esq);
        int d = menorChave(p->dir);

        if (e < atual) { atual = e; }
        if (d < atual) { atual = d; }
    }
    return atual;
}

int maiorChave(NO* p) {
    if(!p) { return -99999; }
    int atual = p->chave;
    if (p) {
        int e = maiorChave(p->esq);
        int d = maiorChave(p->dir);

        if (e > atual) { atual = e; }
        if (d > atual) { atual = d; }
    }
    return atual;
}

// Procura a chave na arvore inteira usando pré-ordem (usando retorno NO*)
NO* busca_local(NO* p, int ch, bool *achou) {
    NO* aux;
    *achou = false;
    if(!p)
        return(NULL);

    if(p->chave == ch) {
        *achou = true;
        return(p);
    }

    aux = busca_local(p->esq, ch, achou);
    if(*achou)
        return(aux);
    else
        return(busca_local(p->dir, ch, achou));
}

NO* busca(NO* raiz, int ch) {
    bool achou;
    return(busca_local(raiz, ch, &achou));
}

// Retorna o endereço do pai da chave procurada (usando função void)
void travessiap(NO* p, int ch, NO* *no_pai, bool *achou) {
if(p) {
    if(p->esq)
        if(p->esq->chave == ch) {
            *achou = true;
            *no_pai = p;
        }

        if(!*achou)
            if(p->dir)
                if(p->dir->chave == ch) {
                    *achou = true;
                    *no_pai = p;
                }

        if(!*achou)
            travessiap(p->esq, ch, no_pai, achou);
        if(!*achou)
            travessiap(p->dir, ch, no_pai, achou);
    }
}


NO* pai(NO* raiz, int ch) {
    bool achou = false;
    NO* no_pai;
    if(raiz) {
        if(raiz->chave == ch)
            return(NULL);
        else {
            travessiap(raiz, ch, &no_pai, &achou);
            return(no_pai);
        }
    }
}

void raizErrada (NO** raiz) {
    NO* p = *raiz;
    if ((*raiz)->esq) {
        (*raiz) = (*raiz)->esq;
    }

    else if ((*raiz)->dir) {
        (*raiz) = (*raiz)->dir;
    }

    free(p);
}

NO* deletar(NO** q, NO** erradin) {
    NO*p = *q;
    NO* errado = *erradin;

    if (!(p)) { return NULL; }

    else {

        if( ((!errado->esq) || (!errado->dir)) && p == errado) {
                raizErrada(erradin);
                return NULL;
        }

        //Folha
        if(!errado->esq && !errado->dir) {
            NO* daddy = pai(p, errado->chave);

            if (daddy->esq == errado) {
                free(daddy->esq);
                daddy->esq = NULL;
            }

            else {
                free(daddy->dir);
                daddy->dir = NULL;
            }
            return NULL;
        }

        //1 Filho (sem ser raiz)
        else if(errado->esq == NULL || errado->dir == NULL) {
            NO*temp;
            if(errado->esq == NULL)
                temp = errado->dir;
            else
                temp = errado->esq;
            if (p != errado) {
                NO* daddy = pai(p, errado->chave);
                if (daddy->esq == errado) { daddy->esq = temp; }
                else { daddy->dir = temp;  }
                free(errado);
                errado = NULL;
            }
            return temp;
        }

        //2 Filhos
        else {

            int aux = maiorChave(errado->esq);
            NO*temp = busca(errado->esq, aux);

            int aux2 = errado->chave;
            errado->chave = temp->chave;
            temp->chave = aux2;

            NO* daddy = pai(errado, temp->chave);

            if (!temp->esq && !temp->dir) {

                if (daddy->esq == temp) {
                    free (daddy->esq);
                    daddy->esq = NULL;
                }
                else {
                    free (daddy->dir);
                    daddy->dir = NULL;
                }
            }

            else {
                NO* auxx = daddy->esq;
                daddy->esq = temp->esq;
                free(auxx);
            }
        }
    }
    return p;
}

//------------------------------------------
// O EP consiste em implementar esta funcao
//------------------------------------------


void organizar (NO* *raiz) {
    NO* p = *raiz;
    if (!p) { return; }

    else if (p) {
        int maiorEsquerda = maiorChave(p->esq);
        int menorEsquerda = menorChave(p->esq);

        int maiorDireita  = maiorChave(p->dir);
        int menorDireita  = menorChave(p->dir);

        int aux;

        NO* impostor = busca(p->esq, maiorEsquerda);
        NO* malandro = busca(p->dir, menorDireita);

        //erro: raiz
        if (    (maiorDireita != -99999 && p->chave > maiorDireita && p->dir->chave != maiorDireita) ||
                (menorEsquerda != 99999 && p->chave < menorEsquerda && p->esq->chave != menorEsquerda)) {

            if( ((!p->esq) || (!p->dir))) {
                raizErrada(raiz);
                return;
            }
            else {
                deletar(&p,&p);
                return;
            }
        }

        //erro: nó esquerdo
        else if ( maiorEsquerda != -99999 && impostor && maiorEsquerda >=  p->chave && menorEsquerda != 99999) {
            deletar(&p, &impostor);
            return;
        }
        //erro: nó direito
        else if (menorDireita != 99999 && malandro && menorDireita <= p->chave && maiorDireita != -99999) {
            deletar(&p, &malandro);
            return;
        }
    }
    organizar(&(p->esq));
    organizar(&(p->dir));
}

//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {

}
