#include "window.h"

window::window(int win_h, int win_w, std::string win_name) {
	window_ = new sf::RenderWindow(sf::VideoMode(win_w, win_h), win_name);
}