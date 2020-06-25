#pragma once

#include "qt.h"
#include "dictionary.h"
//Окно файла со словами

class FileWindow : public QWidget
{
	Q_OBJECT

public:
	FileWindow(const QFileInfo& filePath, Dictionary& dict, QWidget *parent = Q_NULLPTR);

private:
	//ui
	QVBoxLayout *m_verticalLayout;
	QTableWidget *m_wordsTable;
	//заголовок таблицы
	QStringList m_tableHeader{ "Word", "Declension" };


	//создание ui
	void setupUi();

	void processFile(const QFileInfo& filePath);


	//максимум сколько может отрезать от окончания
	const int MAX_CUT_LIMIT = 3;

	//ссылка на словарь
	Dictionary &m_dict;

	//обработанные слова с сопаставленным падежем
	std::vector<std::pair<QString, QString>> m_words;
};
