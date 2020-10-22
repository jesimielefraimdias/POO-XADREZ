#include "Tabuleiro.h"
#include <string>
#include <math.h>
#include "Peao.h"

using std::cout;
using std::endl;
using std::string;
using std::stoi;


//Criamos a matriz de posições e passamos as peças para suas respectivas posições iniciais.
Tabuleiro::Tabuleiro(Peca **pretas, Peca **brancas, const int quantPecas, const int &estado){
	int t = 0;
	estadoTabuleiro = estado;
	
	for(int i = 2; i < tamanho - 2; i++){
		for(int j = 0; j < tamanho; j++){
			tab[i][j] = new Posicao();
		}
	}
	
	for(int i = 0; i < 2; i++){
		for(int j = 0; j < quantPecas/2; j++,t++){
				
				tab[i][j] = new Posicao(pretas[t]);
				tab[tamanho -1 -i][j] = new Posicao(brancas[t]);
		}
	}	
	
	for(int i = 0; i < tamanho; i++){
		enPassantD[i] = 0;
		enPassantE[i] = 0;
	}
}

//Deletamos a matriz de posições.
Tabuleiro::~Tabuleiro(){
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			tab[i][j]->setPeca(0);
			delete tab[i][j];
		}
	}
}

//Imprimi o tabuleiro e pinta as peças pretas.
void Tabuleiro::imprimirTabuleiro() const{
	Peca *aux;
	string linhas = "abcdefgh";
	cout<<endl<<endl<<"						";
	cout<<"    1   2   3   4   5   6   7   8"<<endl;
	cout<<"						";
	cout<<"   _______________________________ "<<endl;
	for(int i = 0; i < tamanho; i++){
		cout<<"						";
		cout<<linhas[i]<<" ";
		
		for(int j = 0; j < tamanho; j++){
			cout<<"| ";
			if((aux = tab[i][j]->getPeca()) == 0) cout<<" ";
			else if(aux->getCor() == true) cout<<"\033[1;30m"<<aux->desenha()<<"\033[0m";
			else cout<<aux->desenha();
			cout<<" ";		
		}
		
		cout<<"|"<<endl;
		cout<<"						";
		cout<<"  |___|___|___|___|___|___|___|___|"<<endl;		
	}
	cout<<endl<<endl;	
}

