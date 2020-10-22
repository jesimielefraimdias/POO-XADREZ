#ifndef TORRE_H_
#define TORRE_H_

#include <iostream>
#include "Peca.h"


class Torre:public Peca{
	private:
		bool roque;
	public:
		Torre(bool color);//Iniciamos a peça com a respectiva cor.
		int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n); //Checa se o movimento é válido
																									 //apenas dentro da matriz.
};

#endif
