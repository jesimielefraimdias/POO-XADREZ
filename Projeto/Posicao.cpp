#include "Posicao.h"
#include <iostream>

//Construtor simples que inicializa a peca com a posição vazia.
Posicao::Posicao(Peca *p){
	peca = p;
}
//Métodos set e get.
void Posicao::setPeca(Peca *p){	peca = p; }

Peca* Posicao::getPeca(){
	return peca;
}
