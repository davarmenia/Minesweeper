#include "message.h"

message::message(sf::Vector2f pos) {
	
	if (!font.loadFromFile("LED Dot-Matrix.ttf"))
	{
		// error...
	}
	text.setFont(font); // font is a sf::Font
	text.setString("Get ready and press one of the points to start game");
	text.setCharacterSize(24); // in pixels, not points!
	text.setFillColor(sf::Color::Red);
	text.setStyle(sf::Text::Bold);
	text.setPosition(pos);
}

sf::Text& message::get_text() {
	return text;
}

void message::set_text(std::string new_text) {
	text.setString(new_text);
}