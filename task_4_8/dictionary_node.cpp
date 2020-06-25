#include "dictionary_node.h"

//DictionaryNode::DictionaryNode() {
//	m_declensions = std::vector<std::pair<QString, Declension>>();
//}

void DictionaryNode::addDeclension(const QString& prefix, Declension d) {
	m_declensions.push_back({ prefix, d });
	//try {
		//m_declensions[prefix] = d;
	//}
	//catch (const std::exception& ex) {
	//	throw std::exception("Word prefix already ");
	//}
}

//TODO: возникает неоднозначность, когда префикс для разных падежей одинаков
//не решается в лоб.
Declension DictionaryNode::getDeclension(const QString& prefix) {
	auto declIt = std::find_if(m_declensions.cbegin(), m_declensions.cend(), [prefix](const std::pair<QString, Declension>& p) {
		return p.first == prefix;
	});
	//auto declIt = m_declensions.find(prefix);
	if (declIt == m_declensions.cend())
		throw std::exception("Can't found declension");
	return declIt->second;
}

QString DictionaryNode::getPrefix(Declension d) {
	auto prefixIt = std::find_if(m_declensions.cbegin(), m_declensions.cend(), [d](const std::pair<QString, Declension>& p) {
		return p.second == d;
	});
	//auto prefixIt = std::find_if(m_declensions.cbegin(), m_declensions.cend(), [d](const auto decl) {
	//	return decl.second == d;
	//});

	if (prefixIt == m_declensions.cend())
		throw std::exception("Declension is not exists in dictionary node");
	return prefixIt->first;
}

size_t DictionaryNode::size() const {
	return m_declensions.size();
}

std::vector<QString> DictionaryNode::getDeclensionPrefixes() const {
	std::vector<QString> res;

	for (auto d : m_declensions) {
		res.push_back(d.first);
	}
	
	return res;
}