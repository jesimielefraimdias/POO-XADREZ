#ifndef JOGADOR_H_
#define JOGADOR_H_


#include <iostream>
#include "Peca.h"
#include <iostream>

using std::string;

/*Essa é uma classe genérica para podermos fazer a implementação parcial do jogo, ou seja, ela está muito limitada.*/
class Jogador{
		private:
			static const int quant = 16;
			const string nome; 					//Nome do jogador.
			const bool cor; 				//Vai ser importante para definir a cor das peças do jogador.
			Peca **pecas;
		public:
			~Jogador();
			Jogador(const Jogador &jogador);
			Jogador(const string &n, const bool &color, Peca **p); 	//Construtor que recebe a cor e o nome do jogador.
			string getNome();				//Apenas retorna o nome do jogador.
			void imprimirCapturadas(); 		//Imprimi todas as peças capturadas.
};

#endif
