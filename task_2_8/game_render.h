#pragma once

#include "game_field.h"
#include <Windows.h>

//Цвет фермера
const int FARMER_COLOR = 10;
//Цвет крота под землей
const int HIDDEN_MOLE_COLOR = 14;
//Цвет крота на поверхности
const int SHOW_MOLE_COLOR = 12;
//Цвет семьи кротов
const int CHILD_MOLE_COLOR = 13;
//Урожай который еще не съели
const int CELL_EXISTS = 7;
//Все остальное
const int OTHER_ITEMS_COLOR = 8;

class GameRender {
public:
	void render(const GameField& field);
};