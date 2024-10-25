#include <stdio.h>
#include <stdlib.h>
#include "racional.h"
#define MAX 100 

/*define o tamanho do vetor*/
void define_n(int *p_n){
  int i = 0;

  while(i == 0){

    scanf("%d", p_n);

    if(*p_n > 1 && *p_n < 100){
      i = 1;
    }
    else
      printf("Tente outro valor");
  }
}

/*criar um vetor de ponteiros que apontam para variaveis que possuem um local alocado na memória*/
void cria_vetor(struct racional **p_vetor, int n){
  int i;
  for(i = 0; i < n; i++){
    long num, den;
    scanf("%ld %ld", &num, &den);

    p_vetor[i] = cria_r(num, den);
  }
}

/*imprime o vetor usando a função de imprimir racionais*/
void imprime_vetor(struct racional **p_vetor, int n){
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
void retirar_elemento(struct racional **p_vetor, int *p_n) {
  int i;
  for (i = 0; i < *p_n; i++) {
    if (NaN(*p_vetor[i])) {
      p_vetor[i] = p_vetor[*p_n - 1];

      (*p_n)--;  
      i--;  
    }
  }
} 


/*ordena o vetor*/
void ordena_vetor(struct racional **p_vetor, int n) {
  int i, j;
  struct racional *aux;

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - i - 1; j++) {
      if (compara_r(p_vetor[j], p_vetor[j + 1]) > 0) {  
        aux = p_vetor[j];
        p_vetor[j] = p_vetor[j + 1];
        p_vetor[j + 1] = aux;
      }
    }
  }
}

/*aloca a soma na memória e realiza a soma*/
struct racional* soma_vetor(struct racional **p_vetor, int n) {
    struct racional *p_resultado = (struct racional*)malloc(sizeof(struct racional));
  
    if (p_resultado == NULL || !p_resultado) {
        printf("NULL");
        return NULL;
    }

    struct racional total = {0, 1}; 
    struct racional aux;

    for (int i = 0; i < n; i++) {
        soma_r(&total, &*p_vetor[i], &aux);
        total = aux;
    }

    *p_resultado = total; 

    return p_resultado; 
}


int main ()
{
  struct racional *p_resultado, **p_vetor;
  int i;

  /*define o n*/
  int n, n_orig;
  int *p_n = &n;
  define_n(p_n);
  /*salva o n original para poder dar free em todos os ponteiros do vetor*/
  n_orig = n;


  /*aloca espaço para o vetor de acordo com o n*/
  p_vetor = (struct racional **)malloc(n * sizeof(struct racional *));
  if(!p_vetor){
    printf("Falha na alocação de memória");
    return 1;
  }

  cria_vetor(p_vetor, n);

  imprime_vetor(p_vetor, n);

  retirar_elemento(p_vetor, &n);

  imprime_vetor(p_vetor, n);

  ordena_vetor(p_vetor,n);

  imprime_vetor(p_vetor, n);

  p_resultado = soma_vetor(p_vetor, n);

  printf("SOMA = ");
  imprime_r(p_resultado);
  printf("\n");

  /*libera da memória todos valores do vetor
  e aponta os ponteiros para NULL*/
  for(i = 0; i < n_orig; i++){
    destroi_r(p_vetor[i]);
    p_vetor[i] = NULL;
  }
  
  imprime_vetor(p_vetor,n);

  /*libera da memória o vetor*/
  free(p_vetor);
  p_vetor = NULL;

  /*libera da memória o espaço alocado para soma*/
  destroi_r(p_resultado);
  p_resultado = NULL;

  return (0) ;
}

