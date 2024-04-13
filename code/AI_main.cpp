/**
* @file AI_main.cpp
* @author Maciej Kwiecinski, Olek Kurek, Patryk Kregiel
* @date 13.01.2023
* @brief This File containt various functions used by AI.
*/



#include "AI_main.h"
#include "Game_state.h"
#include "Auxiliary_functions.h"

extern int turn;
extern long int liczba_operacji;

 ////////////////////////////////////////////////////////
 /////////////////                 //////////////////////
 /////////////////        AI       //////////////////////
 /////////////////                 //////////////////////
 ////////////////////////////////////////////////////////

 /// AI Auxiliary function that return's value validation of points on the game board that you provide. Mostly used by AI to determine with move is better.
 ///
 /// @param board This is a pointer to array with state of the game board.
int validate(int board[10][10]) {
	int pieces_value = 0; //bot_value - > black(2)
	int enemy_pieces_value = 0;//player_value -> white(3)

	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == 2) {
				//if this is a piece of player one
				pieces_value = pieces_value + 100;
				//positioning of this piece
				if (i == 8) {
					pieces_value = pieces_value + 40; // this piece will advance in 1 move. Value it little more
				}
				else if (i == 7) {
					pieces_value = pieces_value + 30; // this piece will advance in 2 moves. Value it little more
				}
				else if (i == 6) {
					pieces_value = pieces_value + 10; // this piece will advance in 3 moves. Value it little more 
				}
				else if (i == 5) {
					pieces_value = pieces_value + 4; // this piece will advance in 4 moves. Value it little more 
				}

				if ((j == 9 || j == 0) && i > 5) {
					pieces_value = pieces_value + 5; // This piece is on the border, soo it can't be attacked. Value it little more
				}

			}
			else if (board[i][j] == 20) {
				//If this is a king of player one
				pieces_value = pieces_value + 300;
				//positioning of this king
				if (i > 0 && i < 9 && j < 9 && j> 0) {
					if (i < 5) {
						pieces_value = pieces_value + i; // This king is more in the middle, so it can make more moves. Value it little more
					}
					if (i >= 5) {
						pieces_value = pieces_value + 10 - i; // This king is more in the middle, so it can make more moves. Value it little more
					}
				}


			}
			else if (board[i][j] == 3) {
				//If this is a piece of player two
				enemy_pieces_value = enemy_pieces_value + 100;
				if (i == 1) {
					enemy_pieces_value = enemy_pieces_value + 40; // this piece will advance in 1 move. Value it little more
				}
				else if (i == 2) {
					enemy_pieces_value = enemy_pieces_value + 30; // this piece will advance in 2 moves. Value it little more
				}
				else if (i == 3) {
					enemy_pieces_value = enemy_pieces_value + 10; // this piece will advance in 3 moves. Value it little more 
				}
				else if (i == 4) {
					enemy_pieces_value = enemy_pieces_value + 4; // this piece will advance in 4 moves. Value it little more 
				}

				if ((j == 9 || j == 0) && i < 5) {
					enemy_pieces_value = enemy_pieces_value + 5; // This piece is on the border, soo it can't be attacked. Value it little more
				}



			}
			else if (board[i][j] == 30) {
				//If this is a king of player two
				enemy_pieces_value = enemy_pieces_value + 300;
				if (i > 0 && i < 9 && j < 9 && j> 0) {
					if (i > 0 && i < 9 && j < 9 && j> 0) {
						if (i < 5) {
							enemy_pieces_value = enemy_pieces_value + i; // This king is more in the middle, so it can make more moves. Value it little more
						}
						if (i >= 5) {
							enemy_pieces_value = enemy_pieces_value + 10 - i; // This king is more in the middle, so it can make more moves. Value it little more
						}
					}
				}

			}
		}
	}
	return  pieces_value - enemy_pieces_value;
}


/**
 * @brief Structure for saving the best move for a AI.
 *
 *
 */
struct best_move {
	int start_x_pos; /**< Starting col position of the piece */
	int start_y_pos; /**< Starting row position of the piece */
	int new_x_pos;   /**< Destination row coordinates */
	int new_y_pos;	 /**< Destination col coordinates */
	int best_value;  /**< Value of the move. */
	int deleted_piece; /**< Is it a attack move? If yes then save what piece it attacks. */
};


