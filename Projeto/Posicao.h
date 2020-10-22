#ifndef POSICAO_H_
#define POSICAO_H_


#include "Peca.h"
#include <iostream>

class Posicao{
	private:
		Peca *peca;				
	public:
		Posicao(Peca *p = 0);
		Peca* getPeca();
		void setPeca(Peca *p);
		
};
#endif
