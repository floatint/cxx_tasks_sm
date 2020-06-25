#pragma once

#include "qt.h"
#include "ui_dict_editor.h"
#include "dictionary.h"
#include "dictionary_node.h"

//Редактор словаря. Сверстан в Qt Designer

class DictEditorWindow : public QDialog
{
	Q_OBJECT

public:
	DictEditorWindow(Dictionary& dict, QWidget *parent = Q_NULLPTR);

private:
	Ui::DictEditorWindow ui;

	//подключение логики
	void setupSlots();

	//логика
	//обработка добавления слова
	void addWord();
	//удалить слово из словаря
	void deleteWord();
	//сохранить слово
	void saveWord();
	//обработка выбора слова в списке
	void wordListItemChanged(QListWidgetItem *curr, QListWidgetItem *prev);
	//обновление списка слов
	void updateWordsList();

	//данные

	//временная запись о слове
	DictionaryNode *m_dictNode = nullptr;
	//словарь
	Dictionary& m_dict;

	//список слов, которые находятся в списке
	std::vector<std::pair<QString, DictionaryNode>> m_wordsList;

};