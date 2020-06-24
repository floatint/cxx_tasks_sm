#pragma once

#include <vector>
#include <iostream>

//������������� ������ �� ���� ��������� ������.
//��� �������: �� ��������� � c++ ������������ ���-�������
//�� �� �������� ������ �����������, �� � � ����� �� ���������� ��� 
//����� ������ ������ �� ���. �� ������� ����� ����������.

//����������, �.�. ��� �������� �� �������� ������, ��
//TKy ������ ���� ������������.

//��������� O(n), �� ����� ��� ����� ��� ����� ����������, ������ ����� �������������

//�� ! ������ ���������, ��� ������� �� ���

template<typename TKy, typename TVa>
class MyMap {
public:
	//�������
	TVa& insert(const TKy& k, const TVa& val) {
		int i = get_node_index(k);
		//���� ����� �������� � �����
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

	//�������� ������
	void remove(const TKy& k) {
		int i = get_node_index(k);
		if (i >= m_nodes.size() || m_nodes[i].key != k)
			throw std::invalid_argument("Key not exists in map");
		m_nodes.erase(m_nodes.cbegin() + i);
	}

	//����� ������
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

	//������� �������
	template<typename Ky, typename Va>
	friend std::ostream& operator<<(std::ostream& o, const MyMap<Ky, Va>& v);
private:
	//������������ �������������� �������
	
	//����� ������� �����
	int get_node_index(const TKy& k) {
		
		if (m_nodes.size() == 0)
			return 0;

		int l = -1; //����� �������
		int r = m_nodes.size(); //������
		
		while (l < r - 1) {
			int m = (l + r) / 2;
			if (m_nodes[m].key < k)
				l = m;
			else
				r = m;
		}
		return r;
	}

	//������ � �������
	struct MapNode {
		TKy key;
		TVa value;
	};

	std::vector<MapNode> m_nodes;
};

//��� ������ � �����
template<typename TKy, typename TVa>
std::ostream& operator<<(std::ostream& o, const MyMap<TKy, TVa>& v) {
	for (auto n : v.m_nodes) {
		o << "Key: " << n.key << ", value: " << n.value << std::endl;
	}
	return o;
}