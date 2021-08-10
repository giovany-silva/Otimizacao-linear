#include "abb.h"
#include <string.h>

typedef struct Aluno
{
  char nome[50];
  int matricula;
  char curso[3];
} Aluno;

Aluno *
criar_aluno (char *nome, int matricula, char *curso)
{
  Aluno *a = (Aluno *) calloc (1, sizeof (Aluno));
  sprintf (a->nome, "%s", nome);
  sprintf (a->curso, "%s", curso);
  a->matricula = matricula;
  return a;
}

int
comp_por_mat (const void *a, const void *b)
{
  Aluno *pA = (Aluno *) a;
  Aluno *pB = (Aluno *) b;
  return (pA->matricula - pB->matricula);
}

int
comp_aluno_mat (const void *aluno, const void *matri)
{
  Aluno *pA = (Aluno *) aluno;
  int *matricula = (int *) matri;
  return (pA->matricula - *matricula);
}

int
comp_por_nome (const void *a, const void *b)
{
  Aluno *pA = (Aluno *) a;
  Aluno *pB = (Aluno *) b;
  return (strcmp (pA->nome, pB->nome));
}

int
comp_aluno_nome (const void *aluno, const void *nome)
{
  Aluno *pA = (Aluno *) aluno;
  return strcmp (pA->nome, (char *) nome);
}

void
destroi (const void *a)
{
  Aluno *pA = (Aluno *) a;
  free (pA);
}

void
imprime (const void *a)
{
  Aluno *pA = (Aluno *) a;
  printf ("%d - %s - %s\n", pA->matricula, pA->nome, pA->curso);
}

void
nem_destroi (const void *a)
{
}

int
main ()
{

  //Criando duas arvores, uma por nome, outra por matricula
  arvore arv_por_mat = NULL;
  arvore arv_por_nome = NULL;

  //Adicionando alguns alunos
  Aluno *aluno;

  aluno = criar_aluno ("Camille", 20187, "ADM");
  arv_por_mat = incluir (arv_por_mat, aluno, comp_por_mat);
  arv_por_nome = incluir (arv_por_nome, aluno, comp_por_nome);

  aluno = criar_aluno ("Diana", 20183, "CCO");
  arv_por_mat = incluir (arv_por_mat, aluno, comp_por_mat);
  arv_por_nome = incluir (arv_por_nome, aluno, comp_por_nome);

  aluno = criar_aluno ("Ashe", 20182, "CCO");
  arv_por_mat = incluir (arv_por_mat, aluno, comp_por_mat);
  arv_por_nome = incluir (arv_por_nome, aluno, comp_por_nome);

  aluno = criar_aluno ("Bardo", 20181, "CCO");
  arv_por_mat = incluir (arv_por_mat, aluno, comp_por_mat);
  arv_por_nome = incluir (arv_por_nome, aluno, comp_por_nome);

  aluno = criar_aluno ("Elise", 20188, "SIN");
  arv_por_mat = incluir (arv_por_mat, aluno, comp_por_mat);
  arv_por_nome = incluir (arv_por_nome, aluno, comp_por_nome);

  aluno = criar_aluno ("Fiora", 20184, "SIN");
  arv_por_mat = incluir (arv_por_mat, aluno, comp_por_mat);
  arv_por_nome = incluir (arv_por_nome, aluno, comp_por_nome);

  printf ("Todos alunos por matricula:\n");
  imprime_crescente (arv_por_mat, imprime);
  printf ("\n");
  printf ("Todos alunos por nome:\n");
  imprime_crescente (arv_por_nome, imprime);
  printf ("\n");

  //Procura um aluno com matricula 20182
  int m = 20182;
  Aluno *c = buscar (arv_por_mat, comp_aluno_mat, &m);
  if (c != NULL)
    fprintf (stderr, "%d %s\n", c->matricula, c->nome);

  //Procura um aluno com o nome Bardo
  char n[50] = "Bardo";
  Aluno *d = buscar (arv_por_nome, comp_aluno_nome, n);
  if (d != NULL)
    {
      printf ("%d %s\n", d->matricula, d->nome);
      printf ("Removendo ele da arvore por matricula\n");
      arv_por_mat = remover (arv_por_mat, comp_aluno_mat, &(d->matricula));
      printf ("Removendo ele da arvore por nome\n");
      arv_por_nome = remover (arv_por_nome, comp_aluno_nome, &(d->nome));
      free (d);
    }

  Aluno *alu = buscar (arv_por_nome, comp_aluno_nome, n);
  if (alu != NULL)
    printf ("%d %s\n", alu->matricula, alu->nome);
  else
    printf ("Aluno com nome %s nao existe\n", n);

  m = 20181;
  alu = buscar (arv_por_mat, comp_aluno_mat, &m);
  if (alu != NULL)
    printf ("%d %s\n", alu->matricula, alu->nome);
  else
    printf ("Aluno com matricula %d nao existe\n", m);

  libera_arvore (arv_por_mat, destroi);
  libera_arvore (arv_por_nome, nem_destroi);
  return 0;
}

