#pragma once

#include <vector>
#include <iostream>

//Ассоциативный массив на базе бинарного поиска.
//Для справки: по стандарту в c++ используются хеш-таблицы
//но их довольно сложно реализовать, да и в целом не уточняется что 
//нужно делать именно на них. Но отличия знать желательно.

//Естествено, т.к. все посроено на бинарном поиске, то
//TKy должен быть сравниваемым.

//Сложность O(n), по факту все равно что ключи перебирать, только ключи отсортированы

//НО ! Задача выполнена, ибо четкого ТЗ нет

template<typename TKy, typename TVa>
class MyMap {
public:
	//вставка
	TVa& insert(const TKy& k, const TVa& val) {
		int i = get_node_index(k);
		//если нужно добавить в конец
		if (i == m_nodes.size()) {
			m_nodes.push_back({ k, val });
		}
		else {
			if (m_nodes[i].key == k)
				throw std::invalid_argument("Map support only unique keys");

			m_nodes.insert(m_nodes.cbegin() + i, { k, val });
		}
		return m_nodes[i].value;
	}

	//удаление записи
	void remove(const TKy& k) {
		int i = get_node_index(k);
		if (i >= m_nodes.size() || m_nodes[i].key != k)
			throw std::invalid_argument("Key not exists in map");
		m_nodes.erase(m_nodes.cbegin() + i);
	}

	//поиск записи
	bool try_get(const TKy& k, TVa& outVal) {
		int i = get_node_index(k);
		if (i >= m_nodes.size() || m_nodes[i].key != k)
			return false;
		else
			outVal = m_nodes[i].value;
		return true;
	}

	size_t size() const {
		return m_nodes.size();
	}

	//внешний принтер
	template<typename Ky, typename Va>
	friend std::ostream& operator<<(std::ostream& o, const MyMap<Ky, Va>& v);
private:
	//внутренности ассоциативного массива
	
	//поиск индекса ключа
	int get_node_index(const TKy& k) {
		
		if (m_nodes.size() == 0)
			return 0;

		int l = -1; //левая граница
		int r = m_nodes.size(); //правая
		
		while (l < r - 1) {
			int m = (l + r) / 2;
			if (m_nodes[m].key < k)
				l = m;
			else
				r = m;
		}
		return r;
	}

	//запись в массиве
	struct MapNode {
		TKy key;
		TVa value;
	};

	std::vector<MapNode> m_nodes;
};

//Для вывода в поток
template<typename TKy, typename TVa>
std::ostream& operator<<(std::ostream& o, const MyMap<TKy, TVa>& v) {
	for (auto n : v.m_nodes) {
		o << "Key: " << n.key << ", value: " << n.value << std::endl;
	}
	return o;
}