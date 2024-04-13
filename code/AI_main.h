#ifndef AI_main
#define AI_main
#include <SFML/Graphics.hpp>

/// AI Auxiliary function that return's value validation of points on the game board that you provide. Mostly used by AI to determine with move is better.
///
/// @param board This is a pointer to array with state of the game board.
int validate(int board[10][10]);

/// Minimax algorithm function for checking every combination of the checkers game for a given depth. There is also implemented Alpha Beta Pruning algorithm to reduce total number of posibilities.
///
/// @param board This is a pointer to array with state of the board.
/// @param depth Variable that describes depth of the recursion.
/// @param alpha Variable that represent minimum score that the maximizing player is assured of (Alpha Beta Pruning algorithm)
/// @param beta Variable that represent maximum score that the maximizing player is assured of. (Alpha Beta Pruning algorithm)
/// @param isMaximizingPlayer Describes do you want to Maximize player or not. (Alpha Beta Pruning algorithm)
int minimax(int board[10][10], int depth, int alpha, int beta, bool isMaximizingPlayer);

/// Auxiliary function for returning bigger value from 2 numbers provided.
///
/// @param a First value to compare.
/// @param b Second value to compare.
int max(int a, int b);


/// Auxiliary function for returning smaller value from 2 numbers provided.
///
/// @param a First value to compare.
/// @param b Second value to compare.
int min(int a, int b);




/// AI Auxiliary function that makes attacks for a desired destinations. Returns value of deleted piece between.
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will attack.
/// @param j Col coordinates of piece that will attack.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
int make_ai_attack(int board[10][10], int i, int j, int new_i, int new_j, std::string direction);


/// AI Auxiliary function that undo AI attacks maked by make_ai_attack() function.
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will attack.
/// @param j Col coordinates of piece that will attack.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
void undo_ai_attack(int board[10][10], int i, int j, int new_i, int new_j, std::string direction, int deleted_piece);



/// AI Auxiliary function used to make AI move more transparent in code.
///
/// @param board This is a pointer to array with state of the board.
/// @param i row coordinates of piece that will move.
/// @param j Col coordinates of piece that will move.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
void make_ai_move(int board[10][10], int i, int j, int new_i, int new_j);

/// AI Auxiliary function used to make undo AI move more transparent in code.
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will move.
/// @param j Col coordinates of piece that will move.
/// @param new_i Row coordinates of destination.
/// @param new_j coodrinates of destination.
void undo_ai_move(int board[10][10], int i, int j, int new_i, int new_j);



/// Main AI function to check all possibilites for that particular move using minimax function and choose and do the best one.
///
/// @param board This is a pointer to array with state of the board.
/// @param depth Variable that describes depth of the recursion for miniamax algorithm.
void ai_move(int board[10][10], int depth);


#endif 