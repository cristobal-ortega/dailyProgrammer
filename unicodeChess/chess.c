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
		case 'G':
			return "G";
			break;
		case 'g':
			return "g";
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

char castlingTower(char column, char row, char pos) {
	char piece;
	if ( (column == 'a' && row == '8') || (column == 'h' && row == '8'))
		piece = 'r';
	else if ( (column == 'a' && row == '1') || (column == 'h' && row == '1'))
		piece = 'R';
	else
		piece = board[pos];

	return piece;
}

void castlingKing(char column, char row) {
	if (column == 'e' && row == '8') {
		transformPiece('s','r');
	}
	if (column == 'e' && row == '1') {
		transformPiece('S','R');
	}

}


void ghostPiece(char rowSrc, char rowDst, char columnSrc, char columnDst) {

	char rowMiddle,posMiddle;
	int cBoardMiddle, rBoardMiddle;
	//Pawn moves 2 squares:
	if (rowSrc == '7' && rowDst == '5' ) {
		rowMiddle = '6';
		cBoardMiddle = columnSrc - 'a';
		rBoardMiddle = 8 - (rowMiddle - '0');
		posMiddle = rBoardMiddle*8 + cBoardMiddle;
		board[posMiddle] = 'g';
	}
	if (rowSrc == '2' && rowDst == '4' ) {
		rowMiddle = '3';
		cBoardMiddle = columnSrc - 'a';
		rBoardMiddle = 8 - (rowMiddle - '0');
		posMiddle = rBoardMiddle*8 + cBoardMiddle;
		board[posMiddle] = 'G';
	}


}

void movePawn(char piece, char posDst, char posSrc){
	//Eating a ghost pawn
	if(piece == 'p'){
		if (board[posDst] == 'G')
			board[posDst-'8'] = '.';
		if (board[posSrc-8] == 'g')
			board[posSrc-8] = '.';

	}
	if(piece == 'P'){
		if (board[posDst] == 'g')
			board[posDst+8] = '.';
		if (board[posSrc+8] == 'G')
			board[posSrc+8] = '.';
	}
}

void processMove(char move[]){
	int i = 0;
	char columnSrc,rowSrc,columnDst,rowDst,piece,posSrc,posDst;
	int cBoardSrc, rBoardSrc, cBoardDst, rBoardDst;

	columnSrc = move[0];
	rowSrc = move[1];
	columnDst = move[3];
	rowDst = move[4];

	cBoardSrc = columnSrc - 'a';
	rBoardSrc = 8 - (rowSrc - '0');

	posSrc = rBoardSrc*8 + cBoardSrc;

	//King moves => no castling for them
	castlingKing(columnSrc,rowSrc);
	//Tower move => no castling for that tower
	piece = castlingTower(columnSrc,rowSrc,posSrc);



	board[posSrc] = '.';

	cBoardDst = columnDst - 'a';
	rBoardDst = 8 - (rowDst - '0');

	posDst = rBoardDst*8 + cBoardDst;

	movePawn(piece,posDst,posSrc);

	board[posDst] = piece;

	ghostPiece(rowSrc, rowDst, columnSrc, columnDst);

	printf("Something captured: %c\n", move[2]);

}

int main (int argc, char* argv[]) {

	printf("Enter the initial board: ");
	//fgets(board, sizeof(board),stdin);

	initBoard("snbqkbns/pppppppp/8/8/8/8/PPPPPPPP/SNBQKBNS");
	printf("%s\n", board);

	printBoard();

	char white[7];
	char black[7];
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
