#include "game_field.h"

GameField::GameField(size_t w, size_t h) {
	m_width = w;
	m_height = h;
	m_field = new bool*[h];
	for (int i = 0; i < h; i++) {
		m_field[i] = new bool[w];
		for (int j = 0; j < w; j++) {
			m_field[i][j] = true;
		}
	}
	//создаем фермера
	m_farmer = Farmer();
	//ну и пару крыс

	//заведем генераторы рандома
	std::default_random_engine rnd_eng{ std::random_device()() };
	//Для рандомайза позиции
	std::uniform_int_distribution<int> wrnd(0, m_width - 1);
	std::uniform_int_distribution<int> hrnd(0, m_height - 1);

	m_moles.push_back(Mole(wrnd(rnd_eng), hrnd(rnd_eng), MoleGender::Male));
	m_moles.push_back(Mole(wrnd(rnd_eng), hrnd(rnd_eng), MoleGender::Female));

	m_moles.push_back(Mole(wrnd(rnd_eng), hrnd(rnd_eng), MoleGender::Male));
	m_moles.push_back(Mole(wrnd(rnd_eng), hrnd(rnd_eng), MoleGender::Female));
};


GameStatus GameField::update() {
	//заведем генераторы рандома
	std::default_random_engine rnd_eng{std::random_device()()};
	//Для шанса на действие
	std::uniform_real_distribution<double> frnd(0., 1.);
	//Для рандомайза позиции
	std::uniform_int_distribution<int> wrnd(0, m_width - 1);
	std::uniform_int_distribution<int> hrnd(0, m_height - 1);
	//для гендера
	std::uniform_int_distribution<int> grnd(0, 1);
	
	//Сначала обрабатываем шаг игрока
	//т.е. если фермер наступил на крота, который не спрятался - он умирает
	//сохраним координаты фермера
	auto f_x = m_farmer.x();
	auto f_y = m_farmer.y();
	//Статус игры
	GameStatus ret_status = GameStatus::Play;
	//пытаемся найти крота, на которого наступил фермер и который находится на верху
	auto moleIt = std::find_if(m_moles.begin(), m_moles.end(), [f_x, f_y](const Mole& m) {
		return m.x() == f_x && m.y() == f_y && m.status() == MoleStatus::Show;
	});
	//если такой нашелся
	if (moleIt != m_moles.end()) {
		//убиваем его
		m_moles.erase(moleIt);
		ret_status = GameStatus::MoleKilled;
	}
	//далее обрабатываем кротов
	//перебираем всех кротов
	for (auto m = m_moles.begin(); m != m_moles.end(); m++) {
		//генерируем случайное число
		auto active = frnd(rnd_eng);
		//если было решено, что крот будет что-то делать
		if (active >= MOLE_ACTIVE_PROB) {
			//проверим, какой статус имеет крот
			if (m->status() == MoleStatus::MakeChild) {
				//добавляем нового крота рядом с родителями
				if (frnd(rnd_eng) >= MOLE_BORN_PROB) {
					m_moles.push_back(Mole(m->x(), m->y(), (MoleGender)grnd(rnd_eng)));
					//находим партнера крота
					auto part = std::find_if(m_moles.begin(), m_moles.end(), [&m](const Mole& p) {
						return m->x() == p.x() && m->y() == p.y() && m->gender() != p.gender() && m->status() == p.status();
					});
					//меняем статус
					part->setStatus(MoleStatus::Hidden);
					m->setStatus(MoleStatus::Hidden);
				}
			}
			//если он прячется
			if (m->status() == MoleStatus::Hidden) {
				//возможно он захочет зменить позицию
				if (frnd(rnd_eng) >= MOLE_MOVE_PROB) {
					//перемещаем
					m->setX(wrnd(rnd_eng));
					m->setY(hrnd(rnd_eng));
				}
				//возможно он захочет сделать маленького крота
				//тогда ему нужен партнер
				auto part = std::find_if(m, m_moles.end(), [&m](const Mole& p) {
					return m->x() == p.x() && m->y() == p.y() && m->gender() != p.gender() && m->status() == p.status();
				});
				//если такой имеется
				if (part != m_moles.cend()) {
					//заставляем рожать
					m->setStatus(MoleStatus::MakeChild);
					part->setStatus(MoleStatus::MakeChild);
				}
				else {
					//возможно, захочет выйти на поверхность
					if (frnd(rnd_eng) >= MOLE_SHOW_PROB) {
						m->setStatus(MoleStatus::Show);
					}
				}

			}
			//если на поверхности
			if (m->status() == MoleStatus::Show) {
				//возможно, захочет покушать
				if (frnd(rnd_eng) >= MOLE_EAT_PROB) {
					//съели урожай
					m_field[m->y()][m->x()] = false;
				}
				//возможно, он захочет спрятаться
				if (frnd(rnd_eng) >= MOLE_HIDE_PROB) {
					m->setStatus(MoleStatus::Hidden);
				}
			}
		}
	}
	//тут подводим итоги
	
	//Если все кроты мертвы
	if (m_moles.size() == 0)
		ret_status = GameStatus::AllMolesDead;

	//если все поле съедено
	auto f_cnt = 0;
	for (int y = 0; y < m_height; y++)
		for (int x = 0; x < m_width; x++)
			if (m_field[y][x])
				f_cnt++;
	if (f_cnt == 0)
		ret_status = GameStatus::FieldIsEmpty;

	//Возвращаем статус
	return ret_status;
}

void GameField::moveFarmer(MoveDirection dir) {
	if (dir == MoveDirection::Up) {
		if (m_farmer.y() - 1 >= 0) {
			m_farmer.setY(m_farmer.y() - 1);
		}
	}

	if (dir == MoveDirection::Down) {
		if (m_farmer.y() + 1 <= m_height - 1) {
			m_farmer.setY(m_farmer.y() + 1);
		}
	}

	if (dir == MoveDirection::Left) {
		if (m_farmer.x() - 1 >= 0) {
			m_farmer.setX(m_farmer.x() - 1);
		}
	}

	if (dir == MoveDirection::Right) {
		if (m_farmer.x() + 1 <= m_width - 1) {
			m_farmer.setX(m_farmer.x() + 1);
		}
	}
}

const bool** GameField::getField() const {
	return (const bool**)m_field;
}

const Farmer& GameField::getFarmer() const {
	return m_farmer;
}

const std::list<Mole>& GameField::getMoles() const {
	return m_moles;
}

size_t GameField::width() const {
	return m_width;
}

size_t GameField::height() const {
	return m_height;
}

