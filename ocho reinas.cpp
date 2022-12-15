#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#define filas 8
#define columnas 8

void Show(int[]);
void Rotate(int*);
void Reflect(int*);

using namespace std;

class WINNER{
	public:
		int queens[8];
		WINNER * NEXT;
		WINNER(int[]);
		~WINNER();
};

WINNER::WINNER(int board[8]){
	
	int i;
	
	Show(board);
	
	for(i=0;i<filas;i++){
		queens[i] = board[i];
	}
}

WINNER::~WINNER(){
}

class LIST{
	private:
		WINNER * START;
		void Add(WINNER *);
	public:
		static int total;
		LIST();
		~LIST();
		void New(int[]);
		void Search(int[]);
};

int LIST::total;

LIST::LIST(){
	START = NULL;
}

LIST::~LIST(){
	WINNER * W, *WAUX;
	W = START;
	
	while (W){
		WAUX = W->NEXT;
		delete W;
		W = WAUX;
	}
}

void LIST::New(int board[7]){
	int cont, i, k, j, flag;
	WINNER * W;
	W = START;
	
	while(W and flag == 0){
		
		for(j=0;j<2;j++){
			for(k=0;k<4;k++){
				cont = 0;
				for(i=0;i<filas;i++){
					if (W->queens[i] == board[i])
						cont++;
				}
				if (cont == 8)
					flag = 1;
				Rotate(W->queens);
			}
			Reflect(board);
		}
			
		W = W->NEXT;
	}
	
	if (flag == 0){
		
		total++;
		cout << "\n\n  Solution " << total << ":";
		WINNER * WN;
		WN = new WINNER(board);
		
		Add(WN);
	}
}

void LIST::Add(WINNER * WN){
	WN->NEXT = START;
	START = WN;
}

void LIST::Search(int board[]){

	int k, flag=0;
	int static row = 1;
	
	if ( board[row-1] + 1 > 8 ){ // if it's the end of the row
		if (row == 1) // no options left to try
			return;
		board[row-1] = 0; // clear row
		row--; // backwards
		flag = 1;
	}
	else
		board[row-1] = board[row-1] + 1;
		
	if (flag == 0){
		for(k=0;k<row-1;k++){ // check previous rows
			if (row-1 != 0){ // if current row is not the first row
				if (board[k] != 0){ // if not empty
					if ((abs((k + 1) - row) == abs(board[k] - board[row - 1])) or (k + 1 == row or board[k] == board[row - 1])){ // if position not allowed
						flag = 1;
						break;
					}
				}
			}
		}
	}
	
	if (flag==0){ //position allowed
		if (row == 8){ // success
			New(board); // save
		}
		else{
			row++;// next row
		}
	}
	Search(board); // try next position
}

int main(){	
		
	int board[7] = {0,0,0,0,0,0,0};
	LIST L;
	
	L.Search(board);
	cout << "\n\n Total of unique solutions (no rotations, no reflection): " << L.total;
	
}

void Show(int board[]){
	
	int i, j;
	
	cout << "\n\n      A B C D E F G H\n";
	for (i=0; i<filas;i++){
		cout << "\n  "<< i + 1 <<"-  " ;
		for (j=0;j<columnas;j++)
			if (board[i] == j + 1)
				cout << i + 1 << " ";
			else
				cout << "- ";
	}
	
}

void Rotate(int * board){
	
	int auxboard[8];
	int i;

	for(i=0; i<filas; i++){
		auxboard[board[i] - 1] = (8 - (i + 1)) + 1;
	}
	
	for(i=0; i<filas; i++){
		board[i] = auxboard[i];
	}
}

void Reflect(int * board){
	
	int auxboard[8];
	int i;
	
	for(i=0; i<filas; i++){
		auxboard[i] = (8 - board[i]) + 1;
	}
	
	for(i=0; i<filas; i++){
		board[i] = auxboard[i];
	}
}
