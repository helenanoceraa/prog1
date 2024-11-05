// TAD lista de nÃºmeros inteiros
// Carlos Maziero - DINF/UFPR, Out 2024
//
// ImplementaÃ§Ã£o do TAD - a completar
//
// ImplementaÃ§Ã£o com lista encadeada dupla nÃ£o-circular
#include "lista.h"
#include <stdlib.h>
#include <stdio.h>

/*Cria um nó com o último e o primeiro elemento 
apontados para NULL e o tamanho da lista como 0*/
struct lista_t *lista_cria (){

    struct lista_t *lst = (struct lista_t *)malloc(sizeof(struct lista_t));
    
    if(!lst){
        return NULL;
    }

    //Ajusta os ponteiros 
    lst->prim = NULL;
    lst->ult = NULL;
    lst->tamanho = 0;

    return lst; 
}

/*Libera o espaço de todos os elementos e da lista na memoria
usando a função lista_retira*/
struct lista_t *lista_destroi(struct lista_t *lst) {
    int item;

    while (lst != NULL && lst->prim != NULL) {
        lista_retira(lst, &item, 1); 
    }

    free(lst);
    return NULL; 
}

//Insere um elemento na posição indicada 
int lista_insere(struct lista_t *lst, int item, int pos) {
    int i;
    struct item_t *p, *aux;

    if (lst == NULL) {
        return -1; 
    }

    p = (struct item_t *)malloc(sizeof(struct item_t));
    if (!p) {
        return -1;  
    }

    p->valor = item; 

    // Inserir no final da lista
    if (pos < 0 || pos > lst->tamanho) {
        p->ant = lst->ult;
        p->prox = NULL;

        if (lst->ult != NULL) {
            lst->ult->prox = p;
        } else {
            lst->prim = p;  
        }

        lst->ult = p; 
    }else if (pos == 0) { 
    // Inserir no início da lista

        p->prox = lst->prim;
        p->ant = NULL;

        if (lst->prim != NULL) {
            lst->prim->ant = p;
        } else {
            lst->ult = p;  
        }
        lst->prim = p;
    }else {
    // Inserir no meio da lista

        aux = lst->prim;
        
        for (i = 0; i < pos - 1 && aux != NULL; i++) {
            aux = aux->prox;
        }

        if (aux == NULL) {     
            free(p);         
            return -1;         
        }

        p->ant = aux;
        p->prox = aux->prox;

        if (aux->prox != NULL) {
            aux->prox->ant = p;
        } else {
            lst->ult = p; 
        }

        aux->prox = p;
    }

    //Ajusta e retorna o tamanho 
    lst->tamanho++;
    return lst->tamanho;
}

//Retira o elemento da lista na posição desejada 
int lista_retira(struct lista_t *lst, int *item, int pos) {
    struct item_t *aux;

    if (lst == NULL || lst->prim == NULL) {
        return -1; 
    }

    //ajusta o índice para o último no caso de -1 e maior que a lista
    if (pos < 0 || pos >= lst->tamanho) {
        pos = lst->tamanho - 1; 
    }

    aux = lst->prim;

    //encontra a posição
    for (int i = 0; i < pos; i++) {
        aux = aux->prox; 
    }

    *item = aux->valor;

    if (aux->ant != NULL) {
        aux->ant->prox = aux->prox;
    } else {
        lst->prim = aux->prox; 
    }

    if (aux->prox != NULL) {
        aux->prox->ant = aux->ant;
    } else {
        lst->ult = aux->ant;
    }

    free(aux); 
    lst->tamanho--;

    return 0; 
}

//procura uma posição dada e acha o valor dela 
int lista_consulta(struct lista_t *lst, int *item, int pos) {
    struct item_t *aux;

    if (lst == NULL) {
        return -1; 
    }

    if (pos < -1 || pos >= lst->tamanho) {
        return -1; 
    }else if(pos == -1){
        aux = lst->ult; 
    } else {
        aux = lst->prim; 
        
        for (int i = 0; i < pos; i++) {
            aux = aux->prox; 
        }
    }

    *item = aux->valor;

    return 0; 
}

//encontra a primeira ocorrencia de um valor dado na lista
int lista_procura(struct lista_t *lst, int valor) {
    if (lst == NULL) {
        return -1; 
    }

    struct item_t *aux = lst->prim; 
    int pos = 0; 

    while (aux != NULL) { 
        if (aux->valor == valor) { 
            return pos; 
        }
        aux = aux->prox; 
        pos++; 
    }

    return -1; 
}

//retorna o tamanho da lista
int lista_tamanho (struct lista_t *lst){
    if (lst == NULL) {
        return -1; 
    }
    return lst->tamanho;
}

//imprime a lista inteira
void lista_imprime (struct lista_t *lst){
    int i;
    struct item_t *aux = lst->prim;
    for(i = 0; i < lst->tamanho; i++){
        printf("%d ", aux->valor);
        aux = aux->prox;
    }
}


