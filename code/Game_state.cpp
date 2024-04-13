/**
* @file Game_state.cpp
* @author Maciej Kwiecinski, Olek Kurek, Patryk Kregiel
* @date 13.01.2023
* @brief This file containt functions needed for drawing and manipulating game status
*/
#include "Game_state.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Auxiliary_functions.h"

extern sf::RenderWindow window; //!< Global window for the whole game and menu.

 /// Function used to draw pieces and board on the screen
 ///
 /// @param board This is pointer to array with state of the board.
 /// @param board_start_position_x This is a offset for where the board actally starts.
 /// @param board_start_position_y This is a offset for where the board actally starts.
void draw_game_state(int board[10][10], int board_start_position_x, int board_start_position_y) {
	sf::Texture piece_1;
	sf::Texture piece_1_king;
	sf::Texture piece_2;
	sf::Texture piece_2_king;
	sf::Texture game_board;
	game_board.loadFromFile("resources/mapa_10x10.jpg");
	piece_1.loadFromFile("resources/Piece_1.png");
	piece_1_king.loadFromFile("resources/Piece_1_king.png");
	piece_2.loadFromFile("resources/Piece_2.png");
	piece_2_king.loadFromFile("resources/Piece_2_king.png");
	sf::Sprite pionek_czer(piece_1);
	sf::Sprite king_czer(piece_1_king);
	sf::Sprite pionek_czar(piece_2);
	sf::Sprite king_czar(piece_2_king);
	sf::Sprite sprite_game_board(game_board);
	window.draw(sprite_game_board);
	sf::CircleShape black_pawn[20];
	sf::CircleShape black_king[20];
	sf::CircleShape white_pawn[20];
	sf::CircleShape white_king[20];
	sf::CircleShape possible_move[20];
	sf::CircleShape obramowka[20];


	for (int i = 0; i < 20; i++) {
		black_pawn[i].setRadius(44);
		black_pawn[i].setOutlineColor(sf::Color::Red);
		black_pawn[i].setOutlineThickness(5);
		black_pawn[i].setFillColor(sf::Color(0, 0, 0, 255));

		black_king[i].setRadius(44);
		black_king[i].setOutlineColor(sf::Color(250, 150, 100));
		black_king[i].setOutlineThickness(5);
		black_king[i].setFillColor(sf::Color(0, 0, 0, 255));

		white_pawn[i].setRadius(44);
		white_pawn[i].setOutlineColor(sf::Color::Red);
		white_pawn[i].setOutlineThickness(5);

		white_king[i].setRadius(44);
		white_king[i].setOutlineColor(sf::Color(250, 150, 100));
		white_king[i].setOutlineThickness(5);

		possible_move[i].setRadius(47);
		possible_move[i].setFillColor(sf::Color(0, 255, 0, 110));

		obramowka[i].setRadius(30);
		obramowka[i].setFillColor(sf::Color(255, 255, 255, 160));
	}
	int variable = 0;
	int tmp_x = -4;
	int tmp_y = -3;
	board_start_position_x = board_start_position_x + 5;
	board_start_position_y = board_start_position_y + 5;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (j <= 3) {
				tmp_x = -3;
			}
			else if (j >= 5 && j < 7) {
				tmp_x = -5;
			}
			else if (j >= 7) {
				tmp_x = -7;
			}
			else {
				tmp_x = -4;
			}

			if (i <= 2) {
				tmp_y = -1;
			}
			else if (i >= 6) {
				tmp_y = -5;
			}
			else {
				tmp_y = -3;
			}
			if (board[i][j] == 2 && i == 9) {
				board[i][j] = 20; // make king
			}
			if (board[i][j] == 3 && i == 0) {
				board[i][j] = 30; // make king	
			}
			if (board[i][j] == 2 || board[i][j] == 52) {
				//black_pawn[i].setPosition((j * 96) +  board_start_position_x+tmp_x, (i * 96) +  board_start_position_y + tmp_y);
				//window.draw(black_pawn[i]);
				pionek_czer.setPosition((j * 96) + board_start_position_x + tmp_x, (i * 96) + board_start_position_y + tmp_y);
				window.draw(pionek_czer);
			}
			if (board[i][j] == 20 || board[i][j] == 70) {
				//black_king[i].setPosition((j * 96) + board_start_position_x+tmp_x, (i * 96) + 3 + board_start_position_y + tmp_y);
				//window.draw(black_king[i]);
				king_czer.setPosition((j * 96) + board_start_position_x + tmp_x, (i * 96) + board_start_position_y + tmp_y);
				window.draw(king_czer);
			}
			if (board[i][j] == 3 || board[i][j] == 53) {
				//white_pawn[i].setPosition((j * 96) +  board_start_position_x + tmp_x, (i * 96) +  board_start_position_y + tmp_y);
				//window.draw(white_pawn[i]);
				pionek_czar.setPosition((j * 96) + board_start_position_x + tmp_x, (i * 96) + board_start_position_y + tmp_y);
				window.draw(pionek_czar);
			}
			if (board[i][j] == 30 || board[i][j] == 80) {
				//white_king[i].setPosition((j * 96) +  board_start_position_x + tmp_x, (i * 96) + board_start_position_y + tmp_y);
				//window.draw(white_king[i]);
				king_czar.setPosition((j * 96) + board_start_position_x + tmp_x, (i * 96) + board_start_position_y + tmp_y);
				window.draw(king_czar);
			}
			if (board[i][j] == 99) {
				possible_move[i].setPosition((j * 96) + board_start_position_x + tmp_x, (i * 96) + board_start_position_y + tmp_y);
				window.draw(possible_move[i]);
			}
			if (board[i][j] == 52 || board[i][j] == 70 || board[i][j] == 53 || board[i][j] == 80) {
				obramowka[i].setPosition((j * 96) + 18 + tmp_x + board_start_position_x, (i * 96) + 16 + tmp_y + board_start_position_y);
				window.draw(obramowka[i]);
			}
		}
	}
	window.display();
}



