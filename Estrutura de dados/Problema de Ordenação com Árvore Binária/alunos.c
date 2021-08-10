
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

  Aluno *pA = (Aluno *) a;
  free (pA);
}

int
main (int argc, char **argv)
{
  if (argc > 4)
    exit (0);
  arvore arv_por_mat = NULL;
  arvore arv_por_nome = NULL;
  char x, n[50];
  Aluno *d;
  int i;
  do
    {
      scanf ("%c", &x);
      switch (x)
	{
	case 'i':
	  {
	    Aluno *novo = (Aluno *) calloc (1, sizeof (Aluno));
	    scanf ("%s %d %s", novo->nome, &novo->matricula, novo->curso);


	    arv_por_mat = incluir (arv_por_mat, novo, comp_por_mat);
	    arv_por_nome = incluir (arv_por_nome, novo, comp_por_nome);
	    break;
	  }

	case 'n':
	  {

	    scanf ("%s", n);
	    d = buscar (arv_por_nome, comp_aluno_nome, n);

	    if (d != NULL)
	      {
		printf ("%d - %s - %s\n", d->matricula, d->nome, d->curso);


	      }
	  }
	  break;
	case 'm':
	  {

	    scanf ("%d", &i);
	    d = buscar (arv_por_mat, comp_aluno_mat, &i);
	    if (d != NULL)
	      {
		printf ("%d - %s - %s\n\n", d->matricula, d->nome, d->curso);


	      }
	    break;
	  }

	case '1':
	  {
	    imprime_crescente (arv_por_mat, imprime);
	    printf ("\n");
	    break;
	  }

	case 'A':
	  {
	    imprime_crescente (arv_por_nome, imprime);
	    printf ("\n");
	    break;
	  }

	case 'r':
	  {
	    scanf ("%s", n);
	    d = buscar (arv_por_nome, comp_aluno_nome, n);
	    arv_por_nome = remover (arv_por_nome, comp_aluno_nome, n);	//<=ver se deve pegar o retorno...
	    arv_por_mat =
	      remover (arv_por_mat, comp_aluno_mat, &(d->matricula));
	    free (d);
	    break;
	  }
	case 's':
	  {
	    scanf ("%d", &i);
	    d = buscar (arv_por_mat, comp_aluno_mat, &i);
	    arv_por_mat = remover (arv_por_mat, comp_aluno_mat, &i);
	    arv_por_nome = remover (arv_por_nome, comp_aluno_nome, d->nome);
	    free (d);




	    break;
	  }

	default:
	  break;





	}


    }
  while (x != 'x');
  libera_arvore (arv_por_mat, destroi);
  libera_arvore (arv_por_nome, nem_destroi);
  return 0;
}

