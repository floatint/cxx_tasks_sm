#include "dictionary_node.h"

DictionaryNode::DictionaryNode() {
	m_declensions = std::map<Declension, QString>();
}

void DictionaryNode::addDeclension(const QString& prefix, Declension d) {
	m_declensions[d] = prefix;
}

//TODO: возникает неоднозначность, когда префикс для разных падежей одинаков
//не решается в лоб.
Declension DictionaryNode::getDeclension(const QString& prefix) {
	auto declIt = std::find_if(m_declensions.cbegin(), m_declensions.cend(), [prefix](const std::pair<Declension, QString>& p) {
		return p.second == prefix;
	});

	if (declIt == m_declensions.cend())
		throw std::exception("Can't found declension");
	return declIt->first;
}

QString DictionaryNode::getPrefix(Declension d) {
	auto prefixIt = m_declensions.find(d);

	if (prefixIt == m_declensions.cend())
		throw std::exception("Declension is not exists in dictionary node");
	return prefixIt->second;
}

size_t DictionaryNode::size() const {
	return m_declensions.size();
}

std::vector<QString> DictionaryNode::getDeclensionPrefixes() const {
	std::vector<QString> res;

	for (auto d : m_declensions) {
		res.push_back(d.second);
	}
	
	return res;
}