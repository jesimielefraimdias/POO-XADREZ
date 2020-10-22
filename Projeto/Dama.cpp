#include "Dama.h"
#include <cmath>

/*
//Construtor que inicializa o atributo cor e o atributo capturada para falso.
Dama::Dama(bool color):Peca(color,'d'){}
*/
Dama::Dama(bool color):Peca(color,'d'){
}

int** Dama::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
	//Existem 8 possíveis posições que o rei pode andar.
	if((fabs(linhaOrigem - linhaDestino) != fabs(colunaOrigem - colunaDestino)) &&
	(linhaOrigem != linhaDestino && colunaOrigem != colunaDestino)) {
		return 0;
	}
	n = 1;
	
	if(linhaOrigem != linhaDestino && colunaOrigem != colunaDestino) n += fabs(linhaOrigem - linhaDestino);
	else if(linhaOrigem != linhaDestino && colunaOrigem == colunaDestino) n += fabs(linhaOrigem - linhaDestino);
	else n += fabs(colunaOrigem - colunaDestino);
	
	int sinalI;
	int sinalJ;
	sinalI = sinalJ = 1;
	int **posicoes = alocarMatrizPosicoes(n);
	
	//primeiro quadrante.
	if(linhaOrigem > linhaDestino && colunaOrigem < colunaDestino){
		sinalI  = -sinalI ;
	}	
	//segundo quadrante.
	else if(linhaOrigem > linhaDestino && colunaOrigem > colunaDestino){
		sinalI =-sinalI ;
		sinalJ =-sinalJ;
	}
	//terceiro quadrante.
	else if(linhaOrigem < linhaDestino && colunaOrigem > colunaDestino){
		sinalJ =-sinalJ;
	}
	else if(linhaOrigem == linhaDestino){
		if(colunaOrigem > colunaDestino) /*((colunaOrigem - colunaDestino) > 0)*/ sinalJ = - sinalJ;
		sinalI = 0;
	}else if(colunaOrigem == colunaDestino){
		if(linhaOrigem > linhaDestino)/*((linhaOrigem - linhaDestino) > 0)*/ sinalI = - sinalI;
		sinalJ = 0;
	}

	//quarto quadrante, mantém os dois sinais = 1.
	
	for(int k = 0, i = 0, j = 0; k < n; k++, i+=1*sinalI, j+=1*sinalJ){
		posicoes[k][0] = linhaOrigem+i;
		posicoes[k][1] = colunaOrigem+j;
	}
	return posicoes;
}
/*
int** Dama::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
	int **matrizPosicoes = 0;
	
	if((matrizPosicoes = Bispo::checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, n)) == 0){
			matrizPosicoes = Torre::checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, n);
	}
	
	
	return matrizPosicoes;
}
*/
