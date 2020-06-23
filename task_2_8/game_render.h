#pragma once

#include "game_field.h"
#include <Windows.h>

//���� �������
const int FARMER_COLOR = 10;
//���� ����� ��� ������
const int HIDDEN_MOLE_COLOR = 14;
//���� ����� �� �����������
const int SHOW_MOLE_COLOR = 12;
//���� ����� ������
const int CHILD_MOLE_COLOR = 13;
//������ ������� ��� �� �����
const int CELL_EXISTS = 7;
//��� ���������
const int OTHER_ITEMS_COLOR = 8;

class GameRender {
public:
	void render(const GameField& field);
};