#include "dictionary.h"

void Dictionary::addNode(const QString& base, const DictionaryNode& node) {
	m_nodes[base] = node;
}

void Dictionary::removeNode(const QString& base) {
	m_nodes.erase(base);
}

bool Dictionary::getNode(const QString& base, DictionaryNode& out) {
	auto nodeIt = m_nodes.find(base);
	if (nodeIt == m_nodes.end())
		return false;
	out = nodeIt->second;
	return true;;
}

std::vector<QString> Dictionary::getBases() const {
	std::vector<QString> res;

	for (auto n : m_nodes) {
		res.push_back(n.first);
	}

	return res;
}

size_t Dictionary::size() const {
	return m_nodes.size();
}