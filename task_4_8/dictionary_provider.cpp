#include "dictionary_provider.h"

Dictionary DictionaryProvider::loadFromFile(const QFileInfo& path) {
	if (!path.isFile())
		throw std::exception("Dictionary path is not a file");
	if (!path.exists())
		throw std::exception("Dictionary file not exists");
	
	//�������� ������� ����
	QFile file(path.filePath());
	//���� ������� �������
	if (file.open(QIODevice::ReadOnly)) {
		QDataStream data_stream(&file);
		int sign = -1;
		data_stream >> sign;
		if (sign != DICTIONARY_SIGNATURE)
			throw std::exception("Invalid dictionary signature");
		else {
			Dictionary dict;
			//�������� ���-�� �������
			size_t nodes_cnt = 0;
			data_stream >> nodes_cnt;
			//���� �� ���� �������
			for (size_t i = 0; i < nodes_cnt; i++) {
				//������ ������� �����
				QString base;
				data_stream >> base;
				//������ ���-�� �������
				size_t decl_cnt = 0;
				data_stream >> decl_cnt;
				DictionaryNode node;
				//������ ��� ������ ��� �������� �����
				for (size_t j = 0; j < decl_cnt; j++) {
					//������ �������
					QString prefix;
					data_stream >> prefix;
					//������ �����
					size_t decl = 0;;
					data_stream >> decl;
					//��������� � ������
					node.addDeclension(prefix, (Declension)decl);
				}
				//��������� ������ � �������
				dict.addNode(base, node);
			}
			return dict;
		}
	}
	else
		throw std::exception("Can't open dictionary file");
}

void DictionaryProvider::saveToFile(const QFileInfo& path, Dictionary& dict) {
	//�������� ������� ����
	QFile file(path.filePath());
	//���� ������� �������
	if (file.open(QIODevice::WriteOnly)) {
		QDataStream data_stream(&file);
		//����� ��������� 
		data_stream << DICTIONARY_SIGNATURE;
		//����� ���-�� �������
		size_t node_cnt = dict.size();
		data_stream << node_cnt;
		//���������� ������
		auto bases = dict.getBases();
		for (size_t i = 0; i < node_cnt; i++) {
			//����� ������� �����
			data_stream << bases[i];
			//�������� ������
			DictionaryNode node;
			dict.getNode(bases[i], node);
			//�������� ���-�� ��������� ������� ��� ������� �����
			size_t declens_cnt = node.size();
			//����� ���-�� �������
			data_stream << declens_cnt;
			for (size_t j = 0; j < declens_cnt; j++) {
				//����� �������
				data_stream << node.getPrefix((Declension)j);
				//����� �����
				data_stream << j;
			}
		}
		
	}
	else
		throw std::exception("Can't open dictionary file");
}