int Tabuleiro::checaMovimentoNoTabuleiro(const string& origem, const string& destino, const bool &vez){
	
	//Variáveis que irão ser passadas para o método verificarJogada.
	int linhaOrigem = -1;
	int colunaOrigem = -1;
	int linhaDestino = -1;
	int colunaDestino = -1;
	
	//Variável que irá ser passada para o checaMovimento das peças.
	int n;
	
	//Variáveis que irá ser passada para o método encontrarMeuRei.
	int linhaRei;
	int colunaRei;
	
	//Variável que será passada para o método checaEnPassant.
	int enPassant = 0;
	int retorno = -1; //Para auxiliar nos vários retornos.
	
	//Irão verificar se é possível capturar ou movimentar.
	bool ocorreuCaptura = false;
	bool ocorreuMovimento = false;
	
	
	//Desmantelamos as string para posições que podem ser usadas.
	if(verificaJogada(origem,destino,linhaOrigem,colunaOrigem,linhaDestino,colunaDestino) == false) return -1;
	Peca *pecaOrigem,*pecaDestino; //Variáveis para nos auxiliar na movimentação e captura.

	
	//Verificamos se a origem não é nula e se é a peça pertencente ao jogador.
	if((pecaOrigem = tab[linhaOrigem][colunaOrigem]->getPeca()) == 0  || pecaOrigem->getCor() != vez) return -1;
	//Verificamos se o destino não está com uma peça da nossa cor.
	if((pecaDestino = tab[linhaDestino][colunaDestino]->getPeca()) != 0 && pecaDestino->getCor() == vez) return -1;
	
	//Solicitamos a matriz de posições que retorna nulo caso seja inválida.
	int **posicoes = pecaOrigem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino,n);
	if(posicoes == 0) return -1;
	
	//Verificamos se não tem peças ocupando a locomoção.
	for(int i = 1; i < n-1; i++){
		 if(tab[posicoes[i][0]][posicoes[i][1]]->getPeca() != 0){ 
			 return -1;
		}
	}
	//Verificamos se é um peão que tem capturas e movimentações especiais.
	if(toupper(pecaOrigem->desenha()) == 'P'){
		//Se forem as linhas nas condições teremos de acionar o nosso controle dos atributos.
		if(linhaDestino == 3 || linhaDestino == 4) controleEnPassant(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino);
		//Se a origem e destino possuem a mesma coluna e o mesmo é nulo, então podemos movimentar.
		if(colunaOrigem == colunaDestino && pecaDestino == 0){
			ocorreuMovimento = true; 
		/* Se o destino e origem forem diferentes e o destino não for nulo, temos a captura do peão normal
		 * , porém, se não for, chamamos o checaEnPassant para verificar se possui a captura por en passant.*/
		} else if((colunaOrigem != colunaDestino && pecaDestino != 0) ||
		(pecaDestino = checaEnPassant(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino, vez, enPassant)) != 0){
			ocorreuCaptura = true;
		}
	} 
	//Porém, se não for um peão, o código em si é polimorfico para as demais peças.
	else {
		//Caso o destino seja vazio não temos captura.
		if(pecaDestino == 0 ) {
			ocorreuMovimento = true;
		//Se não, temos captura.
		} else {
			ocorreuCaptura = true;
		}
	}
	
	//Como não iremos mais utilir a matriz de posições podemos remover.
	 for(int i = 0; i < n; i ++){
			delete posicoes[i];
	}
	delete []posicoes;
	
	//Agora, podemos verificar as movimentações, se movimentou ou capturou então movemos a peça.
	if(ocorreuMovimento == true || ocorreuCaptura == true){
		tab[linhaDestino][colunaDestino]->setPeca(pecaOrigem); //Setando a origem e destino.
		tab[linhaOrigem][colunaOrigem+enPassant]->setPeca(0); //Apagando os rastros.
		tab[linhaOrigem][colunaOrigem]->setPeca(0);
	}
	
	if(ocorreuCaptura == true){
		pecaDestino->captura();
	}
	//Caso a movimentação não nos deixou em xeque então temos que verificar se o jogador contrário esta em xeque.
	encontrarMeuRei(linhaRei,colunaRei,!vez);//Procuramos o rei dele.
	//Se o rei dele está em xeque iremos retornar o estado 2.
	if(verificarXeque(linhaRei,colunaRei,!vez) == true){
		retorno = 2;
	} else { //Se o rei não estiver em xeque o jogo está normal.
		retorno = 1;
	}
	encontrarMeuRei(linhaRei,colunaRei,vez);//Procuramos o rei dele.
	if(verificarXeque(linhaRei,colunaRei,vez) == true){
		retorno = 3;
	}
		//Atualizamos os atributos do enPassant.
	atualizaEnPassant();
	return retorno;//Retornamos.
}

bool Tabuleiro::verificaJogada(const string& origem, const string& destino, int &linhaOrigem, int &colunaOrigem, int &linhaDestino, int &colunaDestino){
//Verificamos se a orgem e o destino são iguais.
	if(origem == destino) return false;

	//Representa as linhas que serão passadas para inteiros.
	string linhas = "ABCDEFGH";
	int n = linhas.size(); //tamanho da string.
	
	//--------------------------------------
	colunaOrigem = stoi(origem.substr(1,1))-1; //Passamos o caracter em string para inteiro.
	//--------------------------------------
	colunaDestino = stoi(destino.substr(1,1))-1; //Passamos o caracter em string para inteiro.
	//--------------------------------------
	//Passamos a posição que se encontra em caracter para inteiro.
	for(int i = 0; i < n; i++){

		if(linhas[i] == origem[0]){ linhaOrigem = i;}
		if(linhas[i] == destino[0]){ linhaDestino = i;}
		if(linhaOrigem > 0 && linhaDestino > 0 && colunaOrigem > 0 && colunaDestino > 0) break;
	}
	//Verificamos se as posições origem e destino são validas no tabuleiro.
	if(linhaOrigem < 0 || linhaOrigem >= n || linhaDestino < 0 || linhaDestino >= n || colunaOrigem < 0 || colunaOrigem >= n || colunaDestino < 0 || colunaDestino >= n) return false;
	
	return true;
}

