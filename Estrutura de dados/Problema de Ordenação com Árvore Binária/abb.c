//IMPLEMENTE AQUI AS SUAS FUNCOES

#include "abb.h"

typedef struct No
{
  void *dado;
  struct No *esq, *dir;
} No;


No *
criar_no (void *d)
{
  arvore novo = (arvore) malloc (sizeof (No));
  novo->dado = d;
  novo->esq = NULL;
  novo->dir = NULL;
  return novo;
}

arvore
incluir (arvore a, void *d,
	 int (*comp_registros) (const void *, const void *))
{
  if (a == NULL)
    {
      arvore novo = criar_no (d);

      return novo;
    }

  else
    {

      if (comp_registros (a->dado, d) > 0)
	a->esq = incluir (a->esq, d, comp_registros);




      else if (comp_registros (a->dado, d) < 0)
	a->dir = incluir (a->dir, d, comp_registros);



    }



  return a;

}

void *
buscar (arvore a, int (*comp_reg_info) (const void *, const void *),
	void *qualquer)
{


  if (a != NULL)
    {


      if (comp_reg_info (a->dado, qualquer) > 0)
	return buscar (a->esq, comp_reg_info, qualquer);




      else if (comp_reg_info (a->dado, qualquer) < 0)
	return buscar (a->dir, comp_reg_info, qualquer);






    }



  if (a != NULL)
    return a->dado;
  return a;
}

void
libera_arvore (arvore r, void (*destroi) (const void *))
{
  if (r != NULL)
    {

      libera_arvore (r->esq, destroi);
      libera_arvore (r->dir, destroi);
      destroi (r->dado);
      free (r);

    }



}

void
imprime_crescente (arvore r, void (*imprime) (const void *))
{

  if (r != NULL)
    {
      imprime_crescente (r->esq, imprime);
      imprime (r->dado);

      imprime_crescente (r->dir, imprime);
    }


}

//A funcao de remover usa essa funcao aqui
arvore
removeraiz (arvore r)
{
  No *p, *q;
  if (r->esq == NULL)
    {
      q = r->dir;
      free (r);
      return q;
    }
  p = r;
  q = r->esq;
  while (q->dir != NULL)
    {
      p = q;
      q = q->dir;
    }
  if (p != r)
    {
      p->dir = q->esq;
      q->esq = r->esq;
    }
  q->dir = r->dir;
  free (r);
  return q;
}

//Essa funcao de remover ja funciona se voce implementar o resto corretamente.
arvore
remover (arvore a, int (*comp_reg_info) (const void *, const void *),
	 void *qualquer)
{
  if (a == NULL)
    return NULL;
  if (comp_reg_info (a->dado, qualquer) == 0)
    return removeraiz (a);
  else if (comp_reg_info (a->dado, qualquer) > 0)
    a->esq = remover (a->esq, comp_reg_info, qualquer);
  else if (comp_reg_info (a->dado, qualquer) < 0)
    a->dir = remover (a->dir, comp_reg_info, qualquer);
  return a;
}

