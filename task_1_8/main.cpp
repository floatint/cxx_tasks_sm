// task_1_8.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include "main.h"

//Константы для выполнения
const int BUFFER_SIZE = 13;//18;

int main()
{
	//забиваем нулями
	char buff[BUFFER_SIZE]; 
	memset(buff, '\0', BUFFER_SIZE);
	int res = my_snprintf(buff, BUFFER_SIZE, "%s,123%d", 2, "test", 10);
	//int res = my_snprintf(buff, BUFFER_SIZE - 1, "test %s, %05d", 2, "my_str", 10);
	if (res > 0) {
		std::cout << buff << std::endl;
	} else {
		switch (res)
		{
		case BUFFER_IS_NULL:
			std::cout << "Buffer is null" << std::endl;
			break;
		case FORMAT_IS_NULL:
			std::cout << "Format string is null" << std::endl;
			break;
		case BUFFER_TOO_SMALL:
			std::cout << "Buffer too small" << std::endl;
			break;
		case EMPTY_PLACEHOLDER:
			std::cout << "Placeholder is empty" << std::endl;
			break;
		case PLACEHOLDER_BUFFER_TOO_SMALL:
			std::cout << "Placeholder buffer too small" << std::endl;
			break;
		case INVALID_PLACEHOLDER_CURRENCY_SPEC:
			std::cout << "Invalid placeholder currency spec" << std::endl;
			break;
		case INVALID_PLACEHOLDER_SIZE_SPEC:
			std::cout << "Invalid placeholder size spec" << std::endl;
			break;
		default:
			break;
		}
	}
	//auto a = 0;
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
