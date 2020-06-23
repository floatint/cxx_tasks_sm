#pragma once

#include "mole_gender.h"
#include "mole_status.h"

//Модель крота

class Mole {
public:
	Mole(int x, int y, MoleGender gender);
	MoleGender gender() const;
	MoleStatus status() const;
	int x() const;
	int y() const;
	void setX(int x);
	void setY(int y);
	void setStatus(MoleStatus s);
private:
	MoleGender m_gender;
	MoleStatus m_status;
	int m_x;
	int m_y;
};
