#include <iostream>
#include <ctime>    // For time()
#include <cstdlib>  // For srand() and rand()
#include <fstream>
#include <string>

using namespace std;
const int ROWS = 8;
const int COLS = 8;
const char HUMAN_PLAYER = 'X'; const char HUMAN2_PLAYER = 'O'; const char COMPUTER_PLAYER = 'O'; const char COMPUTER2_PLAYER = 'X';
struct best {
	int row;
	int coloumn;
};
class board {

private:
	char board[9][9];
	int nodeCount = 0;
public:
	void build() {
		char a = '1';

		int i;

		for (i = 1; i < 9; i++) {
			board[i][0] = a;
			board[0][i] = a;
			a++;

		}

		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				board[i][j] = ' ';
			}
		}
		board[0][0] = ' ';
		board[4][4] = 'X'; board[4][5] = 'O';
		board[5][4] = 'O'; board[5][5] = 'X';
	}




	void print() {
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				cout << board[i][j];
			}
			cout << "\n";
		}
	}




	int PlaceDisc(int row, int col, char disc, char board[9][9])
	{
		int num_flipped = 0;

		if (board[row][col] != ' ')
			return 0;

		board[row][col] = disc;

		char opposing_disc;
		if (disc == HUMAN_PLAYER)
			opposing_disc = COMPUTER_PLAYER;
		else
			opposing_disc = HUMAN_PLAYER;

		// Do we have discs to the right to flip?
		int disc_pos = -1;
		for (int c = col + 1; c < COLS && board[row][c] != ' ' && disc_pos == -1; c++)
		{
			if (board[row][c] == disc)
				disc_pos = c;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > col + 1)
		{
			// Flip discs to the right
			for (int c = col + 1; c < disc_pos; c++)
			{
				board[row][c] = disc;
				num_flipped++;
			}
		}

		// Do we have discs to the left to flip?
		disc_pos = -1;
		for (int c = col - 1; c >= 0 && board[row][c] != ' ' && disc_pos == -1; c--)
		{
			if (board[row][c] == disc)
				disc_pos = c;
		}

		//if (disc_pos > -1) cout << "left disc_pos = " << disc_pos << endl;

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < col - 1)
		{
			// Flip discs to the left
			for (int c = col - 1; c > disc_pos; c--)
			{
				board[row][c] = disc;
				num_flipped++;
			}
		}

		// Do we have discs above to flip?
		disc_pos = -1;
		for (int r = row - 1; r >= 0 && board[r][col] != ' ' && disc_pos == -1; r--)
		{
			if (board[r][col] == disc)
				disc_pos = r;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < row - 1)
		{
			// Flip discs above
			for (int r = row - 1; r > disc_pos; r--)
			{
				board[r][col] = disc;
				num_flipped++;
			}
		}

		// Do we have discs below to flip?
		disc_pos = -1;
		for (int r = row + 1; r < ROWS && board[r][col] != ' ' && disc_pos == -1; r++)
		{
			if (board[r][col] == disc)
				disc_pos = r;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > row + 1)
		{
			// Flip discs below
			for (int r = row + 1; r < disc_pos; r++)
			{
				board[r][col] = disc;
				num_flipped++;
			}
		}

		// Do we have discs diagnally up-left to flip?
		disc_pos = -1;
		int c = col - 1;
		for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != ' ' && disc_pos == -1; r--)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c--;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < row - 1)
		{
			c = col - 1;
			for (int r = row - 1; r > disc_pos; r--)
			{
				board[r][c] = disc;
				num_flipped++;
				c--;
			}
		}

		// Do we have discs diagnally up-right to flip?
		disc_pos = -1;
		c = col + 1;
		for (int r = row - 1; c < COLS && r >= 0 && board[r][c] != ' ' && disc_pos == -1; r--)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c++;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < row - 1)
		{
			c = col + 1;
			for (int r = row - 1; r > disc_pos; r--)
			{
				board[r][c] = disc;
				num_flipped++;
				c++;
			}
		}

		// Do we have discs diagnally down-left to flip?
		disc_pos = -1;
		c = col - 1;
		for (int r = row + 1; c >= 0 && r < ROWS && board[r][c] != ' ' && disc_pos == -1; r++)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c--;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > row + 1)
		{
			c = col - 1;
			for (int r = row + 1; r < disc_pos; r++)
			{
				board[r][c] = disc;
				num_flipped++;
				c--;
			}
		}

		// Do we have discs diagnally down-right to flip?
		disc_pos = -1;
		c = col + 1;
		for (int r = row + 1; c < COLS && r < ROWS && board[r][c] != ' ' && disc_pos == -1; r++)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c++;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > row + 1)
		{
			c = col + 1;
			for (int r = row + 1; r < disc_pos; r++)
			{
				board[r][c] = disc;
				num_flipped++;
				c++;
			}
		}

		// Reset board if nothing was flipped... illegal move
		if (num_flipped == 0)
			board[row][col] = ' ';

		return num_flipped;
	}


	int numFlippedCoins(int row, int col, char disc, char board[9][9])
	{
		int num_flipped = 0;

		if (board[row][col] != ' ')
			return 0;



		char opposing_disc;
		if (disc == HUMAN_PLAYER)
			opposing_disc = COMPUTER_PLAYER;
		else
			opposing_disc = HUMAN_PLAYER;

		// Do we have discs to the right to flip?
		int disc_pos = -1;
		for (int c = col + 1; c < COLS && board[row][c] != ' ' && disc_pos == -1; c++)
		{
			if (board[row][c] == disc)
				disc_pos = c;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > col + 1)
		{
			// Flip discs to the right
			for (int c = col + 1; c < disc_pos; c++)
			{

				num_flipped++;
			}
		}

		// Do we have discs to the left to flip?
		disc_pos = -1;
		for (int c = col - 1; c >= 0 && board[row][c] != ' ' && disc_pos == -1; c--)
		{
			if (board[row][c] == disc)
				disc_pos = c;
		}

		//if (disc_pos > -1) cout << "left disc_pos = " << disc_pos << endl;

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < col - 1)
		{
			// Flip discs to the left
			for (int c = col - 1; c > disc_pos; c--)
			{

				num_flipped++;
			}
		}

		// Do we have discs above to flip?
		disc_pos = -1;
		for (int r = row - 1; r >= 0 && board[r][col] != ' ' && disc_pos == -1; r--)
		{
			if (board[r][col] == disc)
				disc_pos = r;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < row - 1)
		{
			// Flip discs above
			for (int r = row - 1; r > disc_pos; r--)
			{

				num_flipped++;
			}
		}

		// Do we have discs below to flip?
		disc_pos = -1;
		for (int r = row + 1; r < ROWS && board[r][col] != ' ' && disc_pos == -1; r++)
		{
			if (board[r][col] == disc)
				disc_pos = r;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > row + 1)
		{
			// Flip discs below
			for (int r = row + 1; r < disc_pos; r++)
			{

				num_flipped++;
			}
		}

		// Do we have discs diagnally up-left to flip?
		disc_pos = -1;
		int c = col - 1;
		for (int r = row - 1; c >= 0 && r >= 0 && board[r][c] != ' ' && disc_pos == -1; r--)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c--;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < row - 1)
		{
			c = col - 1;
			for (int r = row - 1; r > disc_pos; r--)
			{

				num_flipped++;
				c--;
			}
		}

		// Do we have discs diagnally up-right to flip?
		disc_pos = -1;
		c = col + 1;
		for (int r = row - 1; c < COLS && r >= 0 && board[r][c] != ' ' && disc_pos == -1; r--)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c++;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos < row - 1)
		{
			c = col + 1;
			for (int r = row - 1; r > disc_pos; r--)
			{

				num_flipped++;
				c++;
			}
		}

		// Do we have discs diagnally down-left to flip?
		disc_pos = -1;
		c = col - 1;
		for (int r = row + 1; c >= 0 && r < ROWS && board[r][c] != ' ' && disc_pos == -1; r++)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c--;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > row + 1)
		{
			c = col - 1;
			for (int r = row + 1; r < disc_pos; r++)
			{

				num_flipped++;
				c--;
			}
		}

		// Do we have discs diagnally down-right to flip?
		disc_pos = -1;
		c = col + 1;
		for (int r = row + 1; c < COLS && r < ROWS && board[r][c] != ' ' && disc_pos == -1; r++)
		{
			if (board[r][c] == disc)
				disc_pos = r;
			c++;
		}

		// Make sure we found a disc and that it is at least 2 spots away
		if (disc_pos != -1 && disc_pos > row + 1)
		{
			c = col + 1;
			for (int r = row + 1; r < disc_pos; r++)
			{

				num_flipped++;
				c++;
			}
		}

		// Reset board ANYWAY !!!!!
		board[row][col] = ' ';

		return num_flipped;
	}







	void GetHumanMove()
	{
		int row, col;
		bool illegal_move;

		// Make sure there is a legal move that can be made
		if (1)
		{
			do
			{
				illegal_move = false;

				cout << "Row? ";
				cin >> row;
				while (row < 0 || row > ROWS)
				{
					cout << "Please select a row between 0 and " << (ROWS) << ".\n";
					cout << "Row? ";
					cin >> row;
				}

				cout << "Col? ";
				cin >> col;
				while (col < 0 || col > COLS)
				{
					cout << "Please select a column between 0 and " << (COLS) << ".\n";
					cout << "Col? ";
					cin >> col;
				}

				if (board[row][col] != ' ')
				{
					cout << "Please select an empty row and column.\n";
					illegal_move = 1;
				}
				else
				{
					int discs_flipped = PlaceDisc(row, col, HUMAN_PLAYER, board);
					if (discs_flipped == 0)
					{
						cout << "Illegal move.\n";
						illegal_move = true;
					}
					else if (discs_flipped == 1)
						cout << "\nYou flipped 1 disc.\n\n";
					else
						cout << "\nYou flipped " << discs_flipped << " discs.\n\n";
				}
			} while (illegal_move);
		}




		//move is not possbile !!!!
		else
		{
			cout << "X cannot move.\n";
		}

	}

