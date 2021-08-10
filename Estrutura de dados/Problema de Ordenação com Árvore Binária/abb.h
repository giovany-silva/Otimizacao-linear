//NAO ALTERE ESSE ARQUIVO
#include <stdio.h>
#include <stdlib.h>

typedef struct No * arvore;

//Incluir: recebe o endereco de uma arvore, uma 
//o endereco d de um registro do tipo TIPO
//funcao que compara dois registros do tipo TIPO.
//Insere d em a e devolve o novo endereco da arvore.
arvore incluir(arvore a, void * d, int (*comp_registros)(const void *, const void*));


//**********************************
//NAO ALTERE ESSE ARQUIVO
//**********************************



//Buscar: recebe o endereco de uma arvore, uma
//funcao que compara um registro do tipo TIPO
//com alguma informacao passada no ultimo parametro
//Devolve o endereco de memoria do registro que
//atende aquela informacao ou NULL caso nenhum atenda.
void * buscar(arvore a, int (*comp_reg_info)(const void *, const void*), void * qualquer);

//Remover: recebe o endereco de uma arvore, uma
//funcao que compara um registro do tipo TIPO
//com alguma informacao passada no ultimo parametro
//Apaga da arvore o no cujo registro atende aquela informacao.
//Devolve o novo enredeco da arvore.
arvore remover(arvore a, int (*comp_reg_info)(const void *, const void*), void * qualquer);

//Libera_arvore: recebe o endereco de uma arvore
//e uma funcao para liberar o dado de cada no
void libera_arvore(arvore r, void (*destroi)(const void *));

//Imprime uma arvore usando parenteses (raiz, arv_esq, arv_direita)
void imprime_crescente(arvore r, void (*imprime)(const void *));
