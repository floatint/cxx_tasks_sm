// task_2_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <conio.h>
#include <iostream>

#include "main.h"
#include "game_render.h"
#include "key_codes.h"
#include "move_direction.h"


int main()
{
	//Игровое поле
	GameField gf(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);
	//Рендер игры
	GameRender render;
	//Статус игры
	GameStatus status = GameStatus::NotStared;

	while (true) {
		if (status == GameStatus::NotStared) {
			//Приветствие игрока
			std::cout << "Welcome to the game !" << std::endl;
			//Печатаем инструкцию
			std::cout << "Help:" << std::endl;
			std::cout << "Game exit: ESC" << std::endl;
			std::cout << "Start game: F" << std::endl;
			std::cout << "New game: N" << std::endl;
			std::cout << "Farmer navigation: arrow up, down, left or right" << std::endl;
			std::cout << "Pass step: SPACE" << std::endl;
		}
		else {
			//рисуем
			render.render(gf);
			//пишем статус
			if (status == GameStatus::AllMolesDead) {
				std::cout << "All moles are dead. You win. Press F or N to play new game." << std::endl;
			}
			if (status == GameStatus::FieldIsEmpty) {
				std::cout << "The field was eaten. You faild. Press F or N to play new game." << std::endl;
			}
			if (status == GameStatus::MoleKilled) {
				std::cout << "Farmer kill mole." << std::endl;
				status = GameStatus::Play;
			}
		}
		auto key = _getch();
		if (key && key != 224) {
			//если нажата не стрелка
			system("cls");

			//Выход из игры
			if (key == (int)KeyCodes::Esc) {
				return 0;
			}

			//если игра продолжается просто симулируем ее
			if (key == (int)KeyCodes::Space) {
				if (status == GameStatus::Play) {
					status = gf.update();
				}
			}

			//начинаем игру
			if (key == (int)KeyCodes::F || key == (int)KeyCodes::f) {
				if (status != GameStatus::NotStared) {
					gf = GameField(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);
				}
				status = GameStatus::Play;
			}

			//новая игра
			if (key == (int)KeyCodes::N || key == (int)KeyCodes::n) {
				gf = GameField(GAME_FIELD_WIDTH, GAME_FIELD_HEIGHT);
				status = GameStatus::NotStared;
			}

		}
		else {
			if (status == GameStatus::Play) {
				auto ex = _getch();
				switch (ex) {
				case (int)KeyCodes::Up:
					gf.moveFarmer(MoveDirection::Up);
					break;
				case (int)KeyCodes::Down:
					gf.moveFarmer(MoveDirection::Down);
					break;
				case (int)KeyCodes::Left:
					gf.moveFarmer(MoveDirection::Left);
					break;
				case (int)KeyCodes::Right:
					gf.moveFarmer(MoveDirection::Right);
					break;
				}
				//очищаем экран
				system("cls");
				//просчитываем игру
				status = gf.update();
			}
		}
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
