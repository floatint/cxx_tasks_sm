// task_2_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <Windows.h>
#include <conio.h>
#include <iostream>

#include "game_render.h"
#include "key_codes.h"
#include "move_direction.h"

int main()
{
	GameField gf(10, 10);
	GameRender render;
	render.render(gf);
	while (true) {
		auto key = _getch();
		if (key && key != 224) {
			//other key
		}
		else {
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
			auto s = gf.update();
			//рисуем
			render.render(gf);
			if (s == GameStatus::AllMolesDead)
				std::cout << "All moles are dead. You win." << std::endl;
		}
	}
    //std::cout << "Hello World!\n";
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
