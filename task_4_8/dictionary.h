#pragma once

#include <map>

#include "qt.h"
#include "dictionary_node.h"

//—ловарь дл€ слов, который содержит базовое слово (ну или его часть), 
// оторое содержит небольшой словарь с окончан€ми и падежом.

class Dictionary {
public:
	void addNode(const QString& base, const DictionaryNode& node);
	void removeNode(const QString& base);
	bool getNode(const QString& base, DictionaryNode& out);
	//ѕолучить список базовых слов
	std::vector<QString> getBases() const;
	size_t size() const;
private:
	std::map<QString, DictionaryNode> m_nodes;
};