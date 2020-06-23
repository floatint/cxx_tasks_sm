#pragma once

#include <list>
#include <random>
#include <functional>

#include "farmer.h"
#include "move_direction.h"
#include "mole.h"
#include "game_status.h"

class GameField {
public:
	GameField(size_t w, size_t h);
	//Ћогика игры
	GameStatus update();
	//двигаем игрока по полю
	void moveFarmer(MoveDirection dir);
	//ѕоиск крота по заданным координатам
	//возвращает итератор, по скольку
	//через него проще манипулировать модел€ми
	//std::list<Mole>::iterator findMole(int x, int y);
	std::list<Mole>::iterator findMole(const std::function<bool(Mole&)>& predicate);
	/*
		–азное дл€ рендера
	*/
	//ѕолучить игровое поле
	const bool** getField() const;
	//ѕолучить модель игрока
	const Farmer& getFarmer() const;
	//ѕолучить модели кротов
	const std::list<Mole>& getMoles() const;
	//получить ширину пол€
	size_t width() const;
	//получить высоту пол€
	size_t height() const;
private:
	bool **m_field;
	size_t m_width;
	size_t m_height;
	Farmer m_farmer;
	std::list<Mole> m_moles;
};