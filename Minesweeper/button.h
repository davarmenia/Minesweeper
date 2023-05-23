#include <SFML/Graphics.hpp>

#pragma once
class button
{
public:
	button(int w_w, int w_h, int h_c, int v_c);
	sf::RectangleShape& get_button(sf::Vector2f position, int index);
	sf::Vector2f get_button_size() { return sf::Vector2f(button_w, button_h); }

private:
	sf::RectangleShape button_rect;
	sf::Texture texture;
	
	void init_texure();

	int button_h;
	int button_w;
};

