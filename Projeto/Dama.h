#ifndef DAMA_H_
#define DAMA_H_

#include <iostream>
#include "Peca.h"

//class Dama:public virtual Bispo, public virtual Torre{
class Dama:public Peca{
	public:
		Dama(bool color);	//Iniciamos a peça com a respectiva cor.
		int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n);
		

};

#endif
