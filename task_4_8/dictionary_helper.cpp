#include "dictionary_helper.h"

QString DictionaryHelper::getBase(const std::vector<QString>& words) {
	if (words.size() == 0)
		throw std::exception("Words list is empty");
	//���������
	QString base;
	//������ ��������� -> �������� ����� ���������� ����� ����� �����
	//������� �� ������ ���������� �����
	QString fw = *std::min_element(words.cbegin(), words.cend());
	//�������� ��� �� ��� ���� �� ������
	if (fw.isEmpty())
		throw std::exception("Base word is empty");
	//QString fw = words[0];
	for (int i = 0; i < fw.size(); i++) {
		//��������� ������ ������
		auto c = fw[i];
		//��������� ����� ��������� ���� ������ � ������� i
		auto check = [&words, &c, &i]() {
			for (auto w = words.cbegin() + 1; w != words.cend(); w++) {
				//auto ww = w[i];
				if (w->at(i) != c)
					return false;
			}
			return true;
		};
		//���� ��������� ������ � ������� i �� ���� ������ ��������, �� ��������� ���
		if (check())
			base += c;
		else
			//����� ��� ������ ����������
			return base;
	}
	return base;
}