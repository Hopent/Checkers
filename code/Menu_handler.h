
#ifndef Menu_handler
#define Menu_handler

#include <SFML/Graphics.hpp>

/// class used to create and manipulate buttons


/**
 * @brief Button class used for triangle manipulations.
 */
class Button{
	public:
		/**
			* Create a new Button.
			* @brief Default constructor.
	*/
		Button()
		{

		}
		/**
			 * Create a new Button object.
			 * @brief Constructor.
			 * @param t The Text of the button
			 * @param size Size of the button
			 * @param CharSize Char size of the text on the button.
			 * @param bgColor Color of the background
			 * @param textColor Color of the text on the button.
	 */
		Button(std::string t, sf::Vector2f size, int CharSize, sf::Color bgColor, sf::Color textColor)
		{
			text.setString(t);
			text.setFillColor(textColor);
			text.setCharacterSize(CharSize);
			button.setSize(size);
			button.setFillColor(bgColor);
		}

		/**
		 * @brief Set size of the button 
		 * @param size_2 Vector with 2 values. (new Width and height)
		*/
		void setSize(sf::Vector2f size_2) {
			button.setSize(size_2);
		}
		/*!
		* \brief This function set font.
		* \param font Variable of type sf::Font for text font changing.
		*/
		void setFont(sf::Font& font)
		{
			text.setFont(font);
		}
		/*!
		* \brief This function change Background color of button.
		* \param color Variable of type sf::Color used to declare color.
		*/
		void setBackground(sf::Color color)
		{
			button.setFillColor(color);
		}
		/*!
		* \brief This function change color of the text on button.
		* \param color Variable of type sf::Color used to declare color.
		*/
		void setText(sf::Color color)
		{
			text.setFillColor(color);
		}
		/*!
		* \brief This function change position of the buttion
		* \param position Vector with 2 values. (new position_x and new position_y)
		*/
		void setPosition(sf::Vector2f position)
		{
			button.setPosition(position);
			float x_position = (position.x + button.getLocalBounds().width / 10) - (text.getLocalBounds().width / 10);
			float y_position = (position.y + button.getLocalBounds().height / 5) - (text.getLocalBounds().height / 5);
			text.setPosition({ x_position, y_position });
		}
		/*!
		* \brief This function draw the button on the window.
		* \param window Pointer to the main window you want to draw on.
		*/
		void draw(sf::RenderWindow& window)
		{
			window.draw(button);
			window.draw(text);
		}
		//obsluga myszki w menu
		/*!
		* \brief This function checks is the mouse over button.
		* \param window Pointer to the main window you want to checks position on.
		*/
		bool isMouseOver(sf::RenderWindow& window)
		{
			float x_mouse = sf::Mouse::getPosition(window).x;
			float y_mouse = sf::Mouse::getPosition(window).y;
			float x_button = button.getPosition().x;
			float y_button = button.getPosition().y;
			float button_width = button.getPosition().x + button.getLocalBounds().width;
			float button_height = button.getPosition().y + button.getLocalBounds().height;
			if (x_mouse < button_width && x_mouse > x_button && y_mouse < button_height && y_mouse > y_button)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
	private:
		sf::RectangleShape button; //!< Variable with Shape of the button
		sf::Text text; //!< Variable with the text that you want to draw on the button.
};

#endif 