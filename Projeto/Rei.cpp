#include "Rei.h"


//Construtor que inicializa o atributo cor e o atributo capturada para falso.
Rei::Rei(bool color):Peca(color,'r'){
	roque = true;
}

int** Rei::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
	//Existem 8 possíveis posições que o rei pode andar.
	if(((linhaOrigem+1 != linhaDestino) && (linhaOrigem-1 != linhaDestino) && (linhaOrigem != linhaDestino)) ||
		((colunaOrigem+1 != colunaDestino) && (colunaOrigem-1 != colunaDestino) && (colunaOrigem != colunaDestino))){
		return 0;
	}

	int **posicoes = alocarMatrizPosicoes(n = 2);

	
	posicoes[0][0] = linhaOrigem;
	posicoes[0][1] = colunaOrigem;
	posicoes[1][0] = linhaDestino;
	posicoes[1][1] = colunaDestino;
	
	return posicoes;
}

bool Rei::checaRoque(bool rock){	
	return rock & roque;
}
