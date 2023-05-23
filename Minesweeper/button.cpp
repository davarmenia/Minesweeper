#include "button.h"

button::button(int w_w, int w_h, int h_c, int v_c) {
	button_w = w_h / v_c;
	button_h = w_w / h_c;

	button_rect.setSize(sf::Vector2f(button_w, button_h));
	//button_rect.setFillColor(sf::Color::Green);

	init_texure();

}

sf::RectangleShape& button::get_button(sf::Vector2f position, int index) {
	button_rect.setPosition(position);
	button_rect.setTextureRect(sf::IntRect(index * 40, 0, 40, 40));
	button_rect.setTexture(&texture);
	return button_rect;
}

void button::init_texure() {
	if (!texture.loadFromFile("C:\\Users\\Arsen\\Desktop\\Minesweeper\\x64\\Debug\\images\\digit.png"))
	{
		// error...
	}
	//if (!texture.loadFromFile("C:\\Users\\Davit\\OneDrive\\Desktop\\Minesweeper\\x64\\Debug\\images\\digit.png"))
	//{
	//	// error...
	//}
}