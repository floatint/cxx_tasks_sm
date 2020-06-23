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
	//������� �������
	m_farmer = Farmer();
	//�� � ���� ����
	m_moles.push_back(Mole(3, 7, MoleGender::Male));
	m_moles.push_back(Mole(4, 4, MoleGender::Female));
};

//����, ��� ���� ����� ���-�� ������
const double MOLE_ACTIVE_PROB = 0.30;
//����, ��� ���� �������
const double MOLE_SHOW_PROB = 0.25;
//����, ��� ���� ���������
const double MOLE_HIDE_PROB = 0.20;
//����, ��� ���� ����� ������
const double MOLE_EAT_PROB = 0.25;
//����, ��� ���� ����� ���������
const double MOLE_MOVE_PROB = 0.30;

//TODO: ������ ���� �������� �� ����� ��� ������� ��������
//MOLE_EAT_PROB = 0.6 - � ������������ 60% ���� ���� �� ����� �� ����� ���-��
GameStatus GameField::update() {
	//������� ���������� �������
	std::default_random_engine rnd_eng{std::random_device()()};
	std::uniform_real_distribution<double> frnd(0., 1.);
	std::uniform_int_distribution<int> wrnd(0, m_width - 1);
	std::uniform_int_distribution<int> hrnd(0, m_height - 1);
	//������� ������������ ��� ������
	//�.�. ���� ������ �������� �� �����, ������� �� ��������� - �� �������
	//�������� ���������� �������
	auto f_x = m_farmer.x();
	auto f_y = m_farmer.y();
	GameStatus ret_status = GameStatus::Ok;
	//�������� ����� �����, �� �������� �������� ������ � ������� ��������� �� �����
	auto moleIt = findMole([&f_x, &f_y](Mole& m) {
		return m.x() == f_x && m.y() == f_y && m.status() == MoleStatus::Show;
	});
	//���� ����� �������
	if (moleIt != m_moles.end()) {
		//������� ���
		m_moles.erase(moleIt);
		ret_status = GameStatus::MoleKilled;
	}
	//����� ������������ ������
	//���������� ���� ������
	for (auto m = m_moles.begin(); m != m_moles.end(); m++) {
		//���������� ��������� �����
		auto active = frnd(rnd_eng);
		//���� ���� ������, ��� ���� ����� ���-�� ������
		if (active >= MOLE_ACTIVE_PROB) {
			//��������, ����� ������ ����� ����
			//���� �� ��������
			if (m->status() == MoleStatus::Hidden) {
				//�������� �� ������� ������� �������
				if (frnd(rnd_eng) >= MOLE_MOVE_PROB) {
					//����������
					m->setX(wrnd(rnd_eng));
					m->setY(hrnd(rnd_eng));
				}
				//��������, ������� �����
				if (frnd(rnd_eng) >= MOLE_SHOW_PROB) {
					m->setStatus(MoleStatus::Show);
				}
			}
			//���� �� �����������
			if (m->status() == MoleStatus::Show) {
				//��������, ������� ��������
				if (frnd(rnd_eng) >= MOLE_EAT_PROB) {
					//����� ������
					m_field[m->y()][m->x()] = false;
				}
				//��������, �� ������� ����������
				if (frnd(rnd_eng) >= MOLE_HIDE_PROB) {
					m->setStatus(MoleStatus::Hidden);
				}
			}
		}
	}
	//��� �������� �����
	
	if (m_moles.size() == 0)
		ret_status = GameStatus::AllMolesDead;

	//���� ��� ���� �������
	auto f_cnt = 0;
	for (int y = 0; y < m_height; y++)
		for (int x = 0; x < m_width; x++)
			if (m_field[y][x])
				f_cnt++;
	if (f_cnt == 0)
		ret_status = GameStatus::FieldIsEmpty;

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

//std::list<Mole>::iterator GameField::findMole(int x, int y) {
//	for (auto m = m_moles.begin(); m != m_moles.end(); m++)
//		if (m->x() == x && m->y() == y)
//			return m;
//	return m_moles.end();
//}

std::list<Mole>::iterator GameField::findMole(const std::function<bool(Mole&)>& predicate) {
	for (auto m = m_moles.begin(); m != m_moles.end(); m++)
		if (predicate(*m))
			return m;
	return m_moles.end();
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

