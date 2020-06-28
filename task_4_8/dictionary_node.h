#pragma once

#include <vector>
#include <map>

#include "qt.h"
#include "declension.h"

//ћини-словарь, который сопостовл€ет окончани€ падежам.

class DictionaryNode {
public:
	DictionaryNode();
	void addDeclension(const QString& prefix, Declension d);
	Declension getDeclension(const QString& prefix);
	QString getPrefix(Declension d);
	size_t size() const;
	//ѕолучить список всех окончаний
	std::vector<QString> getDeclensionPrefixes() const;
private:
	std::map<Declension, QString> m_declensions;
};