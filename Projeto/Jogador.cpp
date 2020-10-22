#include "Jogador.h"

using std::cout;
using std::endl;

/*Como já foi explicado no Jogador.h temos dois construtores para diferentes ocasiões. */
Jogador::Jogador(const string &n, const bool &color, Peca **p):nome(n),cor(color),pecas(p){
}

Jogador::Jogador(const Jogador &jogador):nome(jogador.nome),cor(jogador.cor),pecas(jogador.pecas){
}
Jogador::~Jogador(){
	for(int i = 0; i < quant; i++){
		pecas[i] = 0;
	}
}

//Apenas retorna o nome.
string Jogador::getNome(){
	return nome;
}

void Jogador::imprimirCapturadas(){
	int capturadas = 0;
	bool aux = false;
	cout<<"						";
	for(int i = 0; i < quant; i++){
		if(capturadas == 8 && aux == false){
			cout<<endl<<"						";
			aux = true;
		}
		if(pecas[i]->getCapturada() == true){
			if(pecas[i]->getCor() == true) cout<<"\033[1;30m"<<pecas[i]->desenha()<<"\033[0m";
			else cout<<pecas[i]->desenha();
			cout<<"    ";
			capturadas+=1;
		}
	}
	cout<<endl;	
}




