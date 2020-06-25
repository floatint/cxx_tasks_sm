#include "filewindow.h"
#include "words_file_provider.h"


FileWindow::FileWindow(const QFileInfo& filePath, Dictionary& dict, QWidget *parent)
	: QWidget(parent),
	m_dict(dict)
{
	setupUi();
	//обрабатываем файл
	processFile(filePath);
	//смотрим что получилось и выводим на форму
	for (auto wIt = m_words.cbegin(); wIt != m_words.cend(); wIt++) {
		int row = m_wordsTable->rowCount();
		m_wordsTable->insertRow(row);
		m_wordsTable->setItem(row, 0, new QTableWidgetItem(wIt->first));
		m_wordsTable->setItem(row, 1, new QTableWidgetItem(wIt->second));
	}
}

//
void FileWindow::setupUi() {
	m_verticalLayout = new QVBoxLayout(this);
	m_verticalLayout->setSpacing(6);
	m_verticalLayout->setContentsMargins(11, 11, 11, 11);
	m_wordsTable = new QTableWidget(this);
	m_wordsTable ->setColumnCount(2);
	m_wordsTable->setShowGrid(true);
	m_wordsTable->setHorizontalHeaderLabels(m_tableHeader);
	m_wordsTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

	m_verticalLayout->addWidget(m_wordsTable);
}

void FileWindow::processFile(const QFileInfo& filePath) {
	//получаем список слов из файла
	auto words = WordsClassProvider::readFile(filePath);
	//идем по всем словам
	bool found = false; //нашли ли слово в словаре
	for (auto w : words) {
		//идея в следующем, чтобы отрезать по очереди максимум 3 символа от конца слова на входе
		//оно же окончание и найти базу
		for (int i = 0; i < MAX_CUT_LIMIT; i++) {
			//пока не нашли
			if (!found) {
				QString tmpBase = w.chopped(i);
				DictionaryNode node;
				if (m_dict.getNode(tmpBase, node)) {
					//если нашли базовое слово, то определим в каком оно падеже
					//получаем префикс
					QString prefix = w.right(i);
					//получаем падеж
					Declension decl = node.getDeclension(prefix);
					//добавляем в список
					m_words.push_back({ w, declensionToString(decl) });
					found = true;
				}
				else
					found = false;
			}
		};
		//не удалось определить падеж
		if (!found)
			m_words.push_back({ w, QString::fromUtf8(u8"неизвестный падеж") });
		else
			found = false;
	};
};