//sprawdza ktore jednostki moga zaatakowac i zwieksza ich wartosc o 50, aby mozna bylo je wyroznic rysujac
//Jesli moze jakakolwiek jednostka zaatakowac to jest to ruch wymuszony, dlatego przed każdym ruchem należy sprawdzic czy sa takie wymuszone ruchy
//Checks overall player attack opportunities, and changes the values on the board (piece that are incremented by 50, are the pieces that are allowed to attack)
/// Checks overall player attack opportunities, and changes the values on the board (piece that are incremented by 50, are the pieces that are allowed to attack)
///
/// @param gracz Describes for with player you want to check attack opportunity.
/// @param board This is a pointer to array with state of the board.
/// @param continue_i Variable that describes on with row you want to check attack_opportunity for specific piece only.
/// @param continue_j Variable that describes on with column you want to check attack_opportunity for specific piece only.
bool check_attack_opportunity(int gracz, int board[10][10], int continue_i, int continue_j) {
	int enemy = -1;
	if (gracz == 3) { enemy = 2; }
	if (gracz == 2) { enemy = 3; }
	bool can_attack = false;
	if (continue_i != -1 && continue_j != -1) {
		int i = continue_i;
		int j = continue_j;
		if (gracz == 2) {
			if (board[i][j] == 2 || board[i][j] == 20) {
				if (board[i + 1][j - 1] == enemy || board[i + 1][j - 1] == enemy * 10) {
					if (board[i + 2][j - 2] == 1) {
						//dol_lewo
						board[i][j] = board[i][j] + 50;
						can_attack = true;
					}
				}
				if (board[i + 1][j + 1] == enemy || board[i + 1][j + 1] == enemy * 10) {
					if (board[i + 2][j + 2] == 1) {
						//dol_prawo
						if (board[i][j] < 50) {
							board[i][j] = board[i][j] + 50;
						}
						can_attack = true;
					}
				}
			}
			if (board[i][j] == 20) {
				if (board[i - 1][j - 1] == enemy || board[i - 1][j - 1] == enemy * 10) {
					if (board[i - 2][j - 2] == 1) {
						//gora_lewo
						board[i][j] = board[i][j] + 50;
						can_attack = true;
					}
				}
				if (board[i - 1][j + 1] == enemy || board[i - 1][j + 1] == enemy * 10) {
					if (board[i - 2][j + 2] == 1) {
						//gora_prawo
						if (board[i][j] < 50) {
							board[i][j] = board[i][j] + 50;
						}
						can_attack = true;
					}
				}
			}
		}

		if (gracz == 3) {
			if (board[i][j] == 3 || board[i][j] == 30) {
				if (board[i - 1][j - 1] == enemy || board[i - 1][j - 1] == enemy * 10) {
					if (board[i - 2][j - 2] == 1) {
						//gora_lewo
						board[i][j] = board[i][j] + 50;
						can_attack = true;
					}
				}
				if (board[i - 1][j + 1] == enemy || board[i - 1][j + 1] == enemy * 10) {
					if (board[i - 2][j + 2] == 1) {
						//gora_prawo
						if (board[i][j] < 50) {
							board[i][j] = board[i][j] + 50;
						}
						can_attack = true;
					}
				}


			}
			if (board[i][j] == 30) {
				if (board[i + 1][j - 1] == enemy || board[i + 1][j - 1] == enemy * 10) {
					if (board[i + 2][j - 2] == 1) {
						//dol_lewo
						board[i][j] = board[i][j] + 50;
						can_attack = true;
					}
				}
				if (board[i + 1][j + 1] == enemy || board[i + 1][j + 1] == enemy * 10) {
					if (board[i + 2][j + 2] == 1) {
						//dol_prawo
						if (board[i][j] < 50) {
							board[i][j] = board[i][j] + 50;
						}
						can_attack = true;
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < 10; i++) {
			for (int j = 0; j < 10; j++) {
				if (gracz == 2) {
					if (board[i][j] == 2 || board[i][j] == 20) {
						if (board[i + 1][j - 1] == enemy || board[i + 1][j - 1] == enemy * 10) {
							if (board[i + 2][j - 2] == 1) {
								//dol_lewo
								board[i][j] = board[i][j] + 50;
								can_attack = true;
							}
						}
						if (board[i + 1][j + 1] == enemy || board[i + 1][j + 1] == enemy * 10) {
							if (board[i + 2][j + 2] == 1) {
								//dol_prawo
								if (board[i][j] < 50) {
									board[i][j] = board[i][j] + 50;
								}
								can_attack = true;
							}
						}
					}
					if (board[i][j] == 20) {
						if (board[i - 1][j - 1] == enemy || board[i - 1][j - 1] == enemy * 10) {
							if (board[i - 2][j - 2] == 1) {
								//gora_lewo
								board[i][j] = board[i][j] + 50;
								can_attack = true;
							}
						}
						if (board[i - 1][j + 1] == enemy || board[i - 1][j + 1] == enemy * 10) {
							if (board[i - 2][j + 2] == 1) {
								//gora_prawo
								if (board[i][j] < 50) {
									board[i][j] = board[i][j] + 50;
								}
								can_attack = true;
							}
						}
					}
				}

				if (gracz == 3) {
					if (board[i][j] == 3 || board[i][j] == 30) {
						if (board[i - 1][j - 1] == enemy || board[i - 1][j - 1] == enemy * 10) {
							if (board[i - 2][j - 2] == 1) {
								//gora_lewo
								board[i][j] = board[i][j] + 50;
								can_attack = true;
							}
						}
						if (board[i - 1][j + 1] == enemy || board[i - 1][j + 1] == enemy * 10) {
							if (board[i - 2][j + 2] == 1) {
								//gora_prawo
								if (board[i][j] < 50) {
									board[i][j] = board[i][j] + 50;
								}
								can_attack = true;
							}
						}


					}
					if (board[i][j] == 30) {
						if (board[i + 1][j - 1] == enemy || board[i + 1][j - 1] == enemy * 10) {
							if (board[i + 2][j - 2] == 1) {
								//dol_lewo
								board[i][j] = board[i][j] + 50;
								can_attack = true;
							}
						}
						if (board[i + 1][j + 1] == enemy || board[i + 1][j + 1] == enemy * 10) {
							if (board[i + 2][j + 2] == 1) {
								//dol_prawo
								if (board[i][j] < 50) {
									board[i][j] = board[i][j] + 50;
								}
								can_attack = true;
							}
						}
					}
				}

			}
		}
	}
	return can_attack;
}


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
bool color_mandatory_moves(int gracz, int board[10][10], int i, int j) {
	int enemy = -1;
	if (gracz == 3) { enemy = 2; }
	if (gracz == 2) { enemy = 3; }
	//struktura -> selected -> wymuszone == 1;
	bool attack = false;


	if (gracz == 2) {
		if (board[i][j] == 52 || board[i][j] == 70) {
			if (board[i + 1][j - 1] == 3 || board[i + 1][j - 1] == 30) {
				if (board[i + 2][j - 2] == 1) {
					board[i + 2][j - 2] = 99;
					bool attack = true;
					//atak_dol_lewo
				}
			}
			if (board[i + 1][j + 1] == 3 || board[i + 1][j + 1] == 30) {
				if (board[i + 2][j + 2] == 1) {
					board[i + 2][j + 2] = 99;
					bool attack = true;
					//atak_dol_prawo
				}
			}
		}
		if (board[i][j] == 70) {
			if (board[i - 1][j - 1] == 3 || board[i - 1][j - 1] == 30) {
				if (board[i - 2][j - 2] == 1) {
					board[i - 2][j + 2] = 99;
					bool attack = true;
					//atak_gora_lewo
				}
			}
			if (board[i - 1][j + 1] == 3 || board[i - 1][j + 1] == 30) {
				if (board[i - 2][j + 2] == 1) {
					board[i - 2][j + 2] = 99;
					bool attack = true;
					//atak_gora_prawo
				}
			}
		}
	}
	if (gracz == 3) {
		if (board[i][j] == 53 || board[i][j] == 80) {
			if (board[i - 1][j - 1] == 2 || board[i - 1][j - 1] == 20) {
				if (board[i - 2][j - 2] == 1) {
					board[i - 2][j - 2] = 99;
					bool attack = true;
					//atak_gora_lewo
				}
			}
			if (board[i - 1][j + 1] == 2 || board[i - 1][j + 1] == 20) {
				if (board[i - 2][j + 2] == 1) {
					board[i - 2][j + 2] = 99;
					bool attack = true;
					//atak_gora_prawo
				}
			}
		}
		if (board[i][j] == 80) {
			if (board[i + 1][j - 1] == 2 || board[i + 1][j - 1] == 20) {
				if (board[i + 2][j - 2] == 1) {
					board[i + 2][j - 2] = 99;
					bool attack = true;
					//atak_dol_lewo
				}
			}
			if (board[i + 1][j + 1] == 2 || board[i + 1][j + 1] == 20) {
				if (board[i + 2][j + 2] == 1) {
					board[i + 2][j + 2] = 99;
					bool attack = true;
					//atak_dol_prawo
				}
			}
		}
	}
	return attack;


}


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
/// @param board This is a pointer to array with state of the board.
/// @param turnn Describes for with player you want to check.
int can_move(int board[10][10], int turnn) {
	int enemy = -1;
	bool player = false;
	bool player_attack = false;
	bool player_move = false;
	bool up_left = false, up_right = false, down_left = false, down_right = false;
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			if (!player) {//sprawdza czy  gracz ma przynajmniej jednego pionka
				if (board[i][j] == turnn || board[i][j] == turnn * 10 || board[i][j] == turnn + 50 || (board[i][j] == (turnn * 10) + 50)) {
					player = true;
				}
			}
			if ((!player_move || !player_attack) && player) {
				if (turnn == 2) {
					if (board[i][j] == 20 || board[i][j] == 70) {
						if ((board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == 99) && j > 0) { up_left = true; player_move = true; }
						if ((board[i - 1][j + 1] == 1 || board[i - 1][j + 1] == 99) && j < 9) { up_right = true; player_move = true; }
					}
					if ((board[i][j] == 2 || board[i][j] == 52) || (board[i][j] == 20 || board[i][j] == 70)) {
						if ((board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == 99) && j > 0) { down_left = true; player_move = true; }
						if ((board[i + 1][j + 1] == 1 || board[i + 1][j + 1] == 99) && j < 9) { down_right = true; player_move = true; }
					}
				}
				if (turnn == 3) {
					if ((board[i][j] == 3 || board[i][j] == 53) || (board[i][j] == 30 || board[i][j] == 80)) {
						if ((board[i - 1][j - 1] == 1 || board[i - 1][j - 1] == 99) && j > 0) { up_left = true; player_move = true; }
						if ((board[i - 1][j + 1] == 1 || board[i - 1][j + 1] == 99) && j < 9) { up_right = true; player_move = true; }
					}
					if (board[i][j] == 30 || board[i][j] == 80) {
						if ((board[i + 1][j - 1] == 1 || board[i + 1][j - 1] == 99) && j > 0) { down_left = true; player_move = true; }
						if ((board[i + 1][j + 1] == 1 || board[i - 1][j - 1] == 99) && j < 9) { down_right = true; player_move = true; }
					}
				}

				if (player && player_move) {
					return 0;
				}

				if (board[i][j] == 2 || board[i][j] == 20) { enemy = 3; }
				if (board[i][j] == 3 || board[i][j] == 30) { enemy = 2; } //jesli moze zaatakowac to moze tez sie ruszyc
				int zmienna = board[i + 1][j - 1];
				if (is_enemy(turnn, board[i + 1][j - 1]) && board[i + 2][j - 2] == 1 && i < 8 && j > 1) {
					down_left = true;
				}

				if (is_enemy(turnn, board[i + 1][j + 1]) && board[i + 2][j + 2] == 1 && i < 8 && j < 8) {
					down_right = true;
				}
				if (is_enemy(turnn, board[i - 1][j - 1]) && board[i - 2][j - 2] == 1 && i > 1 && j > 1) {
					up_left = true;
				}
				if (is_enemy(turnn, board[i - 1][j + 1]) && board[i - 2][j + 2] == 1 && i > 1 && j < 8) {
					up_right = true;
				}
				if (board[i][j] == 2 || board[i][j] == 52) {
					if (down_left || down_right) { player_attack = true; }
				}
				if (board[i][j] == 3 || board[i][j] == 53) {
					if (up_left || up_right) { player_attack = true; }
				}
				if (board[i][j] == turnn * 10 || board[i][j] == (turnn * 10) + 50) {
					if (up_left || up_right || down_left || down_right) { player_attack = true; }
				}

				if (player && player_attack) {
					return 0;
				}
			}
		}
	}

	//std::cout <<std::endl<< up_left << up_right << down_left << down_right << std::endl << player << player_attack << player_move;
	return 1;//jesli nie moze sie poruszyc ani zrobic ruchu to przegrywa
}


//This function checks where the piece can move (move but without a attacks)
/// This function marks on the board selected piece moves capability by changing values in the game board array. (value 99 means that you can move selected piece to that destination)
///
/// @param board This is a pointer to array with state of the board.
/// @param allowed_moves Struct that provides informations about mandatory moves or piece that we had  selected. In this function we need it to know with piece we had selected.
void check_moves(int board[10][10], struct wymuszone_ruchy& allowed_moves) {
	int selected_x = allowed_moves.selected_piece_x;
	int selected_y = allowed_moves.selected_piece_y;
	clear_moves(board, 0, allowed_moves);
	if (board[selected_y][selected_x] == 2 || board[selected_y][selected_x] == 20 || board[selected_y][selected_x] == 30) {
		if (board[selected_y + 1][selected_x - 1] == 1) {
			board[selected_y + 1][selected_x - 1] = 99;
			//std::cout << "dol_lewo";
		}
		if (board[selected_y + 1][selected_x + 1] == 1) {
			board[selected_y + 1][selected_x + 1] = 99;
			//std::cout << "dol_prawo";
		}
	}
	if (board[selected_y][selected_x] == 3 || board[selected_y][selected_x] == 20 || board[selected_y][selected_x] == 30) {
		if (board[selected_y - 1][selected_x - 1] == 1) {
			board[selected_y - 1][selected_x - 1] = 99;
			//std::cout << "gora_lewo";
		}
		if (board[selected_y - 1][selected_x + 1] == 1) {
			board[selected_y - 1][selected_x + 1] = 99;
			//std::cout << "gora_prawo";
		}
	}
}