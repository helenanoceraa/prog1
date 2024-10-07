#include <stdio.h>
#include <stdlib.h>
#include <time.h>


struct racional {
 long num; /* numerador */
 long den; /* denominador */
};

/* retorna um número aleatório entre min e max */
long aleat (long min, long max)
{
    long num;
    int i = 0;
    while(i == 0){
        num = rand();
        if(num >= min && num <= max){
            i = 1;
        }
    }
    return num;
}

// Máximo Divisor Comum 
long mdc(long a, long b) {
    if (a < 0) a = -a; // Valor absoluto
    if (b < 0) b = -b;
    
    if (b == 0) return a; // Condição para evitar divisão por zero
    
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
    long resultado = (a * b) / mdc(a, b);
    return resultado;
}


//simplifica racionais
struct racional simplifica_r (struct racional r)
{   
    long div; 

    if(r.den == 0){
        return r;
    } 

    div = mdc(r.num, r.den);

    r.num = r.num / div;
    r.den = r.den / div;


    if((r.num < 0 && r.den < 0) || (r.num > 0 && r.den < 0)){
        r.num = - r.num;
        r.den = - r.den;
    }
    return r; 
}

/*cria um numero racional aleatorio*/
struct racional sorteia_r (long min, long max){
    struct racional r;


    r.num = min + rand() % (max - min + 1);  
    r.den = min + rand() % (max - min + 1); 

    return r;
}

/*checa se o numero existe no conjunto dos reais*/
int valido_r (struct racional r){
    if(r.den == 0)
        return 0;
    else 
        return 1;
}

/*imprime o numero racional*/
void imprime_r (struct racional r){
    struct racional s;
    if(!valido_r(r)){
        printf("NaN ");
    } else{
        if(r.num == r.den){
            printf("1 ");
        } else{
            if(r.num == 0){
                printf("0 ");
            } else{
                s = simplifica_r(r);
                if(s.den == 1){
                        printf("%ld ", s.num);
                } else{
                    printf("%ld/%ld ", s.num, s.den);
                }
            }
        }
    }

}


int soma_r (struct racional r1, struct racional r2, struct racional *r3){
    struct racional r;
    int valida;


    if(r1.den == r2.den){
        r.num = r1.num + r2.num;
        r.den = r1.den;
    }

    else{
        long min = mmc(r1.den, r2.den);

        r1.num = (min / r1.den) * r1.num;
        r2.num = (min / r2.den) * r2.num;

        r.num = r1.num + r2.num;
        r.den = min;
    }
    
    *r3 = simplifica_r(r);
    
    valida = valido_r(*r3);
    if(valida == 1)
        return 1;
    else 
        return 0; 
}

int subtrai_r (struct racional r1, struct racional r2, struct racional *r3){    
    struct racional r;
    int valida;

    if(r1.den == r2.den){
        r.num = r1.num - r2.num;
        r.den = r1.den;
    }

    else{
        long min = mmc(r1.den, r2.den);

        r1.num = (min / r1.den) * r1.num;
        r2.num = (min / r2.den) * r2.num;

        r.num = r1.num - r2.num;
        r.den = min;
    }
    
    *r3 = simplifica_r(r);
        
        valida = valido_r(*r3);
        if(valida == 1)
            return 1;
        else 
            return 0;
}

int multiplica_r (struct racional r1, struct racional r2, struct racional *r3){
    struct racional r;
    int valida;

    r.num = r1.num * r2.num;
    r.den = r1.den * r2.den; 

    *r3 = simplifica_r(r);
        
    valida = valido_r(*r3);
    if(valida == 1)
        return 1;
    else 
        return 0;
}

int divide_r (struct racional r1, struct racional r2, struct racional *r3){
    struct racional r;
    int valida;

    r.num = r1.num * r2.den;
    r.den = r2.num * r1.den; 

    if(r.den == 0){
        printf("DIVISAO INVALIDA\n");
        exit(-1);
    }

    *r3 = simplifica_r(r);
        
    valida = valido_r(*r3);
    if(valida == 1)
        return 1;
    else 
        return 0;
}
