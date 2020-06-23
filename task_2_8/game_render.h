#pragma once

#include "game_field.h"
#include <Windows.h>

const int FARMER_COLOR = 10;
const int HIDDEN_MOLE_COLOR = 14;
const int SHOW_MOLE_COLOR = 12;
const int OTHER_ITEMS_COLOR = 8;

class GameRender {
public:
	static void render(const GameField& field);
private:
	//TODO: вынести в логику, там он тоже используется
	//Поиск крота по заданным координатам
	static std::list<Mole>::const_iterator findMole(const std::list<Mole>& moles, int x, int y);
};