void GetHumanMove2()
	{
		int row, col;
		bool illegal_move;

		// Make sure there is a legal move that can be made
		if (1)
		{
			do
			{
				illegal_move = false;

				cout << "Row? ";
				cin >> row;
				while (row < 0 || row > ROWS)
				{
					cout << "Please select a row between 0 and " << (ROWS) << ".\n";
					cout << "Row? ";
					cin >> row;
				}

				cout << "Col? ";
				cin >> col;
				while (col < 0 || col > COLS)
				{
					cout << "Please select a column between 0 and " << (COLS) << ".\n";
					cout << "Col? ";
					cin >> col;
				}

				if (board[row][col] != ' ')
				{
					cout << "Please select an empty row and column.\n";
					illegal_move = 1;
				}
				else
				{
					int discs_flipped = PlaceDisc(row, col, HUMAN2_PLAYER, board);
					if (discs_flipped == 0)
					{
						cout << "Illegal move.\n";
						illegal_move = true;
					}
					else if (discs_flipped == 1)
						cout << "\nYou flipped 1 disc.\n\n";
					else
						cout << "\nYou flipped " << discs_flipped << " discs.\n\n";
				}
			} while (illegal_move);
		}




		//move is not possbile !!!!
		else
		{

		}

	}

	//minimax for computer move !!!!!! //

	best minimax(bool possible[9][9], char AIboard[9][9], char PLAYER)
	{


        bool possible2[9][9];
		int bestMoveScore = 100; // -100 is arbitrary
		best bestMove;
		bestMove.coloumn = 0; bestMove.row = 0;
		//save AI board in temp !! //
		char tempAIboard[9][9];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				tempAIboard[i][j] = AIboard[i][j];
			}
		}




		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (possible[i][j] == true) {


					PlaceDisc(i, j, PLAYER, AIboard);

					for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                           possible2[i][j] = AIboard[i][j];
                        }
                    }


					//compute Possible (alpha-beta pruning) values AGAIN !!!!!
					for (int r = 1; r <= 8; r++) {
						for (int c = 1; c <= 8; c++) {
							int row = r; int col = c;
							int discs_flipped = numFlippedCoins(r, c, PLAYER, AIboard);

							if (discs_flipped == 0)
							{
								possible2[r][c] = false;

							}
							else {

								possible2[r][c] = true;

							}

						}
					}




					int tempMoveScore = maxSearch(possible2, AIboard, PLAYER);

					if (tempMoveScore < bestMoveScore) {

						bestMoveScore = tempMoveScore;
						bestMove.row = i;
						bestMove.coloumn = j;
					}


					//recover previous AI board !! //
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							AIboard[i][j] = tempAIboard[i][j];
						}
					}
					for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                           possible2[i][j] = AIboard[i][j];
                        }
                    }

					//compute Possible (alpha-beta pruning) values AGAIN !!!!!
					for (int r = 1; r <= 8; r++) {
						for (int c = 1; c <= 8; c++) {
							int row = r; int col = c;
							int discs_flipped = numFlippedCoins(r, c, PLAYER, AIboard);

							if (discs_flipped == 0)
							{
								possible2[r][c] = false;

							}
							else {

								possible2[r][c] = true;

							}

						}
					}

				}
			}
		}
		cout << endl;
		cout << "Computer though about " << nodeCount <<" possible scenario"<< endl;
		cout << "Computer's move: " << bestMove.row <<" "<<bestMove.coloumn<<"\n"<< endl;
		nodeCount = 0;

		return bestMove;

	}

	int score(char AIboard[9][9]) {
		if (checkWin(HUMAN_PLAYER, AIboard)) { return 10; }
		else if (checkWin(COMPUTER_PLAYER, AIboard)) { return -10; }
		return 0; // draw
	}


	bool gameOver(char AIboard[9][9]) {
		if (checkWin(HUMAN_PLAYER, AIboard)) return true;
		else if (checkWin(COMPUTER_PLAYER, AIboard)) return true;

		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (numFlippedCoins(i, j, HUMAN_PLAYER, AIboard) != 0 || numFlippedCoins(i, j, HUMAN_PLAYER, AIboard) != 0) {
					return false;
				}
			}
		}
		return true;
	}

	bool checkWin(char playerChar, char AIboard[9][9]) {
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (numFlippedCoins(i, j, COMPUTER2_PLAYER, AIboard) != 0 || numFlippedCoins(i, j, COMPUTER_PLAYER, AIboard) != 0) {
					return false;
				}
			}
		}
		return true;
	}








	int maxSearch(bool possible[9][9], char AIboard[9][9], char PLAYER) {
		nodeCount++;
		if (gameOver(AIboard)) return score(AIboard);
		best bestMove;
        bool possible2[9][9];
		//save AI board in temp !! //
		char tempAIboard[9][9];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				tempAIboard[i][j] = AIboard[i][j];
			}
		}
		int bestMoveScore = -1000;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (possible[i][j] == true) {

					PlaceDisc(i, j, PLAYER, AIboard);


					for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                           possible2[i][j] = AIboard[i][j];
                        }
                    }



					for (int i = 1; i <= 8; i++) {
						for (int j = 1; j <= 8; j++) {
							int row = i; int col = j;
							int discs_flipped = numFlippedCoins(row, col, PLAYER, AIboard);

							if (discs_flipped == 0)
							{
								possible2[i][j] = false;

							}
							else {

								possible2[i][j] = true;
							}

						}
					}
					int tempMoveScore = minSearch(possible2, AIboard, PLAYER);

                    srand(time(NULL));
					//If two values are equal, then we can choose randomly. SO every move will be different but the best step that computer can take !!
					int secretChoise = rand() % 2 + 1;
					if (tempMoveScore == bestMoveScore && secretChoise==1) {
						bestMoveScore = tempMoveScore;
						bestMove.row = i;
						bestMove.coloumn = j;

					}
					else if (tempMoveScore > bestMoveScore && secretChoise==2) {

						bestMoveScore = tempMoveScore;
						bestMove.row = i;
						bestMove.coloumn = j;

					}
					//recover previous AI board !! //
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							AIboard[i][j] = tempAIboard[i][j];
						}
					}
					for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                           possible2[i][j] = AIboard[i][j];
                        }
                    }

					//compute Possible (alpha-beta pruning) values AGAIN !!!!!
					for (int r = 1; r <= 8; r++) {
						for (int c = 1; c <= 8; c++) {
							int row = r; int col = c;
							int discs_flipped = numFlippedCoins(r, c, PLAYER, AIboard);

							if (discs_flipped == 0)
							{
								possible2[r][c] = false;

							}
							else {

								possible2[r][c] = true;

							}

						}
					}
				}
			}
		}

		return bestMoveScore;
	}



	int minSearch(bool possible[9][9], char AIboard[9][9], char PLAYER) {
		if (gameOver(AIboard)) return score(AIboard);
		best bestMove;
        bool possible2[9][9];
		//save AI board in temp !! //
		char tempAIboard[9][9];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				tempAIboard[i][j] = AIboard[i][j];
			}
		}

		int bestMoveScore = 1000;
		for (int i = 1; i < 9; i++) {
			for (int j = 1; j < 9; j++) {
				if (possible[i][j] == true) {
					PlaceDisc(i, j, PLAYER, AIboard);

					for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                           possible2[i][j] = possible[i][j];
                        }
                    }


					for (int i = 1; i <= 8; i++) {
						for (int j = 1; j <= 8; j++) {
							int row = i; int col = j;
							int discs_flipped = numFlippedCoins(row, col, PLAYER, AIboard);

							if (discs_flipped == 0)
							{
								possible2[i][j] = false;

							}
							else {

								possible2[i][j] = true;
							}

						}
					}

					int tempMove = maxSearch(possible2, AIboard, PLAYER);

					int secretChoise = rand() % 2 + 1;
					if (tempMove == bestMoveScore && secretChoise == 2) {
						bestMoveScore = tempMove;
						bestMove.row = i;
						bestMove.coloumn = j;

					}
					else if (tempMove < bestMoveScore &&secretChoise==1) {
						bestMoveScore = tempMove;
						bestMove.row = i;
						bestMove.coloumn = j;



					}

					//recover previous AI board !! //
					for (int i = 0; i < 9; i++) {
						for (int j = 0; j < 9; j++) {
							AIboard[i][j] = tempAIboard[i][j];
						}
					}
					for (int i = 0; i < 9; i++) {
                        for (int j = 0; j < 9; j++) {
                           possible2[i][j] = possible[i][j];
                        }
                    }

					//compute Possible (alpha-beta pruning) values AGAIN !!!!!
					for (int r = 1; r <= 8; r++) {
						for (int c = 1; c <= 8; c++) {
							int row = r; int col = c;
							int discs_flipped = numFlippedCoins(r, c, PLAYER, AIboard);

							if (discs_flipped == 0)
							{
								possible2[r][c] = false;

							}
							else {

								possible2[r][c] = true;

							}

						}
					}
				}
			}
		}

		return bestMoveScore;
	}


	int computerMove()
	{
		char AIboard[9][9];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				AIboard[i][j] = board[i][j];
			}

		}
		bool possible[9][9];
		//I am searching the possible moves that computer can play and put it in the array !!!
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				int row = i; int col = j;
				int discs_flipped = numFlippedCoins(row, col, COMPUTER_PLAYER, AIboard);

				if (discs_flipped == 0)
				{
					possible[i][j] = false;

				}
				else {

					possible[i][j] = true;
				}

			}
		}

        cout<<"\nComputer is thinking ..."<<endl;
		best AImove = minimax(possible, AIboard, COMPUTER_PLAYER);

		PlaceDisc(AImove.row, AImove.coloumn, COMPUTER_PLAYER, board);
        if(AImove.row==0 && AImove.coloumn==0){
            cout << "\nHUMAN WINS!!!\n\n" << endl;
            return 1;
        }
		if (checkWin(COMPUTER_PLAYER, AIboard)) {
			cout << "\nWINNER IS COMPUTER 1!!! (O)\n\n" << endl;
			return 1;
		}
	}


	int computer2Move()
	{
		char AIboard[9][9];
		for (int i = 0; i < 9; i++) {
			for (int j = 0; j < 9; j++) {
				AIboard[i][j] = board[i][j];
			}

		}
		bool possible[9][9];
		//I am searching the possible moves that computer can play and put it in the array !!!
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				int row = i; int col = j;
				int discs_flipped = numFlippedCoins(row, col, COMPUTER2_PLAYER, AIboard);

				if (discs_flipped == 0)
				{
					possible[i][j] = false;

				}
				else {

					possible[i][j] = true;
				}

			}
		}


		best AImove = minimax(possible, AIboard, COMPUTER2_PLAYER);

		PlaceDisc(AImove.row, AImove.coloumn, COMPUTER2_PLAYER, board);
		if (checkWin(COMPUTER2_PLAYER, AIboard)) {
			cout << "\nWINNER IS COMPUTER 2!!! (X) \n\n" << endl;
			return 2;
		}
	}







};