//Controlamos o EnPassant setando estados para quem irá ser capturada e para quem irá capturar.
void Tabuleiro::controleEnPassant(const int &linhaOrigem, const int &colunaOrigem, const int &linhaDestino, const int &colunaDestino){
		
		Peao *pecaOrigem = (Peao*)tab[linhaOrigem][colunaOrigem]->getPeca();
		
		if(pecaOrigem->getCor() == false && linhaDestino == 3){
			enPassantD[colunaDestino] = 3;
		} 
		else if(pecaOrigem->getCor() == false && linhaDestino == 4 && pecaOrigem->getPrimeiroMov() == 2){
			enPassantE[colunaDestino] = 1;
		}
		else if(pecaOrigem->getCor() == true && linhaDestino == 4 ){
			enPassantE[colunaDestino] = 3;
		} 
		else if(pecaOrigem->getCor() == true && linhaDestino == 3 && pecaOrigem->getPrimeiroMov() == 2){
			enPassantD[colunaDestino] = 1;
		}
}
//Atualizamos o EnPassant a cada jogada para ficar de acordo com as regras do xadrez.
void Tabuleiro::atualizaEnPassant(){

	for(int i = 0; i < tamanho; i++){
		
		if(enPassantD[i] == 1) enPassantD[i]++;
		else if(enPassantD[i] == 2) enPassantD[i] = 0;
		
		if(enPassantD[i] >= 3 && enPassantD[i] < 5) enPassantD[i]++;
		else if(enPassantD[i] == 5) enPassantD[i] = 0;
		//else if((enPassantD[i] == 3 && (aux = tab[3][i]->getPeca()) == 0) || aux->getCor() == false) enPassantD[i] = 0;
		
		
		
		if(enPassantE[i] == 1) enPassantE[i]++;
		else if(enPassantE[i] == 2) enPassantE[i] = 0;
		
		if(enPassantE[i] >= 3 && enPassantE[i] < 5) enPassantE[i]++;
		else if(enPassantE[i] == 5) enPassantE[i] = 0;
		
	}
}

//Cheamos se o enPassant poderá ser aplicado.
Peca* Tabuleiro::checaEnPassant(const int &linhaOrigem, const int &colunaOrigem, const int &linhaDestino, const int &colunaDestino, const bool &vez, int &enPassant){
	 int j = 1; //Servirá para saber se o en Passant é para esquerda ou direita.
	 
	 //Para saber se o en Passant será para direita ou esquerda.
	 if(colunaOrigem > colunaDestino) j = -j;
	 if(tab[linhaDestino][colunaDestino]->getPeca() != 0 && colunaOrigem == colunaDestino) return 0;
	 Peca *aux = tab[linhaOrigem][colunaOrigem+j]->getPeca();
	 
	 
	 if(vez == false && linhaOrigem == 3 && enPassantD[colunaOrigem] == 5 && 
		enPassantD[colunaOrigem+j] == 2){
			enPassant = j;
			return aux;
	 }
	 
	  if(vez == true && linhaOrigem == 4 && enPassantE[colunaOrigem] == 5 && 
		enPassantE[colunaOrigem+j] == 2){
			enPassant = j;
			return aux;
	 }
	 return 0;
}

