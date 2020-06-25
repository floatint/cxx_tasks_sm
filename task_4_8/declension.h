#pragma once

#include "qt.h"

//������������ �������

enum class Declension {
	Nominative, //������������
	Genetive, //�����������
	Dative, //���������
	Accusative, //�����������
	Instrumental, //������������
	Prepositional, //����������
};

//������� enum � ������
QString declensionToString(Declension d);

