#include "Cavalo.h"

Cavalo::Cavalo(bool color):Peca(color,'c'){
}


int** Cavalo::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
	
	if( //Não irei otimizar nenhuma comparação na primeira fase.
		//Aqui possui todas as 8 possíveis possições que um cavalo pode andar em L
   !((linhaOrigem+2 == linhaDestino && colunaOrigem+1 == colunaDestino) ||
	(linhaOrigem+1 == linhaDestino && colunaOrigem+2 == colunaDestino) ||
	(linhaOrigem-1 == linhaDestino && colunaOrigem+2 == colunaDestino) ||
	(linhaOrigem-2 == linhaDestino && colunaOrigem+1 == colunaDestino) ||
	(linhaOrigem-2 == linhaDestino && colunaOrigem-1 == colunaDestino) ||
	(linhaOrigem-1 == linhaDestino && colunaOrigem-2 == colunaDestino) ||
	(linhaOrigem+1 == linhaDestino && colunaOrigem-2 == colunaDestino) ||
	(linhaOrigem+2 == linhaDestino && colunaOrigem-1 == colunaDestino)
	)){
		return 0;
	}
	int **posicoes = alocarMatrizPosicoes(n = 2);
	
	posicoes[0][1] = linhaOrigem;
	posicoes[0][1] = colunaOrigem;
	posicoes[1][0] = linhaDestino;
	posicoes[1][1] = colunaDestino;
	
	return posicoes;
}

