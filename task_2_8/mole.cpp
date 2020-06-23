#include "mole.h"

Mole::Mole(int x, int y, MoleGender gender) {
	m_x = x;
	m_y = y;
	m_gender = gender;
	m_status = MoleStatus::Hidden;
}

MoleGender Mole::gender() const {
	return m_gender;
}

MoleStatus Mole::status() const {
	return m_status;
}

int Mole::x() const {
	return m_x;
}

int Mole::y() const {
	return m_y;
}

void Mole::setX(int x) {
	m_x = x;
}

void Mole::setY(int y) {
	m_y = y;
}

void Mole::setStatus(MoleStatus s) {
	m_status = s;
}
