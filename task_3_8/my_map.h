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
		//���� ��������� ������, ������ �������
		if (m_nodes.size() == 0) {
			m_nodes.push_back({ k, val });
			return m_nodes[0].value;
		} else {
			
			auto node_pos = calc_node_pos(k);
			//���� ����� �������� � �����
			if (node_pos == m_nodes.size()) {
				m_nodes.insert(m_nodes.cbegin() + node_pos, { k, val });
			}
			else {
				if (m_nodes[node_pos].key == k)
					throw std::invalid_argument("Map support only unique keys");

				m_nodes.insert(m_nodes.cbegin() + node_pos, { k, val });
			}
			return m_nodes[node_pos].value;
		}
	}

	//�������� ������
	void remove(const TKy& k) {
		auto node_pos = get_node_pos(k);
		if (node_pos < 0)
			throw std::invalid_argument("Key not exists in map");
		m_nodes.erase(m_nodes.cbegin() + node_pos);
	}

	//����� ������
	bool try_get(const TKy& k, TVa& outVal) {
		auto node_pos = get_node_pos(k);
		if (node_pos < 0)
			return false;
		else
			outVal = m_nodes[node_pos].value;
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
	
	//���� ����� ��� �������
	int calc_node_pos(const TKy& k) const {
		//���� ������ ����, ��� �������� ���� ������ ������ �������� ����������
		if (m_nodes.size() == 0 || (k < m_nodes[0].key))
			return 0;
		else if (m_nodes[m_nodes.size() - 1].key < k) //���� �������� ���� ������ ���� ���������
			return m_nodes.size();

		int i = 0; // ������� ������� � �������
		int s = m_nodes.size(); //�������� ������, ��� �� �� ������� �������
		int m = 0; // �������� �������
		
		//���� �� ��������� ��� ��������
		while (i < s - 1) {
			m = (i + s) / 2; //������� ��������
			//
			if (k < m_nodes[m].key)
				s = m;
			else if (k == m_nodes[m].key)
				i = m + 1;
		}
		return i;
	}

	//����� ������� �����
	int get_node_pos(const TKy& k) {
		if (m_nodes.size() == 0 || (k < m_nodes[0].key))
			return -1;
		else if (m_nodes[m_nodes.size() - 1].key < k)
			return -1;

		int i = 0;
		int s = m_nodes.size();
		int m = 0;

		while (i < s - 1) {
			m = (i + s) / 2;
			if (k < m_nodes[m].key)
				s = m;
			else {
				if (k == m_nodes[m].key)
					return m;
				i = m + 1;
			}
		}
		return i;
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