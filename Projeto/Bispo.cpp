#include "Bispo.h"
#include <math.h>

//Construtor que inicializa o atributo cor e o atributo capturada para falso.
Bispo::Bispo(bool color):Peca(color,'b'){
}


/*Esse método identifica uma constante K para linha e para coluna, e se o módulos delas serem iguais,
 * então a peça está andando corretamente. */
int** Bispo::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
		
	if(fabs(linhaOrigem - linhaDestino) != fabs(colunaOrigem - colunaDestino)) return 0;
	
	n = fabs(linhaOrigem - linhaDestino)+1;
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
	//quarto quadrante, mantém os dois sinais = 1.
	
	for(int k = 0, i = 0, j = 0; k < n; k++,i+=1*sinalI,j+=1*sinalJ){
			posicoes[k][0] = linhaOrigem+i;
			posicoes[k][1] = colunaOrigem+j;
	}
	return posicoes;
}
