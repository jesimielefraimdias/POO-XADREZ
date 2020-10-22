#include "Jogo.h"
#include "Torre.h"
#include "Bispo.h"
#include "Cavalo.h"
#include "Dama.h"
#include "Peao.h"
#include "Rei.h"
#include <string>
#include <iostream>
#include <fstream>
using std::cin;
using std::cout;
using std::endl;
using std::stoi;
using std::bad_alloc;
using std::ifstream;
using std::ofstream;

//Recebemos o nome dos jogadores.
Jogo::Jogo(const string &nome_jogador0, const string &nome_jogador1){
	vez = JOGADOR0; //Inicia com false, pois o false representa as brancas e as brancas sempre serão as primeiras.
	estado = INICIO_JOGO; //Inicio do jogo é o 0.
	//Tentamos alocar as peças de cada jogador.
	try{
		pretas[0] = new Torre(true);
		pretas[1] = new Cavalo(true);
		pretas[2] = new Bispo(true);
		pretas[3] = new Dama(true);
		pretas[4] = new Rei(true);
		pretas[5] = new Bispo(true);
		pretas[6] = new Cavalo(true);
		pretas[7] = new Torre(true);
		
		brancas[0] = new Torre(false);
		brancas[1] = new Cavalo(false);
		brancas[2] = new Bispo(false);
		brancas[3] = new Dama(false);
		brancas[4] = new Rei(false);
		brancas[5] = new Bispo(false);
		brancas[6] = new Cavalo(false);
		brancas[7] = new Torre(false);
		
		for(int j = quantPecas/2; j < quantPecas; j++){ 
			pretas[j] = new Peao(true);
			brancas[j] = new Peao(false);
		}
		tab = new Tabuleiro(pretas,brancas,quantPecas,estado);
		jogador_1 = new Jogador(nome_jogador1,true,pretas);
		jogador_0 = new Jogador(nome_jogador0,false,brancas);
	
	//Usamos o catch para indicar um bad_alloc.
	}catch(bad_alloc){
		cout<<"Memória insuficiente"<<endl;
		exit(1);
	}
}

Jogo::~Jogo(){
	
	delete tab;
	delete jogador_0;
	delete jogador_1;
	
	for(int i = 0; i < quantPecas; i++){
		 delete pretas[i];
		 delete brancas[i];
	}
	
}

//Após uma jogada do jogador atual, é chamado esse método para trocar a vez.
void Jogo::mudarVezDoJogador(){
	vez = tab->quantJogadas()%2;
}


/*Aqui temos uma série de mensagens para exibir o estado do jogo atual.
 * A cada nova jogada ele é chamado, e por isso, o tabuleiro a cada jogada é atualizado.*/
void Jogo::estadoDoJogo(){
		system("clear"); //Vai ser usado para dar uma falsa impressão de dinamismo ao jogo.
		cout<<"\n\n\n"<<endl;
		ostream &operator<< (ostream & o, Tabuleiro &tab);
		
		cout<<"						";
		if(estado == MEIO_JOGO){ 
			cout<<"  	 JOGO EM ANDAMENTO:"<<endl;
			cout<<"							";
			cout<<"Vez do jogador ";
			
			if(vez == JOGADOR0) 			 cout<<jogador_0->getNome();
			else if(vez == JOGADOR1) 		 cout<<jogador_1->getNome(); 
			
			cout<<"!"<<endl;
			
		}else if(estado == BRANCO_EM_XEQUE){ 
			cout<<"    O jogador "<<jogador_0->getNome()<<" está em xeque!"<<endl;
		}else if(estado == PRETO_EM_XEQUE){ 
			cout<<"    O jogador "<<jogador_1->getNome()<<" está em xeque!"<<endl;
		}
		
		else if(estado == RECEBEU_XEQUE_MATE){
			cout<<"O jogador ";
			if(vez == JOGADOR0) cout<<jogador_0->getNome();
			else 		 cout<<jogador_1->getNome(); 
			
			cout<<" recebeu xeque-mate!"<<endl;
		}else if(estado == RENDER){
			cout<<"    O jogador ";
			if(vez == JOGADOR0) cout<<jogador_0->getNome();
			else 		 cout<<jogador_1->getNome(); 
			
			cout<<" rendeu-se!"<<endl;
		}
		else if(estado == INICIO_JOGO){
			cout<<"    	    Inicio do jogo!"<<endl;
			cout<<"							";
			cout<<"Vez do jogador "<<jogador_0->getNome()<<"!"<<endl;
		}else if(estado == PAUSAR){
			cout<<"    	O jogo foi pausado!"<<endl;
		}
		jogador_0->imprimirCapturadas();
		cout<<*tab;
		jogador_1->imprimirCapturadas();
}

