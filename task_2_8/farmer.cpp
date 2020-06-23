#include "farmer.h"

Farmer::Farmer() : Farmer(0, 0) {}

Farmer::Farmer(int x, int y) {
	m_x = x;
	m_y = y;
}

int Farmer::x() const {
	return m_x;
}

int Farmer::y() const {
	return m_y;
}

void Farmer::setX(int x) {
	m_x = x;
}

void Farmer::setY(int y) {
	m_y = y;
}