#include "loadImage.h"
void draw();
vector<string>cor_vertice;//armazena as ligacoes e cores dos vertices      

FILE * arq=NULL;
 string branco=" \[style=\" filled\",fillcolor=\"#ffffb2\"];\n",
 vermelho=" [style=\"filled\",fillcolor=\"#ff001f\"];\n",
 azul=" [style=\"filled\",fillcolor=\"#3a31fa\"];\n";

typedef struct info info;

struct info{
  int grau,proximidade,indice;
};
//atualiza cor do vertice
void atualiza_vertice(int numero,string cor);

//faz ligacao entre vertices
void liga(int a,int b,vector<vector<int>>&grafo);

//imprime grafo
void imprime(vector<vector<int>>grafo,int n);

//calcula distancia entre todos os vertices
void floydWarshall(vector<vector<int>> graph);

//atualiza a distancia de um v a outro  que esteja queimado
void atualizar_proximidade(int vertice_queimado,vector<int>estado,vector<int>&proximidade);

//atualiza o grau intocavel dos vizinhos após esse v for queimado
void atualizar_grau(int vertice_queimado,vector<int>&grau);

//guarda distancia entre cada vértice
vector<vector<int>>distancia;

//número de bombeiros , número de vértices, máximo defensável por rodada, foco inicial, máx dias consec.
int n_bombeiros,n_vertices,max_d,foco_inicial,max_dias_consec,a,b;

//ordenação lista prioritária


vector<vector<int>>grafo;  
bool existe=true;

//definição da enum
enum tipo { intocado = 0, queimado, defendido};

//regra para o sort do vetor prioridade
bool compare(const info &a,const info &b){
    	if(a.grau > b.grau) return true;//maior grau
    	else{ 
        if(a.grau < b.grau) return false;
    	  else {//menor distancia
    		  if(a.proximidade <= b.proximidade) return true;
    		  else return false;
        }
    	}
	return false;
}

