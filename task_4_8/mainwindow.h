#pragma once

#include "qt.h"
#include "dictionary.h"

//Главное окно приложения

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
	//ui
	QWidget *m_centralWidget;
	QVBoxLayout *m_verticalLayout;
	QMdiArea *m_mdiArea;
	QMenuBar *m_menuBar;
	QMenu *m_fileMenu;
	QMenu *m_dictionaryMenu;
	QAction *m_dictOpenAction;
	QAction *m_dictSaveAction;
	QAction *m_editDictAction;
	QAction *m_newDictAction;
	QAction *m_openFileAction;

	//создание ui
	void setupUi();
	//установка текста на элементах
	void setupText();
	//подключение логики
	void setupSlots();

	//логика(слоты)

	//создать новый соварь
	void createDictionary();
	//открыть словарь
	void openDictionary();
	//сохранить словарь
	void saveDictionary();
	//открыть файл со словами
	void openFile();
	//открыть редактор словаря
	void openDictEditor();

	//состояние главного меню

	//открыт редактор словаря
	bool m_editorOpen;

	//словарь
	Dictionary m_dict;
};
