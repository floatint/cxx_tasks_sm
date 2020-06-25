#pragma once

#include "qt.h"

//Перечисление падежей

enum class Declension {
	Nominative, //Именительный
	Genetive, //Родительный
	Dative, //Дательный
	Accusative, //Винительный
	Instrumental, //Творительный
	Prepositional, //Предложный
};

//перевод enum в строку
QString declensionToString(Declension d);

