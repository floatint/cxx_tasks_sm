#pragma once

#include "qt.h"

//Обертка над сообщениями пользователю

class Messages {
public:
	static void error(const QString& msg);
	static void info(const QString& msg);
	//низкоуровневая обертка
	static void showMessage(const QString& title, const QString& msg);
};