void Jogo::interface(){
	int opcao = 0;
	
	cout<<"JOGO DE XADREZ"<<endl;
	cout<<"_____________________________"<<endl;
	cout<<"Escolha uma opção!"<<endl;
	cout<<"1 - Novo Jogo"<<endl;
	cout<<"2 - Carregar Jogo"<<endl;
	cout<<"3 - Sair"<<endl;

	cin>>opcao;
	
	do{
		
		switch(opcao){
			case 1:
				play();
				return;
				break;
			case 2:
				carregarJogo();
				play();
				return;
				break;
			case 3:
				exit(1);
				return;
			default:
				cout << "Opção inválida!" << endl;
				cin>>opcao;
		}
	}while(opcao != 3);
}

void Jogo::play(){
	istream &operator>> (istream & i, Tabuleiro &tab);
	
	
		while(estado != RECEBEU_XEQUE_MATE && estado != PAUSAR && estado != RENDER){
			estadoDoJogo();
			do{
				
				try{
					cout<<"Digite sua jogada: ";
					cin>>*tab;
					estado = tab->getEstadoTabuleiro();
					
				}catch(int i){
					estado = i;
					if(estado == ENTRADA_INVALIDA){
						cout<<"JOGADA INVÁLIDA, DIGITE NOVAMENTE!!"<<endl;
					}
				}
			}while(estado  == ENTRADA_INVALIDA);
			mudarVezDoJogador();
		}

		if(estado == PAUSAR){
			salvarJogo(tab->getJogadas());
		}
		estadoDoJogo();
		return;
	

}		

void Jogo::salvarJogo(queue<string> jogadas){
	ofstream arquivo;
	try{
		arquivo.open("jogadasSalvas.txt");
		if(arquivo.is_open() == false) throw "O arquivo não foi aberto\n";
	}catch(string erro){
		 cout<<erro;
		 return;
	}
	
	while(jogadas.empty() == false){
		arquivo<<jogadas.front()<<"\n";
		jogadas.pop();
	}
	arquivo.close();
}

void Jogo::carregarJogo(){	
	
	int estadoAux;
	string linha;
	string origem;
	string destino;
	string erro = "O arquivo está corrompido, o jogo prosseguirá a partir daqui!";
	ifstream arquivo;
	
	try{
		arquivo.open("jogadasSalvas.txt");
		if(arquivo.is_open() == false) throw "O arquivo não existe";
	}catch(string erro){
		cout<<erro<<endl;
		exit(1);
	}
	while(getline(arquivo,linha)){
		try{
		
			if(linha.find(">>") == -1) throw erro;
			
			origem = linha.substr(0,linha.find(">>"));
			destino = linha.substr(linha.find(">>")+2,linha.size());
			if(origem.size() != 2 || destino.size() != 2) throw erro;
		
			if(((estadoAux = tab->checaMovimentoNoTabuleiro(origem,destino,vez)) == -1)){
				throw erro;
			}else {
				estado = estadoAux;
				if(vez == false && estado == 2) estado = 3;
				else if(vez == true && estado == 2) estado = 2;
				tab->guardarJogada(linha);
			}
		}catch(string err){
			cout<<endl<<err;
			arquivo.close();
			return;
		}
		
	}
	arquivo.close();
}
