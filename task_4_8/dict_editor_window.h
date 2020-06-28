#pragma once

#include "qt.h"
#include "ui_dict_editor.h"
#include "dictionary.h"
#include "dictionary_node.h"

//�������� �������. �������� � Qt Designer

class DictEditorWindow : public QDialog
{
	Q_OBJECT

public:
	DictEditorWindow(Dictionary& dict, QWidget *parent = Q_NULLPTR);

private:
	Ui::DictEditorWindow ui;

	//����������� ������
	void setupSlots();

	//������
	//��������� ���������� �����
	void newWord();
	//������� ����� �� �������
	void deleteWord();
	//��������� �����
	void saveWord();
	//��������� ������ ����� � ������
	void wordListItemChanged(QListWidgetItem *curr, QListWidgetItem *prev);
	//���������� ������ ����
	void updateWordsList();

	//������

	//������� ��������� �������
	const QString DIALOG_TITLE = "Dictionary Editor";
	//��������������� ���������� ��� �������, ����� �� ����� � ��������
	bool m_isUpdated;

	//��������� ������ � �����
	DictionaryNode *m_dictNode = nullptr;
	//�������
	Dictionary& m_dict;

	//������ ����, ������� ��������� � ������
	std::vector<std::pair<QString, DictionaryNode>> m_wordsList;

};