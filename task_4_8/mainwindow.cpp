#include "mainwindow.h"
#include "dictionary_provider.h"
#include "messages.h"
#include "dict_editor_window.h"
#include "filewindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
	setupUi();
	m_editorOpen = false;
    //ui.setupUi(this);
}

//
void MainWindow::setupUi() {
	m_centralWidget = new QWidget(this);
	m_verticalLayout = new QVBoxLayout(m_centralWidget);
	m_verticalLayout->setSpacing(6);
	m_verticalLayout->setContentsMargins(11, 11, 11, 11);
	m_mdiArea = new QMdiArea(m_centralWidget);
	m_verticalLayout->addWidget(m_mdiArea);
	this->setCentralWidget(m_centralWidget);
	//menu bar setting
	m_menuBar = new QMenuBar(this);
	m_fileMenu = new QMenu(m_menuBar);
	m_dictionaryMenu = new QMenu(m_menuBar);
	m_editDictAction = new QAction(this);
	m_dictOpenAction = new QAction(this);
	m_dictSaveAction = new QAction(this);
	m_newDictAction = new QAction(this);
	m_openFileAction = new QAction(this);
	this->setMenuBar(m_menuBar);
	m_menuBar->addAction(m_fileMenu->menuAction());
	m_fileMenu->addAction(m_dictOpenAction);
	m_fileMenu->addAction(m_newDictAction);
	m_fileMenu->addAction(m_dictSaveAction);
	m_fileMenu->addAction(m_openFileAction);
	m_dictionaryMenu->addAction(m_editDictAction);

	//set ui text
	this->setupText();
	//connect slots
	this->setupSlots();
	//just resize window
	this->resize(500, 500);
}

void MainWindow::setupText() {
	this->setWindowTitle("Dictionary");
	m_fileMenu->setTitle("File");
	m_newDictAction->setText("New dictionary");
	m_dictOpenAction->setText("Open dictionary file");
	m_dictionaryMenu->setTitle("Dictionary");
	m_editDictAction->setText("Edit dictionary");
	m_dictSaveAction->setText("Save dictionary");
	m_openFileAction->setText("Open file");
}


void MainWindow::openDictionary() {
	//выбираем файл со словарем
	QString dictFileName = QFileDialog::getOpenFileName(this, "Select dictionary file");
	if (!dictFileName.isEmpty()) {
		//read file
		try {
			//читаем словарь
			m_dict = DictionaryProvider::loadFromFile(QFileInfo(dictFileName));
			//добавляем пункт в меню
			m_menuBar->addAction(m_dictionaryMenu->menuAction());
		}
		catch (std::exception& ex) {
			Messages::error(ex.what());
		}

	}
	else {
		Messages::error("Dictionary file was not selected");
	};
}

void MainWindow::saveDictionary() {
	//выбираем файл, куда сохраняем
	QString dictFileName = QFileDialog::getSaveFileName(this, "Select dictionary file");
	Dictionary newDict;
	if (!dictFileName.isEmpty()) {
		//пытаемся записать
		try {
			//пишем словарь
			DictionaryProvider::saveToFile(QFileInfo(dictFileName), m_dict);
		}
		catch (std::exception& ex) {
			Messages::error(ex.what());
		}

	}
	else {
		Messages::error("Dictionary file was not selected");
	};
}

void MainWindow::createDictionary() {
	m_dict = Dictionary();
	//добавляем пункт в меню
	m_menuBar->addAction(m_dictionaryMenu->menuAction());
}

void MainWindow::openFile() {
	auto w = new FileWindow(QFileInfo(""));
	m_mdiArea->addSubWindow(w);
	w->show();
}

void MainWindow::openDictEditor() {
	DictEditorWindow w(m_dict);
	w.exec();
}

void MainWindow::setupSlots() {
	connect(m_openFileAction, &QAction::triggered, this, &MainWindow::openFile);
	connect(m_dictSaveAction, &QAction::triggered, this, &MainWindow::saveDictionary);
	connect(m_editDictAction, &QAction::triggered, this, &MainWindow::openDictEditor);
	connect(m_dictOpenAction, &QAction::triggered, this, &MainWindow::openDictionary);
	connect(m_newDictAction, &QAction::triggered, this, &MainWindow::createDictionary);
}