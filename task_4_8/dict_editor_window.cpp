#include "dict_editor_window.h"
#include "dictionary_helper.h"
#include "declension.h"
#include "messages.h"

#include <set>

DictEditorWindow::DictEditorWindow(Dictionary& dict, QWidget *parent)
	: QDialog(parent),
	m_dict(dict)
{
	//m_dict = dict;
	m_dictNode = nullptr;
	ui.setupUi(this);
	//обновляем список слов
	updateWordsList();
	//рисуем комбобоксы
	ui.declSelect_2->setModel(qobject_cast<QStandardItemModel*>(ui.declSelect_1->model()));
	ui.declSelect_3->setModel(qobject_cast<QStandardItemModel*>(ui.declSelect_1->model()));
	ui.declSelect_4->setModel(qobject_cast<QStandardItemModel*>(ui.declSelect_1->model()));
	ui.declSelect_5->setModel(qobject_cast<QStandardItemModel*>(ui.declSelect_1->model()));
	ui.declSelect_6->setModel(qobject_cast<QStandardItemModel*>(ui.declSelect_1->model()));
	//подключаем логику
	setupSlots();
}

void DictEditorWindow::setupSlots() {
	connect(ui.wordsList, &QListWidget::currentItemChanged, this, &DictEditorWindow::wordListItemChanged);
	connect(ui.addButton, &QPushButton::clicked, this, &DictEditorWindow::addWord);
	connect(ui.saveButton, &QPushButton::clicked, this, &DictEditorWindow::saveWord);
	connect(ui.deleteButton, &QPushButton::clicked, this, &DictEditorWindow::deleteWord);
}

void DictEditorWindow::addWord() {
	if (m_dictNode != nullptr)
		delete m_dictNode;
	//создаем временный объект
	m_dictNode = new DictionaryNode();
	//зануляем поля ввода
	ui.prefixEdit_1->clear();
	ui.prefixEdit_2->clear();
	ui.prefixEdit_3->clear();
	ui.prefixEdit_4->clear();
	ui.prefixEdit_5->clear();
	ui.prefixEdit_6->clear();
	ui.wordsList->setCurrentIndex(QModelIndex());
}

void DictEditorWindow::saveWord() {
	if (m_dictNode == nullptr && ui.wordsList->currentIndex().row() < 0) {
		Messages::info("Please, select word or add new");
		return;
	}
	//проверим, чтобы все поля были заполнены
	if (ui.prefixEdit_1->text().isEmpty() ||
		ui.prefixEdit_2->text().isEmpty() ||
		ui.prefixEdit_3->text().isEmpty() ||
		ui.prefixEdit_4->text().isEmpty() ||
		ui.prefixEdit_5->text().isEmpty() ||
		ui.prefixEdit_6->text().isEmpty()
		)
	{
		Messages::info("Please, fill all input fields");
		return;
	}
	else {
		//проверим, что комбобоксы указывают на разные падежи и нет дубликатов
		std::vector<int> declIndexes;
		declIndexes.push_back(ui.declSelect_1->currentIndex());
		declIndexes.push_back(ui.declSelect_2->currentIndex());
		declIndexes.push_back(ui.declSelect_3->currentIndex());
		declIndexes.push_back(ui.declSelect_4->currentIndex());
		declIndexes.push_back(ui.declSelect_5->currentIndex());
		declIndexes.push_back(ui.declSelect_6->currentIndex());
		
		//проверим при помощи конвертирования в set, есть ли дубликаты падежей
		auto tmp = std::set<int>(declIndexes.cbegin(), declIndexes.cend());
		if (tmp.size() != declIndexes.size()) {
			Messages::info("Declensions must by unique");
			return;
		}
		//получим базовое слово
		std::vector<QString> words;
		words.push_back(ui.prefixEdit_1->text());
		words.push_back(ui.prefixEdit_2->text());
		words.push_back(ui.prefixEdit_3->text());
		words.push_back(ui.prefixEdit_4->text());
		words.push_back(ui.prefixEdit_5->text());
		words.push_back(ui.prefixEdit_6->text());
		
		QString baseWord = DictionaryHelper::getBase(words);

		//базовое слово есть, далее для каждого получим префикс и падеж
		//DictionaryNode newDictNode;
		//получим индексы падежей для каждого слова
		std::vector<int> declensIndexes;
		declensIndexes.push_back(ui.declSelect_1->currentIndex());
		declensIndexes.push_back(ui.declSelect_2->currentIndex());
		declensIndexes.push_back(ui.declSelect_3->currentIndex());
		declensIndexes.push_back(ui.declSelect_4->currentIndex());
		declensIndexes.push_back(ui.declSelect_5->currentIndex());
		declensIndexes.push_back(ui.declSelect_6->currentIndex());
		//заполняем запись в словаре
		for (int i = 0; i < words.size(); i++) {
			//получаем префикс
			auto prefix = words[i].right(words[i].size() - baseWord.size());
			Declension decl = (Declension)declensIndexes[i];
			m_dictNode->addDeclension(prefix, decl);
		}

		//добавляем запись в словарь
		m_dict.addNode(baseWord, *m_dictNode);
		//обновим список слов
		updateWordsList();
	}
}

void DictEditorWindow::deleteWord() {
	//если ничего не выбрано
	if (ui.wordsList->currentIndex().row() < 0)
		return;
	auto dictNode = m_wordsList[ui.wordsList->currentIndex().row()];
	//удаляем из словаря
	m_dict.removeNode(dictNode.first);
	//обновляем ui
	updateWordsList();
}

void DictEditorWindow::wordListItemChanged(QListWidgetItem *curr, QListWidgetItem *prev) {
	if (m_dictNode != nullptr) {
		delete m_dictNode;
	}
	//если выбрано слово
	if (curr != nullptr) {
		//получим его индекс в списке
		auto i = ui.wordsList->row(curr);
		//получаем все префиксы, и устанавливаем ui
		ui.prefixEdit_1->setText(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Nominative));
		ui.declSelect_1->setCurrentIndex((int)Declension::Nominative);
		ui.prefixEdit_2->setText(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Genetive));
		ui.declSelect_2->setCurrentIndex((int)Declension::Genetive);
		ui.prefixEdit_3->setText(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Dative));
		ui.declSelect_3->setCurrentIndex((int)Declension::Dative);
		ui.prefixEdit_4->setText(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Accusative));
		ui.declSelect_4->setCurrentIndex((int)Declension::Accusative);
		ui.prefixEdit_5->setText(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Instrumental));
		ui.declSelect_5->setCurrentIndex((int)Declension::Instrumental);
		ui.prefixEdit_6->setText(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Prepositional));
		ui.declSelect_6->setCurrentIndex((int)Declension::Prepositional);

		m_dictNode = new DictionaryNode();
	}
	//получаем базовое слово
	//QString base = 
	//Messages::error("fail");
}

void DictEditorWindow::updateWordsList() {
	//очистим список слов
	m_wordsList.clear();
	//далее опять заполним его 
	for (int i = 0; i < m_dict.size(); i++) {
		auto bases = m_dict.getBases();
		DictionaryNode node;
		m_dict.getNode(bases[i], node);
		m_wordsList.push_back({ bases[i], node });
	}
	//очищаем визуал
	ui.wordsList->clear();
	//заполняем снова
	for (int i = 0; i < m_wordsList.size(); i++) {
		//в списке слова в именительном падеже
		ui.wordsList->addItem(m_wordsList[i].first + m_wordsList[i].second.getPrefix(Declension::Nominative));
	}
}