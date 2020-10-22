#include "Peao.h"

using std::cout;
using std::endl;

//Construtor que inicializa o atributo cor e o atributo capturada para falso.
Peao::Peao(bool color):Peca(color,'p'){
	primeiroMov = 0;
}


int** Peao::checaMovimento(int linhaOrigem, int colunaOrigem, int linhaDestino, int colunaDestino, int &n){
	int aux = 1;
	int **posicoes = 0;
	
	if(!cor){ //Se a cor for branca, teremos que descer de um em um na nossa matriz com o pião, por isso, fazemos
			  //a nossa auxiliar ficar negativa.
		aux = -aux;
	}
	
	if(linhaOrigem+aux == linhaDestino && (colunaOrigem == colunaDestino || colunaOrigem+1 == colunaDestino || colunaOrigem-1 == colunaDestino)){
		posicoes = alocarMatrizPosicoes(n = 2);
		posicoes[0][0] = linhaOrigem;
		posicoes[0][1] = colunaOrigem;
		posicoes[1][0] = linhaDestino;
		posicoes[1][1] = colunaDestino;
		primeiroMov = 1;
	} else if(primeiroMov == 0 && linhaOrigem+2*aux == linhaDestino && colunaOrigem == colunaDestino){
		posicoes = alocarMatrizPosicoes(n = 3);
		posicoes[0][0] = linhaOrigem;
		posicoes[0][1] = colunaOrigem;
		posicoes[1][0] = linhaOrigem+aux;
		posicoes[1][1] = colunaDestino;
		posicoes[2][0] = linhaDestino;
		posicoes[2][1] = colunaDestino;
		primeiroMov = 2;
	} 
	
	return posicoes;
}

int Peao::getPrimeiroMov(){
	return primeiroMov;
}


