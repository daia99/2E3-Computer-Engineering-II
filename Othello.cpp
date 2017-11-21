//===================================
//Andrew Dai - ASCII 2-Player Othello 
//===================================

//======================================================
//To play, compile and run this CPP file.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//Place your token on the board and try 
//to trap as many of your opponent's pieces as possible.
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//You have the option to change the board size by 
//changing the value on line 27 (default is 8x8).
//======================================================

#include <iostream>
#include <iomanip>
#include <cmath>
#include <string>
#include <math.h>

using namespace std;

const char TOKENS[] = { ' ', 'X', 'O' }; //To be printed out on the board

const int PLAYER1 = 1; //X Token
const int PLAYER2 = 2; //O Token

const int BOARD_SIZE = 8; //An even-numbered board size recommended

void init_board(int a[][BOARD_SIZE], int size); //Sets up initial board state
void print_board(const int a[][BOARD_SIZE], int size); //Prints board with coordinate system and current board state

int search_row(const int a[][BOARD_SIZE], int size, int x, int y, int player, int dx, int dy); //Checks a row for the number of trapped enemy pieces in a line, returns that number
bool valid_move(const int a[][BOARD_SIZE], int size, int x, int y, int player); //Returns false if illegal move is made by the player
void place_piece(int a[][BOARD_SIZE], int size, int x, int y, int player); //Places a legal piece by the player on the board, flips all possible trapped pieces
void flip_pieces(int a[][BOARD_SIZE], int size, int x, int y, int player, int dx, int dy); //checks line and flips all possible pieces
bool board_full(const int a[][BOARD_SIZE], int size, int player); //checks for remaining possible moves, returns true if board is full

int check_winner(const int a[][BOARD_SIZE], int size); //declares player with most points, or draw

int main() {
	int player;
	int x, y;

	int board[BOARD_SIZE][BOARD_SIZE];

	init_board(board, BOARD_SIZE);
	print_board(board, BOARD_SIZE);

	player = PLAYER2;

	//Main game loop and logic
	while (1) {
		player = (player * 2) % 3; //Changing turns, starting with Player 1 (X)
		if (board_full(board, BOARD_SIZE, player)) { //Checks to see if current player can make a move. If not, alternates player
			player = (player * 2) % 3;
			if (board_full(board, BOARD_SIZE, player)) //If the board is full, game loop ends here
				break;
		}

		cout << "Player \'" << TOKENS[player] << "\', please enter the coordinates for your move, x and y, as 2 numbers separated with a space: ";
		cin >> x >> y;
		
		//Invalid move loop
		while (!valid_move(board, BOARD_SIZE, x, y, player)) {
			cout << "Invalid move, try again, player " << TOKENS[player] << ':' << endl;
			cin >> x >> y; //reads in new coordinates
		}

		place_piece(board, BOARD_SIZE, x, y, player); //updates board with new piece
		print_board(board, BOARD_SIZE);
	}
	
	int winner = check_winner(board, BOARD_SIZE); //Checks board to see who has the highest score
	if (winner != -1) //if not a draw
		cout << "Player " << TOKENS[winner] << " WINS!" << endl;
	else cout << "DRAW!" << endl;
	
	return 0;
}

void init_board(int a[][BOARD_SIZE], int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			a[i][j] = 0;
		}
	}
	a[size / 2 - 1][size / 2 - 1] = 2;
	a[size / 2][size / 2 - 1] = 1;
	a[size / 2 - 1][size / 2] = 1;
	a[size / 2][size / 2] = 2;
}

void print_board(const int a[][BOARD_SIZE], int size) {
	int x, y;

	cout << "   ";

	for (x = 0; x < size; x++) 
		cout << setw(2) << x;
	
	cout << endl;

	cout << string(size * 2 + 4, '-') << endl;

	for (y = 0; y < size; y++) {
		cout << setw(3) << y << '|';
		for (x = 0; x < size; x++) {
			cout << TOKENS[a[y][x]] << '|';
		}
		cout << endl;
	}

	cout << string(size * 2 + 4, '-') << endl;
}

int search_row(const int a[][BOARD_SIZE], int size, int x, int y, int player, int dx, int dy) {
	int count = 0;
	int unitX = dx;
	int unitY = dy;
	//if line if search within bounds and also detects opponent's piece this loops
	while ((x+dx) >= 0 && (x+dx) < size && (y+dy) >= 0 && (y+dy) < size && a[y+dy][x+dx] != 0 && a[y+dy][x+dx] != player) {
		dx += unitX;
		dy += unitY;
		count++;
	}
	if ((x+dx) < 0 || (x+dx) >= size || (y+dy) < 0 || (y+dy) >= size) //if hits wall, doesn't count
		return 0;
	//if the last space is player's piece trapping other pieces in line, return number of trapped pieces
	if (a[y+dy][x+dx] == player) {
		return count;
	}
	return 0;
}

bool valid_move(const int a[][BOARD_SIZE], int size, int x, int y, int player) {
	if (x >= size || x < 0 || y >= size || y < 0 || a[y][x] != 0)
		return false;
	
	for (double theta = 0; theta < M_PI * 2; theta += M_PI / 4) {
		int dy = round(sin(theta));
		int dx = round(cos(theta));

		if (search_row(a, size, x, y, player, dx, dy) > 0)
			return true;
	}

	return false;
}

void place_piece(int a[][BOARD_SIZE], int size, int x, int y, int player) {
	a[y][x] = player;
	for (double theta = 0; theta < M_PI * 2; theta += M_PI / 4) {
		int dy = round(sin(theta));
		int dx = round(cos(theta));
		flip_pieces(a, size, x, y, player, dx, dy);
	}
}

void flip_pieces(int a[][BOARD_SIZE], int size, int x, int y, int player, int dx, int dy) {
	int count = search_row(a, size, x, y, player, dx, dy);
	int unitX = dx;
	int unitY = dy;
	for (int i = 1; i <= count; i++) {
		a[y+dy][x+dx] = player;
		dx += unitX;
		dy += unitY;
	}
}

bool board_full(const int a[][BOARD_SIZE], int size, int player) { //Change search algorithim
	for (int y = 0; y < size; y++) {
		for (int x = 0; x < size; x++) {
			if (a[y][x] == 0 && valid_move(a, size, x, y, player)) {
					return false;
				}
			}
		}
	return true;
}

int check_winner(const int a[][BOARD_SIZE], int size) {
	int score1 = 0, score2 = 0;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (a[i][j] == 1)
				score1++;
			if(a[i][j] == 2) 
				score2++;
		}
	}
	if (score1 > score2)
		return 1;
	else if (score2 > score1)
		return 2;
	else return -1;
}
