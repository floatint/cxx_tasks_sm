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
	//������ ����
	GameStatus update();
	//������� ������ �� ����
	void moveFarmer(MoveDirection dir);
	//����� ����� �� �������� �����������
	//���������� ��������, �� �������
	//����� ���� ����� �������������� ��������
	//std::list<Mole>::iterator findMole(int x, int y);
	std::list<Mole>::iterator findMole(const std::function<bool(Mole&)>& predicate);
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