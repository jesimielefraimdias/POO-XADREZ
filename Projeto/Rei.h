#ifndef REI_H
#define REI_H_

#include <iostream>
#include "Peca.h"

class Rei:public Peca{
	private:
		bool roque;
	public:
		Rei(bool color);//Iniciamos a peça com a respectiva cor.
		int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n);
		bool checaRoque(bool rock);
		
};
#endif
