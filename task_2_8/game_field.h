#pragma once

#include <list>
#include <random>
#include <functional>

#include "farmer.h"
#include "move_direction.h"
#include "mole.h"
#include "game_status.h"

/*
	Ќиже настройки игры. ћен€й их в любую сторону и чувствуй изменение сложности.
	„ем значение меньше - тем чаже будет выполн€тс€ то или иное действие.
*/

//шанс, что крот будет что-то делать
const double MOLE_ACTIVE_PROB = 0.30;
//шанс, что крот вылезет
const double MOLE_SHOW_PROB = 0.25;
//шанс, что крот спр€четс€
const double MOLE_HIDE_PROB = 0.50;//0.20;
//шанс, что крот съест урожай
const double MOLE_EAT_PROB = 0.25;
//шанс, что крот будет двигатьс€
const double MOLE_MOVE_PROB = 0.30;
//шанс, что родилс€ новый крот
const double MOLE_BORN_PROB = 0.10;

class GameField {
public:
	GameField(size_t w, size_t h);
	//Ћогика игры
	GameStatus update();
	//двигаем игрока по полю
	void moveFarmer(MoveDirection dir);
	
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