#pragma once

#include "game_field.h"
#include <Windows.h>

//Цвет фермера
const int FARMER_COLOR = 10;
//Цвет крота под землей
const int HIDDEN_MOLE_COLOR = 14;
//Цвет крота на поверхности
const int SHOW_MOLE_COLOR = 12;
//Урожай который еще не съели
const int CELL_EXISTS = 7;
//Все остальное
const int OTHER_ITEMS_COLOR = 8;

class GameRender {
public:
	void render(const GameField& field);
private:
	//TODO: вынести в логику, там он тоже используется
	//Поиск крота по заданным координатам
	static std::list<Mole>::const_iterator findMole(const std::list<Mole>& moles, int x, int y);
};