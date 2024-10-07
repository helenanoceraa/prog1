#include <stdio.h>
#include "header.h"

#define MAX 100 


/*coloca os valores dentro do vetor */
void cria_vetor(struct racional *p_vetor, int n){
    int i;
    for(i = 0; i < n; i++){
        //printf("Numerador: ");      se for colocar um a um é bom ter mas se for colocar tudo junto vai printar várias vezes sem necessidade
        scanf("%ld", &p_vetor[i].num);

        //printf("Denominador: ");
        scanf("%ld", &p_vetor[i].den);
    }
}

/*define o tamanho do vetor */
void define_n(int *p_n){
  int i = 0;

  while(i == 0){

    //printf("Tamanho do vetor ");
    scanf("%d", p_n);

    if(*p_n > 1 && *p_n < 100){
      i = 1;
    }
    else
      printf("Tente outro valor");
  }
}

/*imprime o vetor usando a função de imprimir racionais*/
void imprime_vetor(struct racional *p_vetor, int n){
  int i;
  printf("VETOR = ");
  for(i = 0; i < n; i++){
    imprime_r(p_vetor[i]);
  }
  printf("\n");
}

/*identifica o NaN para conseguir tirar ele depois*/
int NaN(struct racional r) {
    return r.den == 0;
}

/*retira o NaN*/
void retirar_elemento(struct racional *p_vetor, int *p_n) {
     int i;
    for (i = 0; i < *p_n; i++) {
        if (NaN(p_vetor[i])) {
            p_vetor[i] = p_vetor[*p_n - 1];

            (*p_n)--;  
            i--;  
        }
    }
}


/*compara os racionais para eu poder ordenar o vetor*/
int compara_racionais(struct racional *r1, struct racional *r2){
  struct racional r3;
  struct racional *p_r3 = &r3;
  subtrai_r(*r1, *r2, p_r3);

  if (r3.num > 0) {
      return 1;
  }
  else if (r3.num < 0) {
      return -1;
  }
  else {
      return 0;
  }
}

/*ordena o vetor*/
void ordena_vetor(struct racional *p_vetor, int n){
  int i, j;
  struct racional aux;
  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (compara_racionais(&p_vetor[j], &p_vetor[j + 1]) > 0) {
        aux = p_vetor[j];
        p_vetor[j] = p_vetor[j + 1];
        p_vetor[j + 1] = aux;
      }
    }
  }
}

void soma_vetor(struct racional *vetor, int n, struct racional *resultado) {
    struct racional total = {0, 1}; 
    struct racional aux; 

    for (int i = 0; i < n; i++) {
        soma_r(total, vetor[i], &aux); 
        total = aux; 
    }

    *resultado = total; 
}

int main ()
{
  int n;
  int *p_n = &n;
  //long vetor[MAX];

  struct racional vetor[MAX];
  struct racional *p_vetor = vetor;
  struct racional resultado;

  define_n(p_n);

  cria_vetor(p_vetor, n);

  imprime_vetor(p_vetor, n); 

  retirar_elemento(p_vetor, &n);

  imprime_vetor(p_vetor, n);

  ordena_vetor(p_vetor,n);

  imprime_vetor(p_vetor, n);

  soma_vetor(p_vetor, n, &resultado);

  printf("VETOR = ");
  imprime_r(resultado);
  printf("\n");

  return (0);
}