/// AI Auxiliary function used to make AI move more transparent in code.
///
/// @param board This is a pointer to array with state of the board.
/// @param i row coordinates of piece that will move.
/// @param j Col coordinates of piece that will move.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
void make_ai_move(int board[10][10], int i, int j, int new_i, int new_j) {
	board[new_i][new_j] = board[i][j];
	board[i][j] = 1;
}

/// AI Auxiliary function used to make undo AI move more transparent in code.
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will move.
/// @param j Col coordinates of piece that will move.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
void undo_ai_move(int board[10][10], int i, int j, int new_i, int new_j) {
	board[i][j] = board[new_i][new_j];
	board[new_i][new_j] = 1;
}

/// AI Auxiliary function that makes attacks for a desired destinations. Returns value of deleted piece between.
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will attack.
/// @param j Col coordinates of piece that will attack.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
/// @param direction Direction of attack.
/// @return Returns value of deleted piece after attack.
int make_ai_attack(int board[10][10], int i, int j, int new_i, int new_j, std::string direction) {
	int deleted_piece;
	if (direction == "up_left") {
		make_ai_move(board, i, j, new_i, new_j);
		deleted_piece = board[i - 1][j - 1];
		board[i - 1][j - 1] = 1;
		return deleted_piece;
	}
	else if (direction == "up_right") {
		make_ai_move(board, i, j, new_i, new_j);
		deleted_piece = board[i - 1][j + 1];
		board[i - 1][j + 1] = 1;
		return deleted_piece;
	}
	else if (direction == "down_left") {
		make_ai_move(board, i, j, new_i, new_j);
		deleted_piece = board[i + 1][j - 1];
		board[i + 1][j - 1] = 1;
		return deleted_piece;
	}
	else if (direction == "down_right") {
		make_ai_move(board, i, j, new_i, new_j);
		deleted_piece = board[i + 1][j + 1];
		board[i + 1][j + 1] = 1;
		return deleted_piece;
	}
}


/// AI Auxiliary function that undo AI attacks maked by make_ai_attack() function.
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will attack.
/// @param j Col coordinates of piece that will attack.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
/// @param direction  Direction of attack.
/// @param deleted_piece Value of deleted piece before attack.
void undo_ai_attack(int board[10][10], int i, int j, int new_i, int new_j, std::string direction, int deleted_piece) {
	if (direction == "up_left") {
		make_ai_move(board, i, j, new_i, new_j);
		board[new_i - 1][new_j - 1] = deleted_piece;
	}
	else if (direction == "up_right") {
		make_ai_move(board, i, j, new_i, new_j);
		board[new_i - 1][new_j + 1] = deleted_piece;
	}
	else if (direction == "down_left") {
		make_ai_move(board, i, j, new_i, new_j);
		board[new_i + 1][new_j - 1] = deleted_piece;
	}
	else if (direction == "down_right") {
		make_ai_move(board, i, j, new_i, new_j);
		board[new_i + 1][new_j + 1] = deleted_piece;
	}
}

/// Auxiliary function for returning smaller value from 2 numbers provided.
///
/// @param a First value to compare.
/// @param b Second value to compare.
int min(int a, int b) {
	if (a < b) {
		return a;
	}
	else {
		return b;
	}
}