bool Tabuleiro::verificarCaptura(const int &linhaOrigem, const int &colunaOrigem,const int &linhaDestino, const int &colunaDestino, const bool vez){
	int n;
	//Criamos dois apontadores do tipo Peca para receber as pecas origem e destino que iremos trabalhar.
	Peca *pecaOrigem,*pecaDestino;

	
	//Verificamos se existe determinada peça na origem e destino.
	if((pecaOrigem = tab[linhaOrigem][colunaOrigem]->getPeca()) == 0  || pecaOrigem->getCor() != vez) return false;
	if((pecaDestino = tab[linhaDestino][colunaDestino]->getPeca()) != 0 && pecaDestino->getCor() == vez) return false;
	
	//Solicitamos a matriz de posições que retorna nulo caso seja inválida.
	int **posicoes = pecaOrigem->checaMovimento(linhaOrigem, colunaOrigem, linhaDestino, colunaDestino,n);
	if(posicoes == 0) return false;

	//Verificamos se as posições entre as peças origens e destino estão vazias, pois só assim será possível
	//deslocar, por exemplo, a torre ou bispo.
	for(int i = 1; i < n-1; i++){
		 if(tab[posicoes[i][0]][posicoes[i][1]]->getPeca() != 0){ 
			 return false;
		}
	}
	//Removemos a matriz de posições.
	for(int i = 0; i < n; i ++){
		posicoes[i] = 0;
		delete posicoes[i];
	}
	delete []posicoes;
	
	//Retornamos true ou false caso as capturas sejam possíveis ou não.
	if(toupper(pecaOrigem->desenha()) == 'P'){
		if((colunaOrigem == colunaDestino && pecaDestino == 0) || (colunaOrigem != colunaDestino && pecaDestino != 0)){
			return true;
		}
		return false;
	} 
	return true;
}



//Verifica se determinada posição pode ser capturada pelas peças contrárias.
bool Tabuleiro::verificarXeque(const int &linha, const int &coluna, const bool &vez){
	
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			//Passamos a vez do jogador contrário e como destino a nossa peça.
			if(verificarCaptura(i, j,linha,coluna,!vez) == true) return true;
		}
	}
	return false;
}


//Método para encontrar o rei, vasculhamos todo o tabuleiro até encontrar nosso rei.
void Tabuleiro::encontrarMeuRei(int &linha, int &coluna, const bool vez){
	Peca *aux;
	
	for(int i = 0; i < tamanho; i++){
		for(int j = 0; j < tamanho; j++){
			//Passamos por todas as peças.
			aux = tab[i][j]->getPeca();
			if(aux != 0 && toupper(aux->desenha()) == 'R' && aux->getCor() == vez){
				linha = i;
				coluna = j;
				return;
			}
		}
	}
}

//Imprimimos o tabuleiro que é a saída.
ostream & operator<< (ostream & o, Tabuleiro &tab){
	tab.imprimirTabuleiro();
	return o;
}

//A entrada colocará todas as jogadas validas em uma fila.
istream &operator>> (istream & i, Tabuleiro &tab){
	
	char aux;
	int linha,coluna, estado = -1;
	bool vez = tab.quantJogadas()%2; 
	string s; 
	string origem;
	string destino;
	
	
	for(int j = 0; j < 6; j++){
		i>>aux;
		s+=toupper(aux);
	}

	

	//Verificamos se possui algum caso especial de entrada.
	if(s == "PAUSAR"){
		tab.setEstadoTabuleiro(5);
		return i;
	}
	else if(s == "RENDER"){
		tab.setEstadoTabuleiro(6);
		return i;
	}else if(s.find(">>") == -1) throw -1;
	
	
	origem = s.substr(0,s.find(">>"));
	destino = s.substr(s.find(">>")+2,s.size());
	
	if(origem.size() != 2 || destino.size() != 2) throw -1;
	
	tab.encontrarMeuRei(linha,coluna,vez);

	if((estado = tab.checaMovimentoNoTabuleiro(origem,destino,vez)) != -1){
		tab.setEstadoTabuleiro(estado);
	} else throw -1;
	
	if(vez == false && estado == 2) estado = 3;
	else if(vez == true && estado == 2) estado = 2;
	else if(vez == false && estado == 3) estado = 4;
	else if(vez == true && estado == 3) estado = 4;
	tab.setEstadoTabuleiro(estado);
	if(estado != 4) tab.guardarJogada(s);
	
	return i;
}
//Retorna a quantidade de jogadas
int Tabuleiro::quantJogadas() const{
	return jogadas.size();
}

//Guarda a jogada na fila.
void Tabuleiro::guardarJogada(const string& j){
	jogadas.push(j);
}
//Retornamos nossa fila.
queue<string> Tabuleiro::getJogadas() const{
		return jogadas;
}

int Tabuleiro::getEstadoTabuleiro() const{
	return estadoTabuleiro;
}

void Tabuleiro::setEstadoTabuleiro(const int &estado){
	estadoTabuleiro = estado;
}
