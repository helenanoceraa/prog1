#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct racional {
 long num; /* numerador */
 long den; /* denominador */
};

/* retorna um número aleatório entre min e max, inclusive. 
Não entendi para que eu vou usar isso*/
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

/* Máximo Divisor Comum entre a e b */
/* calcula o MDC pelo método de Euclides */
long mdc (long a, long b)
{
    long resto, maior, menor;
    if(a == 0){
        return a;
    }
    else{
        if(a < 0){
            a = -a;
        }
        if(b < 0){
            b = -b;
        }
        if(a > b){
            maior = a;
            menor = b;
        }
        else {
            maior = b;
            menor = a;
        }
        resto = 1;
        while(resto != 0){
            resto = maior % menor;
            maior = menor;
            menor = resto;
        }
        return maior;
    }
}


/* Mínimo Múltiplo Comum entre a e b */
/* mmc = (a * b) / mdc (a, b) */
long mmc (long a, long b)
{
    long resultado = (a * b) / mdc(a, b);
    return resultado;
}


/* Recebe um número racional e o simplifica.
 * Por exemplo, ao receber 10/8 deve retornar 5/4.
 * Se ambos numerador e denominador forem negativos, deve retornar um positivo.
 * Se o denominador for negativo, o sinal deve migrar para o numerador.
 * Se r for inválido, devolve-o sem simplificar. */
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

void imprime_r (struct racional r){
    struct racional s;
    if(!valido_r(r)){
        printf("INVALIDO ");
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


struct racional soma_r (struct racional r1, struct racional r2){
    struct racional r;

    if(r1.den == r2.den){
        r.num = r1.num + r2.num;
        r.den = r1.den;
        return r;
    }

    else{
        long min = mmc(r1.den, r2.den);

        r1.num = (min / r1.den) * r1.num;
        r2.num = (min / r2.den) * r2.num;

        r.num = r1.num + r2.num;
        r.den = min;
        return r;
    }
}

struct racional subtrai_r (struct racional r1, struct racional r2){
    struct racional r;

    if(r1.den == r2.den){
        r.num = r1.num + r2.num;
        r.den = r1.den;
        return r;
    }

    else{
        long min = mmc(r1.den, r2.den);

        r1.num = (min / r1.den) * r1.num;
        r2.num = (min / r2.den) * r2.num;

        r.num = r1.num - r2.num;
        r.den = min;
        return r;
    }
}

struct racional multiplica_r (struct racional r1, struct racional r2){
    struct racional r;

    r.num = r1.num * r2.num;
    r.den = r1.den * r2.den; 

    return r;
}

struct racional divide_r (struct racional r1, struct racional r2){
    struct racional r;

    r.num = r1.num * r2.den;
    r.den = r2.num * r1.den; 

    if(r.den == 0){
        printf("DIVISAO INVALIDA\n");
        exit(-1);
    }

    return r;
}