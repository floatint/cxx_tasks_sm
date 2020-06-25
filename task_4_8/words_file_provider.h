#pragma once

#include "qt.h"


//Класс-читатель файлов со словами

class WordsClassProvider {
public:
	//читаем слова из файла
	static std::vector<QString> readFile(const QFileInfo& filePath);
};
