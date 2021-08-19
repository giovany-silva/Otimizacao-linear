/**************
para compilar 
gcc -pedantic-errors -Wall -std=c99 labirinto.c -o labirinto
para executar
./labirinto < pequeno.txt
**************/

#include <stdio.h>
#include <stdlib.h>

//funcoes auxiliares
void print_position (int x, int y);
void print_maze (char **maze, int largura, int altura);

//seu trabalho deve modificar apenas a funcao labirinto
int
labirinto (int x_atual, int y_atual, char **maze, int largura, int altura)
{
  if ((x_atual >= 0 && y_atual >= 0)
      && (x_atual < largura && y_atual < altura))
    {

      if (maze[x_atual][y_atual] != 'V')
	{
	  if ((maze[x_atual][y_atual] == '0'
	       || maze[x_atual][y_atual] == 'S'))
	    {
	      if (maze[x_atual][y_atual] == '0')
		printf ("(%d ,%d)", x_atual, y_atual);

	      if ((x_atual + 1 >= 0 && x_atual + 1 < largura)
		  && (y_atual >= 0 && y_atual < altura))
		{
		  if (maze[x_atual + 1][y_atual] == 'E')
		    {
		      printf ("(%d,%d)\n", x_atual + 1, y_atual);
		      exit (1);
		    }
		}
	      else if ((x_atual - 1 >= 0 && x_atual - 1 < largura)
		       && (y_atual >= 0 && y_atual < altura))
		{
		  if (maze[x_atual - 1][y_atual] == 'E')
		    {
		      printf ("(%d,%d)\n", x_atual - 1, y_atual);
		      exit (1);

		    }
		}
	      else if ((x_atual >= 0 && x_atual < largura)
		       && (y_atual - 1 >= 0 && y_atual - 1 < altura))
		{
		  if (maze[x_atual][y_atual - 1] == 'E')
		    {
		      printf ("(%d,%d)\n", x_atual, y_atual - 1);
		      exit (1);

		    }
		}

	      else if ((x_atual >= 0 && x_atual < largura)
		       && (y_atual + 1 >= 0 && y_atual + 1 < altura))
		{
		  if (maze[x_atual][y_atual + 1] == 'E')
		    {
		      printf ("(%d,%d)\n", x_atual, y_atual + 1);
		      exit (1);

		    }
		}


	      maze[x_atual][y_atual] = 'V';	//isso eh para demarcar as posiC'C5es vistidas  
	      labirinto (x_atual - 1, y_atual, maze, largura, altura);
	      labirinto (x_atual + 1, y_atual, maze, largura, altura);
	      labirinto (x_atual, y_atual - 1, maze, largura, altura);
	      labirinto (x_atual, y_atual - 1, maze, largura, altura);
	    }


	}
      else
	return 0;
    }


  else
    {
      return 0;
    }

  return 0;
}

//voce nao precisa mexer no main
int
main (void)
{
  int largura, altura, x_saida, y_saida, x, y;

  scanf ("%d %d\n", &largura, &altura);

  char **a = malloc (largura * sizeof (char *));
  for (x = 0; x < largura; x++)
    {
      a[x] = malloc (altura * sizeof (char));
    }

  for (y = altura - 1; y >= 0; y--)
    {
      for (x = 0; x < largura; x++)
	{
	  a[x][y] = getchar ();
	  if (a[x][y] == 'S')
	    {
	      x_saida = x;
	      y_saida = y;
	    }
	}
      getchar ();		//pegar a quebra de linha
    }


  print_maze (a, largura, altura);

  labirinto (x_saida, y_saida, a, largura, altura);
  //eu acredito que seja mais facil comecar a busca pela saida

  printf ("\n");

  return 0;
}


//voce nao precisa mexer nas funcoes auxiliares
void
print_maze (char **maze, int largura, int altura)
{
  int x, y;
  for (y = altura - 1; y >= 0; y--)
    {
      for (x = 0; x < largura; x++)
	{
	  printf ("%c", maze[x][y]);
	}
      printf ("\n");
    }
}

void
print_position (int x, int y)
{
  printf ("(%d, %d)", x, y);
}
