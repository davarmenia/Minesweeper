#include "settings.h"
#include <iostream>

settings::settings() {
	game_name = "Minesweeper";
	game_heigth = 640;
	game_width = 900;

	horizonical_count = 30;
	vertical_count = 20;

	generate_game_map();
	init_game_array();
}

bool settings::isValid_(int row, int col) {
	return (row >= 0) && (row < vertical_count) && (col >= 0) && (col < horizonical_count);
}

void settings::init_game_array() {
	for (int m = 0; m < vertical_count; m++) {
		std::vector<int> tmp;
		std::vector<int> tmp_d;
		for (int n = 0; n < horizonical_count; n++) {
			tmp.push_back(10);
			tmp_d.push_back(0);
		}
		game_array.push_back(tmp);
		draw_array.push_back(tmp_d);
	}
	for (auto& it : mine_map) {
		int r = it / horizonical_count;
		int c = it - (it / horizonical_count) * horizonical_count;
		game_array[r][c] = 11;
	}
	for (int m = 0; m < vertical_count; m++) {
		for (int n = 0; n < horizonical_count; n++) {
			if (game_array[m][n] == 11)
				continue;
			int count = 0;
			if (isValid_(m - 1, n - 1)) {
				if (game_array[m - 1][n - 1] == 11)
					count++;
			}
			if (isValid_(m - 1, n)) {
				if (game_array[m - 1][n] == 11)
					count++;
			}
			if (isValid_(m - 1, n + 1)) {
				if (game_array[m - 1][n + 1] == 11)
					count++;
			}
			if (isValid_(m, n - 1)) {
				if (game_array[m][n - 1] == 11)
					count++;
			}
			if (isValid_(m, n)) {
				if (game_array[m][n] == 11)
					count++;
			}
			if (isValid_(m, n + 1)) {
				if (game_array[m][n + 1] == 11)
					count++;
			}
			if (isValid_(m + 1, n - 1)) {
				if (game_array[m + 1][n - 1] == 11)
					count++;
			}
			if (isValid_(m + 1, n)) {
				if (game_array[m + 1][n] == 11)
					count++;
			}
			if (isValid_(m + 1, n + 1)) {
				if (game_array[m + 1][n + 1] == 11)
					count++;
			}
			if (!count)
				game_array[m][n] = 9;
			else
				game_array[m][n] = count;
		}
	}
}

void settings::generate_game_map() {
	const int AMOUNT = 200;
	int MAX = vertical_count * horizonical_count;

	int value[AMOUNT];

	srand(time(NULL));

	for (int i = 0; i < AMOUNT; i++)
	{
		bool check;
		int n;
		do
		{
			n = rand() % MAX;
			check = true;
			for (int j = 0; j < i; j++)
				if (n == value[j])
				{
					check = false;
					break;
				}
		} while (!check);
		value[i] = n;
		mine_map.push_back(n);
	}
}

void settings::set_game_array_value(int m, int n, int value) {
	draw_array[m][n] = value;
}