#pragma once

//Модель фермера

class Farmer {
public:
	Farmer();
	Farmer(int x, int y);
	int x() const;
	int y() const;
	void setX(int x);
	void setY(int y);
private:
	int m_x;
	int m_y;
};