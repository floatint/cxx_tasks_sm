#pragma once

#include <vector>
#include "qt.h"

//����� � ��������� ������� ��������� ����

class DictionaryHelper {
public:
	//�������� ������� ����� �� ������ ���� � ������ �������
	static QString getBase(const std::vector<QString>& words);
};