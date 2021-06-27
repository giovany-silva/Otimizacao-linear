#include <iostream>
#include <fstream>
#include <math.h>
#include <vector>
#include <limits>

using namespace std;

typedef long long int itype;

//solucao inocente que visita os vertices na ordem que são visitados
// em c++ o simbolo & é para indicar uma passagem de parametro por
// referência. É como fazer um "int * obj" no c; porem na função 
// podemos fazer algo como "obj = 0" e não precisa ser "*obj = 0"
void fool(vector<itype> &costs, int n, vector<int> &perm, itype &obj){
  vector <bool> visitado;
  for(int i = 0; i < n; i++) visitado.push_back(false);
  
  int primeiro = 0;
  perm.push_back(primeiro);

  int ultimo = primeiro;
  obj=0;
  
  for(int i = 1; i < n; i++){
    obj += costs[ultimo*n + i];
    perm.push_back(i);
    ultimo = i;
  }
  //custo de fechar o ciclo
  obj += costs[primeiro*n + ultimo];
  
  return;
}

int main(int argc, char *argv[]) {
  if(argc < 3){
    cout << "Uso incorreto, tente " << argv[0] << " arquivo_entrada arquivo_saida" << endl;
    return -1;
  }
  
  int n;
  ifstream entrada;
  entrada.open(argv[1]);
  ofstream saida;
  saida.open(argv[2]);
  entrada >> n;
  
  vector<double> x(n);
  vector<double> y(n);
  
  for (int p = 0; p < n; p++) {
    entrada >> x[p] >> y[p];
  }
  entrada.close();
  
  vector<itype> costs(n*n);
  
  for (int u = 0; u < n; u++) {
    for (int v = u+1; v < n; v++) {
      //O Calculo do custo da aresta é assim distancia euclidiana dos pontos doubles
      // e depois pega o piso.
      itype cost = floor(sqrt(pow(x[u] - x[v], 2) + pow(y[u] - y[v], 2)));
      costs[u*n + v] = cost;
      costs[v*n + u] = cost;
    }
  }
  
  //solucao
  vector<int> perm;
  itype obj;
  
  //fool
  fool(costs, n, perm, obj);
  
  //imprime a solucao
  saida << obj << endl;
  for(int i = 0; i < n; i++){
    saida << perm[i] << " ";
  }
  saida << endl;
  
  saida.close();
  return 0;
}
