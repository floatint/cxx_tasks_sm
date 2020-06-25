#pragma once


#include "qt.h"
#include "dictionary.h"


//I/O манипуляции со словарем

//сигнатура словаря
const int DICTIONARY_SIGNATURE = 0xDFFD;

class DictionaryProvider {
public:
	static Dictionary loadFromFile(const QFileInfo& path);
	static void saveToFile(const QFileInfo& path, Dictionary& dict);
};