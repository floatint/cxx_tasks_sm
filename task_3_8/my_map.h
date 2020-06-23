#pragma once

#include <vector>

//Ассоциативный массив на базе бинарного поиска.
//Для справки: по стандарту в c++ используются хеш-таблицы
//но их довольно сложно реализовать, да и в целом не уточняется что 
//нужно делать именно на них. Но отличия знать желательно.

template<typename TKy, typename TVa>
class MyMap {
public:
	//вставка
	TVa& insert(const TKy& k, const TVa& val) {
		if (m_nodes.size() == 0) {
			m_nodes.push_back({ k, val });
			return m_nodes[0].value;
		} else {
			auto node_pos = calc_node_pos(k);

			if (m_nodes[node_pos].key == k)
				throw std::invalid_argument("Map support only unique keys");


			m_nodes.insert(m_nodes.cbegin() + node_pos, { k, val });
			return m_nodes[node_pos].value;
		}
	}

	//удаление записи
	void remove(const TKy& k) {
		auto node_pos = get_node_pos(k);
		if (node_pos < 0)
			throw std::invalid_argument("Key not exists in map");
		m_nodes.erase(m_nodes.cbegin() + node_pos);
	}

	//поиск записи
	bool try_get(const TKy& k, TVa& outVal) {
		auto node_pos = get_node_pos(k);
		if (node_pos < 0)
			return false;
		else
			outVal = m_nodes[node_pos].value;
		return true;
	}

private:
	//внутренности ассоциативного массива
	
	//ищем место для вставки
	int calc_node_pos(const TKy& k) const {
		//если массив пуст, или заданный ключ меньше самого меньшего имеющегося
		if (m_nodes.size() == 0 || (k < m_nodes[0].key))
			return 0;
		else if (m_nodes[m_nodes.size() - 1].key < k) //если заданный ключ больше всех имеющихся
			return m_nodes.size();

		int i = 0; // текущая позиция в массиве
		int s = m_nodes.size(); //сохраним размер, что бы не дергать функцию
		int m = 0; // середина массива
		
		//пока не переберем все элементы
		while (i < s) {
			m = (i + s) / 2; //считаем середину
			//
			if (k < m_nodes[m].key)
				s = m;
			else if (k == m_nodes[m].key)
				i = m + 1;
		}
		return i;
	}

	//поиск индекса ключа
	int get_node_pos(const TKy& k) {
		if (m_nodes.size() == 0 || (k < m_nodes[0].key))
			return -1;
		else if (m_nodes[m_nodes.size() - 1].key < k)
			return -1;

		int i = 0;
		int s = m_nodes.size();
		int m = 0;

		while (i < s) {
			m = (i + s) / 2;
			if (k < m_nodes[m].key)
				s = m;
			else {
				if (k == m_nodes[m].key)
					return m;
				i = m + 1;
			}
		}
		return -1;
	}

	//запись в массиве
	struct MapNode {
		TKy key;
		TVa value;
	};

	std::vector<MapNode> m_nodes;
};