#ifndef PECA_H_
#define PECA_H_

#include <iostream>

class Peca{
	protected:
		bool capturada; //True se estiver capturada ou false se estiver livre.
		const bool cor; //True se a cor for preta ou false se a cor for branca.
		const char peca;
	public:
		Peca(bool color, char p);
		char desenha();//Retorna um char com a letra da peça (a cor dela fará o retorno ser maiúscolo u minúsculo.)
		virtual int** checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n) = 0;
		void captura();
		bool getCapturada(); //Retorna true caso a peça esteja capturada.
		bool getCor();
		int** alocarMatrizPosicoes(int &n);
};

#endif
