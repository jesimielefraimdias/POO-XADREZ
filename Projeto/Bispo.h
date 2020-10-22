#ifndef BISPO_H_
#define BISPO_H_

#include <iostream>
#include "Peca.h"

class Bispo:public Peca{
	public:
		Bispo(bool color);//Iniciamos a peça com a respectiva cor.
		int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n);
};

#endif
