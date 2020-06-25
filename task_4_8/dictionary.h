#pragma once

#include <map>

#include "qt.h"
#include "dictionary_node.h"

//������� ��� ����, ������� �������� ������� ����� (�� ��� ��� �����), 
//������� �������� ��������� ������� � ���������� � �������.

class Dictionary {
public:
	void addNode(const QString& base, const DictionaryNode& node);
	void removeNode(const QString& base);
	DictionaryNode& getNode(const QString& base);
	//�������� ������ ������� ����
	std::vector<QString> getBases() const;
	size_t size() const;
private:
	std::map<QString, DictionaryNode> m_nodes;
};