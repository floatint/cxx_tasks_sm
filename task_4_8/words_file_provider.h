#pragma once

#include "qt.h"


//�����-�������� ������ �� �������

class WordsClassProvider {
public:
	//������ ����� �� �����
	static std::vector<QString> readFile(const QFileInfo& filePath);
};
