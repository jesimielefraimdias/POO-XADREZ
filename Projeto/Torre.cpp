#include "Torre.h"
#include <math.h>


//Construtor que inicializa o atributo cor e o atributo capturada para falso.
Torre::Torre(bool color):Peca(color,'t'){
}

int** Torre::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
	//A torre só anda se a o destino tiver a linha ou coluna igual ao da origem.
	if(linhaOrigem != linhaDestino && colunaOrigem != colunaDestino) return 0;
	
	int sinalI = 1;
	int sinalJ = 1;
	n = 1;
	
	if(linhaOrigem != linhaDestino) n += fabs(linhaOrigem - linhaDestino);
	else n += fabs(colunaOrigem - colunaDestino);
	
	int **posicoes = alocarMatrizPosicoes(n);
	
	
	if(linhaOrigem == linhaDestino){
		if(colunaOrigem > colunaDestino) /*((colunaOrigem - colunaDestino) > 0)*/ sinalJ = - sinalJ;
		sinalI = 0;
	}else{
		if(linhaOrigem > linhaDestino)/*((linhaOrigem - linhaDestino) > 0)*/ sinalI = - sinalI;
		sinalJ = 0;
	}

	for(int k = 0, i = 0, j = 0; k < n; k++, i+=1*sinalI, j+=1*sinalJ){
		posicoes[k][0] = linhaOrigem+i;
		posicoes[k][1] = colunaOrigem+j;
	}
	
	return posicoes;
}
