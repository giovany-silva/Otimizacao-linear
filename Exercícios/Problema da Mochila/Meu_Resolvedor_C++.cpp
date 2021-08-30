#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#define itype unsigned

void read_instance(unsigned *n, itype *K, itype **v, itype **w, string filename);
void solve_knap_guloso(itype n, itype K, itype *v, itype *w, itype *obj, int *x);

int main(int argc, char * argv[]) {
  itype n, K;
  itype *v;
  itype *w;
  int *x;
  itype obj;

  read_instance(&n, &K, &v, &w, argv[1]);
  //Aloca espaço para as variaveis de decisao
  x = (int*) malloc(sizeof(int)*n);

  solve_knap_guloso(n, K, v, w, &obj, x);

  ofstream saida;
  string outputname = argv[2];
  saida.open(outputname.c_str());

  //imprime a solucao
  saida << obj << " " << endl;
  for(unsigned i = 0; i < n-1; i++) saida << x[i] << " ";
  saida << x[n-1] << endl;

  //libera a memoria alocada
  free(x);
  free(v);
  free(w);
  return 0;
}

void read_instance(unsigned *n, itype *K, itype **v, itype **w, string filename){
  ifstream entrada;
  entrada.open(filename.c_str());
  entrada >> *n >> *K;
  *v = (itype*) malloc(sizeof(itype)*(*n));
  *w = (itype*) malloc(sizeof(itype)*(*n));
  for(itype i = 0; i < *n; i++){
	  entrada >> (*v)[i] >> (*w)[i];
  }
  entrada.close();
}

void solve_knap_guloso(itype n, itype K, itype *v, itype *w, itype *obj, int *x){
  //Se quiser voce pode apenas modificar essa funcao para codificar o seu resolvedor

  //Inicializacao
  itype capacidade_restante = K;
  *obj = 0;
  for(unsigned i = 0; i < n; i++) x[i] = 0;

  //verificar ate qual item cabe
  for(unsigned i = 0; i < n; i++){
    //cabe
    if(w[i] <= capacidade_restante){
       x[i] = 1;
       *obj = *obj + v[i];
       capacidade_restante = capacidade_restante - w[i];
    }else{
       break;
    }
  }

  return;
}
