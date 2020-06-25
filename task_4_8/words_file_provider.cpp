#include "words_file_provider.h"

std::vector<QString> WordsClassProvider::readFile(const QFileInfo& filePath) {
	if (!filePath.isFile())
		throw std::exception("Words file path is not a file");
	if (!filePath.exists())
		throw std::exception("Words file not exists");
	//пытаемся открыть файл
	QFile file(filePath.filePath());
	//если удалось открыть
	if (file.open(QIODevice::ReadOnly)) {
		//читаем
		QTextStream in(&file);
		QString buffer = in.readAll();
		//Разбиваем весь файл по пробелам
		return buffer.split(' ', Qt::SplitBehaviorFlags::SkipEmptyParts).toVector().toStdVector();
	}
	else
		throw std::exception("Can't open words file");
	return std::vector<QString>();
}