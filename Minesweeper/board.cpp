#include "board.h"

board::board(int h_c, int v_c, sf::RenderWindow& game_wind) {
	hrz_count = h_c;
	vrt_count = v_c;

	lines.setPrimitiveType(sf::Lines);
	sf::Vertex line_[1];
	for (int h = 0; h < hrz_count; h++) {
		lines.append(sf::Vector2f(h * game_wind.getSize().x / hrz_count, 0));
		lines.append(sf::Vector2f(h * game_wind.getSize().x / hrz_count, game_wind.getSize().y));
	}
	for (int w = 0; w < vrt_count; w++) {
		lines.append(sf::Vector2f(0, w * game_wind.getSize().y / vrt_count));
		lines.append(sf::Vector2f( game_wind.getSize().x, w * game_wind.getSize().y / vrt_count));
	}
}