int main() {
	int choice;
	char tmp[2];
	int x = 1;
	while (1) {
		cout << "Welcome to interactive OTHELLO game.\n1-Human vs Computer\n2-Computer against Computer\n3-Human vs Human\nEnter your choise please:";
		cin>>choice;

		if (choice == 1) {
			board boardObj;
			boardObj.build();
			boardObj.print();
			while (1) {
				boardObj.GetHumanMove();
				boardObj.print();
				if(boardObj.computerMove()==1){
                        break;
                }
				boardObj.print();
			}
		}
		else if (choice == 2) {
			int winner = 0;
			board boardObj;
			boardObj.build();
			boardObj.print();
			while (1) {

				winner = boardObj.computerMove();
				boardObj.print();
				if (winner == 2 || winner == 1) {
					break;
				}
				winner = boardObj.computer2Move();

				boardObj.print();
				if (winner == 2 || winner == 1) {
					break;
				}

			}
		}
		else if (choice == 3) {
			board boardObj;
			boardObj.build();
			boardObj.print();
			while (1) {
				boardObj.GetHumanMove();
				boardObj.print();
				boardObj.GetHumanMove2();
				boardObj.print();
			}
		}


		else {
			cout << "Please enter valid choice. (1-3)\n\n";
		}
	}
	return 0;
}









