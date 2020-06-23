#include "game_render.h"
#include <iostream>
#include <algorithm>

void GameRender::render(const GameField& field) {
	//�������� ������ ����
	auto f = field.getField();
	auto h = field.height();
	auto w = field.width();
	auto farm = field.getFarmer();
	auto moles = field.getMoles();
	//������� ����� ������ ����� ������� ��
	HANDLE con = GetStdHandle(STD_OUTPUT_HANDLE);
	//������ ������� ����
	for (int y = 0; y < h; y++) {
		for (int x = 0; x < w; x++) {
			if (x == 0)
				std::cout << '|' << ' ';
			else
				std::cout << ' ';
			//���� �� ������ ����� ������, �� �� � ����������
			if (farm.x() == x && farm.y() == y) {
				SetConsoleTextAttribute(con, FARMER_COLOR);
				std::cout << 'F';
				SetConsoleTextAttribute(con, OTHER_ITEMS_COLOR);
			}
			else {
				//���� � ������ ����
				auto moleIt = std::find_if(moles.cbegin(), moles.cend(), [x, y](const Mole& m) {
					return m.x() == x && m.y() == y;
				});
				//auto moleIt = field.findMole([&x, &y](const Mole& m) {
				//	return m.x() == x && m.y() == y;
				//});
				if (moleIt != moles.cend()) {
					if (moleIt->status() == MoleStatus::Hidden) {
						SetConsoleTextAttribute(con, HIDDEN_MOLE_COLOR);
					}
					if (moleIt->status() == MoleStatus::Show) {
						SetConsoleTextAttribute(con, SHOW_MOLE_COLOR);
					}
					if (moleIt->status() == MoleStatus::MakeChild) {
						SetConsoleTextAttribute(con, CHILD_MOLE_COLOR);
					}
					std::cout << "M";
					SetConsoleTextAttribute(con, OTHER_ITEMS_COLOR);
				}
				else {
					//������ ������

					//���� ��� ��� �� ����� - �������
					if (f[y][x])
						SetConsoleTextAttribute(con, CELL_EXISTS);
					std::cout <<f[y][x];
					//����������� ����
					if (f[y][x])
						SetConsoleTextAttribute(con, OTHER_ITEMS_COLOR);

				}
			}
			std::cout << ' ' << '|';
		}
		std::cout << std::endl;
	}
	//print status bar
	for (int i = 0; i < w * 4; i++) {
		std::cout << '=';
		if (i == w * 4 - 1)
			std::cout << std::endl;
	}
	std::cout << "Status: ";

}