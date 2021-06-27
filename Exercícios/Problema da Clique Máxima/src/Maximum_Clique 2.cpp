#include"funcoes.h"


int N_VERTICES;
int N_ARESTAS;
std::stack<pair<vector<int>, vector<int> > >pilha; //PILHA DE ESTADOS(VERTICES NA CLIQUE/VERTICES QUE NAO ESTAO)
std::vector<int>Q, K; //estao /nao estao
bool **grafo, *clique; //GRAFO COM SUAS LIGACOES
void libera();
int main()
{       cout<<"DIGITE N VERT. E N AREST"<<endl;
        cin>>N_VERTICES>>N_ARESTAS; //le o numero de vertices e arestas
        
        inicializa_grafo();
	inicializa_clique();	
	le_entrada();
       

	cria_vet_vertices();

	pilha.push(std::make_pair(std::vector<int>(Q), std::vector<int>(K))); //inicializa a pilha de estados

	while(!pilha.empty())
	{

		pair<vector<int>, vector<int> >auxiliar; //remove o estado do topo da pilha
		auxiliar = pilha.top();
		pilha.pop();

		copia(Q, auxiliar.first); //Q<= first
		copia(K, auxiliar.second); //K<=second

		std::cout << "i am here! (1)" << std::endl;

		std::cout << "Q: ";
		for(vector<int>::iterator it = Q.begin(); it != Q.end(); it++)
		{
			cout << *it << " ";

		}

		std::cout << std::endl << "i am here! (2)" << std::endl;
		std::cout << "K: ";
		for(vector<int>::iterator it = K.begin(); it != K.end(); it++)
		{
			cout << *it << " ";

		}

		std::cout << std::endl << "i am here! (3)" << std::endl;

		cout << Q.size() << " " << K.size();
		cout << endl;
		std::cout << "i am here! (4)" << std::endl;
		int counter = 1;
		while(K.size() != 0 && tam_clique() < Q.size() + K.size())
		{
			std::cout << "i am here! (5) (" << counter++ << ")" << std::endl;
			std::cout << "before K: ";
			for(std::vector<int>::iterator it = K.begin(); it != K.end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;
			//vector<int>::iterator vert_dt = --K.end(); //deletou o  vértice v de K
			//std::cout << "*vert_dt value: " << *vert_dt << std::endl;
			int v = K[0];
			std::cout << "v: " << v << std::endl;
			std::cout << "   inside 1" << std::endl;
			//K.pop_back();
			K.erase(K.begin());
			std::cout << "after K: ";
			for(std::vector<int>::iterator it = K.begin(); it != K.end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;
			std::cout << "   inside 2" << std::endl;
                        pilha.push(make_pair(std::vector<int>(Q), std::vector<int>(K))); //L 7
			std::cout << "   inside 3" << std::endl;
			//se v está ligado com todos os vértices de Q ele é adicionado em Q
			//obs : se clique vazia v eh adicionado, o "novo" K serah os vizinhos de v que
			//nao estao em Q
			//adiciona_v(*vert_dt);//Passa o Q e vértice deletado de K
			std::cout << "Q before: ";
			for(std::vector<int>::iterator it = Q.begin(); it != Q.end(); ++it)
				std::cout << *it << " ";
			adiciona_v(v);
			std::cout << "   inside 4" << std::endl;
			//atualiza_k(*vert_dt);
			atualiza_k(v);
			std::cout << "   inside 5" << std::endl;
			std::cout << "Q after: ";
			for(std::vector<int>::iterator it = Q.begin(); it != Q.end(); ++it)
				std::cout << *it << " ";
			std::cout << std::endl;

	

		}
	if(tam_clique() < Q.size())
		{
			adiciona_na_clique();//atualiza clique
		}



	}
 
 printa_clique();
libera();

	return 0;
}




void  printa_clique()
{

  

	std::cout << "printing..." << std::endl;

	for(int i = 0; i < N_VERTICES; i++)
	{
		if(faz_parte(i))
			cout<<i<<" ";
	}
         cout<<"("<<tam_clique()<<")";






}
void copia(vector<int>& vet1, vector<int>& vet2)
{
	vet1.clear();
	for(vector<int>::iterator it = vet2.begin(); it != vet2.end(); ++it)
	{

		vet1.push_back(*it);

	}

}
void adiciona_na_clique()
{
	memset(clique, false, sizeof(bool) * N_VERTICES);//zerou clique
	vector<int>::iterator it ;

	for(it = Q.begin(); it != Q.end(); ++it)
	{
		clique[*it] = true; //atualiza a clique de acordo com a posicao
	}

}

void atualiza_k(int v)
{
	/*vector<int>::iterator it;
	std::cout << "inside atualiza_k (1)" << std::endl;
	bool *aux = retorna_vizinhos(v);
	std::cout << "inside atualiza_k (2)" << std::endl;
	sort(K.begin(), K.end());
	std::cout << "inside atualiza_k (3)" << std::endl;

	std::cout << "vector K: ";
	for(std::vector<int>::iterator _it = K.begin(); _it != K.end(); ++_it)
		std::cout << *_it << " ";
	std::cout << std::endl;

	//Verifica  os vértices de Q
	int counter = 1;

	std::vector<int> erase_elements;
	for(it = K.begin(); it != K.end(); ++it)
	{
		std::cout << "inside atualiza_k (4) (" << counter++ << ")" << std::endl;
		//se v nao for vizinho de um vértice de Q sai do laço
		std::cout << (*it ? "!= NULL" : "== NULL") << std::endl;
		if(!aux[*it]) //se nao for vizinho de v
		{
			std::cout << "*it = " << *it << std::endl;
			std::cout << "before if" << std::endl;

			for(std::vector<int>::iterator _it = K.begin(); _it != K.end(); ++_it)
				std::cout << *_it << " ";
			std::cout << std::endl;

			erase_elements.push_back(*it);

			std::cout << "after if" << std::endl;
		}

	}

	for(std::vector<int>::iterator erase = erase_elements.begin(); erase != erase_elements.end(); ++erase)
	{
		std::vector<int>::iterator find = std::find(K.begin(), K.end(), *erase);

		if(find == K.end()) continue;
		std::cout << "removing element: " << *find << std::endl;

		K.erase(find);
	}

	std::cout << "inside atualiza_k (5)" << std::endl;*/

	bool* neighbours = retorna_vizinhos(v);
	std::vector<int> new_K, v_neighbours;

	std::cout << "inside atualiza_k, v: " << v << std::endl;

	for(int i = 0; i < N_VERTICES; i++)
	{
		bool is_neighbour = neighbours[i];

		if(!is_neighbour) continue;

		std::cout << "neighbour: " << i << std::endl;

		v_neighbours.push_back(i);
	}

	for(std::vector<int>::iterator it = K.begin(); it != K.end(); it++)
	{
		std::cout << "checking " << *it << std::endl;
		std::vector<int>::iterator find = std::find(v_neighbours.begin(), v_neighbours.end(), *it);

		if(find == v_neighbours.end())
		{
			std::cout << "is not neighbour" << std::endl;
			continue;
		}
		std::cout << "is neighbour" << std::endl;
		new_K.push_back(*it);
	}
	std::cout << "new_K finishing function: ";
	for(std::vector<int>::iterator it = new_K.begin(); it != new_K.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;

	copia(K, new_K);
	std::cout << "K finishing function: ";
	for(std::vector<int>::iterator it = K.begin(); it != K.end(); ++it)
		std::cout << *it << " ";
	std::cout << std::endl;
}

void adiciona_v(int v)
{
	/*vector<int>::iterator it;
	bool esta = true;
	bool *aux = retorna_vizinhos(v);
	sort(Q.begin(), Q.end());

	if(Q.empty())
	{

		Q.push_back(v);
		return;
	}
	//Verifica  os vértices de Q
	for(it = Q.begin(); it != Q.end(); ++it)
	{
		//se v nao for vizinho de um vértice de Q sai do laço
		if(!aux[*it]) //se nao for vizinho de v
		{
			esta = false;
			break;
		}

	}

	if(esta)
	{
		Q.push_back(v);
	}
	return;*/
	Q.push_back(v);
}


int tam_clique()
{
	int i = 0, tam = 0;

	while(i < N_VERTICES)
	{

		if(faz_parte(i))tam++;
		i++;
	}

	return tam;
}
//adiciona  os VERTICES  ao vetor K
void cria_vet_vertices()
{

	for(int i = 0; i < N_VERTICES; i++)
	{
		K.push_back(i); //k[i]=i

	}



}
void le_entrada()
{
int i;
char c;

    for(i=0;i<N_ARESTAS;i++){
                             int x,y;
                             
        		      cin>>x>>y;
        
                             adiciona_no_grafo(x,y);
        
    }
    

}
void inicializa_clique()
{clique=(bool*)malloc(sizeof(bool)*N_VERTICES);
	int i;
	for(i = 0; i < N_VERTICES; i++)
	{

		clique[i] = false;
	}


}
void inicializa_grafo()
{ grafo=(bool**)malloc(sizeof(bool*)*N_VERTICES);
	int i, j;
	for(i = 0; i < N_VERTICES; i++)
	{grafo[i]=(bool*)malloc(sizeof(bool)*N_VERTICES);
		for(j = 0; j < N_VERTICES; j++)
		{
			grafo[i][j] = false;

		}
	}


}
void adiciona_no_grafo(int x, int y)
{
	grafo[x][y] = true;
        grafo[y][x] = true;

}
//vai retornar vizinhos do vértices removidos que não estão na clique
bool * retorna_vizinhos(int vert)
{
	return grafo[vert];
}

bool faz_parte(int vert)
{
	return clique[vert];

}

void libera(){
free(clique);
int i, j;
	for(i = 0; i < N_VERTICES; i++)free(grafo[i]);
free(grafo);
}
