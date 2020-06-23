#pragma once


//обертка над чтением из консоли

template<typename T>
bool read_value(T& out) {
	if (!(std::cin >> out)) {
		std::cin.clear();
		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "Invalid or unexpected user's input." << std::endl;
		return false;
	}
	return true;
}