/// Auxiliary function for returning bigger value from 2 numbers provided.
///
/// @param a First value to compare.
/// @param b Second value to compare.
int max(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

/// Minimax algorithm function for checking every combination of the checkers game for a given depth. There is also implemented Alpha Beta Pruning algorithm to reduce total number of posibilities.
///
/// @param board This is a pointer to array with state of the board.
/// @param depth Variable that describes depth of the recursion.
/// @param alpha Variable that represent minimum score that the maximizing player is assured of (Alpha Beta Pruning algorithm)
/// @param beta Variable that represent maximum score that the maximizing player is assured of. (Alpha Beta Pruning algorithm)
/// @param isMaximizingPlayer Describes do you want to Maximize player or not. (Alpha Beta Pruning algorithm)
int minimax(int board[10][10], int depth, int alpha, int beta, bool isMaximizingPlayer){
	/*window.clear(sf::Color(0, 0, 0, 0));
	draw_game_state(board, 0, 0);
	window.display();
	if (isMaximizingPlayer) {
		//printf("Punkty po ruchu bota : %d \n", validate(board));
	}
	else {
		//printf("Punkty po ruchu gracza : %d \n", validate(board));
	}
	Sleep(100);*/
	int bestscore = 0;
	liczba_operacji++;
	if (isMaximizingPlayer) {
		if (depth == 0 || can_move(board, 3) == 1) {
			return validate(board); // AI points
		}

	}
	else {
		if (depth == 0 || can_move(board, 2) == 1) {
			return validate(board); // AI points
		}

	}

	bool attack_possible = false;
	if (isMaximizingPlayer) {
		//"Gracz" wybiera swój ruch (3)
		bestscore = std::numeric_limits<int>::max();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (board[i][j] == 3 || board[i][j] == 30) {
					//attacks 
					if ((board[i - 1][j - 1] == 2 || board[i - 1][j - 1] == 20) && board[i - 2][j - 2] == 1 && i > 1 && j > 1) {
						//gora_lewo_atak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i - 2, j - 2, "up_left");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, false);
						undo_ai_attack(board, i - 2, j - 2, i, j, "up_left", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value < bestscore) {
							bestscore = value;
						}
						beta = min(beta, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}
					else if ((board[i - 1][j + 1] == 2 || board[i - 1][j + 1] == 20) && board[i - 2][j + 2] == 1 && i > 1 && j < 8) {
						//gora_prawo_atak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i - 2, j + 2, "up_right");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, false);
						undo_ai_attack(board, i - 2, j + 2, i, j, "up_right", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value < bestscore) {
							bestscore = value;
						}
						beta = min(beta, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}

				}
				if (board[i][j] == 30) {
					if ((board[i + 1][j - 1] == 2 || board[i + 1][j - 1] == 20) && board[i + 2][j - 2] == 1 && i < 8 && j > 1) {
						//dol_lewo_attak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i + 2, j - 2, "down_left");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, false);
						undo_ai_attack(board, i + 2, j - 2, i, j, "down_left", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value < bestscore) {
							bestscore = value;
						}
						beta = min(beta, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}
					if ((board[i + 1][j + 1] == 2 || board[i + 1][j + 1] == 20) && board[i + 2][j + 2] == 1 && i < 8 && j < 8) {
						//dol_prawo_atak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i + 2, j + 2, "down_right");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, false);
						undo_ai_attack(board, i + 2, j + 2, i, j, "down_right", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value < bestscore) {
							bestscore = value;
						}
						beta = min(beta, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}
				}
			}
		}
		if (attack_possible == false) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (board[i][j] == 3 || board[i][j] == 30) {
						if (board[i - 1][j - 1] == 1 && i > 0 && j > 0) {
							//gora_lewo_ruch
							int piece = board[i][j];
							make_ai_move(board, i, j, i - 1, j - 1);
							int value = minimax(board, depth - 1, alpha, beta, false);
							undo_ai_move(board, i, j, i - 1, j - 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value < bestscore) {
								bestscore = value;
							}
							beta = min(beta, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
						if (board[i - 1][j + 1] == 1 && i > 0 && j < 9) {
							//gora prawo
							int piece = board[i][j];
							make_ai_move(board, i, j, i - 1, j + 1);
							int value = minimax(board, depth - 1, alpha, beta, false);
							undo_ai_move(board, i, j, i - 1, j + 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value < bestscore) {
								bestscore = value;
							}
							beta = min(beta, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
					}
					if (board[i][j] == 30) {
						if (board[i + 1][j - 1] == 1 && i < 9 && j > 0) {
							//ruch_dol lewo
							int piece = board[i][j];
							make_ai_move(board, i, j, i + 1, j - 1);
							int value = minimax(board, depth - 1, alpha, beta, false);
							undo_ai_move(board, i, j, i + 1, j - 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value < bestscore) {
								bestscore = value;
							}
							beta = min(beta, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
						if (board[i + 1][j + 1] == 1 && i < 9 && j < 9) {
							//ruch_dol_prawo
							int piece = board[i][j];
							make_ai_move(board, i, j, i + 1, j + 1);
							int value = minimax(board, depth - 1, alpha, beta, false);
							undo_ai_move(board, i, j, i + 1, j + 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value < bestscore) {
								bestscore = value;
							}
							beta = min(beta, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
					}
				}
			}
		}
		if (bestscore == std::numeric_limits<int>::max()) {
			return validate(board);
		}
		else {
			return bestscore;
		}
	}
	else {
		//AI wybiera swój ruch (2)
		bestscore = std::numeric_limits<int>::min();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (board[i][j] == 2 || board[i][j] == 20) {
					if ((board[i + 1][j - 1] == 3 || board[i + 1][j - 1] == 30) && board[i + 2][j - 2] == 1 && i < 8 && j > 1) {
						//dol_lewo_attak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i + 2, j - 2, "down_left");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, true);
						undo_ai_attack(board, i + 2, j - 2, i, j, "down_left", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > bestscore) {
							bestscore = value;
						}
						alpha = max(alpha, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}
					else if ((board[i + 1][j + 1] == 3 || board[i + 1][j + 1] == 30) && board[i + 2][j + 2] == 1 && i < 8 && j < 8) {
						//dol_prawo_atak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i + 2, j + 2, "down_right");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, true);
						undo_ai_attack(board, i + 2, j + 2, i, j, "down_right", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > bestscore) {
							bestscore = value;
						}
						alpha = max(alpha, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}

				}
				if (board[i][j] == 20) {
					if ((board[i - 1][j - 1] == 3 || board[i - 1][j - 1] == 30) && board[i - 2][j - 2] == 1 && i > 1 && j > 1) {
						//gora_lewo_atak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i - 2, j - 2, "up_left");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, true);
						undo_ai_attack(board, i - 2, j - 2, i, j, "up_left", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > bestscore) {
							bestscore = value;
						}
						alpha = max(alpha, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}
					else if ((board[i - 1][j + 1] == 3 || board[i - 1][j + 1] == 30) && board[i - 2][j + 2] == 1 && i > 1 && j < 8) {
						//gora_prawo_atak
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i - 2, j + 2, "up_right");
						//missing part when you are allowed for multi attacks in one move 
						int value = minimax(board, depth - 1, alpha, beta, true);
						undo_ai_attack(board, i - 2, j + 2, i, j, "up_right", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > bestscore) {
							bestscore = value;
						}
						alpha = max(alpha, value);
						if (beta <= alpha) {
							return bestscore;
						}
					}
				}



			}
		}
		if (attack_possible == false) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (board[i][j] == 2 || board[i][j] == 20) {
						if (board[i + 1][j - 1] == 1 && i < 9 && j > 0) {
							//ruch_dol_lewo 
							int piece = board[i][j];
							make_ai_move(board, i, j, i + 1, j - 1);
							int value = minimax(board, depth - 1, alpha, beta, true);
							undo_ai_move(board, i, j, i + 1, j - 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > bestscore) {
								bestscore = value;
							}
							alpha = max(alpha, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
						if (board[i + 1][j + 1] == 1 && i < 9 && j < 9) {
							//ruch_dol_prawo
							int piece = board[i][j];
							make_ai_move(board, i, j, i + 1, j + 1);
							int value = minimax(board, depth - 1, alpha, beta, true);
							undo_ai_move(board, i, j, i + 1, j + 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > bestscore) {
								bestscore = value;
							}
							alpha = max(alpha, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
					}

					if (board[i][j] == 20) {
						if (board[i - 1][j - 1] == 1 && i > 0 && j > 0) {
							//gora_lewo_ruch
							int piece = board[i][j];
							make_ai_move(board, i, j, i - 1, j - 1);
							int value = minimax(board, depth - 1, alpha, beta, true);
							undo_ai_move(board, i, j, i - 1, j - 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > bestscore) {
								bestscore = value;
							}
							alpha = max(alpha, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
						if (board[i - 1][j + 1] == 1 && i > 0 && j < 9) {
							//gora prawo
							int piece = board[i][j];
							make_ai_move(board, i, j, i - 1, j + 1);
							int value = minimax(board, depth - 1, alpha, beta, true);
							undo_ai_move(board, i, j, i - 1, j + 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > bestscore) {
								bestscore = value;
							}
							alpha = max(alpha, value);
							if (beta <= alpha) {
								return bestscore;
							}
						}
					}
				}
			}
		}
		if (bestscore == std::numeric_limits<int>::min()) {
			return validate(board);
		}
		else {
			return bestscore;
		}
	}
}


/// Main AI function to check all possibilites for that particular move using minimax function and choose and do the best one.
///
/// @param board This is a pointer to array with state of the board.
/// @param depth Variable that describes depth of the recursion for miniamax algorithm.
void ai_move(int board[10][10], int depth) {
	struct best_move move;
	bool attack_possible = false;
	int recursion_depth = depth;
	int base_ai_points = validate(board);
	int alpha = std::numeric_limits<int>::min(); //std::numeric_limits<int>::min();
	int beta = std::numeric_limits<int>::max();


	if (turn == 2) {
		move.best_value = std::numeric_limits<int>::min();
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (board[i][j] == 2 || board[i][j] == 20) {
					//sprawdza ataki w dol
					if ((board[i + 1][j - 1] == 3 || board[i + 1][j - 1] == 30) && board[i + 2][j - 2] == 1 && i < 8 && j > 1) {
						//atak dol_lewo
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i + 2, j - 2, "down_left");
						int value = minimax(board, recursion_depth, alpha, beta, true);
						printf("Atak w dol_lewo : %d\n", value);
						undo_ai_attack(board, i + 2, j - 2, i, j, "down_left", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5)) {
							move.best_value = value;
							move.start_y_pos = i;
							move.start_x_pos = j;
							move.new_y_pos = i + 2;
							move.new_x_pos = j - 2;
							move.deleted_piece = deleted_piece;
						}
					}
					else if ((board[i + 1][j + 1] == 3 || board[i + 1][j + 1] == 30) && board[i + 2][j + 2] == 1 && i < 8 && j < 8) {
						//atak dol_prawo
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i + 2, j + 2, "down_right");
						int value = minimax(board, recursion_depth, alpha, beta, true);
						printf("Atak w dol_prawo : %d\n", value);
						undo_ai_attack(board, i + 2, j + 2, i, j, "down_right", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5)) {
							move.best_value = value;
							move.start_y_pos = i;
							move.start_x_pos = j;
							move.new_y_pos = i + 2;
							move.new_x_pos = j + 2;
							move.deleted_piece = deleted_piece;
						}
					}
				}
				if (board[i][j] == 20) {
					//sprawdz ataki w gore
					if ((board[i - 1][j - 1] == 3 || board[i - 1][j - 1] == 30) && board[i - 2][j - 2] == 1 && i > 1 && j > 1) {
						//atak_gora_lewo
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i - 2, j - 2, "up_left");
						int value = minimax(board, recursion_depth, alpha, beta, true);
						printf("Atak w gora_lewo : %d\n", value);
						undo_ai_attack(board, i - 2, j - 2, i, j, "up_left", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5)) {
							move.best_value = value;
							move.start_y_pos = i;
							move.start_x_pos = j;
							move.new_y_pos = i - 2;
							move.new_x_pos = j - 2;
							move.deleted_piece = deleted_piece;
						}
					}
					if ((board[i - 1][j + 1] == 3 || board[i - 1][j + 1] == 30) && board[i - 2][j + 2] == 1 && i > 1 && j < 8) {
						//atak_gora_prawo
						attack_possible = true;
						int piece = board[i][j];
						int deleted_piece = make_ai_attack(board, i, j, i - 2, j + 2, "up_right");
						int value = minimax(board, recursion_depth, alpha, beta, true);
						printf("Atak w gora_prawo : %d\n", value);
						undo_ai_attack(board, i - 2, j + 2, i, j, "up_right", deleted_piece);
						if (piece != board[i][j]) {
							board[i][j] = piece;
						}
						if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5)) {
							move.best_value = value;
							move.start_y_pos = i;
							move.start_x_pos = j;
							move.new_y_pos = i - 2;
							move.new_x_pos = j + 2;
							move.deleted_piece = deleted_piece;
						}
					}
				}
			}
		}




		if (attack_possible == false) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					if (board[i][j] == 2 || board[i][j] == 20) {
						if (board[i + 1][j - 1] == 1 && i < 9 && j > 0) {
							//ruch dol_lewo
							int piece = board[i][j];
							make_ai_move(board, i, j, i + 1, j - 1);
							int value = minimax(board, recursion_depth, alpha, beta, true);
							printf("Dol_lewo [%d] [%d]: %d \n", i, j, value);
							undo_ai_move(board, i, j, i + 1, j - 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5) || (board[i][j] == 2 && i == 8)) {
								move.best_value = value;
								move.start_y_pos = i;
								move.start_x_pos = j;
								move.new_y_pos = i + 1;
								move.new_x_pos = j - 1;
								move.deleted_piece = -1;
							}
						}
						if (board[i + 1][j + 1] == 1 && i < 9 && j < 9) {
							//ruch dol_prawo
							int piece = board[i][j];
							make_ai_move(board, i, j, i + 1, j + 1);
							int value = minimax(board, recursion_depth, alpha, beta, true);
							printf("Dol_prawo [%d] [%d]: %d \n", i, j, value);
							undo_ai_move(board, i, j, i + 1, j + 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5) || (board[i][j] == 2 && i == 8)) {
								move.best_value = value;
								move.start_y_pos = i;
								move.start_x_pos = j;
								move.new_y_pos = i + 1;
								move.new_x_pos = j + 1;
								move.deleted_piece = -1;
							}
						}
					}
					if (board[i][j] == 20) {
						if (board[i - 1][j - 1] == 1) {
							//ruch_gora_lewo
							int piece = board[i][j];
							make_ai_move(board, i, j, i - 1, j - 1);
							int value = minimax(board, recursion_depth, alpha, beta, true);
							printf("Gora_lewo [%d] [%d]: %d \n", i, j, value);
							undo_ai_move(board, i, j, i - 1, j - 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5)) {
								move.best_value = value;
								move.start_y_pos = i;
								move.start_x_pos = j;
								move.new_y_pos = i - 1;
								move.new_x_pos = j - 1;
								move.deleted_piece = -1;
							}
						}
						if (board[i - 1][j + 1] == 1 && i > 0 && j < 9) {
							//ruch_gora_prawo
							int piece = board[i][j];
							make_ai_move(board, i, j, i - 1, j + 1);
							int value = minimax(board, recursion_depth, alpha, beta, true);
							printf("Gora_prawo [%d] [%d]: %d \n", i, j, value);
							undo_ai_move(board, i, j, i - 1, j + 1);
							if (piece != board[i][j]) {
								board[i][j] = piece;
							}
							if (value > move.best_value || (value == move.best_value && rand() % 10 + 1 > 5)) {
								move.best_value = value;
								move.start_y_pos = i;
								move.start_x_pos = j;
								move.new_y_pos = i - 1;
								move.new_x_pos = j + 1;
								move.deleted_piece = -1;
							}
						}

					}



				}
			}
		}

		printf("Ruch AI z pozycji : [%d] [%d] do [%d] [%d]", move.start_y_pos, move.start_x_pos, move.new_y_pos, move.new_x_pos);

		board[move.new_y_pos][move.new_x_pos] = board[move.start_y_pos][move.start_x_pos];
		board[move.start_y_pos][move.start_x_pos] = 1;
		if (move.deleted_piece != -1) {
			//printf("Wartosc zaatakowanej figury :%d ", move.deleted_piece);
			delete_piece_between(board, move.start_y_pos, move.start_x_pos, move.new_y_pos, move.new_x_pos);
		}
		turn = 3;

	}
	printf("base : %d\n", base_ai_points);
}
