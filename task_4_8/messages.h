#pragma once

#include "qt.h"

//������� ��� ����������� ������������

class Messages {
public:
	static void error(const QString& msg);
	static void info(const QString& msg);
	//�������������� �������
	static void showMessage(const QString& title, const QString& msg);
};