int main(){
loadImage *load;
load=new loadImage();

//número de bombeiros, números de vértices, máximo defensável por rodada, foco inicial, número de dias consec.
cin>>n_bombeiros>>n_vertices>>max_d>>foco_inicial>>max_dias_consec;

grafo.resize(n_vertices);
for(int i=0;i<n_vertices;i++){
	grafo[i].resize(n_vertices,INT_MAX);
	grafo[i][i]=0;
}
//armazena o grau de cada vértice
vector<int>grau(n_vertices,0);
while(cin>>a>>b){	
	liga(a,b,grafo);
	grau[a]++;
	grau[b]++;
}
for(int i=0;i<n_vertices;i++){
	cor_vertice.push_back(branco);
}
 
distancia.resize(n_vertices);

for(int i=0;i<n_vertices;i++){
	distancia[i].resize(n_vertices);
}

//armazena o estado de cada vértice 
vector<int>estado(n_vertices,intocado);


//armazena qtos dias consecutivos os bombeiros estao trabalhando
vector<pair<int,int>>bombeiro(n_bombeiros);//grau - num bombeiro
vector<int>proximidade(n_vertices,INT_MAX);//guarda a proximidade de um vertice a um foco de incendio

for(int i=0;i<n_bombeiros;i++){
	bombeiro[i].second=i;//número do bombeiro
}

//calcula a distância entre cada vértice
floydWarshall(grafo);

//queima o primeiro vértice
estado[foco_inicial]=queimado;
cor_vertice[foco_inicial]=vermelho;
draw();
load->desenha();

while(existe){//eqto existe vert. a ser queimado

//pega os que trabalharam menos
sort(bombeiro.begin(),bombeiro.end());

int qtd_bombeiros=0;

	//calcula quantos bombeiros podem trabalhar nessa rodada
	for(int i=0;i<n_bombeiros;i++){
		//caso foi atingido o número máximo 
		if(qtd_bombeiros==max_d)break;

		if(bombeiro[i].first>=max_dias_consec){//esse bombeiro nao trabalha nessa rodada
			bombeiro[i].first=0;
		}
		else{//esse bombeiro trabalha
			bombeiro[i].first++;
			qtd_bombeiros++;
		}	
	}
	//defesa por grau e por proximidade
        vector<info>proximo_vertice;
	
	for(int i=0;i<n_vertices;i++){

		if(estado[i]==intocado){

			proximo_vertice.push_back({grau[i],proximidade[i],i});
		}
	}

	//ordena grau - proximidade
	
	
	sort(proximo_vertice.begin(),proximo_vertice.end(),compare);
	//for(int i=0;i<n_vertices;i++)cout<<grau[i]<<" ";
	
	
	for(int i=0;i<qtd_bombeiros;i++){
		
		for(info v:proximo_vertice){
			if(estado[v.indice]==intocado){//se estah intocado defenda-o
				estado[v.indice]=defendido;
				atualiza_vertice(v.indice,azul);
				//atualizar o grau intocavel dos adjacentes a ele
				atualizar_grau(v.indice,grau);
        			draw();
				load->desenha();
				break;
			}
		}
	}

	cout<<"\nVértices defendidos:\n";
	for(int i=0;i<n_vertices;i++){
		if(estado[i]==defendido){
			cout<<i<<" ";
		}
	}
	existe=false;
	for(int i=0;i<n_vertices;i++){
		if(estado[i]== intocado){
			existe=true;
			break;
		}
	}

	if(!existe)break;//se nao há mais vértices saia

	//que começem as queimadas...
	vector<int>lista_queimados;

	for(int i=0;i<n_vertices;i++){
        	
		if(estado[i]==queimado){
			for(int j=0;j<n_vertices;j++){//para cada uns dos vizinhos
				if(grafo[i][j]==1 and estado[j]==intocado){//se eh vizinho e nao estah defendido queime-o
						
					//adiciona na lista de queimados
					lista_queimados.push_back(j);

					//atualizar proximidade dos vértices a esse queimado
					atualizar_proximidade(j,estado,proximidade);

					//atualizar o grau intocavel dos adjacentes a ele
					atualizar_grau(j,grau);
				}
			}
		}
	}
	for(int i : lista_queimados){
		estado[i]=queimado;
		atualiza_vertice(i,vermelho);
        	draw();
		

	}load->desenha();

}
sleep(10);
	load->sair();
	


	//imprime(grafo,n_vertices);

return 0;
}
void atualizar_grau(int vertice_queimado,vector<int>&grau){
  for(int i=0;i<n_vertices;i++){
	if(grafo[i][vertice_queimado]==1){//estao conectados
		grau[i]--;//o grau intocavel diminui em 1
 
	}
  }
}
void atualizar_proximidade(int vertice_queimado,vector<int>estado,vector<int>&proximidade){

for(int i=0;i<n_vertices;i++){
	if(estado[i]==intocado){//se nao estah queimado e nem defendido calcule a distancia.
		if(distancia[i][vertice_queimado]<proximidade[i]){
			proximidade[i]=distancia[i][vertice_queimado];
		}	
	}
}

}
void floydWarshall(vector<vector<int>> graph) {
  int nV= graph[0].size();  

  for (int i = 0; i < nV; i++)
    for (int j = 0; j < nV; j++){
		distancia[i][j] = graph[i][j];
    }	
  // Adding vertices individually
  for (int k = 0; k < nV; k++) {
    for (int i = 0; i < nV; i++) {
      for (int j = 0; j < nV; j++) {
        if (distancia[i][k] + distancia[k][j] < distancia[i][j])
          distancia[i][j] = distancia[i][k] + distancia[k][j];
      }
    }
  }
  //imprime(distancia,nV);
}

void liga(int a,int b,vector<vector<int>>&grafo){
	grafo[a][b]=grafo[b][a]=1;
}
void imprime(vector<vector<int>>grafo,int n){
for(int i=0;i<n;i++)
	for(int  j=0;j<n;j++){
		cout<<grafo[i][j]<<" ";
	}
	cout<<endl;
}

void draw(){

   string txt="graph \{ ratio=\"fill\";\nsize=\"7.0,7.0!\";\nmargin=0;\n";

 for(int i=0;i<n_vertices;i++){
   for(int j=i+1;j<n_vertices;j++){
	if(grafo[i][j]==1){
		txt+=to_string(i)+" -- ";
                txt+=to_string(j)+";\n";
	}
   } 
 }
 for(int i=0;i<n_vertices;i++){
	txt+=to_string(i)+cor_vertice[i];
 }
 txt+="node[shape=point, height=4, width=2];}";


//A -- B;\nA -- C;\ncores_AKI;
	

 arq=fopen("hw.dot","w");
 fprintf(arq,"%s\n",txt.c_str());
 fclose(arq);
 system("dot -Tpng hw.dot -o hw.png");
}
void atualiza_vertice(int numero,string cor){
	cor_vertice[numero]=cor;
}