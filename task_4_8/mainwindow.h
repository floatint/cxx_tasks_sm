#pragma once

#include "qt.h"
#include "dictionary.h"

//������� ���� ����������

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

	//�������� ui
	void setupUi();
	//��������� ������ �� ���������
	void setupText();
	//����������� ������
	void setupSlots();

	//������(�����)

	//������� ����� ������
	void createDictionary();
	//������� �������
	void openDictionary();
	//��������� �������
	void saveDictionary();
	//������� ���� �� �������
	void openFile();
	//������� �������� �������
	void openDictEditor();

	//��������� �������� ����

	//������ �������� �������
	bool m_editorOpen;

	//�������
	Dictionary m_dict;
};
