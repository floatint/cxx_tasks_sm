#pragma once

#include <list>
#include <random>
#include <functional>

#include "farmer.h"
#include "move_direction.h"
#include "mole.h"
#include "game_status.h"

/*
	���� ��������� ����. ����� �� � ����� ������� � �������� ��������� ���������.
	��� �������� ������ - ��� ���� ����� ���������� �� ��� ���� ��������.
*/

//����, ��� ���� ����� ���-�� ������
const double MOLE_ACTIVE_PROB = 0.30;
//����, ��� ���� �������
const double MOLE_SHOW_PROB = 0.25;
//����, ��� ���� ���������
const double MOLE_HIDE_PROB = 0.50;//0.20;
//����, ��� ���� ����� ������
const double MOLE_EAT_PROB = 0.25;
//����, ��� ���� ����� ���������
const double MOLE_MOVE_PROB = 0.30;
//����, ��� ������� ����� ����
const double MOLE_BORN_PROB = 0.10;

class GameField {
public:
	GameField(size_t w, size_t h);
	//������ ����
	GameStatus update();
	//������� ������ �� ����
	void moveFarmer(MoveDirection dir);
	
	/*
		������ ��� �������
	*/
	//�������� ������� ����
	const bool** getField() const;
	//�������� ������ ������
	const Farmer& getFarmer() const;
	//�������� ������ ������
	const std::list<Mole>& getMoles() const;
	//�������� ������ ����
	size_t width() const;
	//�������� ������ ����
	size_t height() const;
private:
	bool **m_field;
	size_t m_width;
	size_t m_height;
	Farmer m_farmer;
	std::list<Mole> m_moles;
};