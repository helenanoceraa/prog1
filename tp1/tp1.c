/*
 * Tipos Abstratos de Dados - TADs
 * Arquivo do programa principal, que usa o TAD racional.
 * Feito em 16/09/2024 para a disciplina CI1001 - Programação 1.
*/
/* coloque aqui seus includes (primeiro os <...>, depois os "...") */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "racional.h"


/* programa principal */
int main ()
{
    srand (0); 

    int n, max, i, c;

    c = 0;
    while(c == 0){
        puts("Valor n entre 0 e 100: ");
        scanf("%d", &n);
        puts("Valor max entre 0 e 30: ");
        scanf("%d", &max);
        if(n < 100 && n > 0 && max > 0 && max < 30){
            c = 1;
        }
        else{
            puts("Numero invalido, tente outro numero");
        }
    }
    

    for(i = 1; i <= n; i++){
        printf("%d: ", i);

        /*sortear dois racionais*/
        struct racional r1 = sorteia_r(-max, max);
        struct racional r2 = sorteia_r(-max, max);

        imprime_r(r1);
        imprime_r(r2);

        if(!valido_r(r1) || !valido_r(r2)){
            printf("NUMERO INVALIDO\n");
            exit(-1);
        }

        /*calcula as expressoes*/
        struct racional s = soma_r(r1, r2);
        struct racional sub = subtrai_r(r1, r2);
        struct racional m = multiplica_r (r1, r2);
        struct racional d = divide_r (r1, r2);

        /*imprime a resposta*/
        imprime_r(s);
        imprime_r(sub);
        imprime_r(m);
        

        imprime_r(d);
        printf("\n");
    
    
    }
    return (0) ;
}