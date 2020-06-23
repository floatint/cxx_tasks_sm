#include "game_render.h"
#include <iostream>
#include <algorithm>

void GameRender::render(const GameField& field) {
	//сохраним данные игры
	auto f = field.getField();
	auto h = field.height();
	auto w = field.width();
	auto farm = field.getFarmer();
	auto moles = field.getMoles();
	//получим хендл коноли чтобы красить ее
	HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);
	//рисуем игровое поле
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (x == 0)
				std::cout << '|' << ' ';
			else
				std::cout << ' ';
			//если на клетке стоит фермер, то он в приоритете
			if (farm.x() == x && farm.y() == y) {
				SetConsoleTextAttribute(con, FARMER_COLOR);
				std::cout << 'F';
				SetConsoleTextAttribute(con, OTHER_ITEMS_COLOR);
			}
			else {
				//если в клетке крот
				auto moleIt = findMole(moles, x, y);
				if (moleIt != moles.cend()) {
					if (moleIt->status() == MoleStatus::Hidden) {
						SetConsoleTextAttribute(con, HIDDEN_MOLE_COLOR);
					}
					if (moleIt->status() == MoleStatus::Show) {
						SetConsoleTextAttribute(con, SHOW_MOLE_COLOR);
					}
					std::cout << "M";
					SetConsoleTextAttribute(con, OTHER_ITEMS_COLOR);
				}
				else {
					//рисуем урожай

					//если его еще не съели - выделим
					if (f[y][x])
						SetConsoleTextAttribute(con, CELL_EXISTS);
					std::cout <<f[y][x];
					//восстановим цвет
					if (f[y][x])
						SetConsoleTextAttribute(con, OTHER_ITEMS_COLOR);

				}
			}
			std::cout << ' ' << '|';
		}
		std::cout << std::endl;
	}
	//print status bar
	for (int i = 0; i < w * 4; i++) {
		std::cout << '=';
		if (i == w * 4 - 1)
			std::cout << std::endl;
	}
	std::cout << "Status: ";

}

std::list<Mole>::const_iterator GameRender::findMole(const std::list<Mole>& moles, int x, int y) {
	for (auto m = moles.cbegin(); m != moles.cend(); m++) {
		if (m->x() == x && m->y() == y)
			return m;
	}
	return moles.cend();
}