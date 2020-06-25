#pragma once

#include <vector>
#include "qt.h"

//Класс с некоторой логикой обработки слов

class DictionaryHelper {
public:
	//получаем базовое слово из списка слов в разных падежах
	static QString getBase(const std::vector<QString>& words);
};