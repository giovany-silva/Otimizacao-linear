#include "lista.h"

p_no cria_lista(){
  return NULL;
}

p_no adiciona_elemento(p_no lista, int d){
  p_no novo = (p_no) malloc(sizeof(No));
  novo->dado = d;
  novo->prox = lista;
  return novo;
}

void imprime_lista(p_no lista){
  p_no no_atual = lista;
  while(no_atual != NULL){
    printf("%d ", no_atual->dado);
    no_atual = no_atual->prox;
  }
  printf("\n");
}

void imprime_recursiva(p_no lista){
  if(lista != NULL){
    imprime_recursiva(lista->prox);
    printf("%d ", lista->dado);
  }
}

void desaloca_lista(p_no lista){
  if(lista != NULL){
    desaloca_lista(lista->prox);
    free(lista);
  }
}



p_no concatena(p_no primeira, p_no segunda){//<=ESSA eh a versao  recursiva de concatena...
  if(primeira == NULL)
    return segunda;
    
  
primeira->prox=concatena(primeira->prox,segunda);
  
return primeira;
}


p_no inverte_lista(p_no lista, p_no novo_ultimo)//<=ESSA eh a versao nao recursiva de inversao recursivo...

{
  if(lista == NULL){
    return NULL;
  }
  p_no atual=lista,proximo=lista->prox,temporario=lista->prox;
while(proximo!=NULL){
temporario=temporario->prox;//o temporario percorre a lista nem mudar a original
proximo->prox=atual;//inverte o camninho do proximo ao atual
atual=proximo;//o proximo a ser trocado 
proximo=temporario;//o proximo elemento ...
}       
     lista->prox=NULL; 
return lista=atual;


  
  
  
 
}

/*
Exercicios: 
Fazer concatena recursivo
Fazer inverte_lista naum recursivo
*/


















