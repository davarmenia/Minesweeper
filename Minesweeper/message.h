#include "SFML/Graphics.hpp"
#pragma once
class message
{
public:
	message(sf::Vector2f pos);
	sf::Text& get_text();
	void set_text(std::string);

private:
	sf::Text text;
	sf::Font font;
};

