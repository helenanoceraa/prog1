#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct racional {
    long num; 
    long den; 
};

/* cria um numero racional, aloca na memória e devolve um ponteiro */
struct racional *cria_r (long numerador, long denominador){
  
    struct racional *p_r = malloc(sizeof(struct racional));

    if(!p_r){
        printf("NULL");
        exit(1); 
    }

    p_r->num = numerador; 
    p_r->den = denominador;

    return p_r;
}


/*checa se o numero existe no conjunto dos reais*/
int valido_r (struct racional *r){
     if (r != NULL && r->den != 0) {
        return 1;  
    } else {
        return 0;  
    }
}

/* Máximo Divisor Comum */
long mdc(long a, long b) {
    if (a < 0) a = -a; 
    if (b < 0) b = -b;
    
    if (b == 0) return a; 
    
    while (b != 0) {
        long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

/* Mínimo Múltiplo Comum */
long mmc (long a, long b)
{
    return (a * b) / mdc(a, b);
}

/*simplifica racionais */
void simplifica_r(struct racional *r) {  
    long div = 0;

    if (r->den == 0) {
        return;
    } 

    div = mdc(r->num, r->den); 

    r->num = r->num / div;
    r->den = r->den / div;

    if ((r->num < 0 && r->den < 0) || (r->num > 0 && r->den < 0)) {
        r->num = -r->num;
        r->den = -r->den;
    }
}


/*imprime o numero racional*/
void imprime_r(struct racional *r) {
    if (r == NULL) {
        printf("NULL ");
        return; 
    }

    if(!valido_r(r)){
        printf("NaN ");
    } else{
        if(r->num == r->den){
            printf("1 ");
        } else{
            if(r->num == 0){
                printf("0 ");
            } else{
                simplifica_r(r);
                if(r->den == 1){
                        printf("%ld ", r->num);
                } else{
                    printf("%ld/%ld ", r->num, r->den);
                }
            }
        }
    }
}

/* libera a memória do racional
no programa principal o ponteiro passa a apontar para NULL */
void destroi_r (struct racional *r){
    if (r != NULL){
        free(r);
    }
}

/*soma dois racionais passados por referência*/
int soma_r (struct racional *r1, struct racional *r2, struct racional *r3){

    if(r1->den == r2->den){
        r3->num = r1->num + r2->num;
        r3->den = r1->den;
    }

    else{
        long min = mmc(r1->den, r2->den);

        r1->num = (min / r1->den) * r1->num;
        r2->num = (min / r2->den) * r2->num;

        r3->num = r1->num + r2->num;
        r3->den = min;
    }
    
    simplifica_r(r3);
    
    return valido_r(r3);
}

/*subtrai dois racionais passados por referência*/
int subtrai_r(struct racional *r1, struct racional *r2, struct racional *r3) {    

    if (!valido_r(r1) || !valido_r(r2)) {
        printf("NaN ");
        return 0; 
    }

    
    if (r1->den == r2->den) {
        r3->num = r1->num - r2->num;
        r3->den = r1->den;
    } else {
        long min = mmc(r1->den, r2->den);

        long num1 = (min / r1->den) * r1->num;
        long num2 = (min / r2->den) * r2->num;

        r3->num = num1 - num2;
        r3->den = min;
    }
    
    simplifica_r(r3);
    
    return valido_r(r3);
}


/*compara os racionais para ordenar o vetor na função ordena_vetor*/
int compara_r (struct racional *r1, struct racional *r2){
  struct racional r3;
  struct racional *p_r3 = &r3;
  subtrai_r(r1, r2, p_r3);

  if (p_r3->num > 0) {
      return 1;
  }
  else if (p_r3->num < 0) {
      return -1;
  }
  else {
      return 0;
  }
}

/*multiplica dois racionais passados por referência*/
int multiplica_r (struct racional *r1, struct racional *r2, struct racional *r3){

    r3->num = r1->num * r2->num;
    r3->den = r1->den * r2->den; 

    simplifica_r(r3);

    return valido_r(r3);
}

/*divide dois racionais passados por referência*/
int divide_r (struct racional *r1, struct racional *r2, struct racional *r3){

    r3->num = r1->num * r2->den;
    r3->den = r2->num * r1->den; 

    if(r3->den == 0){
        printf("DIVISAO INVALIDA\n");
        exit(-1);
    }

    simplifica_r(r3);
    
    return valido_r(r3);
}