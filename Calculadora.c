#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct SNo{
    int digito;
    struct SNo *prox;
    struct SNo *ant;
}No;

No *cria(int n){
    No *aux = (No *)malloc(sizeof(No));
    aux->prox = NULL;
    aux->ant = NULL;
    aux->digito = n;
}


int comprimento(No *n1){
    int r = 0;
    No *aux = n1;
    while(aux!=NULL && ++r>0) aux = aux->prox;
    return r;
}

No *cmpNo(No *n1, No *n2){
    No *aux1=n1, *aux2=n2;
    int c1=comprimento(n1), c2=comprimento(n2);
    if (c1<c2 || c1>c2) return (c1<c2 ? -1 : 1);
    while (aux1!=NULL){
        if (aux1->digito < aux2->digito || aux1->digito > aux2->digito)
            return (aux1->digito < aux2->digito ? -1 :  1);
        aux1 = aux1->prox;
        aux2 = aux2->prox;
    }
    return 0;
}

No *clona(No *n){
    No *aux=n, *r = NULL, *k = NULL, *z = NULL;
    while(aux!=NULL){
        k = cria(aux->digito);
        if (r==NULL){
            r = k;
            z = k;
        }else{
            k->ant = z;
            z->prox = k;
            z = k;
        }
        aux = aux->prox;
    }
    return r;
}

No *le(){
    char k;
    No *ult=NULL, *x, *ini=NULL;
    k = getch();
    while(k!=13){
        if (strchr("1234567890", k)!=NULL){
            x = cria(k-48);
            if (ini==NULL){
                ini = x;
                ult = x;
            }else{
                x->ant = ult;
                ult->prox = x;
                ult = x;
            }
            putch(k);
        }
        k = getch();
        if (k==8){
            x=ult->ant;
            x->prox=NULL;
            
            free(ult);
            ult=x;
            putch(k);
            putch(' ');
        }
        if (k==13 || k==8) putch(k);
    }
    return ini;
}


No *soma(No *n1, No *n2){
    No *auxN1=n1, *auxN2=n2;
    No *r=NULL, *x;
    int n, resto=0;

    while(auxN1->prox!=NULL)
        auxN1 = auxN1->prox;
    while(auxN2->prox!=NULL)
        auxN2 = auxN2->prox;
    while(auxN1!=NULL || auxN2!=NULL){

        if (auxN1!=NULL){
            n = auxN1->digito;
            auxN1 = auxN1->ant;
        }
        else
            n = 0;

        if (auxN2!=NULL){
            n += auxN2->digito;
            auxN2 = auxN2->ant;
        }
        n += resto;
        x = cria(n % 10);
        resto = n / 10;
        x->prox = r;
        if (r!=NULL) r->ant = x;
        r = x;
    }
    if (resto>0){
        x = cria(resto);
        x->prox = r;
        if (r!=NULL) r->ant = x;
        r = x;
    }
    return r;
}

No *divisao(No *n1, No *n2){
    No *res=cria(0), *resto=clona(n1), *um=cria(1), *x;
    int k = cmpNo(resto, n2);
    while (k>=0){
        x = res;
        res = soma(x,um);
        libera(x,-1);

        x = resto;
        resto  = subtracao(x,n2);
        libera(x,-1);
        k = cmpNo(resto, n2);
    }
    libera(resto,-1);
    libera(um, -1);
    return res;
}

void imprime(No *numero){
    No *aux=numero;
    if (aux!=NULL){
        printf("%d",aux->digito);
        imprime(aux->prox);
    }
}


int main()
{
    No *numero1=NULL;
    No *numero2=NULL;
    No *resultado=NULL;
    char op;
    printf("\nInforme o numero 1:",'0','9');
    numero1 = le();
    printf("\nInforme o numero 2:");
    numero2 = le();
    printf("\nInforme a operacao (+ - * /):");
    scanf("%c",&op);
    if (op == '+'){
        resultado = soma(numero1, numero2);
    }else if (op == '-'){
        resultado = subtracao(numero1, numero2);
    }else if (op == '*'){
        resultado = multiplicacao(numero1, numero2);
    }else if (op == '/'){
        resultado = divisao(numero1, numero2);
    }
    printf("\n\nResultado:");
    imprime(resultado);
    libera(numero1,-1);
    libera(numero2,-1);
    libera(resultado,-1);
    return 0;
}
