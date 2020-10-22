#ifndef TABULEIRO_H_
#define TABULEIRO_H_

#include <iostream>
#include <queue>

#include "Posicao.h"
#include "Tabuleiro.h"
#include "Peca.h"

using std::queue;
using std::string;
using std::ostream;
using std::istream;


class Tabuleiro{
	private:
		static const int tamanho = 8;		//Uma constante para a matriz.
		Posicao *tab[tamanho][tamanho];		//uma matriz de Posicao de 8 X 8.
		//Representa os estados do en Passant da linha D e E.
		int enPassantD[tamanho];			
		int enPassantE[tamanho];
		queue<string> jogadas;  //Fila para guardar as jogadas em um arquivo.
		int estadoTabuleiro;
	
	public:
		//Construtor do tabuleiro que recebe as peças brancas e pretas e a quantidade para coloca-las no tabuleiro.
		Tabuleiro(Peca **pretas, Peca **brancas,const int quantPecas, const int &estado);
		~Tabuleiro(); //Destrutor.
		void imprimirTabuleiro() const;	//Imprimi o tabuleiro.
		void encontrarMeuRei(int &linha, int&coluna, const bool vez); //Encontra o rei do jogador.
		//Faz a checagem se o enPassant é valido e se for retorna a peça que vai ser capturada por enPassant.
		Peca* checaEnPassant(const int &linhaOrigem, const int &colunaOrigem, const int &linhaDestino, const int &colunaDestino, const bool &vez, int &enPassant);
		//Controla o EnPassant atualizando os atributos enpassantD e enpassantE.
		void controleEnPassant(const int &linhaOrigem, const int &colunaOrigem, const int &linhaDestino, const int &colunaDestino);
		//Atualizamos os atributos de EnPassant a cada jogada.
		void atualizaEnPassant();
		//Checamos os movimentos e retornamos -1 para erro, 2 para você deixou o outro jogador em xeque e 3 para o outro jogador recebeu xeque mate.
		int checaMovimentoNoTabuleiro(const string& origem, const string& destino, const bool &vez);
		//Verificamos se a jogada passada é válida.
		bool verificaJogada(const string& origem, const string& destino, int &linhaOrigem, int &colunaOrigem, int &linhaDestino, int &colunaDestino);
		//Verificamos se um dado jogador está em xeque.
		bool verificarXeque(const int &linha, const int &coluna, const bool &vez);
		//Verificamos se uma dada posição ou peça pode ser alcançada por um dado jogador.
		bool verificarCaptura(const int &linhaOrigem, const int &colunaOrigem,const int &linhaDestino, const int &colunaDestino, const bool vez);
		
		//Retorna a quantidade de jogadas que está no tabuleiro.
		int quantJogadas() const;
		//Guarda uma dada jogada.
		void guardarJogada(const string& j);
		//Retorna a fila de jogadas que é o nosso atributo.
		queue<string>getJogadas() const;
		//Imprimi o tabuleiro.
		friend ostream & operator<< (ostream & o, Tabuleiro &tab);
		//Recebe uma jogada do jogador.
		friend istream &operator>> (istream & i, Tabuleiro &tab);
		int getEstadoTabuleiro() const;
		void setEstadoTabuleiro(const int &estado);
};

#endif
