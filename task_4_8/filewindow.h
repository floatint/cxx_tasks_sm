#pragma once

#include "qt.h"
#include "dictionary.h"
//���� ����� �� �������

class FileWindow : public QWidget
{
	Q_OBJECT

public:
	FileWindow(const QFileInfo& filePath, Dictionary& dict, QWidget *parent = Q_NULLPTR);

private:
	//ui
	QVBoxLayout *m_verticalLayout;
	QTableWidget *m_wordsTable;
	//��������� �������
	QStringList m_tableHeader{ "Word", "Declension" };


	//�������� ui
	void setupUi();

	void processFile(const QFileInfo& filePath);


	//�������� ������� ����� �������� �� ���������
	const int MAX_CUT_LIMIT = 3;

	//������ �� �������
	Dictionary &m_dict;

	//������������ ����� � �������������� �������
	std::vector<std::pair<QString, QString>> m_words;
};
