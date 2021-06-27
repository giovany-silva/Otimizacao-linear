#include<bits/stdc++.h>
using namespace std;
int bom,N_VERTICES,max_d,fs,k;
set<pair<int,int>>lista_arestas;
void gera_instancia();
int porcentagem;
int main()
{
//número de bombeiros, números de vértices, máximo defensável por rodada, foco inicial, número de dias consec.

	cout<<"\nDigite o número de bombeiros\n";
	cin>>bom;

	cout<<"DIGITE O n vert.";
	cin>>N_VERTICES;

	cout<<"\nDigite a porcentagem de densidade requerida\n";
	cin>>porcentagem;

	cout<<"\nDigite o número de máximo de vértices defensaveis por rodada\n";
	cin>>max_d;

	cout<<"\nDigite o foco inicial\n";
	cin>>fs;

	cout<<"\nDigite o número de dias consec.\n";
	cin>>k;

	gera_instancia();
	return 0;
}


void gera_instancia()
{
FILE* arq=NULL;

arq=fopen("instancia().txt","w");
	while((lista_arestas.size()/(double)(N_VERTICES*(N_VERTICES-1)/2))*100<=porcentagem){
	cout<<(lista_arestas.size()/(double)(N_VERTICES*(N_VERTICES-1)/2))*100<<endl;
		vector<int>v;
		
		while(1){
			int a=rand()%N_VERTICES;
			int b=rand()%N_VERTICES;
		if(a!=b){
	        	v.push_back(a);
        		v.push_back(b);
			break;
		}


	  	}
        		 sort(v.begin(),v.end());

	                lista_arestas.insert(make_pair(v[0],v[1]));         
  		

	}

fprintf(arq,"%d\n%d\n%d\n%d\n%d\n",bom,N_VERTICES,max_d,fs,k);

for(pair<int,int>p:lista_arestas){
	fprintf(arq,"%d %d\n",p.first,p.second);

}

fclose(arq);
}