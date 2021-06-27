#include <ilcplex/ilocplex.h>
#include <vector>
#include <time.h>
#include "loadImage.h"
using namespace std;
#define EPSL 0.0001

void draw();
std::vector<string>cor_vertice;//armazena as ligacoes e cores dos vertices

FILE * arq=NULL;
 string branco=" \[style=\" filled\",fillcolor=\"#ffffb2\"];\n",
 vermelho=" [style=\"filled\",fillcolor=\"#ff001f\"];\n",
 azul=" [style=\"filled\",fillcolor=\"#3a31fa\"];\n";

vector<pair<int,int>>grafo;
ILOSTLBEGIN
IloInt nf,nv,max_d,fs,k,T;
typedef IloArray<IloIntVarArray> IloIntVarArray2;

int main(int argc, char * argv[]){

    IloEnv env;
clock_t start_t, end_t, total_t;
	try{


		ifstream entrada;
		ofstream saida;

		entrada.open(argv[1]);



		//número de bombeiros, números de vértices, máximo defensável por rodada, foco inicial, número de dias consec.
		entrada >> nf >> nv>>max_d>>fs>>k;

			
    T = nv; //no pior dos casos, queima 1 vertice por dia, podemos melhorar esse limite.
    
    //B[v][t] é 1 se v está queimando (BURNING) no tempo t
    //D[v][t] é 1 se v está defendido no tempo t
    //F[i][t] é 1 se o bombeiro i trabalha no tempo t

		IloIntVarArray2 B(env), D(env), F(env); //,Q(env);


		int a,b;

		//leitura do grafo
		while(entrada>>a>>b){
			grafo.push_back(make_pair(a,b));
		}
		entrada.close();

	cor_vertice.resize(nv);

		for(int i=0;i<nv;i++)cor_vertice[i]=branco;

		cor_vertice[fs]=vermelho;
		draw();
		system("dot -Tpng hw.dot -o hw.png");
 		loadImage *load=new loadImage();
  		load->desenha();

		//inicialização dos vetores
     for(int i = 0; i < nv; i++){
				B.add(IloIntVarArray(env,T, 0,1));
			}

      for(int i = 0; i < nv; i++){
				D.add(IloIntVarArray(env, T, 0, 1));
			}
      for(int i = 0; i < nf; i++){
				F.add(IloIntVarArray(env, T, 0, 1));
			}
			IloModel model(env);
			//model.add(Q[fs][1]==1);

    //RESTRICAO 2, SE v_linha esta queimando em t-1, 
    //o vizinho v esta defendido ou queimando em t
    for(IloInt t = 1; t < T; t++){
      for(IloInt v = 0; v < nv; v++){
        //Para cada vizinho de v
        for(IloInt e = 0; e < grafo.size(); e++){
          IloInt v_linha = -1;
          if(grafo[e].first == v) v_linha = grafo[e].second;
          if(grafo[e].second == v) v_linha = grafo[e].first;
          if(v_linha == -1) continue;
          model.add(B[v][t] + D[v][t] - B[v_linha][t-1] >= 0);
        }
      }
    }

    //RESTRICAO3, vertice esta defendido ou queimando (ou nenhum deles)
    for(IloInt t = 1; t < T; t++){
      for(IloInt v = 0; v < nv; v++){
        model.add(B[v][t] + D[v][t] <= 1);
      }
    }

    //RESTRICAO4 se ele esta queimando em t-1 entao vai queimar em t
    for(IloInt t = 1; t < T; t++){
      for(IloInt v = 0; v < nv; v++){
        model.add(B[v][t] - B[v][t-1] >= 0);
      }
    }

    //RESTRICAO5 se ele esta defendido em t-1 entao continua defendido em t 
    for(IloInt t = 1; t < T; t++){
      for(IloInt v = 0; v < nv; v++){
        model.add(D[v][t] - D[v][t-1] >= 0);
      }
    }

    //RESTRICAO6 maximo de vertices que podem ser defendidos
    for(IloInt t = 1; t < T; t++){
      IloExpr defendidos_antes(env);
      IloExpr defendidos_agora(env);
      IloExpr bombeiros_trabalhando_hoje(env);
      for(IloInt v = 0; v < nv; v++){
        defendidos_antes += D[v][t-1];
        defendidos_agora += D[v][t];
      }
      for(IloInt i = 0; i < nf; i++){
        bombeiros_trabalhando_hoje += F[i][t];
      }
      model.add(defendidos_agora - defendidos_antes <= max_d);
      model.add(defendidos_agora - defendidos_antes <= bombeiros_trabalhando_hoje);
    }

    //RESTRICAO7
    model.add(B[fs][0] == 1);

    //RESTRICAO8
    for(IloInt v = 0; v < nv; v++){
      if(v != fs) model.add(B[v][0] == 0);
    }
    for(IloInt v = 0; v < nv; v++){
      model.add(D[v][0] == 0);
    }

    //RESTRICAO9 um bombeiro nao trabalha K dias consecutivos
    for(IloInt t = 1; t < T - k; t++){
      for(IloInt i = 0; i < nf; i++){
        IloExpr dias_trabalhado_na_janela(env);
        for(IloInt t_linha = t; t_linha <= t+k-1; t_linha++){
          dias_trabalhado_na_janela += F[i][t_linha];
        }
        model.add(dias_trabalhado_na_janela <= k);
      }
    }

    IloExpr queimado_final(env);
		for(IloInt v = 0; v < nv; v++){
		  queimado_final += B[v][T-1];
		}
		// maximizar |V|- total de vértices queimados
		model.add(IloMaximize(env, nv - queimado_final));

	//resolver e pegar quantos  e quais vertices foram defendidos...
        IloCplex solver(model);
        //solver.setParam(IloCplex::Param::MIP::Tolerances::MIPGap, 0.00001);

        solver.solve();

        cout << "Status solucao: " << solver.getStatus() << endl;
        cout << "Valor solucao:  " << std::fixed << solver.getObjValue() << endl;
		saida.open(argv[2]);
		//P Ã© um array numÃ©rico com n posiÃ§Ãµes
		//IloNumArray P(env, n);
		//IloNumArray V(env, n);
 

  for(IloInt t = 1; t < T; t++){
      cout << "defendidos em " << t << ":" << endl;
      for(IloInt v = 0; v < nv; v++){
        if(solver.getValue(D[v][t]) >= 1 - EPSL){
	    cor_vertice[v]=azul;
        }
	else if(solver.getValue(B[v][t]) >= 1 - EPSL){
	    cor_vertice[v]=vermelho;
	    draw();
	}
        
      }
	load->desenha();
    }

   for(IloInt v=0;v<nv;v++){//se estah intocado após o fim das queimadas defenda
	if(solver.getValue(D[v][T-1])<=0 and solver.getValue(B[v][T-1])<=0){//intocado defende
	    cor_vertice[v]=azul;
	    draw();
        }
	load->desenha();

   }

	}
	catch (IloException& ex) {
		cerr << "Error: " << ex << endl;
	}
	catch (...) {
		cerr << "Error" << endl;
	}
	env.end();
  end_t = clock();
  total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  cout<<" "<<total_t;

return 0;
}
void draw(){

   string txt="graph \{ ratio=\"fill\";\nsize=\"7.0,7.0!\";\nmargin=0;\n";

   for(pair<int,int>p:grafo){
		txt+=to_string(p.first)+" -- ";
                txt+=to_string(p.second)+";\n";
   }
 
   for(int i=0;i<nv;i++){
	txt+=to_string(i)+cor_vertice[i];
   }

   txt+="node[shape=point, height=4, width=2];}";


//A -- B;\nA -- C;\ncores_AKI;


   FILE *arq=fopen("hw.dot","w");
   fprintf(arq,"%s\n",txt.c_str());
   fclose(arq);
   system("dot -Tpng hw.dot -o hw.png");
}
