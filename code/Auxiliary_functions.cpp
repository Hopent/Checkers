/**
 * @file Auxiliary_functions.cpp
 * @author Maciej Kwiecinski
 * @date 29.05.2022
 * @brief Containt additional functions.
 */

#include "Auxiliary_functions.h"
#include <SFML/Graphics.hpp>

int turn = 3;  //!< Global Variable ford escribing with player should move now.

sf::RenderWindow window(sf::VideoMode(1010, 1010, 32), "Warcaby",
	sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close); //!< Global window for the whole game and menu.

long int liczba_operacji = 0; //!< Global Variable for counting number of possibilites in minimax algorithm.




 //This function checks is the value passed is a enemy to the player -> gracz

 /// Function that return is the piece provided a enemy for a player.
 ///
 /// @param player Describes for with player you want to mark attack/move opportunity.
 /// @param enemy Describes enemy value that you want to check.
bool is_enemy(int player, int enemy) {
	if (player == 2) {
		if (enemy == 3 || enemy == 30 || enemy == 53 || enemy == 80) {
			return true;
		}
	}
	if (player == 3) {
		if (enemy == 2 || enemy == 20 || enemy == 52 || enemy == 70) {
			return true;
		}
	}
	return false;
}


//This function cleares moddified values in the board array
//with "delete_moves" value set to 1, it will delete as well selected_piece in struct allowed_moves

/// This function changes board game value's to the previous state.
///
/// @param board This is a pointer to array with state of the board.
/// @param delete_moves Variable that describes possibility for unselecting piece in struct provided as 3 argument.
/// @param allowed_moves Struct that provides informations about mandatory moves or piece that we had  selected.
void clear_moves(int board[10][10], int delete_moves, struct wymuszone_ruchy& allowed_moves) {
	if (delete_moves == 1) {
		allowed_moves.selected_piece_x = -1;
		allowed_moves.selected_piece_y = -1;
	}
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (board[i][j] == 99) {
				board[i][j] = 1;
			}
			if (delete_moves == 1) {
				if (board[i][j] > 50) {
					board[i][j] = board[i][j] - 50;
				}
			}
		}
	}
}

//This function delete the piece after a attack

/// This function deletes a piece on attack. 
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will attack.
/// @param j Col coordinates of piece that will attack.
/// @param y Row coordinates of piece that will be attacked.
/// @param x Col coodrinates of piece that will be attacked.
void delete_piece_between(int board[10][10], int i, int j, int y, int x) {
	//i, j - piece coordinate
	//y, x - destination coordinate

	if (y > i) { //dol
		if (x > j) { //dol_prawo
			board[i + 1][j + 1] = 1;
		}
		if (x < j) { //dol_lewo
			board[i + 1][j - 1] = 1;
		}
	}
	if (y < i) {//gora
		if (x > j) { //gora_prawo
			board[i - 1][j + 1] = 1;
		}
		if (x < j) { //gora_lewo
			board[i - 1][j - 1] = 1;
		}
	}

}

