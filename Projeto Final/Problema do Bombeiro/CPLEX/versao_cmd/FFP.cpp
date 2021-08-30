#include <ilcplex/ilocplex.h>
#include <vector>

using namespace std;
#define EPSL 0.0001

ILOSTLBEGIN

typedef IloArray<IloIntVarArray> IloIntVarArray2;

int main(int argc, char * argv[]){
    IloEnv env;
	try{
		IloInt nf,nv,max_d,fs,k,T;

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

		vector<pair<int,int>>grafo;
		int a,b;

		//leitura do grafo
		while(entrada>>a>>b){
			grafo.push_back(make_pair(a,b));
		}
		entrada.close();
		//inicialização dos vetores
     for(int i = 0; i < nv; i++){
				B.add(IloIntVarArray(env,T, 0,1));
				/*for(int j = 0; j < nf; j++){
				  bombeiro.add(B[i][j]);
				}*/
			}

      for(int i = 0; i < nv; i++){
				D.add(IloIntVarArray(env, T, 0, 1));
			}
      for(int i = 0; i < nf; i++){
				F.add(IloIntVarArray(env, T, 0, 1));
			}

      IloModel model(env);

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

    for(IloInt t = 1; t < T; t++){
      cout << "defendidos em " << t << ":" << endl;
      for(IloInt v = 0; v < nv; v++){
        if(solver.getValue(D[v][t]) >= 1 - EPSL){
          cout << "  " << v << endl;
        }
      }
    }

	}
	catch (IloException& ex) {
		cerr << "Error: " << ex << endl;
	}
	catch (...) {
		cerr << "Error" << endl;
	}
	env.end();

return 0;
}
