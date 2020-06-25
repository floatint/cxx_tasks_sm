#pragma once

#include "qt.h"

//Главное окно приложения

class FileWindow : public QWidget
{
	Q_OBJECT

public:
	FileWindow(const QFileInfo& filePath, QWidget *parent = Q_NULLPTR);

private:
	//ui
	QVBoxLayout *m_verticalLayout;
	QTableWidget *m_wordsTable;


	//создание ui
	void setupUi();

	//void processFile(const QFileInfo& filePath);

};
