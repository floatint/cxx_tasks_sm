#include "words_file_provider.h"

std::vector<QString> WordsClassProvider::readFile(const QFileInfo& filePath) {
	if (!filePath.isFile())
		throw std::exception("Words file path is not a file");
	if (!filePath.exists())
		throw std::exception("Words file not exists");
	//�������� ������� ����
	QFile file(filePath.filePath());
	//���� ������� �������
	if (file.open(QIODevice::ReadOnly)) {
		//������
		QTextStream in(&file);
		QString buffer = in.readAll();
		//��������� ���� ���� �� ��������
		return buffer.split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts).toVector().toStdVector();
	}
	else
		throw std::exception("Can't open words file");
	return std::vector<QString>();
}