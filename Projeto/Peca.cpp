#include "Peca.h"

using std::bad_alloc;
using std::cout;
using std::endl;

Peca::Peca(bool color, char p):cor(color),peca(p){
	capturada = false;
}

//O atributo capturada é trocado para true.
void Peca::captura(){
	capturada = true;
}

char Peca::desenha(){
	//Se for preta é maiúsculo.
	if(cor) return toupper(peca);
	
	return peca;
}

//Retorna true caso a peça esteja capturada.
bool Peca::getCapturada(){
	return capturada;
}

bool Peca::getCor(){
	return cor;
}

int** Peca::alocarMatrizPosicoes(int &n){
	int **posicoes;
	try {
		posicoes = new int*[n];
		for(int i = 0; i < n; i++) posicoes[i] = new int[2];
	}
	catch(bad_alloc){
		cout<<"Memória insuficiente!"<<endl;
		exit(1);
	}
	return posicoes;
}
