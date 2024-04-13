#ifndef Auxiliary_functions
#define Auxiliary_functions

/**
 * @brief Structure for mandatory moves and selected piece coordinates.
 *
 *
 */
struct wymuszone_ruchy {
	int selected_piece_x = -1; /**< Selected piece row coordinates */
	int selected_piece_y = -1; /**< Selected piece col coordinates */
	int wymus = -1;			   /**< Variable that describes is there a mandatory move you have to do. */
	int continue_i = -1;	   /**< Variable that describes piece col coordinates that needs to make mandatory move. */
	int continue_j = -1;	   /**< Variable that describes piece row coordinates that needs to make mandatory move. */
};

//This function checks is the value passed is a enemy to the player -> gracz

/// Function that return is the piece provided a enemy for a player.
///
/// @param player Describes for with player you want to mark attack/move opportunity.
/// @param enemy Describes enemy value that you want to check.
bool is_enemy(int player, int enemy);


//This function cleares moddified values in the board array
//with "delete_moves" value set to 1, it will delete as well selected_piece in struct allowed_moves

/// This function changes board game value's to the previous state.
///
/// @param board This is a pointer to array with state of the board.
/// @param delete_moves Variable that describes possibility for unselecting piece in struct provided as 3 argument.
/// @param allowed_moves Struct that provides informations about mandatory moves or piece that we had  selected.
void clear_moves(int board[10][10], int delete_moves, struct wymuszone_ruchy& allowed_moves);


//This function delete the piece after a attack

/// This function deletes a piece on attack. 
///
/// @param board This is a pointer to array with state of the board.
/// @param i Row coordinates of piece that will attack.
/// @param j Col coordinates of piece that will attack.
/// @param y Row coordinates of piece that will be attacked.
/// @param x Col coodrinates of piece that will be attacked.
void delete_piece_between(int board[10][10], int i, int j, int y, int x);

#endif 