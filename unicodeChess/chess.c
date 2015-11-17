#include <stdio.h>
#include <stdlib.h>


char board[64]; //8 rows x 8 columns


char* toUnicode(char a) {
	switch (a) {
		case 's':
			return "\u265c";
			break;
		case 'r':
			return "\u265c";
			break;
		case 'n':
			return "\u265e";
			break;
		case 'b':
			return "\u265d";
			break;
		case 'q':
			return "\u265b";
			break;
		case 'k':
			return "\u265a";
			break;
		case 'p':
			return "\u265f";
			break;
		case 'P':
			return "\u2659";
			break;
		case 'S':
			return "\u2656";
			break;
		case 'R':
			return "\u2656";
			break;
		case 'N':
			return "\u2658";
			break;
		case 'B':
			return "\u2657";
			break;
		case 'Q':
			return "\u2655";
			break;
		case 'K':
			return "\u2654";
			break;
		case '.':
			return ".";
			break;
		default:
			return "\u2650";
			break;
	}

}

void initBoard(char string[]) {
	int i = 0;
	int j = 0;
	while( i < 256 && string[i] != NULL) {
		if(string[i] != '/'){
			if (string[i] > '0' && string[i] < '9'){
				for (int ii = 0; ii < string[i] - '0'; ++ii){
					board[j] = '.';
					++j;
				}
			}
			else{
				board[j] = string[i];
				++j;
			}
		}
		++i;
	}
}

void printBoard() {
	int i = 0;
	int row = 8;
	printf("%i ", row);
	while( i < sizeof(board) ){
		printf("%s ", toUnicode(board[i]));
		++i;
		if ( !(i%8) && row > 1){
			printf("\n%i ", --row);

		}
	}
	printf("\n  a b c d e f g h\n");
}


void transformPiece(char init, char final) {
	for(int i = 0; i < 64; ++i){
		if (board[i] == init)
			board[i] = final;
	}

}


void processMove(char move[]){
	int i = 0;
	char column,row,piece,pos;
	int columnBoard, rowBoard;

	column = move[0];
	row = move[1];

	//King moves => no castling for them
	if (column == 'e' && row == '8') {
		printf("uops");
		transformPiece('s','r');
	}
	if (column == 'e' && row == '1') {
		printf("uops2");
		transformPiece('S','R');
	}
	columnBoard = column - 'a';
	rowBoard = 8 - (row-'0');

	pos = rowBoard*8 + columnBoard;

	//Tower move => no castling for that tower
	if ( (column == 'a' && row == '8') || (column == 'h' && row == '8'))
		piece = 'r';
	else if ( (column == 'a' && row == '1') || (column == 'h' && row == '1'))
		piece = 'R';
	else
		piece = board[pos];
	board[pos] = '.';

	column = move[3];
	row = move[4];
	columnBoard = column - 'a';
	rowBoard = 8 - (row-'0');

	pos = rowBoard*8 + columnBoard;
	board[pos] = piece;

	printf("Something captured: %c\n", move[2]);

}

int main (int argc, char* argv[]) {

	printf("Enter the initial board: ");
	//fgets(board, sizeof(board),stdin);

	initBoard("snbqkbns/pppppppp/8/8/8/8/PPPPPPPP/SNBQKBNS");
	printf("%s\n", board);

	printBoard();

	char white[8];
	char black[8];
	while(1) {
		printf("Enter WHITE movement: ");
		fgets(white, sizeof(white), stdin);
		printf("Movement is: %s\n", white);

		processMove(white);
		printBoard();

		printf("Enter BLACK movement: ");
		fgets(black, sizeof(black), stdin);
		printf("Movement is: %s\n", black);

		processMove(black);
		printBoard();

	}

	printf("\n");

	return 0;
}
