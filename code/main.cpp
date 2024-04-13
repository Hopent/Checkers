/**
* @file main.c
* @author Maciej Kwiecinski, Olek Kurek, Patryk Kregiel
* @date 13.01.2023
* @brief Main file of the checkers game project.
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <iostream>
#include <windows.h>
#include "Auxiliary_functions.h"
#include "Game_state.h"
#include "AI_main.h"
#include "Menu_handler.h"



extern sf::RenderWindow window;		//!< Global window for the whole game and menu.
extern int turn;					//!< Global Variable ford escribing with player should move now.
extern long int liczba_operacji;	//!< Global Variable for counting number of possibilites in minimax algorithm.




int main()
{
	sf::Image icon;
	icon.loadFromFile("resources/icon.png");
	window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	window.setPosition({ window.getPosition().x,0 });
	std::srand(static_cast<unsigned int>(std::time(NULL)));

	// Define some constants
	const int gameWidth = 1010;
	const int gameHeight = 1010;
	const int board_start_position_x = 25;
	const int board_start_position_y = 25;
	int game_status = -1;
	int MenuSelect = 1;
	/*int board_10x10[10][10] = {{2,0,2,0,2,0,2,0,2,0},
								{0,2,0,2,0,2,0,2,0,2},
								{2,0,2,0,2,0,2,0,2,0},
								{0,2,0,2,0,2,0,2,0,2},
								{1,0,1,0,1,0,1,0,1,0},
								{0,1,0,1,0,1,0,1,0,1},
								{3,0,3,0,3,0,3,0,3,0},
								{0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,3,0,3,0},
								{0,3,0,3,0,3,0,3,0,3} };*/

	int board_10x10[10][10] = { {0,2,0,2,0,2,0,2,0,2},
								{2,0,2,0,2,0,2,0,2,0},
								{0,2,0,2,0,2,0,2,0,2},
								{2,0,2,0,2,0,2,0,2,0},
								{0,1,0,1,0,1,0,1,0,1},
								{1,0,1,0,1,0,1,0,1,0},
								{0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,3,0,3,0},
								{0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,3,0,3,0} };


	int new_game_board[10][10] = { {0,2,0,2,0,2,0,2,0,2},
								{2,0,2,0,2,0,2,0,2,0},
								{0,2,0,2,0,2,0,2,0,2},
								{2,0,2,0,2,0,2,0,2,0},
								{0,1,0,1,0,1,0,1,0,1},
								{1,0,1,0,1,0,1,0,1,0},
								{0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,3,0,3,0},
								{0,3,0,3,0,3,0,3,0,3},
								{3,0,3,0,3,0,3,0,3,0} };





	/*int board_10x10[10][10]{{2, 0, 2, 0, 2, 0, 2, 0, 2, 0},
								{ 0,1,0,1,0,1,0,1,0,1 },
								{ 1,0,1,0,1,0,1,0,1,0 },
								{ 0,1,0,1,0,1,0,1,0,1 },
								{ 1,0,1,0,1,0,1,0,1,0 },
								{ 0,1,0,1,0,1,0,1,0,1 },
								{ 1,0,1,0,1,0,1,0,1,0 },
								{ 0,1,0,1,0,1,0,1,0,1 },
								{ 1,0,1,0,1,0,1,0,1,0 },
								{ 0,3,0,3,0,3,0,3,0,3 } };    */




								// Create the window of the application
								//sf::RenderWindow window(sf::VideoMode(gameWidth, gameHeight, 32), "Warcaby",
								//	sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
								//window.setVerticalSyncEnabled(true);




								// Load the text font
	sf::Font font;
	if (!font.loadFromFile("resources/Tribeca.ttf"))
		return EXIT_FAILURE;


	//sf::Texture pionki_czarne;
	//if (!game_board.loadFromFile("pionek_czarny.png"))
	//	return EXIT_FAILURE;
	//sf::Sprite sprite_game_board(pionki_czarne);




	sf::Text text;
	sf::Clock clock;
	int game_state = 0;
	int new_game = 1;
	int AI_level = 0;
	int game_type = 0; // 0 - player vs player, 1 - computer vs player
	int open_menu = 1;
	struct wymuszone_ruchy allowed_moves;
	allowed_moves.selected_piece_x = -1;
	allowed_moves.selected_piece_y = -1;



	if (open_menu == 1) {
	menu1:
		//przyciski
		sf::Texture buttonTexture;
		sf::Texture hoverTexture;
		buttonTexture.loadFromFile("resources/panel.png");
		hoverTexture.loadFromFile("resources/panel_pressed.png");
		sf::Sprite button1;
		sf::Sprite button2;
		sf::Sprite button3;
		sf::Sprite button4;
		sf::Text text1;
		sf::Text text2;
		sf::Text text3;
		sf::Text text4;
		button1.setTexture(buttonTexture);
		button2.setTexture(buttonTexture);
		button3.setTexture(buttonTexture);
		button4.setTexture(buttonTexture);
		button1.setPosition(275, 515);
		button2.setPosition(275, 650);
		button3.setPosition(275, 795);
		button4.setPosition(275, 380);

		//mechanika przyciskow (niewidoczne)
		double posX{ 0.2722772277227723 * window.getSize().x };
		double posY1{ 0.5099009900990099 * window.getSize().y };
		double posY2{ 0.6435643564356436 * window.getSize().y };
		double posY3{ 0.7871287128712871 * window.getSize().y };
		double posY4{ 0.3762376237623762 * window.getSize().y };

		double sizeX{ 0.4752475247524752 * window.getSize().x };
		double sizeY{ 0.1336633663366337 * window.getSize().y };

		Button opcja1("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);
		opcja1.setPosition({ static_cast<float>(posX), static_cast<float>(posY1) });
		opcja1.setFont(font);
		Button opcja2("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);; //ma przekierowac do podmenu
		opcja2.setPosition({ static_cast<float>(posX), static_cast<float>(posY2) });
		opcja2.setFont(font);
		Button opcja3("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);
		opcja3.setPosition({ static_cast<float>(posX), static_cast<float>(posY3) });
		opcja3.setFont(font);
		Button opcja4("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);
		opcja4.setPosition({ static_cast<float>(posX), static_cast<float>(posY4) });
		opcja4.setFont(font);

		//tekst na buttonach - menu glowne
		text1.setString("Gracz vs Gracz");
		text1.setFont(font);
		text1.setCharacterSize(40);
		text1.setFillColor(sf::Color::Black);
		text1.setPosition(310, 550);

		text2.setString("Gracz vs AI");
		text2.setFont(font);
		text2.setCharacterSize(40);
		text2.setFillColor(sf::Color::Black);
		text2.setPosition(365, 685);

		text3.setString("Wyjscie");
		text3.setFont(font);
		text3.setCharacterSize(40);
		text3.setFillColor(sf::Color::Black);
		text3.setPosition(420, 830);

		text4.setString("Kontynuuj");
		text4.setFont(font);
		text4.setCharacterSize(40);
		text4.setFillColor(sf::Color::Black);
		text4.setPosition(375, 415);
		//mechanika menu
		if (MenuSelect == 1)
		{
			std::cout << "menu: " << MenuSelect << std::endl;
			sf::Event event;
			while (window.isOpen() && open_menu == 1)
			{
				window.clear();
				//wyglad tla menu glownego
				sf::RectangleShape mainBackground;
				mainBackground.setSize(sf::Vector2f(gameWidth, gameHeight));
				sf::Texture mainTexture;
				mainTexture.loadFromFile("resources/Menu.png");
				mainBackground.setTexture(&mainTexture);
				window.draw(mainBackground);
				window.draw(button1);
				window.draw(button2);
				window.draw(button3);
				window.draw(text1);
				window.draw(text2);
				window.draw(text3);
				opcja1.draw(window);
				opcja2.draw(window);
				opcja3.draw(window);
				if (new_game == 0 && game_state!= -1)
				{
					window.draw(button4);
					window.draw(text4);
					opcja4.draw(window);
				}
				window.display();
				while (window.pollEvent(event) && open_menu == 1)
				{
					if (event.type == sf::Event::Resized)
					{
						double posX{ 0.2722772277227723 * window.getSize().x };
						double posY1{ 0.5099009900990099 * window.getSize().y };
						double posY2{ 0.6435643564356436 * window.getSize().y };
						double posY3{ 0.7871287128712871 * window.getSize().y };
						double posY4{ 0.3762376237623762 * window.getSize().y };

						double sizeX{ 0.4752475247524752 * window.getSize().x };
						double sizeY{ 0.1336633663366337 * window.getSize().y };

						opcja1.setPosition({ static_cast<float>(posX), static_cast<float>(posY1) });
						opcja1.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
						opcja2.setPosition({ static_cast<float>(posX), static_cast<float>(posY2) });
						opcja2.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
						opcja3.setPosition({ static_cast<float>(posX), static_cast<float>(posY3) });
						opcja3.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
						opcja4.setPosition({ static_cast<float>(posX), static_cast<float>(posY4) });
						opcja4.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
					}
					switch (event.type)
					{
					case sf::Event::Closed:
					{
						window.close();
					}
					case sf::Event::MouseMoved:
					{
						if (opcja1.isMouseOver(window))
						{
							button1.setTexture(hoverTexture);
						}
						else
						{
							button1.setTexture(buttonTexture);
						}
						if (opcja2.isMouseOver(window))
						{
							button2.setTexture(hoverTexture);
						}
						else
						{
							button2.setTexture(buttonTexture);
						}
						if (opcja3.isMouseOver(window))
						{
							button3.setTexture(hoverTexture);
						}
						else
						{
							button3.setTexture(buttonTexture);
						}
						if (opcja4.isMouseOver(window))
						{
							button4.setTexture(hoverTexture);
						}
						else
						{
							button4.setTexture(buttonTexture);
						}
						break;
					}
					case sf::Event::MouseButtonPressed:
					{
						if (event.mouseButton.button == sf::Mouse::Left)
						{
							if (opcja1.isMouseOver(window))
							{
								//window.close();
								//std::cout << "gracz-gracz: tu powinno odpalic gre gracz vs gracz" << std::endl;
								open_menu = 0;
								game_type = 0;
								game_state = 0;
								new_game = 1;
							}
							if (opcja2.isMouseOver(window))
							{
								MenuSelect++;
								//mechanika przyciskow (niewidoczne)
								double posX{ 0.2722772277227723 * window.getSize().x };
								double posY1{ 0.5099009900990099 * window.getSize().y };
								double posY2{ 0.6435643564356436 * window.getSize().y };
								double posY3{ 0.7871287128712871 * window.getSize().y };
								double posY4{ 0.3762376237623762 * window.getSize().y };

								double sizeX{ 0.4752475247524752 * window.getSize().x };
								double sizeY{ 0.1336633663366337 * window.getSize().y };

								Button opcja21("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);
								opcja21.setPosition({ static_cast<float>(posX), static_cast<float>(posY4) });
								opcja21.setFont(font);
								Button opcja22("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);; //ma przekierowac do podmenu
								opcja22.setPosition({ static_cast<float>(posX), static_cast<float>(posY1) });
								opcja22.setFont(font);
								Button opcja23("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);
								opcja23.setPosition({ static_cast<float>(posX), static_cast<float>(posY2) });
								opcja23.setFont(font);
								Button opcja24("", { static_cast<float>(sizeX), static_cast<float>(sizeY) }, 40, sf::Color(255, 255, 255, 0), sf::Color::Black);
								opcja24.setPosition({ static_cast<float>(posX), static_cast<float>(posY3) });
								opcja24.setFont(font);
								std::cout << "gracz-AI: tu odpala sie podmenu wyboru poziomu trudnosci AI" << std::endl;

								//tekst na buttonach - opcje
								text1.setString("Poziom: sredni");
								text1.setFont(font);
								text1.setCharacterSize(40);
								text1.setFillColor(sf::Color::Black);
								text1.setPosition(325, 550);

								text2.setString("Poziom: trudny");
								text2.setFont(font);
								text2.setCharacterSize(40);
								text2.setFillColor(sf::Color::Black);
								text2.setPosition(315, 685);

								text3.setString("Wstecz");
								text3.setFont(font);
								text3.setCharacterSize(40);
								text3.setFillColor(sf::Color::Black);
								text3.setPosition(420, 830);

								text4.setString("Poziom: latwy");
								text4.setFont(font);
								text4.setCharacterSize(40);
								text4.setFillColor(sf::Color::Black);
								text4.setPosition(325, 415);

								//mechanika podmenu
								if (MenuSelect == 2)
								{
									std::cout << "menu: " << MenuSelect << std::endl;
									sf::Event aevent;
									while (window.isOpen() && open_menu == 1)
									{
										window.clear();

										//wyglad tla podmenu opcji
										sf::RectangleShape optionsBackground;
										optionsBackground.setSize(sf::Vector2f(gameWidth, gameHeight));
										sf::Texture optionsTexture;
										optionsTexture.loadFromFile("resources/Menu.png");
										optionsBackground.setTexture(&optionsTexture);
										window.draw(optionsBackground);
										window.draw(button1);
										window.draw(button2);
										window.draw(button3);
										window.draw(button4);
										window.draw(text1);
										window.draw(text2);
										window.draw(text3);
										window.draw(text4);
										opcja21.draw(window);
										opcja22.draw(window);
										opcja23.draw(window);
										opcja24.draw(window);

										window.display();
										while (window.pollEvent(aevent) && open_menu == 1)
										{
											if (aevent.type == sf::Event::Resized)
											{
												double posX{ 0.2722772277227723 * window.getSize().x };
												double posY1{ 0.5099009900990099 * window.getSize().y };
												double posY2{ 0.6435643564356436 * window.getSize().y };
												double posY3{ 0.7871287128712871 * window.getSize().y };
												double posY4{ 0.3762376237623762 * window.getSize().y };

												double sizeX{ 0.4752475247524752 * window.getSize().x };
												double sizeY{ 0.1336633663366337 * window.getSize().y };

												opcja21.setPosition({ static_cast<float>(posX), static_cast<float>(posY4) });
												opcja21.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
												opcja22.setPosition({ static_cast<float>(posX), static_cast<float>(posY1) });
												opcja22.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
												opcja23.setPosition({ static_cast<float>(posX), static_cast<float>(posY2) });
												opcja23.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
												opcja24.setPosition({ static_cast<float>(posX), static_cast<float>(posY3) });
												opcja24.setSize({ static_cast<float>(sizeX), static_cast<float>(sizeY) });
											}
											switch (aevent.type)
											{
											case sf::Event::Closed:
											{
												window.close();
											}
											case sf::Event::MouseMoved:
											{
												if (opcja21.isMouseOver(window))
												{
													button4.setTexture(hoverTexture);
												}
												else
												{
													button4.setTexture(buttonTexture);
												}
												if (opcja22.isMouseOver(window))
												{
													button1.setTexture(hoverTexture);
												}
												else
												{
													button1.setTexture(buttonTexture);
												}
												if (opcja23.isMouseOver(window))
												{
													button2.setTexture(hoverTexture);
												}
												else
												{
													button2.setTexture(buttonTexture);
												}
												if (opcja24.isMouseOver(window))
												{
													button3.setTexture(hoverTexture);
												}
												else
												{
													button3.setTexture(buttonTexture);
												}
												break;
											}
											case sf::Event::MouseButtonPressed:
											{
												if (aevent.mouseButton.button == sf::Mouse::Left)
												{
													if (opcja21.isMouseOver(window))
													{
														//window.close();
														//std::cout << "gracz-latwe AI: tu powinno odpalic gre gracz vs latwe AI" << std::endl;
														open_menu = 0;
														game_type = 1;
														new_game = 1;
														game_state = 0;
														AI_level = 4;
													}
													if (opcja22.isMouseOver(window))
													{
														//window.close();
														//std::cout << "gracz-srednie AI: tu powinno odpalic gre gracz vs srednie AI" << std::endl;
														open_menu = 0;
														game_type = 1;
														new_game = 1;
														game_state = 0;
														AI_level = 6;
													}
													if (opcja23.isMouseOver(window))
													{
														//window.close();
														//std::cout << "gracz-trudne AI: tu powinno odpalic gre gracz vs trudne AI" << std::endl;
														open_menu = 0;
														game_type = 1;
														new_game = 1;
														game_state = 0;
														AI_level = 6;
													}
													if (opcja24.isMouseOver(window))
													{
														MenuSelect--;
														//cout << "menu: " << MenuSelect << endl;
														//std::cout << "wstecz: dziala - powrot do menu glownego" << std::endl;
														goto menu1;
													}
												}
											}
											}
										}
									}
								}
							}
							if (opcja3.isMouseOver(window))
							{
								window.close();
								std::cout << "wyjscie: koniec dzialania programu" << std::endl;
							}
							printf("%d new_game : ", new_game);

							if (opcja4.isMouseOver(window) && new_game == 0)
							{
								open_menu = 0;
								std::cout << "powrot do gry" << std::endl;
							}
							break;
						}
					}
					}
				}
			}
		}

	}
	if (open_menu == 0) {
		if (new_game == 1) {
			for (int i = 0; i < 10; i++) {
				for (int j = 0; j < 10; j++) {
					board_10x10[i][j] = new_game_board[i][j];
				}
			}
			new_game = 0;
		}
		while (window.isOpen())
		{
			//printf("%d\n", sf::Keyboard::O);
			if (turn == 2 && game_type == 1) {
				//printf("Wykonaj ruch");
				ai_move(board_10x10, 8);//AI_level
				draw_game_state(board_10x10, board_start_position_x, board_start_position_y);
				window.display();
				//system("cls");
				printf("Liczba kombinacji: %d ", liczba_operacji);
				liczba_operacji = 0;
			}
			if (game_state != -1) {
				draw_game_state(board_10x10, board_start_position_x, board_start_position_y);
			}


			// Handle events
			sf::Event event;
			while (window.pollEvent(event))
			{
				// Window closed or escape key pressed: exit
				//if ((event.type == sf::Event::Closed) || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))){
				//		window.close();
				//	break;
				//}
				if (event.type == sf::Event::Closed) {
					window.close();
					break;
				}
				if (event.key.code == sf::Keyboard::Escape) {
					open_menu = 1;
					if (MenuSelect == 2) {
						MenuSelect--;
					}
					goto menu1;
				}

				//If was clicked Mouse button
				if (event.type == sf::Event::MouseButtonPressed)
				{
					//If clicked mouse button is left
					if (event.mouseButton.button == sf::Mouse::Left)
					{
						//if clicked mouse position is on the board
						if (event.mouseButton.x >= board_start_position_x && event.mouseButton.y >= board_start_position_y) {
							//Checks if you can continue attack, and makes this move a only validate move.
							if (check_attack_opportunity(turn, board_10x10, allowed_moves.continue_i, allowed_moves.continue_j)) {
								allowed_moves.wymus = 1;
							}
							sf::Vector2u rozmiar;
							rozmiar = window.getSize();
							//For testing purpose
							//wyswietl_tablice(board_10x10);
							//Change mouse_position to array coordinate
							//std::cout << validate(board_10x10) << std::endl;
							int coordinate_x = event.mouseButton.x / (rozmiar.x / 10);
							int coordinate_y = event.mouseButton.y / (rozmiar.y / 10);
							//If clicked position is a validate move (value 99 means that you can move to this possition) and i have selected piece previously
							if (board_10x10[coordinate_y][coordinate_x] == 99 && allowed_moves.selected_piece_x != -1) {
								board_10x10[coordinate_y][coordinate_x] = board_10x10[allowed_moves.selected_piece_y][allowed_moves.selected_piece_x];
								board_10x10[allowed_moves.selected_piece_y][allowed_moves.selected_piece_x] = 1;
								//If it was attack move, then delete a piece that you had attack
								if (allowed_moves.wymus == 1) {
									delete_piece_between(board_10x10, allowed_moves.selected_piece_y, allowed_moves.selected_piece_x, coordinate_y, coordinate_x);

									allowed_moves.continue_i = coordinate_y;
									allowed_moves.continue_j = coordinate_x;
									clear_moves(board_10x10, 1, allowed_moves);
									//If you dont have opportunity for next attack then clear the valuse that you had set in board and change player turn
									//if (!check_attack_opportunity(turn, board_10x10, allowed_moves.continue_i, allowed_moves.continue_j)) {
									clear_moves(board_10x10, 1, allowed_moves);
									allowed_moves.wymus = -1;
									allowed_moves.continue_i = -1;
									allowed_moves.continue_j = -1;
									if (turn == 2) { turn = 3; }
									else if (turn == 3) { turn = 2; }
									//}
								}
								else {
									clear_moves(board_10x10, 1, allowed_moves);
									allowed_moves.wymus = -1;
									allowed_moves.continue_i = -1;
									allowed_moves.continue_j = -1;
									if (turn == 2) { turn = 3; }
									else if (turn == 3) { turn = 2; }
								}
							}
							else if (((board_10x10[coordinate_y][coordinate_x] == turn || board_10x10[coordinate_y][coordinate_x] == turn * 10) && allowed_moves.wymus != 1)) {
								//If you choose a piece that is yours (a piece or king) and you dont have attack opportunity, then make this choosen piece a selected one
								allowed_moves.selected_piece_x = coordinate_x;
								allowed_moves.selected_piece_y = coordinate_y;
								check_moves(board_10x10, allowed_moves);
							}
							else if (allowed_moves.wymus == 1) {
								if (board_10x10[coordinate_y][coordinate_x] == turn + 50 || board_10x10[coordinate_y][coordinate_x] == (turn * 10) + 50) {
									//If i choose a piece that is allowed to attack  (value + 50 means that it is a piece that can attack another piece)
									clear_moves(board_10x10, 0, allowed_moves);
									allowed_moves.selected_piece_x = coordinate_x;
									allowed_moves.selected_piece_y = coordinate_y;
									//Check and draw the attack opportunities on the screen
									color_mandatory_moves(turn, board_10x10, coordinate_y, coordinate_x);
								}
								else {
									clear_moves(board_10x10, 0, allowed_moves);
								}
							}
							
							//std::cout << "mouse x: " << coordinate_x;
							//std::cout << " mouse y: " << coordinate_y << std::endl;
							//std::cout << "Ruch : " << turn << std::endl;
						}
					}
				}
				if (can_move(board_10x10, turn) == 1 && game_state != -1) {
					if (turn == 2) {
						text.setString("Gracz czarny wygral!");
						text.setFont(font);
						text.setCharacterSize(40);
						text.setFillColor(sf::Color::Black);
						text.setPosition(210, 480);
						game_state = -1;
						draw_game_state(board_10x10, board_start_position_x, board_start_position_y);
						window.display();
						window.draw(text);
						window.display();
					}
					if (turn == 3) {
						text.setString("Gracz czerwony wygral!");
						text.setFont(font);
						text.setCharacterSize(40);
						text.setFillColor(sf::Color::Red);
						text.setPosition(175, 480);
						game_state = -1;
						draw_game_state(board_10x10, board_start_position_x, board_start_position_y);
						window.display();
						window.draw(text);
						window.display();
					}
				}
			}


			// Clear the window
			window.clear(sf::Color(0, 0, 0, 0));
			// Draw things on the window
			if (game_state == -1)
			{
				//window.draw(text);
			}
			else
			{
				draw_game_state(board_10x10, board_start_position_x, board_start_position_y);
				window.display();
			}
			// Display things on screen
			//window.display();
			//game_state
		}
	}

	return EXIT_SUCCESS;
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
