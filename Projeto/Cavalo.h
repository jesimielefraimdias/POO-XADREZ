#ifndef CAVALO_H_
#define CAVALO_H_

#include <iostream>
#include "Peca.h"

class Cavalo:public Peca{
	public:
		Cavalo(bool color);	//Iniciamos a peça com a respectiva cor.
		int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n);

};

#endif
