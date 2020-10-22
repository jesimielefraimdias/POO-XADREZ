#ifndef PEAO_H_
#define PEAO_H_


#include <iostream>
#include "Peca.h"

class Peao:public Peca{
	private:
		int primeiroMov;
	public:
		Peao(bool color);//Iniciamos a peça com a respectiva cor.
		int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n);
		int getPrimeiroMov();
};

#endif
