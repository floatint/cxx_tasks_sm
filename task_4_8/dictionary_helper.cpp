#include "dictionary_helper.h"

QString DictionaryHelper::getBase(const std::vector<QString>& words) {
	if (words.size() == 0)
		throw std::exception("Words list is empty");
	//результат
	QString base;
	//логика следующая -> пытаемся найти наибольшую общую часть слова
	//возьмем за основу наименьшее слово
	QString fw = *std::min_element(words.cbegin(), words.cend());
	//проверим что бы оно было не пустое
	if (fw.isEmpty())
		throw std::exception("Base word is empty");
	//QString fw = words[0];
	for (int i = 0; i < fw.size(); i++) {
		//сохраняем первый символ
		auto c = fw[i];
		//проверяем среди остальных слов символ в позиции i
		auto check = [&words, &c, &i]() {
			for (auto w = words.cbegin() + 1; w != words.cend(); w++) {
				//auto ww = w[i];
				if (w->at(i) != c)
					return false;
			}
			return true;
		};
		//если очередной символ в позиции i во всех словах одинаков, то добавляем его
		if (check())
			base += c;
		else
			//иначе нет смысла продолжать
			return base;
	}
	return base;
}