#ifndef Game_state
#define Game_state

/// Function used to draw pieces and board on the screen
 ///
 /// @param board This is pointer to array with state of the board.
 /// @param board_start_position_x This is a offset for where the board actally starts.
 /// @param board_start_position_y This is a offset for where the board actally starts.
void draw_game_state(int board[10][10], int board_start_position_x, int board_start_position_y);

//sprawdza ktore jednostki moga zaatakowac i zwieksza ich wartosc o 50, aby mozna bylo je wyroznic rysujac
//Jesli moze jakakolwiek jednostka zaatakowac to jest to ruch wymuszony, dlatego przed każdym ruchem należy sprawdzic czy sa takie wymuszone ruchy
//Checks overall player attack opportunities, and changes the values on the board (piece that are incremented by 50, are the pieces that are allowed to attack)
/// Checks overall player attack opportunities, and changes the values on the board (piece that are incremented by 50, are the pieces that are allowed to attack)
///
/// @param gracz Describes for with player you want to check attack opportunity.
/// @param board This is a pointer to array with state of the board.
/// @param continue_i Variable that describes on with row you want to check attack_opportunity for specific piece only.
/// @param continue_j Variable that describes on with column you want to check attack_opportunity for specific piece only.
bool check_attack_opportunity(int gracz, int board[10][10], int continue_i, int continue_j);


//sprawdza klikniety pionek czy moze zaatakowac i pokazuje jego sciezki
//Koloruje mozliwe pola do wyboru podczas ataku
//Checks selected piece for attack opportunity and draw them on the board
//It also changes values on the board to 99, it means that selected piece can attack this way

/// This function marks the places on the board where a piece can attack/move. (The places are marked by value "99")
///
/// @param gracz Describes for with player you want to mark attack/move opportunity.
/// @param board This is a pointer to array with state of the board.
/// @param i Variable that describes which row is a piece that you want to marks move's for.
/// @param j Variable that describes which column is a piece that you want to marks move's for.
bool color_mandatory_moves(int gracz, int board[10][10], int i, int j);




//This function checks:
//Do a player have pieces on the board, 
//Do a player can move
//Do a player can attack
//If any of this statement is True, then this player lose the game
//Returns 0 if there is a validate move, or Returns 1 if there isnt any validate moves.


/// This function checks is there any validate move for that player, if not then this player have lose. 
/// It also checks do a player has a pieces on the board, do they can move or even do they can attack. 
/// If any of this is true, then it returns 0 to signal that there is a validate move.
///
/// @param player Describes for with player you want to mark attack/move opportunity.
/// @param enemy Describes enemy value that you want to check.
int can_move(int board[10][10], int turnn);

//This function checks where the piece can move (move but without a attacks)
/// This function marks on the board selected piece moves capability by changing values in the game board array. (value 99 means that you can move selected piece to that destination)
///
/// @param board This is a pointer to array with state of the board.
/// @param allowed_moves Struct that provides informations about mandatory moves or piece that we had  selected. In this function we need it to know with piece we had selected.
void check_moves(int board[10][10], struct wymuszone_ruchy& allowed_moves);


#endif 