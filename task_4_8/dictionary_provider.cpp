#include "dictionary_provider.h"

Dictionary DictionaryProvider::loadFromFile(const QFileInfo& path) {
	if (!path.isFile())
		throw std::exception("Dictionary path is not a file");
	if (!path.exists())
		throw std::exception("Dictionary file not exists");
	
	//пытаемся открыть файл
	QFile file(path.filePath());
	//если удалось открыть
	if (file.open(QIODevice::ReadOnly)) {
		QDataStream data_stream(&file);
		int sign = -1;
		data_stream >> sign;
		if (sign != DICTIONARY_SIGNATURE)
			throw std::exception("Invalid dictionary signature");
		else {
			Dictionary dict;
			//получаем кол-во записей
			size_t nodes_cnt = 0;
			data_stream >> nodes_cnt;
			//идем по всем записям
			for (size_t i = 0; i < nodes_cnt; i++) {
				//читаем базовое слово
				QString base;
				data_stream >> base;
				//читаем кол-во падежей
				size_t decl_cnt = 0;
				data_stream >> decl_cnt;
				DictionaryNode node;
				//читаем все падежи для базового слова
				for (size_t j = 0; j < decl_cnt; j++) {
					//читаем префикс
					QString prefix;
					data_stream >> prefix;
					//читаем падеж
					size_t decl = 0;;
					data_stream >> decl;
					//добавляем в запись
					node.addDeclension(prefix, (Declension)decl);
				}
				//добавляем запись в словарь
				dict.addNode(base, node);
			}
			return dict;
		}
	}
	else
		throw std::exception("Can't open dictionary file");
}

void DictionaryProvider::saveToFile(const QFileInfo& path, Dictionary& dict) {
	//пытаемся открыть файл
	QFile file(path.filePath());
	//если удалось открыть
	if (file.open(QIODevice::WriteOnly)) {
		QDataStream data_stream(&file);
		//пишем сигнатуру 
		data_stream << DICTIONARY_SIGNATURE;
		//пишем кол-во записей
		size_t node_cnt = dict.size();
		data_stream << node_cnt;
		//перебираем записи
		auto bases = dict.getBases();
		for (size_t i = 0; i < node_cnt; i++) {
			//пишем базовое слово
			data_stream << bases[i];
			//получаем запись
			DictionaryNode node;
			dict.getNode(bases[i], node);
			//получаем кол-во префиксов падежей для данного слова
			size_t declens_cnt = node.size();
			//пишем кол-во падежей
			data_stream << declens_cnt;
			for (size_t j = 0; j < declens_cnt; j++) {
				//пишем префикс
				data_stream << node.getPrefix((Declension)j);
				//пишем падеж
				data_stream << j;
			}
		}
		
	}
	else
		throw std::exception("Can't open dictionary file");
}