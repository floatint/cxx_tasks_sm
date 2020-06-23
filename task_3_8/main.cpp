// task_3_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <cstdio>
#include <conio.h>
#include "main.h"

int main()
{
	//Для демонстрации используется 2 типа массивов
	MyMap<std::string, int> int_map; //с ключем из string
	MyMap<int, std::string> str_map; //с ключем из int 

	while (true) {
		std::cout << "Enter action: ";
		std::string cmd;
		if (read_value(cmd)) {
			//работаем с map<int, std::string>
			if (cmd == STR_MAP) {
				if (read_value(cmd)) {
					//показываем мапу целиков
					if (cmd == SHOW) {
						if (str_map.size() == 0)
							std::cout << "String map is empty" << std::endl;
						else
							std::cout << str_map;
						continue;
					}
					//вставка
					if (cmd == INSERT) {
						int key = 0;
						std::string val;
						//читаем ключ и значение
						std::cout << "Enter key: " << std::endl;
						if (read_value(key)) {
							std::cout << "Enter value: " << std::endl;
							if (read_value(val)) {
								//пытаемся вставить
								try {
									str_map.insert(key, val);
								}
								catch (const std::exception& ex) {
									std::cout << ex.what() << std::endl;
								}
							}
						}
						continue;
					}
					//удаление
					if (cmd == REMOVE) {
						int key = 0;
						std::cout << "Enter key: " << std::endl;
						if (read_value(key)) {
							try {
								str_map.remove(key);
							}
							catch (const std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						continue;
					}
					//поиск
					if (cmd == GET) {
						int key = 0;
						std::cout << "Enter key: " << std::endl;
						if (read_value(key)) {
							std::string mval;
							if (str_map.try_get(key, mval)) {
								std::cout << mval << std::endl;
							}
							else {
								std::cout << "Key not found" << std::endl;
							}
						}
						continue;
					}
				}
			}
			//работаем с map<str::string, int>
			if (cmd == INT_MAP) {
				if (read_value(cmd)) {
					//показываем мапу целиков
					if (cmd == SHOW) {
						if (str_map.size() == 0)
							std::cout << "Int map is empty" << std::endl;
						else
							std::cout << int_map;
						continue;
					}
					//вставка
					if (cmd == INSERT) {
						std::string key;
						int val;
						//читаем ключ и значение
						std::cout << "Enter key: " << std::endl;
						if (read_value(key)) {
							std::cout << "Enter value: " << std::endl;
							if (read_value(val)) {
								//пытаемся вставить
								try {
									int_map.insert(key, val);
								}
								catch (const std::exception& ex) {
									std::cout << ex.what() << std::endl;
								}
							}
						}
						continue;
					}
					//удаление
					if (cmd == REMOVE) {
						std::string key;
						std::cout << "Enter key: " << std::endl;
						if (read_value(key)) {
							try {
								int_map.remove(key);
							}
							catch (const std::exception& ex) {
								std::cout << ex.what() << std::endl;
							}
						}
						continue;
					}
					//поиск
					if (cmd == GET) {
						std::string key = 0;
						std::cout << "Enter key: " << std::endl;
						if (read_value(key)) {
							int mval;
							if (int_map.try_get(key, mval)) {
								std::cout << mval << std::endl;
							}
							else {
								std::cout << "Key not found" << std::endl;
							}
						}
						continue;
					}
				}
			}
			if (cmd == EXIT) {
				return 0;
			}
			//сюда попадем в случае кривого инпута
			std::cin.ignore();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::cout << "Invalid command" << std::endl;
		}
	}
    std::cout << "Hello World!\n";
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
