#ifndef JOGO_H_
#define JOGO_H_

#include "Jogador.h"
#include "Tabuleiro.h"
#include "Peca.h"
#include <iostream>

using std::string;

class Jogo{
	private:
		//Por definição, o jogador 0 sempre terá as brancas, fazendo-o assim, sempre ser o primeiro.
		static const int quantPecas = 16;
		//Objetos que são os jogadores.
		Jogador *jogador_0; 
		Jogador *jogador_1;
		//Peças dos jogadores.
		Peca *pretas[quantPecas];
		Peca *brancas[quantPecas];
		//Enum que representa a vez.
		enum v{JOGADOR0,JOGADOR1}; 
		//Enum que representa os estados da variável estado.
		enum e{ENTRADA_INVALIDA = -1, INICIO_JOGO, MEIO_JOGO, BRANCO_EM_XEQUE, PRETO_EM_XEQUE, RECEBEU_XEQUE_MATE, PAUSAR, RENDER};

		//Criamos um atributo Tabuleiro.
		Tabuleiro *tab; 
		
		//Atributos para representar a vez e o estado do jogo.
		bool vez; 
		int estado; 	
	public:
		//O construtor do jogo recebe dois objetos Jogador que serão os jogadores.
		Jogo(const string &nome_jogador0, const string &nome_jogador1); 
		~Jogo();
		void estadoDoJogo();	/*O estado do jogo, imprimi o estado atual (inicio do jogo, meio do jogo, xeque (e quem está em xeque) e xeque-mate (e quem recebeu xeque-mate) */
		void mudarVezDoJogador();   //Muda a vez do jogador.
		void interface();		//Uma sub interface.
		void play();			//Método que inicia o jogo.
		void salvarJogo(queue<string> jogadas); //Método para salvar o jogo em um arquivo.
		void carregarJogo(); //Método para carregar o jogo.
		int getEstado() const;
};

#endif	
